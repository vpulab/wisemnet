// Class which contains methods for covariance and covariance distance calculation.
// Naming conventions:
// - d: number of features

#include "math_utils.h"
#include "eigen_unsym.h"
#include <shell_utils.h>
#include "my_exception.h"
#include <log.h>
// Debug includes
#include <highgui.h>
#include <iostream>

using namespace std;
using namespace Eigen;
using namespace cv;

// Copied from http://www.netlib.no/netlib/toms/382
bool MathUtils::twiddle(int *x, int *y, int *z, int *p)
{
  register int i, j, k;
  j = 1;
  while(p[j] <= 0)
    j++;
  if(p[j-1] == 0)
    {
    for(i = j-1; i != 1; i--)
      p[i] = -1;
    p[j] = 0;
    *x = *z = 0;
    p[1] = 1;
    *y = j-1;
    }
  else
    {
    if(j > 1)
      p[j-1] = 0;
    do
      j++;
    while(p[j] > 0);
    k = j-1;
    i = j;
    while(p[i] == 0)
      p[i++] = -1;
    if(p[i] == -1)
      {
      p[i] = p[k];
      *z = p[k]-1;
      *x = i-1;
      *y = k-1;
      p[k] = -1;
      }
    else
      {
      if(i == p[0])
	return true;
      else
	{
	p[j] = p[i];
	*z = p[i]-1;
	p[i] = 0;
	*x = j-1;
	*y = i-1;
	}
      }
    }
  return false;
}
	
// Initialize auxiliary variables for twiddle algorithm (compute combinations)
void MathUtils::initTwiddle(int n, int m, int** pp)
{
	int i;
	// Allocate p (will have to be deleted by the user)
	*pp = new int[n+2];
	// Get pointer
	int* p = *pp;
	// Initialize p
	p[0] = n+1;
	for(i = 1; i != n-m+1; i++)
	{
		p[i] = 0;
	}
	while(i != n+1)
	{
		p[i] = i+m-n;
		i++;
	}
	p[n+1] = -2;
	if(m == 0)
	{
		p[1] = 1;
	}
}

vector<list<int> > MathUtils::computeCombinations(int n, int k)
{
	// Check input
	if(n < 1 || k < 1 || k > n)
	{
		throw MyException("MathUtils::computeCombinations(): n and k must be positive, and k <= n.");
	}
	// Define result
	vector<list<int> > result;
	// Check if k == n
	if(k == n)
	{
		// Define obvious result
		list<int> res;
		for(int i=0; i<n; i++)
		{
			res.push_back(i);
		}
		// Add to results
		result.push_back(res);
		// Return
		return result;
	}
	// Initialize p
	int *p;
	initTwiddle(n, k, &p);
	// Initialize a vector (all elements)
	int *a = new int[n];
	for(int i=0; i<n; i++)	a[i] = i;
	// Initialize c vector (current combination)
	int *c = new int[k];
	for(int i=0; i<k; i++)	c[i] = n - (k - i);
	// Define auxiliary variables
	int x, y, z;
	// Run twiddle algorithm
	bool twiddle_result = false;
	do
	{
		//cout << "Combination: ";
		//for(int i=0; i<k; i++) cout << c[i] << "\t";
		//cout << "\n";
		// Save current combination
		list<int> combination;
		for(int i=0; i<k; i++)
		{
			combination.push_back(c[i]);
		}
		combination.sort();
		result.push_back(combination);
		// Compute new combination
		twiddle_result = twiddle(&x, &y, &z, p);
		c[z] = a[x];
	}
	while(!twiddle_result);
	// Free stuff
	delete [] p;
	delete [] a;
	delete [] c;
	// Return result
	return result;
}

// Returns the dxd matrix for the given feature set.
// Each row in the matrix represents a separate feature.
// The input image type is supposed to be CV_64F.
Mat MathUtils::computeCovarianceMatrix(const Mat& feat_mat)
{
	// Read feature number, which is the width of the feature matrix
	int feature_number = feat_mat.cols;
	// Define covariance matrix and mean matrix (which we don't use, but cv::calcCovarMatrix requires it)
	Mat cov_mat(feature_number, feature_number, CV_64F), mean(1, feature_number, CV_64F);
	//cout << cov_mat.channels() << ", " << feat_mat.channels() << ", " << mean.channels() << endl;
	// Compute covariance matrix
	calcCovarMatrix(feat_mat, cov_mat, mean, CV_COVAR_NORMAL+CV_COVAR_ROWS+CV_COVAR_SCALE);
	// Return covariance matrix
	return cov_mat;
}
	
