#ifndef ASSEMBLY_SIM_UTILITIES_H
#define ASSEMBLY_SIM_UTILITIES_H

#include <iostream>

namespace Assembly_line_Simulation {
	class Utilities {
		size_t m_widthField{ 1 };	// Specifies the length of the token extracted; used for display purposes
		static char m_delimiter;	// Separates the tokens in any given std::string object.
	public:
		// Sets the field width of the current object to the value of parameter newWidth
		void setFieldWidth(size_t newWidth);

		// Returns the field width of the current object
		size_t getFieldWidth() const;

		// Extracts a token from string str referred to by the first parameter.
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

		// Sets the delimiter for this class to the character received
		static void setDelimiter(char newDelimiter);

		// Returns the delimiter for this class.
		static char getDelimiter();
	};
}
#endif //!ASSEMBLY_SIM_UTILITIES_H