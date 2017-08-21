// Class for the computation of histograms and moments for single-channel or multi-channel images

#include "histogram.h"
#include "my_exception.h"
#include "shell_utils.h"
// Debug includes
#include <iostream>
using namespace std;

// Default constructor, initializes histogram matrix to zeros
Histogram::Histogram() : mean_computed(false)
{
	// Initialize histogram to 0
	for(int i=0; i<256; i++)
	{
		histogram[i] = 0.0f;
	}
}
	
// Constructor; given the input image, computes the histogram.
// - image: input image
Histogram::Histogram(const Mat& image) : mean_computed(false)
{
	computeHistogram(image, Mat::ones(image.rows, image.cols, CV_8UC1));
}

// Constructor; given the input image, computes the histogram.
// - image: input image
// - mask: binary mask
Histogram::Histogram(const Mat& image, const Mat& mask) : mean_computed(false)
{
	computeHistogram(image, mask);
}
	
// Copy constructor
Histogram::Histogram(const Histogram& copy)
{
	for(int i=0; i<256; i++)
	{
		histogram[i] = copy.histogram[i];
	}
	mean_computed = copy.mean_computed;
	saved_mean = copy.saved_mean;
}
	
// Constructor
// - values: input values
Histogram::Histogram(const vector<uchar>& values)
{
	// Initialize histogram to 0
	for(int i=0; i<256; i++)
	{
		histogram[i] = 0.0;
	}
	// Count all occurrencies
	for(vector<uchar>::const_iterator v_it = values.begin(); v_it != values.end(); ++v_it)
	{
		int value = (int) *v_it;
		histogram[value] += 1;
		//cout << "Read: " << value << ", " << ", hist[" << value << "]: " << histogram.at<double>(value,0) << endl;//", hist: " << histogram << endl;
	}
	// Normalize histogram
	float norm_factor = values.size();
	for(int k=0; k<256; k++)
	{
		histogram[k] /= norm_factor;
	}
}

// Actual histogram computation
void Histogram::computeHistogram(const Mat& image, const Mat& mask)
{
	// Initialize histogram to 0
	for(int i=0; i<256; i++)
	{
		histogram[i] = 0.0;
	}
	//histogram.at<double>(256,1) = 10000000.0;
	int valid_pixels = 0;
	// Count all occurrencies
	for(int i=0; i<image.rows; i++)
	{
		for(int j=0; j<image.cols; j++)
		{
			if(mask.at<uchar>(i,j) > 0)
			{
				int value = (int) image.at<uchar>(i,j);
				histogram[value] += 1;
				//cout << "Read: " << value << ", " << ", hist[" << value << "]: " << histogram.at<double>(value,0) << endl;//", hist: " << histogram << endl;
				valid_pixels++;
			}
		}
	}
	// Normalize histogram
	float norm_factor = valid_pixels;
	for(int k=0; k<256; k++)
	{
		histogram[k] /= norm_factor;
	}
	//cout << histogram << endl;
}

// Compute the mean value of the histogram
float Histogram::mean()
{
	// Check if we have already computed the mean
	if(mean_computed)
	{
		// Return the saved value
		//cout << "(returning saved mean: " << saved_mean << ")" << endl;
		return saved_mean;
	}
	// Otherwise, compute it
	//cout << "(computing mean)" << endl;
	float m = 0.0f;
	for(int k=0; k<256; k++)
	{
		m += k*histogram[k];
		//cout << "mean element " << k << ": " << k*histogram.at<double>(k,0) << endl;
	}
	// Save the result
	mean_computed = true;
	saved_mean = m;
	// Return the mean
	return m;
}
	
// Compute the specified centered moment
// - order: moment order
float Histogram::moment(int order)
{
	// Compute mean
	float m = mean();
	// Initialize result
	float result = 0.0f;
	// Go through all values
	for(int k=0; k<256; k++)
	{
		// Initialize term for current gray level to the histogram value
		float term = histogram[k];
		// Multiply as many times as necessary
		for(int i=0; i<order; i++)
		{
			term *= (k - m);
		}
		// Add to result
		result += term;
	}
	// Return result
	return result;
}

// Compute all centered moments from the 2nd up to the specified order (included)
// - max_order: maximum moment order
// - dst: destination for the results; must have enough space for max_order-1 values
void Histogram::moments(int max_order, float* dst)
{
	// Count number of values to write
	int count = max_order - 1;
	// Initialize all values to zero
	for(int i=0; i<count; i++)
	{
		dst[i] = 0.0f;
	}
	// Compute mean
	float m = mean();
	// Go through all values
	for(int k=0; k<256; k++)
	{
		// Compute term for second-order moment
		float term = (k - m)*(k - m)*histogram[k];
		// Add term to corresponding destination and compute the one for the following moment
		for(int i=0; i<count; i++)
		{
			dst[i] += term;
			term *= (k - m);
		}
	}
}
	