// Returns the euclidian distance between two points.
double MathUtils::euclideanDistance(const vector<double>& point_1, const vector<double>& point_2)
{
	// Initialize result variable
	double result = 0.0;
	// Compute sum of squared differences
	for(unsigned int i=0; i<point_1.size(); i++)
	{
		result += (point_1[i] - point_2[i])*(point_1[i] - point_2[i]);
	}
	// Compute squared root
	result = sqrt(result);
	// Return result
	return result;
}
	
// Returns the scalar distance between two covariance matrices, according to Forstner
// The input image type is supposed to be CV_64F.
double MathUtils::covarianceDistance(const Mat& c1, const Mat& c2)
{
	// Compute the generalized eigenvalues of c1 and c2
	//cout << "DISTANZA A: " << endl << c1 << endl;
	//cout << "DISTANZA B: " << endl << c2 << endl;
	Mat eigenvalues = generalizedEigen(c1, c2);
	//cout << "gen eig: " << eigenvalues << endl;
	//cout << "Calcolo autovalori di: " << endl << (c2.inv()*c1) << endl;
	//cout << "\tAutovalori: " << eigenvalues << endl;
	// Initialize the return value
	double distance = 0;
	// Check if no valid eigenvalue is found
	bool valid_found = false;
	// Compute the sum inside the square root
	for(MatConstIterator_<double> it = eigenvalues.begin<double>(); it != eigenvalues.end<double>(); it++)
	{
		if(*it == 0)
		{
			// Skip null eigenvalue
			continue;
		}
		valid_found = true;
		// Compute the generic term of the sum
		//cout << "eigen: " << *it << endl;
		double term = pow(log(*it), 2);
		//cout << "term: " << term << endl;
		distance += term;
		//cout << "\tTermine della somma: " << term << endl;
	}
	// Check for valid eigenvalues
	if(!valid_found)
	{
		throw MyException("Covariance distance: No non-zero generalized eigenvalue found");
	}
	//cout << "\tSomma: " << distance << endl;
	// Compute the square root of the sum
	distance = sqrt(distance);
	//cout << "Distanza: " << distance << endl;
	// Return the value
	return distance;
}

// Returns the intrinsic mean of a set of covariance matrices using Lie algebra (see Porikli's article "Covariance tracking using model update based on Lie algebra").
// If the current model is provided, then the formula applied weighs each matrix according to how close it is to the current model.
// T is the number of elements.
// The input image type is supposed to be CV_64F.
// Throws an exception if for some reasons it is not able to compute the mean matrix
Mat MathUtils::covarianceLieMean(const Mat *matrices, int T, const Mat& current_model, bool weighted)
{
	// Convert array to vector
	vector<const Mat*> vec;
	for(int i=0; i<T; i++)
	{
		vec.push_back(&(matrices[i]));
	}
	// Call other function
	return covarianceLieMean(vec, current_model, weighted);
}

