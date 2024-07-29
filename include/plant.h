// @file plant.h
// @author Ethan Rudy
// @desc Class and enumeration declaration for the Plant class

#ifndef PLANT_H
#define PLANT_H

#include <SFML/Graphics.hpp>
#include "tokenizer.h"

/*
/* Plant Type 
enum PLANT_TYPE {
	MOSS,			// MO
	GOUND_COVER,	// GC
	BUSH,			// BU
	SHRUB,			// SH
	TREE,			// TR
	VINE,			// VI
	FERN,			// FE
	FLOWER,			// FL
	CACTUS,			// CA
	SUCCULENT,		// SU
};


/* Shade Type 
enum SHADE_TYPE {
	FULL_SHADE,		// SH
	PARTIAL_SUN,	// PA
	FULL_SUN,		// SU
};
*/

class Plant {
public:

	/* Default Constructor */
	Plant();

	/* Data Constructor */
	Plant(const std::string& data);

	/**
	* Get Position
	* 
	* @return m_pos, Plant's position
	*/
	const sf::Vector2f& getPosition();

	/**
	* Get Radius
	* 
	* @return m_rad, Plant's viewport radius
	*/
	float getRadius();

	void draw(sf::RenderWindow& window);


	void setPosition(const sf::Vector2f& pos);

	void setRadius(float rad);

	void setDiameter(float diam);

	void setHeight(float height);

	void setName(const std::string& name);

	void setLatin(const std::string& latin);

	void setType(const std::string& type);

	void setShade(const std::string& shade);


	float getDiameter();

	float getHeight();

	std::string getName();

	std::string getLatin();

	std::string getType();

	std::string getShade();

	std::string to_string();

	bool isHovered(const sf::Vector2i& mousePos);

protected:
private:

	// Growth parameters
	std::string m_type;
	std::string m_shade;

	// Property Parameters
	sf::Vector2f m_pos;		// Position (measured in feet from the property's origin (Top left in mom's case)
	float m_rad;			// Radius of the plant in the viewport

	// Physical constraints
	float m_diam;			// Maximum diameter the plant will grow too
	float m_height;			// Maximum height the plant will grow too

	// Human? parameters
	std::string m_col;		// Colloquial name
	std::string m_lat;		// Latin name
};

#endif // !PLANT_H