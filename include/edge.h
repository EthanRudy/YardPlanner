// @file edge.h
// @author Ethan Rudy
// @desc Class declaration for the Edge class

#ifndef EDGE_H
#define EDGE_H

#include <SFML/Graphics.hpp>
#include "tokenizer.h"

enum EDGE_TYPE {
	PROPERTY_LINE,		// PL
	WALL,				// WA
	FENCE,				// FE
	RESERVED,			// RE
};

class Edge {
public:

	/* Default Constructor */
	Edge();

	/* sf::Vector Constructor */
	Edge(const sf::Vector2f& a, const sf::Vector2f& b);

	/* Float Constructor */
	Edge(float a_x, float a_y, float b_x, float b_y);

	/* Data Constructor */
	Edge(const std::string& data);

	/**
	* Get A
	* 
	* @return m_a Starting Point
	*/
	const sf::Vector2f& getA();

	/**
	* Get B
	* 
	* @return m_b Ending Point
	*/
	const sf::Vector2f& getB();

	// TEMP
	EDGE_TYPE getType() { return m_type; }

protected:
private:

	sf::Vector2f m_a;
	sf::Vector2f m_b;

	EDGE_TYPE m_type;


	/**
	* String to Edge TYPE
	*
	* @param str Edge type string representation
	*/
	EDGE_TYPE stringToEType(const std::string& str);
};

#endif // !EDGE_H