// Compute uniformity of histogram
float Histogram::uniformity()
{
	// Initialize result
	float result = 0.0f;
	// Compute uniformity, as the sum of squared bins
	for(int k=0; k<256; k++)
	{
		// Read bin
		float value = histogram[k];
		// Compute term of sum
		result += value*value;
	}
	// Return result
	return result;
}
	
// Equalize the image histogram
void Histogram::equalizeImage(Mat& image, int* extern_mapping)
{
	// Compute histogram
	Histogram hist(image);
	// Equalize
	bool internal_mapping = false;
	int *mapping;
	if(extern_mapping != NULL)
	{
		mapping = extern_mapping;
	}
	else
	{
		mapping = new int[256];
		internal_mapping = true;
	}
	hist.equalize(mapping);
	// Apply to image
	for(int i=0; i<image.rows; i++)
	{
		for(int j=0; j<image.cols; j++)
		{
			uchar& pixel = 	image.at<uchar>(i,j);
		      	pixel = mapping[pixel];
		}
	}
	// Free
	if(internal_mapping)
	{
		delete [] mapping;
	}
}
	
// Equalize the histogram
void Histogram::equalize(int* mapping)
{
	// Compute CDF
	float cdf[256];
	float sum = 0.0f;
	// Go through all bins
	for(int k=0; k<256; k++)
	{
		// Read bin
		float value = histogram[k];
		// Add to sum
		sum += value;
		// Add to CDF
		cdf[k] = sum;
		// If required, save to mapping vector
		if(mapping != NULL)
		{
			mapping[k] = (int) (sum*255.0);
		}
		//cout << sum*255 << ", ";
	}
	//cout << endl;
	// Initialize new histogram values
	float new_pdf[256];
	for(int i=0; i<256; i++)
	{
		new_pdf[i] = 0.0f;
	}
	// Go through current histogram and add probability contributions to new values
	for(int i=0; i<256; i++)
	{
		//cout << "cdf[" << i << "]*255 = " << (int)(cdf[i]*255) << endl;
		new_pdf[(int)(cdf[i]*255.0)] += histogram[i];
	}
	// Update current histogram
	for(int i=0; i<256; i++)
	{
		histogram[i] = new_pdf[i];
	}
}
	
// Normalize the histogram so that the sum of all bins is 1
void Histogram::normalize()
{
	// Initialize bin sum
	float sum = 0.0f;
	// Compute sum
	for(int k=0; k<256; k++)
	{
		// Read and add bin
		sum += histogram[k];
	}
	if(sum == 0.0f)
	{
		throw MyException("Can't normalize histogram, the sum of all bins is 0.");
	}
	// Normalize each element
	for(int k=0; k<256; k++)
	{
		// Normalize bin
		histogram[k] /= sum;
	}
}

// Filter bins at the extremities according to the given threshold
// Save the trim limit bins to the given pointers, if provided
void Histogram::trim(float threshold, int* min_bin, int* max_bin)
{
	// Find the minimum bin higher than the threshold
	for(int i=0; i<256; i++)
	{
		// Get reference to value
		float& bin = histogram[i];
		// Check threshold
		if(bin > threshold)
		{
			// Set min_min
			if(min_bin != NULL)
			{
				*min_bin = i;
			}
			break;
		}
		else
		{
			// Clip to zero
			bin = 0.0f;
		}
	}
	// Same thing, from the end of the histogram
	for(int i=255; i>=0; i--)
	{
		// Get reference to value
		float& bin = histogram[i];
		// Check threshold
		if(bin > threshold)
		{
			// Set max_min
			if(max_bin != NULL)
			{
				*max_bin = i;
			}
			break;
		}
		else
		{
			// Clip to zero
			bin = 0.0f;
		}
	}
	// Normalize histogram
	normalize();
}
	
// Compute Chi-squared distance
float Histogram::ChiSquaredDistance(const Histogram& h1, const Histogram& h2)
{
	float sum = 0.0f;
	for(int k=0; k<256; ++k)
	{
		if(h1[k] != h2[k])
		{
			sum += (h1[k] - h2[k])*(h1[k] - h2[k])/(h1[k] + h2[k]);
		}
	}
	return sum/2;
}
	
// Get max probability
float Histogram::maxProb(int* bin)
{
	// Initialize max probability
	float max_prob = 0.0f;
	// Initialize corresponding bin
	int max_bin = -1;
	// Go through each bin
	for(int k=0; k<256; k++)
	{
		// Check value
		if(histogram[k] > max_prob)
		{
			// Set maximum values
			max_prob = histogram[k];
			max_bin = k;
		}
	}
	// Check if we need to write *bin
	if(bin != NULL)
	{
		*bin = max_bin;
	}
	// Return result
	return max_prob;
}

// Output operator
ostream& operator<< (ostream& out, const Histogram& hist)
{
	out << "[" << hist.histogram[0];
	for(int i=1; i<256; i++)
	{
		out << ", " << hist.histogram[i];
	}
	out << "]";
	return out;
}
