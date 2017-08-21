// Class which contains methods for math stuff
// Naming conventions:
// - d: number of features

#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <vector>
#include <list>
#include <cv.h>
#include <my_exception.h>
#include <Eigen/Eigenvalues>
//#include <Eigen/Array>
//#include <Eigen/Dense>

/** Mathematical utilities (not included in OpenCV)
 */
class MathUtils
{
	private: 
	
	// Defines how many elements of the series we want to compute
	static const int series_elements = 100; // 30 is for debug, 100 is ok

	// Twiddle algorithm (compute combinations)
	static bool twiddle(int *x, int *y, int *z, int *p);

	// Initialize auxiliary variables for twiddle algorithm (compute combinations)
	static void initTwiddle(int n, int k, int** p);

	public:

	/** Get min value from array of data.
	 * \param data Input vector
	 * \returns Minimum value from input vector
	 */
	template <typename T>
	static T min(const std::vector<T>& data);
	/** Get max value from array of data.
	 * \param data Input vector
	 * \returns Maximum value from input vector
	 */
	template <typename T>
	static T max(const std::vector<T>& data);

	/** Compute combinations.
	 * \param data Input vector
	 */
	static std::vector<std::list<int> > computeCombinations(int n, int k);
	
	/** Compute mean and standard deviation.
	 * \param data Input vector
	 * \param mean Output mean
	 * \param stddev Output standard deviation
	 */
	template <typename T>
	static void computeMeanAndStdDev(const std::vector<T>& data, float& mean, float& stddev);

	/** Returns the covariance matrix for the given feature set.
	 * The input image type is supposed to be CV_64F.
	 *
	 * \param features Each row in the matrix represents a separate feature.
	 * \returns Covariance matrix from the input data.
	 */
	static cv::Mat computeCovarianceMatrix(const cv::Mat& features);

	/** Returns the scalar distance between two covariance matrices.
	 * This uses Forstner's distance based on generalized eigenvalues.
	 * The input image type is supposed to be CV_64F.
	 * \param c1 Input covariance matrix
	 * \param c2 Input covariance matrix
	 * \returns Distance between the input matrices
	 */
	static double covarianceDistance(const cv::Mat& c1, const cv::Mat& c2);
	
	/** Computes the euclidean distance between two n-dimensional points.
	 * \param p1 Input point
	 * \param p2 Input point
	 * \returns Distance between input points
	 */
	static double euclideanDistance(const std::vector<double>& p1, const std::vector<double>& p2);

	/** Computes the intrinsic mean of a set of covariance matrices using Lie algebra.
	 * The input image type is supposed to be CV_64F.
	 * \param past_c Array of past covariance matrices to be averaged.
	 * \param size_past Number of past covariance matrices.
	 * \param current_c Covariance matrix representing the current model.
	 * \param weighted If true, weigh the input covariance matrix based on the similarity to the current mode.
	 * \returns Matrix representing the model obtained by averaging the input covariances matrix.
	 */
	static cv::Mat covarianceLieMean(const cv::Mat* past_c, int size_past, const cv::Mat& current_c, bool weighted = false);
	/** Computes the intrinsic mean of a set of covariance matrices using Lie algebra.
	 * The input image type is supposed to be CV_64F.
	 * \param past_c Vector of past covariance matrices to be averaged.
	 * \param current_c Covariance matrix representing the current model.
	 * \param weighted If true, weigh the input covariance matrix based on the similarity to the current mode.
	 * \returns Matrix representing the model obtained by averaging the input covariances matrix.
	 */
	static cv::Mat covarianceLieMean(const std::vector<const cv::Mat*>& past_c, const cv::Mat& current_c, bool weighted = false);
	//static cv::Mat covarianceLieMeanTest(const std::vector<const cv::Mat*>&, const cv::Mat&, bool = false);
	
