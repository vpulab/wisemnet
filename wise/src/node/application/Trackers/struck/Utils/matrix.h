// Generic basic matrix class
#ifndef MATRIX_H
#define MATRIX_H

template<typename T>
class Matrix
{
	private:

	// Data pointer
	T* data;
	// Size
	int _rows, _cols;

	public:

	// Constructors
	
	Matrix() : data(NULL), _rows(0), _cols(0) {}

	Matrix(int rows, int cols);
	
	Matrix(const T* data_, int rows_, int cols_);

	// Copy-constructor
	// ...
	
	// Destructor
	
	virtual ~Matrix();

	// Assignment
	// ...
	
	// Set size
	void setSize(int rows, int cols);

	// Get size
	inline int rows() const { return _rows; }
	inline int cols() const { return _cols; }
	
	// Get data
	inline const T* getData() const { return data; }
	inline T* getData() { return data; }

	// Get object
	inline const T& operator()(int i, int j) const { return data[i*_cols + j]; }
	inline T& operator()(int i, int j) { return data[i*_cols + j]; }
};

template<typename T>
Matrix<T>::Matrix(int rows, int cols) :
	_rows(rows), _cols(cols)
{
	data = new T[_rows*_cols];
}

template<typename T>
Matrix<T>::Matrix(const T* data_, int rows, int cols) :
	data(data_), _rows(rows), _cols(cols)
{
}

template<typename T>
Matrix<T>::~Matrix()
{
	// Check NULL
	if(data != NULL)
	{
		// Free
		delete [] data;
	}
}

template<typename T>
void Matrix<T>::setSize(int rows, int cols)
{
	// Check NULL
	if(data != NULL)
	{
		// Free
		delete [] data;
	}
	// Update size
	_rows = rows;
	_cols = cols;
	// Allocate
	data = new T[_rows*_cols];
}

#endif
