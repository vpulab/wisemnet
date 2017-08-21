// Class for the computation of histograms and moments for single-channel images

#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <cv.h>

using namespace std;
using namespace cv;

/** Histogram class for images, i.e. having bins at 0-255.
 * Suitable for representing grayscale and color-channel histograms. Provides method for normalization, equalization, statistical moment extraction and comparison
 */
class Histogram
{
	/** Friend operator, for output.
	 */
	friend ostream& operator<< (ostream& out, const Histogram& hist);
	
	private:
	
	// Actual histogram storage
	float histogram[256];

	// Flag which says if we have already computed the mean; if yes, next call to mean() will return the saved value
	bool mean_computed;

	// Previously computed mean
	float saved_mean;

	// Actual histogram computation
	void computeHistogram(const Mat& image, const Mat& mask);

	public:

	/** Initialize histogram matrix to zeros.
	 */
	Histogram();
	
	/** Given the input image, computes the histogram.
	 *
	 * \param image Input image
	 */
	Histogram(const Mat& image);
	
	/** Compute from unsigned 8-bit array.
	 *
	 * \param values List of pixel values
	 */
	Histogram(const vector<uchar>& values);
	
	/** Given the input image, computes the histogram using only the pixels specified in the mask.
	 *
	 * \param image Input image
	 * \param mask Binary mask for pixel selection
	 */
	Histogram(const Mat& image, const Mat& mask);

	/** Copy constructor.
	 */
	Histogram(const Histogram& copy);

	// Return the histogram matrix
	//inline const Mat& getHistogram() const { return histogram; }
	//inline Mat& getHistogram() { return histogram; }

	/** \name Retrieve a histogram value.
	 * \param bin Bin whose frequency we want to retrieve.
	 * \return The frequency for the input bin.
	 */
	/**@{*/
	inline float get(int bin) const { return histogram[bin]; }
	inline const float& operator[] (const int bin) const { return histogram[bin]; }
	inline float& operator[] (const int bin) { return histogram[bin]; }
	/**@}*/

	/** Compute the mean value of the histogram.
	 * \return The mean value of the histogram.
	 */
	float mean();

	/** Compute the specified centered moment.
	 * \param order Moment order
	 * \return The histogram's moment at the specified order.
	 */
	float moment(int order);
	
	/** Compute all centered moments from the 2nd up to the specified order (included).
	 * \param max_order Maximum moment order to compute.
	 * \param dst Destination array for the results; must have enough space for max_order-1 values.
	 */
	void moments(int max_order, float* dst);

	/** Compute uniformity of histogram.
	 * \return The uniformity value for the histogram.
	 */
	float uniformity();

	/** Normalize the histogram so that the sum of all bins is 1.
	 */
	void normalize();

	/** Equalize the histogram, and store the gray-level mapping in the provided vector (if not null).
	 * \param mapping Output array, where \c mapping[i] is the new intensity value associated to value i.
	 */
	void equalize(int* mapping = NULL);
	
	/** Equalize the image histogram.
	 * \param image Image to equalize
	 * \param mapping Output array, where \c mapping[i] is the new intensity value associated to value i.
	 */
	static void equalizeImage(Mat& image, int* mapping = NULL);

	/** Filter bins at the extremities according to the given threshold, and save the trim limit bins to the given pointers, if provided.
	 * \param threshold Minimum probability for bins in order not to be trimmed.
	 * \param min_bin Left trimming limit
	 * \param max_bin Right trimming limit
	 */
	void trim(float threshold, int* min_bin = NULL, int* max_bin = NULL);

	/** Compute Chi-squared distance.
	 * \param h1 Input histogram
	 * \param h2 Input histogram
	 * \return The Chi-square distance between the input histograms.
	 */
	static float ChiSquaredDistance(const Histogram& h1, const Histogram& h2);

	/** Get max probability.
	 * \input bin If not NULL, it is set to the bin corresponding to the maximum value.
	 * \return The maximum probability value in the histogram.
	 */
	float maxProb(int* bin = NULL);
	
};

// Output operator
ostream& operator<< (ostream& out, const Histogram& hist);

#endif
