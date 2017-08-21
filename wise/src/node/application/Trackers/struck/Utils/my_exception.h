// Simple class which takes text to provide to what()
#ifndef MY_EXCEPTION_H
#define MY_EXCEPTION_H

#include <exception>
#include <string>

/** Wrapper around \c std::exception for easily setting the error message.
 */
class MyException : public std::exception
{
	private:

	std::string message;

	public:

	/** Constructor with error message.
	 * \param m Error message.
	 */
	inline MyException(std::string m) : message(m) {}

	/** Destructor.
	 */
	virtual ~MyException() throw() {}

	/** Override \c what() by returning the given error message.
	 * \returns Error message passed to constructor.
	 */
	virtual const char* what() { return message.c_str(); }
};

#endif
