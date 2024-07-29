#include "../include/property.h"

Property::Property() = default;


Property::Property(const std::string& edge_path, const std::string& plant_path) {
	
	try {
		load_edges(edge_path);
	}
	catch (std::exception& ex) {
		std::cout << "FILL ERROR: " << ex.what();
	}

	try {
		load_plants(plant_path);
	}
	catch (std::exception& ex) {
		std::cout << "FILL ERROR: " << ex.what();
	}
}

void Property::addPlant(Plant p) {
	m_plants.push_back(p);
}


std::vector<Edge>& Property::getEdges() { 
	return m_edges; 
}


std::vector<Plant>& Property::getPlants() { 
	return m_plants; 
}


// File Error
void Property::file_error(const std::string& x) {
	m_file.open(x);
	if (!m_file) {
		throw std::runtime_error("Could not open file: " + x + "\n");
	}
}


// Load Edges
void Property::load_edges(const std::string& file_path) {
	file_error(file_path);

	while (std::getline(m_file, line)) {

		// Check for comment flag
		if (line[0] == '#') { continue; }

		m_edges.push_back(Edge(line));
	}

	m_file.close();
}


// Load Plants
void Property::load_plants(const std::string& file_path) {
	file_error(file_path);

	while (std::getline(m_file, line)) {

		// Check for comment flag
		if (line[0] == '#') { continue; }

		m_plants.push_back(Plant(line));
	}

	m_file.close();
}

void Property::save() {
	std::ofstream plantFile("./data/plants.dat");

	for (Plant& p : m_plants) {
		plantFile << p.to_string() << "\n";
	}

	plantFile.close();
}

int Property::getSize() {
	return m_plants.size();
}

void Property::removePlant(int index) {
	if (index < 0) { return; }
	m_plants.erase(m_plants.begin() + index, m_plants.begin() + index + 1);
}

int Property::getFirstHovered(const sf::Vector2i& mousePos) {
	int index = -1;
	
	for (int i = 0; i < m_plants.size(); ++i) {
		if (m_plants[i].isHovered(mousePos)) {
			index = i;
			break;
		}
	}

	return index;
}

// Example Plant Data :
// COLLOQUIAL NAME, LATIN NAME, PLANT TYPE, SHADE TYPE, POSITION_X, POSITION_Y, RADIUS, DIAMETER, HEIGHT