	// Returns the intrinsic mean of a set of covariance matrices using the definition.
	// The input image type is supposed to be CV_64F.
	//static cv::Mat covarianceMean(const cv::Mat*, int);
	//static cv::Mat covarianceMean(const std::vector<const cv::Mat*>&, int);
	
	/** Computes the exponential map of a matrix.
	 * \param input Input matrix
	 * \returns Exponential function of the input matrix
	 */
	static cv::Mat exponentialMap(const cv::Mat& input);

	/** Computes the logarithmic map of a matrix.
	 * \param input Input matrix
	 * \returns Logarithmic map of the input matrix
	 */
	static cv::Mat logarithmicMap(const cv::Mat& input);

	/** Computes Cholesky LL' decomposition of a symmetric matrix.
	 * \param input Input matrix, must be symmetric.
	 * \returns Cholesky LL's decomposition
	 */
	static cv::Mat Cholesky(const cv::Mat& input);

	/** Computes the eigenvalues of an asymmetrix matrix.
	 * \param input Input matrix
	 * \returns Matrix containing the eigenvalues of the input matrix.
	 */
	static cv::Mat eigenAsym(const cv::Mat& input);
	
	/** Computes the eigenvalues and eigenvectors of a matrix.
	 * \param input Input matrix.
	 * \param eigenvalues Output eigenvalue matrix
	 * \param Output eigenvector matrix (one eigenvector per row).
	 */
	static void eigenAsym(const cv::Mat& input, cv::Mat& eigenvalues, cv::Mat& eigenvectors);

	/** Computes the generalized eigenvalues of two SYMMETRIC matrices.
	 * The input image type is supposed to be CV_64F.
	 * \param input1 Input matrix
	 * \param input2 Input matrix
	 * \returns Set of generalized eigenvalues
	 */
	static cv::Mat generalizedEigen(const cv::Mat&, const cv::Mat&);

	/** Convert OpenCV CV_64F matrix to Eigen double matrix.
	 * \param mat Input matrix
	 * \returns Input matrix converted to Eigen's format.
	 */
	static Eigen::MatrixXd OpenCVToEigen(const cv::Mat& mat);
};

template <typename T>
T MathUtils::min(const std::vector<T>& data)
{
	if(data.size() == 0)
	{
		throw MyException("Empty data vector.");
	}
	T m = data[0];
	for(typename std::vector<T>::const_iterator it = data.begin()+1; it != data.end(); it++)
	{
		if(*it < m)
			m = *it;
	}
	// Return result
	return m;
}

template <typename T>
T MathUtils::max(const std::vector<T>& data)
{
	if(data.size() == 0)
	{
		throw MyException("Empty data vector.");
	}
	T m = data[0];
	for(typename std::vector<T>::const_iterator it = data.begin()+1; it != data.end(); it++)
	{
		if(*it > m)
			m = *it;
	}
	// Return result
	return m;
}

template <typename T>
void MathUtils::computeMeanAndStdDev(const std::vector<T>& data, float& mean, float& stddev)
{
	// Check data size
	if(data.size() == 0)
	{
		mean = 0;
		stddev = 0;
		return;
	}
	// Initialize mean to 0
	mean = 0;
	// Sum all elements
	for(typename std::vector<T>::const_iterator it = data.begin(); it != data.end(); it++)
	//for(vti it = data.begin(); it != data.end(); it++)
	{
		mean += *it;
	}
	// Divide mean by number of elements
	mean /= data.size();
	// Initialize stddev
	stddev = 0;
	// Sum all squared differences
	for(typename std::vector<T>::const_iterator it = data.begin(); it != data.end(); it++)
	//for(vti it = data.begin(); it != data.end(); it++)
	{
		stddev += (mean - *it)*(mean - *it);
	}
	// Check data size
	if(data.size() == 1)
	{
		stddev = 0;
	}
	else
	{
		// Divide by number of elements (thus computing variance)
		stddev /= (data.size()-1);
		// Compute square root
		stddev = sqrt(stddev);
	}
}

#endif
