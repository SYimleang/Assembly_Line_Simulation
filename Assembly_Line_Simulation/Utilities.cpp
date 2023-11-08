#include <iostream>
#include "Utilities.h"

char Utilities::m_delimiter = '/';

// Sets the field width of the current object to the recieved value
void Utilities::setFieldWidth(size_t newWidth)
{
	m_widthField = newWidth;
}

// Returns the field width of the current object
size_t Utilities::getFieldWidth() const
{
	return m_widthField;
}

// Extracts a token from string "str" 
std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
{
	std::string token;

	// Find the delimeter in "str" until recieved position (next_pos)
	size_t pos = str.find(m_delimiter, next_pos);

	// Checks if the delimiter is found in "str"
	if (pos != std::string::npos) {

		// Extract the token
		token = str.substr(next_pos, pos - next_pos);

		// Remove leading and trailing spaces from the line
		token.erase(0, token.find_first_not_of(" \t"));
		token.erase(token.find_last_not_of(" \t") + 1);

		// Update "next_pos" with the position of the next token
		next_pos = pos + 1;

		// Set "more" to true
		more = true;
	}
	// If delimiter is not found
	else {
		// Extract the token from "next_pos" to the end of "str"
		token = str.substr(next_pos);

		// Remove leading and trailing spaces from the line
		token.erase(0, token.find_first_not_of(" \t"));
		token.erase(token.find_last_not_of(" \t") + 1);

		// Update next_pos to the end of the "string"str"
		next_pos = str.length();

		// Set "more" to false
		more = false;
	}

	// Check if token is empty
	if (token.empty()) {
		more = false;
		throw token;
	}

	// Check if the "m_widthField" is less than the length of the token.
	if (token.length() > m_widthField) {
		// Update "m_widthField" the length of the token
		setFieldWidth(token.length());
	}

	// Return "token"
	return token;
}

// Sets the delimiter for this class to the received character.
void Utilities::setDelimiter(char newDelimiter)
{
	m_delimiter = newDelimiter;
}

// Returns the delimiter for this class.
char Utilities::getDelimiter()
{
	return m_delimiter;
}