Mat MathUtils::covarianceLieMean(const vector<const Mat*>& matrices, const Mat& current_model, bool weighted)
{
	Mat* c = NULL;
	// Get number of elements
	int T = matrices.size();
	try
	{
		// Create a vector of the positive-definite matrices
		vector<const Mat*> C;
		// Counter for how many matrices we inserted
		int newT = 0;
		// Check which matrices we want to include
		for(int i=0; i<T; i++)
		{
			// Compute eigenvalues
			Mat eigenvalues = eigenAsym(*(matrices[i]));
			//cout << "Matrix: " << matrices[i] << endl;
			//cout << "Eigenvalues: " << eigenvalues << endl;
			// Flag for positive eigenvalues
			bool positive = true;
			// Check that they're greater than zero
			for(int j=0; j<eigenvalues.cols; j++)
			{
				if(eigenvalues.at<double>(0,j) <= 0.000001)
				{
					// Set flag to false
					positive = false;
					// Quit cycle
					break;
				}
			}
			// Decide whether to include or not the matrix
			if(positive)
			{
				// Add the matrix to the vector
				C.push_back(matrices[i]);
				// Increase newT
				newT++;
			}
			else
			{
				Log::warning() << ShellUtils::RED << "MathUtils:covarianceLieMean(): skipping matrix: " << endl << *(matrices[i]) << endl;
				Log::warning() << "with eigenvalues: " << eigenvalues << ShellUtils::NORMAL << endl;
			}
		}
		// Set T to newT
		if(newT == 0)
		{
			// Give up, and throw exception
			throw MyException("No valid covariance matrices found.");
		}
		T = newT;
		// Initialize the new model matrix
		Mat C_hat = C[0]->clone();
		// Define the delta matrix
		Mat DC_hat;
		// Initialize the {c_t} set
		c = new Mat[T];
		// Compute ro_star, if necessary; otherwise set it to T
		double ro_star = T;
		if(weighted)
		{
			ro_star = 0.0F;
			for(int t=0; t<T; t++)
			{
				// Check that the distance is different than 0
				double distance = MathUtils::covarianceDistance(*(C[t]), current_model);
				if(distance < 0.00001)
					distance = 0.00001;
				ro_star += distance;
			}
		}
		// Define the error quantity
		double error = 0; // It will be set later in the loop
		// Count iterations; we'll stop if we run too many
		int its = 0;
		do
		{
			// Increase and check iterations
			its++;
			if(its > 100)
			{
				// Give up
				Log::w() << "Covariance mean computation, reached maximum number of iterations." << endl;
				break;
			}
			// Compute the {c_t} set
			for(int i=0; i<T; i++)
			{
				// Compute c_i
				//cout << "-------------Calcolo c[i]---------------" << endl;
				//cout << "C_hat.inv() = " << C_hat.inv() << endl;
				//cout << "C[" << i << "] = " << C[i] << endl;
				c[i] = logarithmicMap(C_hat.inv()*(*(C[i])));
				// Check c[i] != 0
				double minVal, maxVal;
				minMaxLoc(c[i], &minVal, &maxVal);
				if(maxVal == 0)
				{
					if(c != NULL)
					{
						delete [] c;
						c = NULL;
					}
					throw MyException("Found c[i] == 0.");
				}
			}
			//waitKey(0);
			// Initialize a variable for the temporary sum involved in the computation of DC_hat (D = delta)
			double distance_0 = (weighted ? MathUtils::covarianceDistance(*(C[0]), current_model) : 1.0);
			if(distance_0 < 0.0001)
				distance_0 = 0.0001;
			Mat sum = c[0]/distance_0;
			// Compute the rest of the sum, according to whether the mean is weighted or not
			for(int i=1; i<T; i++)
			{
				// Define a variable for the covariance distance from the model, if we need it.
				double distance = (weighted ? covarianceDistance(*(C[i]),current_model) : 1.0);
				if(distance < 0.00001)
					distance = 0.00001;
				sum += c[i]/distance;
			}
			// Compute DC_hat
			//cout << "sum = " << sum << endl << endl;
			DC_hat = exponentialMap(sum/ro_star);
			// Compute the new C_hat
			C_hat = C_hat*DC_hat;
			// Compute the error
			error = norm(logarithmicMap(DC_hat));
			//cout << "error: " << error << endl;
		} while(error > 0.1);
		// Free allocated memory
		if(c != NULL)
		{
			delete [] c;
			c = NULL;
		}
		// Return the result
		return C_hat;
	}
	catch(MyException& e)
	{
		// Free allocated memory
		if(c != NULL)
		{
			delete [] c;
			c = NULL;
		}
		stringstream error;
		error << "MathUtils::covarianceLieMean(): error (probably in the eigenvalue algorithm): " << e.what();
		throw MyException(error.str());
	}
	catch(...)
	{
		// Free allocated memory
		if(c != NULL)
		{
			delete [] c;
			c = NULL;
		}
		stringstream error;
		error << "MathUtils::covarianceLieMean(): error (probably in the eigenvalue algorithm)";
		throw MyException(error.str());
	}
}

// Computes the exponential map of a matrix.
Mat MathUtils::exponentialMap(const Mat& a)
{
	// Read the size of the matrix
	int size = a.rows;
	// Check that the matrix is square
	CV_Assert(a.rows == a.cols);
	// Initialize the output matrix to the first term of the series
	Mat exp_a = Mat::eye(size, size, CV_64F);
	// Store the last computed term to fasten the computation of the new one
	Mat last_term = exp_a.clone();
	// Calculate the remaining elements of the series
	for(int i=1; i<series_elements; i++)
	{
		// Compute the i-th term: a^n/n!
		last_term = last_term*a/i;
		// Add it to the partial sum
		exp_a = exp_a + last_term;
	}
	// Return the result
	return exp_a;
}

