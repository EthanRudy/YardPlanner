// @file tokenizer.cpp
// @author Ethan Rudy
// @desc Class initialization for a tokenizer/parser class

#include "../include/tokenizer.h"


// Default Constructor
Tokenizer::Tokenizer() {
	m_str = "";
}


// String Constructor
Tokenizer::Tokenizer(const std::string& str) {
	m_str = str;
}


// Set String
void Tokenizer::setString(const std::string& str) {
	m_str = str;
}


// Get Next Token
std::string Tokenizer::getNextToken() {
	int cPos = m_str.find(',');

	// No comma found 
	if (cPos == -1) { return m_str; }
	
	// Trim till a non-whitespace character is found
	while (m_str[0] == ' ') { m_str = m_str.substr(1); }
	// Whoops, need to refind it
	cPos = m_str.find(',');
	
	// Find the next token
	std::string token = m_str.substr(0, cPos);

	// Erase it
	m_str = m_str.substr(cPos + 1);

	// Return it
	return token;
}