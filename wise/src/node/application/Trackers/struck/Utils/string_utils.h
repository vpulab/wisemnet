// Class for some string-related stuff...

#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <sstream>
#include <vector>
#include <my_exception.h>

// Format string
std::string stringFormat(const std::string &fmt, ...);

// Split "YYYY-MM-DD hh:mm[:ss]" date into vector
std::vector<std::string> splitDate(const std::string& date);

// Split a string
std::vector<std::string> splitString(const std::string& input, char delim);

// Convert to lowercase
std::string toLower(const std::string& input);

// Convert values to specified type
template<typename T>
T convertFromString(std::string input)
{
	// Define return value
	T result;
	// Open string stream
	std::stringstream ss(input);
	// Try converting
	//getline(ss, result, '\0');
	ss >> result;
	// Check errors
	if(ss.fail())
	{
		// Throw exception
		std::ostringstream error;
		error << "Error converting string '" << input << "'";
		throw MyException(error.str());
	}
	// Return result
	//cout << "input: " << input << ", result: " << result << endl;
	return result;
}

// Convert values to specified type
// string specialization
template<>
std::string convertFromString(std::string input);

// Convert values to specified type
// vector<float> specialization
template<>
std::vector<float> convertFromString(std::string input);

// Convert values from specified type
template<typename T>
std::string convertToString(const T& input)
{
	// Open string stream
	std::stringstream ss;
	// Read input
	ss << input;
	// Return as string
	return ss.str();
}

// Convert values from specified type
// vector<float> specialization
template<>
std::string convertToString(const std::vector<float>& input);

#endif
