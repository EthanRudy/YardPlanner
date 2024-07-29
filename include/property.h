// @file property.h
// @author Ethan Rudy
// @desc Class declaration for the Property class

#include <exception>
#include <fstream>
#include <iostream>
#include <vector>
#include "edge.h"
#include "plant.h"

class Property {
public:

	Property();

	Property(const std::string& edge_path, const std::string& plant_path);

	void addPlant(Plant p);

	std::vector<Edge>& getEdges();

	std::vector<Plant>& getPlants();

	void save();

	int getSize();

	void removePlant(int index);

	int getFirstHovered(const sf::Vector2i& mousePos);

protected:
private:

	std::vector<Edge> m_edges;
	std::vector<Plant> m_plants;

	std::ifstream m_file;
	std::string line;

	/**
	* File Error
	* 
	* @param x File path
	*/
	void file_error(const std::string& x);

	/**
	* Load Edges
	* 
	* @param file_path Relative path to the edge file
	*/
	void load_edges(const std::string& file_path);

	/**
	* Load Plants
	*
	* @param file_path Relative path to the plant file
	*/
	void load_plants(const std::string& file_path);
};