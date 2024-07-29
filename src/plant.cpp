// @file plant.cpp
// @author Ethan Rudy
// @desc Class initialization for the Plant class

#include "../include/plant.h"

// Default Constructor
Plant::Plant() {
	m_type = "NULL";
	m_shade = "NULL";

	m_pos = { -1, -1 };
	m_rad = 0;

	m_diam = -1;
	m_height = -1;

	m_col = "Colloquial";
	m_lat = "Latin";
}


// Data Constructor
Plant::Plant(const std::string& data) {
	/*
	Example Plant Data:
	COLLOQUIAL NAME, LATIN NAME, PLANT TYPE, SHADE TYPE, POSITION_X, POSITION_Y, RADIUS, DIAMETER, HEIGHT
	*/

	Tokenizer plant_token(data);

	m_col = plant_token.getNextToken();												// Colloquial
	m_lat = plant_token.getNextToken();												// Latin

	m_type = plant_token.getNextToken();											// Plant Type
	m_shade = plant_token.getNextToken();											// Shade Type

	float x = stof(plant_token.getNextToken());
	float y = stof(plant_token.getNextToken());
	m_pos = { x, y };	// Viewport coordinates
	m_rad = stof(plant_token.getNextToken());										// Viewport radius

	m_diam = stof(plant_token.getNextToken());										// IRL max diameter
	m_height = stof(plant_token.getNextToken());									// IRL max height
}


// Get Position
const sf::Vector2f& Plant::getPosition() {
	return m_pos;
}


// Get Radius
float Plant::getRadius() {
	return m_rad;
}

void Plant::draw(sf::RenderWindow& window) {
	sf::CircleShape plantCircle(m_rad);
	plantCircle.setOrigin({ m_rad, m_rad });
	plantCircle.setPosition(m_pos);
	plantCircle.setFillColor(sf::Color(70, 200, 255));

	window.draw(plantCircle);
}

void Plant::setPosition(const sf::Vector2f& pos) {
	m_pos = pos;
}

void Plant::setRadius(float rad) {
	m_rad = rad;
}

void Plant::setDiameter(float diam) {
	m_diam = diam;
}

void Plant::setHeight(float height) {
	m_height = height;
}

void Plant::setName(const std::string& name) {
	m_col = name;
}

void Plant::setLatin(const std::string& latin) {
	m_lat = latin;
}

void Plant::setType(const std::string& type) {
	m_type = type;
}

void Plant::setShade(const std::string& shade) {
	m_shade = shade;
}

float Plant::getDiameter() {
	return m_diam;
}

float Plant::getHeight() {
	return m_height;
}

std::string Plant::getName() {
	return m_col;
}

std::string Plant::getLatin() {
	return m_lat;
}

std::string Plant::getType() {
	return m_type;
}

std::string Plant::getShade() {
	return m_shade;
}


std::string Plant::to_string() {
	// Example Plant Data :
	// COLLOQUIAL NAME, LATIN NAME, PLANT TYPE, SHADE TYPE, POSITION_X, POSITION_Y, RADIUS, DIAMETER, HEIGHT
	std::string str = "";
	str += m_col + ", " + m_lat + ", " + m_type + ", " + m_shade + ", " + std::to_string(m_pos.x) + ", " + std::to_string(m_pos.y) + ", " + std::to_string(m_rad) + ", " + std::to_string(m_diam) + ", " + std::to_string(m_height);
	return str;
}

bool Plant::isHovered(const sf::Vector2i& mousePos) {
	float dSqrd = pow(mousePos.x - m_pos.x, 2) + pow(mousePos.y - m_pos.y, 2);
	float d = sqrt(dSqrd);

	if (d <= m_rad) { return true; }
	return false;
}