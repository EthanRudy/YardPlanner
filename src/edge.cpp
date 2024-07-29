// @file edge.cpp
// @author Ethan Rudy
// @desc Class initialization for the Edge class

#include "../include/edge.h"


// Default Constructor
Edge::Edge() {
	m_a = { -1, -1 };
	m_b = { -1, -1 };

	m_type = RESERVED;
}


// sf::Vector Constructor
Edge::Edge(const sf::Vector2f& a, const sf::Vector2f& b) {
	m_a = a;
	m_b = b;

	m_type = RESERVED;
}


// Float Constructor
Edge::Edge(float a_x, float a_y, float b_x, float b_y) {
	m_a = { a_x, a_y };
	m_b = { b_x, b_y };

	m_type = RESERVED;
}


// Data Constructor
Edge::Edge(const std::string& data) {
	Tokenizer edge_token(data);

	float a_x = stof(edge_token.getNextToken());
	float a_y = stof(edge_token.getNextToken());
	float b_x = stof(edge_token.getNextToken());
	float b_y = stof(edge_token.getNextToken());
	m_a = { a_x, a_y };
	m_b = { b_x, b_y };

	m_type = stringToEType(edge_token.getNextToken());
}


// Get A
const sf::Vector2f& Edge::getA() {
	return m_a;
}


// Get B
const sf::Vector2f& Edge::getB() {
	return m_b;
}


// String to PLANT TYPE
EDGE_TYPE Edge::stringToEType(const std::string& str) {
	if (str == "PL") {
		return PROPERTY_LINE;
	}
	else if (str == "WA") {
		return WALL;
	}
	else if (str == "FE") {
		return FENCE;
	}
	else {
		return RESERVED;
	}
}