#include "string_utils.h"
#include <sstream>
#include <algorithm>
#include <iostream>
#include <cstdarg>
#include <cstdio>

using namespace std;

// Format string
std::string stringFormat(const std::string &fmt, ...)
{
	int size=100;
	std::string str;
	va_list ap;
	while (1)
	{
		str.resize(size);
		va_start(ap, fmt);
		int n = vsnprintf((char *)str.c_str(), size, fmt.c_str(), ap);
		va_end(ap);
		if (n > -1 && n < size)
		{
			str.resize(n);
			return str;
		}
		if (n > -1)
			size=n+1;
		else
			size*=2;
	}
}

// Split "YYYY-MM-DD hh:mm[:ss]" date into vector
vector<string> splitDate(const string& date)
{
	vector<string> split_main = splitString(date, ' ');
	vector<string> split_date = splitString(split_main[0], '-');
	vector<string> split_time = splitString(split_main[1], ':');
	vector<string> result;
	for(vector<string>::iterator it = split_date.begin(); it != split_date.end(); it++)	result.push_back(*it);
	for(vector<string>::iterator it = split_time.begin(); it != split_time.end(); it++)	result.push_back(*it);
	return result;
}

// Split string
vector<string> splitString(const string& str, char delim)
{
	vector<string> elems;
	stringstream ss(str);
	string item;
	while(getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}

// Convert to lowercase
string toLower(const string& input)
{
	// Convert string
	string out = input;
	transform(out.begin(), out.end(), out.begin(), ::tolower);
	// Return result
	return out;
}

// Convert values to specified type - specialize for strings
template<>
string convertFromString(string input)
{
	return input;
}

// Convert values to specified type
// vector<float> specialization
template<>
vector<float> convertFromString(string input)
{
	// Split string by "_"
	vector<string> toks = splitString(input, '_');
	// Initialize output
	vector<float> output;
	// Convert each value
	for(vector<string>::iterator it = toks.begin(); it != toks.end(); it++)
	{
		output.push_back(convertFromString<float>(*it));
	}
	// Return result
	return output;
}

// Convert values from specified type
// vector<float> specialization
template<>
string convertToString(const vector<float>& input)
{
	// Check size
	if(input.size() == 0)
	{
		return "";
	}
	// Initialize string stream
	stringstream ss;
	ss << input[0];
	// Add following elements
	if(input.size() > 1)
	{
		for(vector<float>::const_iterator it = input.begin()+1; it != input.end(); it++)
		{
			ss << "_" << *it;
		}
	}
	// Return result
	return ss.str();
}
