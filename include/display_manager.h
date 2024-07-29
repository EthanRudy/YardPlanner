// @file display_manager.h
// @author Ethan Rudy
// @desc Class declaration for the DisplayManager class

#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <exception>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include "property.h"
#include "viewport.h"
#include "button.h"
#include "textbox.h"

struct PlantPointText {
	Label pointLabel;
	TextBox pointText;
};

class DisplayManager {
public:

	/* Data Constructor */
	DisplayManager(const std::string& file_path);

	/* Open */
	void open(Property& prop);

protected:
private:

	sf::RenderWindow m_window;
	sf::Vector2u m_dim;
	float m_fr;

	Viewport m_view;

	std::ifstream m_file;
	std::string m_line;

	bool mouseHeld;
	sf::Vector2i m_pos, m_ppos;

	sf::Font m_font;

	Button createPlant;
	Button deletePlant;
	Button infoPlant;

	bool creating, deleting, info;
	bool firstStage, secondStage, thirdStage;

	sf::Vector2i newCenter;
	float newRad;
	Plant newPlant;

	/*
		PLANT DATA
	*/
	PlantPointText plantTextInputs[6];
	int selected;

	Button submit;

	void file_error(const std::string& x);

	void drawProperty(Property& p);

	void drawEdges(std::vector<Edge>& edges);

	void drawPlants(std::vector<Plant>& plants);

	void drawThin(const sf::Vector2f& start, const sf::Vector2f& end);
	void drawThick(const sf::Vector2f& start, const sf::Vector2f& end);
	void drawDashed(const sf::Vector2f& start, const sf::Vector2f& end);


	void createPointText(PlantPointText& target, const std::string& l_text, const sf::Vector2f& t_pos, const sf::Vector2f& t_dim);
	void drawPointText(PlantPointText& target);
};

#endif // !DISPLAY_MANAGER_H