// Computes the logarithmic map of a DIAGONALIZABLE matrix (check Wikipedia)
Mat MathUtils::logarithmicMap(const Mat& A)
{
	// Read the size of the matrix
	//int size = A.rows;
	// Check that the matrix is square
	CV_Assert(A.rows == A.cols);
	// Compute A's eigenvalues and eigenvectors;
	Mat eigenval, eigenvec;
	eigenAsym(A, eigenval, eigenvec);
	// Compute the A' matrix
	Mat A_ = eigenvec.inv()*A*eigenvec;
	// Substitute the diagonal elements of A' with their logarithm
	Mat d = A_.diag();
	Mat copy_d = d.clone();
	log(d, copy_d);
	copy_d.copyTo(d);
	// Compute the final matrix
	Mat lnA = eigenvec*A_*eigenvec.inv();
	// Return the result
	return lnA;
}
	
// Computes Cholesky LL' decomposition of a symmetric matrix
// The input matrix type is supposed to be CV_64F
Mat MathUtils::Cholesky(const Mat& a)
{
	Mat L = a.clone();
	// Code from "Numeric Recipes"
	int i, j, k, n = a.rows;
	CV_Assert(a.rows == a.cols);
	double sum;
	for(i=0; i<n; i++)
	{
		for(j=i; j<n; j++)
		{
			for(sum=L.at<double>(i,j), k=i-1; k>=0; k--)
			{
				sum -= L.at<double>(i,k)*L.at<double>(j,k);
			}
			if(i == j)
			{
				L.at<double>(i,i) = sqrt(sum);
			}
			else
			{
				L.at<double>(j,i) = sum/L.at<double>(i,i);
			}
		}
	}
	for(i=0; i<n; i++)
	{
		for(j=0; j<i; j++)
		{
			L.at<double>(j,i) = 0;
		}
	}
	// Return result
	return L;
}
	
// Computes the generalized eigenvalues of two SYMMETRIC matrices
Mat MathUtils::generalizedEigen(const Mat& a, const Mat& b)
{
	return eigenAsym(b.inv()*a);
}
	
// Computes the eigenvalues of a matrix
// The input image type is supposed to be CV_64F
Mat MathUtils::eigenAsym(const Mat& a)
{
	// Check matrix is square
	CV_Assert(a.rows == a.cols);
	// Convert matrix to Eigen
	MatrixXd ea = MathUtils::OpenCVToEigen(a);
	// Compute eigenvalues
	EigenSolver<MatrixXd> es(ea);
	// Define output matrix
	Mat result(1, a.rows, CV_64F);
	// Copy eigenvalues
	for(int i=0; i<a.rows; i++)
	{
		result.at<double>(0, i) = real(es.eigenvalues()[i]);
	}
	// Return result
	return result;
}
	
// Computes the eigenvalues and eigenvectors of a matrix
// The input image type is supposed to be CV_64F
void MathUtils::eigenAsym(const Mat& a, Mat& eigenvalues, Mat& eigenvectors)
{
	// Check matrix is square
	CV_Assert(a.rows == a.cols);
	// Convert matrix to Eigen
	MatrixXd ea = MathUtils::OpenCVToEigen(a);
	// Compute eigenvalues
	EigenSolver<MatrixXd> es(ea);
	// Create output matrices
	eigenvalues.create(1, a.rows, CV_64F);
	eigenvectors.create(a.rows, a.rows, CV_64F);
	// Copy eigenvalues
	for(int i=0; i<a.rows; i++)
	{
		eigenvalues.at<double>(0, i) = real(es.eigenvalues()[i]);
	}
	// Copy eigenvectors 
	for(int i=0; i<a.rows; i++)
	{
		for(int j=0; j<a.rows; j++)
		{
			eigenvectors.at<double>(i, j) = real(es.eigenvectors()(i,j));
		}
	}
}
	
// Convert OpenCv CV_64F/CV_32F matrix to Eigen double matrix
MatrixXd MathUtils::OpenCVToEigen(const Mat& mat)
{
	// Check type
	CV_Assert(mat.depth() == CV_64F || mat.depth() == CV_32F);
	// Define output matrix
	MatrixXd eigenmat(mat.rows, mat.cols);
	// Copy data
	for(int i=0; i<mat.rows; i++)
	{
		for(int j=0; j<mat.cols; j++)
		{
			// Read value, according to matrix type
			double value;
			switch(mat.depth())
			{
				case CV_32F:	value = mat.at<float>(i,j); break;
				case CV_64F:	value = mat.at<double>(i,j); break;
			}
			// Write value
			eigenmat(i,j) = value;
		}
	}
	// Return result
	return eigenmat;
}
