// @file tokenizer.h
// @author Ethan Rudy
// @desc Class definition for a tokenizer/parser class

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>

class Tokenizer {
public:

	/* Default Constructor */
	Tokenizer();

	/* String Constructor */
	Tokenizer(const std::string& str);

	/**
	* Set String
	* 
	* @param str New value of m_str
	*/
	void setString(const std::string& str);

	/**
	* Get Next Token
	* 
	* @return token m_str's next Token
	* 
	* EX: m_str = "num1, num2, num3"
	* token == "num1"
	* m_str == "num2, num3"
	*/
	std::string getNextToken();
protected:
private:

	std::string m_str;
};

#endif // !TOKENIZER_H