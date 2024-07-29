// @file display_manager.cpp
// @author Ethan Rudy
// @desc Class initialization for the DisplayManager class

#include "../include/display_manager.h"


// Data Constructor
DisplayManager::DisplayManager(const std::string& file_path) {
	file_error(file_path);

	std::getline(m_file, m_line);
	Tokenizer window_token(m_line);

	unsigned int x = stoi(window_token.getNextToken());
	unsigned int y = stoi(window_token.getNextToken());
	m_dim = { x, y };
	m_fr = stoi(window_token.getNextToken());

	m_file.close();

	m_view = Viewport(sf::Vector2i(m_dim));

	mouseHeld = false;

	m_font.loadFromFile("./data/Consolas.ttf");

	createPlant = Button({ 1552, 10 }, { 350, 100 }, "Create Plant", m_font);
	deletePlant = Button({ 1552, 120 }, { 350, 100 }, "Delete Plant", m_font);
	infoPlant = Button({ 1192, 10 }, { 350, 100 }, "Plant Info", m_font);

	creating = deleting = info = false;
	firstStage = secondStage = thirdStage = false;

	createPointText(plantTextInputs[0], "Colloquial Name", { 1400, 400}, {400, 40});
	createPointText(plantTextInputs[1], "Latin Name (optional)", { 1400, 500}, { 400, 40 });
	createPointText(plantTextInputs[2], "Maximum Diameter (ft)", { 1500, 600}, { 200, 40 });
	createPointText(plantTextInputs[3], "Maximum Height (ft)", { 1500, 700 }, { 200, 40 });
	createPointText(plantTextInputs[4], "Plant Type", { 1400, 800 }, { 400, 40 });
	createPointText(plantTextInputs[5], "Shade Type", { 1400, 900 }, { 400, 40 });
	selected = -1;

	// Radio points

	submit = Button({ 1400, 250 }, { 400, 75 }, "Submit Plant", m_font);
}


// Open
void DisplayManager::open(Property& prop) {
	m_window.create(sf::VideoMode(m_dim.x, m_dim.y), "Yard Planner");
	m_window.setFramerateLimit(m_fr);

	while (m_window.isOpen()) {

		m_pos = sf::Mouse::getPosition() - m_window.getPosition();
		m_pos -= sf::Vector2i(8, 40);

		sf::Event e;
		while (m_window.pollEvent(e)) {

			/*
				HANDLE EVENTS
			*/
			// Close the program
			if (e.type == sf::Event::Closed) { m_window.close(); }
			else if (e.type == sf::Event::MouseButtonPressed) {

				// Check buttons
				if (e.mouseButton.button == sf::Mouse::Left) {
					if (!mouseHeld) {
						//std::cout << "Clicked\n";
						mouseHeld = true;

						// Check Buttons
						if (createPlant.isHovered(m_pos)) {
							// Trigger the create plant sequence
							creating = true;
							firstStage = true;
							deleting = false;
							info = false;
							break;
						}
						else if (deletePlant.isHovered(m_pos)) {
							// Trigger the delete plant sequence
							deleting = true;
							creating = false;
							info = false;
							break;
						}
						else if (infoPlant.isHovered(m_pos)) {
							info = true;
							creating = false;
							deleting = false;
							break;
						}

						// Create Plant Center
						if (creating) {
							if (firstStage) {
								newCenter = m_view.pixToCoord(m_pos);

								for (int i = 0; i < 6; ++i) {
									plantTextInputs[i].pointText.clear();
								}

								firstStage = false;
								secondStage = true;

								newPlant.setPosition(sf::Vector2f(newCenter));

								//std::cout << newCenter.x << ", " << newCenter.y << "\n";;
							}
							else if (secondStage) {
								// Find Radius
								sf::Vector2i trans_pos = m_view.pixToCoord(m_pos);
								float dSqrd = pow(trans_pos.x - newCenter.x, 2) + pow(trans_pos.y - newCenter.y, 2);
								newRad = sqrt(dSqrd) / m_view.getZoom();

								newPlant.setRadius(newRad);

								//std::cout << newRad << "\n";

								secondStage = false;
								thirdStage = true;
							}
							else if (thirdStage) {
								// Info inputs
								selected = -1;
								for (int i = 0; i < 6; ++i) {
									if (plantTextInputs[i].pointText.isHovered(m_pos)) {
										selected = i;
									}
								}

								// Check submit button
								if (submit.isHovered(m_pos)) {
									thirdStage = false;
									creating = false;

									newPlant.setName(plantTextInputs[0].pointText.getChars());
									newPlant.setLatin(plantTextInputs[1].pointText.getChars());
									newPlant.setDiameter(stof(plantTextInputs[2].pointText.getChars()));
									newPlant.setHeight(stof(plantTextInputs[3].pointText.getChars()));
									newPlant.setType(plantTextInputs[4].pointText.getChars());
									newPlant.setShade(plantTextInputs[5].pointText.getChars());

									/*
									* Send to the property
									*/
									prop.addPlant(newPlant);
								}
							}
						}
						else if (deleting) {
							sf::Vector2i trans_mouse = m_view.pixToCoord(m_pos);
							int index = prop.getFirstHovered(trans_mouse);

							if (index < 0) { break; }
							else {
								prop.removePlant(index);
								deleting = false;
							}
						}
						else if (info) {
							sf::Vector2i trans_mouse = m_view.pixToCoord(m_pos);
							int index = prop.getFirstHovered(trans_mouse);

							if (index < 0) { break; }
							else {
								std::vector<Plant> plants = prop.getPlants();
								Plant p = plants[index];
								plantTextInputs[0].pointText.setChars(p.getName());
								plantTextInputs[1].pointText.setChars(p.getLatin());
								plantTextInputs[2].pointText.setChars(std::to_string(p.getDiameter()));
								plantTextInputs[3].pointText.setChars(std::to_string(p.getHeight()));
								plantTextInputs[4].pointText.setChars(p.getType());
								plantTextInputs[5].pointText.setChars(p.getShade());
							}
						}

						

						
					}
				}
			}
			else if (e.type == sf::Event::MouseButtonReleased) {
				// Release lock
				if (e.mouseButton.button == sf::Mouse::Left) {
					if (mouseHeld) { 
						//std::cout << "Released\n";
						mouseHeld = false; 
					}
				}
			}
			else if (e.type == sf::Event::MouseWheelMoved) {
				float delta = e.mouseWheel.delta;
				// Increase Zoom
				if (delta > 0) {
					m_view.changeZoom(.2f);
				}
				// Decrease Zoom
				else if (delta < 0) {
					m_view.changeZoom(-.2f);
				}

			}
			else if (e.type == sf::Event::MouseMoved) {
				if (mouseHeld) {
					//std::cout << "Dragging\n";
					sf::Vector2i delta = m_pos - m_ppos;

					m_view.changeOffset(sf::Vector2f(delta));
				}
			}
			else if (e.type == sf::Event::TextEntered) {
				if (thirdStage && selected != -1) {
					char c = e.text.unicode;
					if (c == '\b') {
						plantTextInputs[selected].pointText.removeChar();
					}
					else {
						plantTextInputs[selected].pointText.addChar(e.text.unicode);
					}
				}
			}
		} 

		m_window.clear(sf::Color(14, 152, 237));

		drawProperty(prop);

		createPlant.draw(m_window);
		deletePlant.draw(m_window);
		infoPlant.draw(m_window);

		if (firstStage) {
			sf::CircleShape plantOrigin = sf::CircleShape(3);
			plantOrigin.setOrigin({ 1.5f, 1.5f });
			plantOrigin.setPosition(sf::Vector2f(m_pos));
			plantOrigin.setFillColor(sf::Color::White);

			m_window.draw(plantOrigin);
		}
		else if (secondStage) {
			sf::Vector2f center = m_view.coordToPix(sf::Vector2f(newCenter));
			float dSqrd = pow(m_pos.x - center.x, 2) + pow(m_pos.y - center.y, 2);
			float d = sqrt(dSqrd) / m_view.getZoom();
			sf::CircleShape plantShape(d);
			plantShape.setOrigin({ d, d });
			plantShape.setPosition(center);
			plantShape.setFillColor(sf::Color(7, 100, 255));

			m_window.draw(plantShape);
		}
		else if (thirdStage) {
			for (int i = 0; i < 6; ++i) {
				drawPointText(plantTextInputs[i]);
			}

			submit.draw(m_window);
		}
		if (info) {
			// Display the plant info

			for (int i = 0; i < 6; ++i) {
				drawPointText(plantTextInputs[i]);
			}
		}

		m_window.display();

		m_ppos = m_pos;
	}

	prop.save();
}


// File Error
void DisplayManager::file_error(const std::string& x) {
	m_file.open(x);
	if (!m_file) {
		throw std::runtime_error("Could not open file: " + x + "\n");
	}
}


// Draw Property
void DisplayManager::drawProperty(Property& p) {
	drawEdges(p.getEdges());
	drawPlants(p.getPlants());
}


// Draw Edges
void DisplayManager::drawEdges(std::vector<Edge>& edges) {

	for (auto edge : edges) {
		sf::Vector2f start = { edge.getA().x, edge.getA().y};
		// Map to viewport

		sf::Vector2f end = { edge.getB().x, edge.getB().y};
		// Map to viewport

		switch (edge.getType())
		{
		case PROPERTY_LINE:
			drawThin(start, end);
			break;
		case WALL:
			drawThick(start, end);
			break;
		case FENCE:
			drawThin(start, end);
			break;
		case RESERVED:
			drawThin(start, end);
			break;
		default:
			break;
		}
	}

}


// Draw Plants
void DisplayManager::drawPlants(std::vector<Plant>& plants) {
	sf::CircleShape plantCircle(0);
	plantCircle.setFillColor(sf::Color(7, 100, 255));

	for (Plant& p : plants) {
		float r = p.getRadius() * m_view.getZoom();
		plantCircle.setPosition(0, 0);
		plantCircle.setRadius(r);
		plantCircle.setOrigin(r, r);
		plantCircle.setPosition(m_view.coordToPix(p.getPosition()));

		m_window.draw(plantCircle);
	}
}

void DisplayManager::drawThin(const sf::Vector2f& start, const sf::Vector2f& end) {
	sf::VertexArray line(sf::LinesStrip, 2);

	sf::Vector2f startTrans = m_view.coordToPix(start);
	sf::Vector2f endTrans = m_view.coordToPix(end);

	line[0] = sf::Vertex(startTrans, sf::Color::White);
	line[1] = sf::Vertex(endTrans, sf::Color::White);

	m_window.draw(line);
}
void DisplayManager::drawThick(const sf::Vector2f& start, const sf::Vector2f& end) {
	sf::Vector2f startTrans = m_view.coordToPix(start);
	sf::Vector2f endTrans = m_view.coordToPix(end);
	
	sf::RectangleShape line({ abs(startTrans.x - endTrans.x), abs(startTrans.y - endTrans.y) });

	// Horizontal Line (increase height)
	if (start.x == end.x) {
		line.setSize(line.getSize() + sf::Vector2f(2, 0));
		line.setPosition(line.getPosition() - sf::Vector2f(1, 0));
	}
	// Vertical Line (increase widths)
	else {
		line.setSize(line.getSize() + sf::Vector2f(0, 2));
		line.setPosition(line.getPosition() - sf::Vector2f(0, 1));
	}

	line.setPosition(m_view.coordToPix(start));

	m_window.draw(line);
}
void DisplayManager::drawDashed(const sf::Vector2f& start, const sf::Vector2f& end) {
	float mag = 5;
	float step = 1.f;

	int amt;
	bool horizontal;
	if (start.y == end.y) {
		horizontal = true;
		amt = end.x - start.x;
	}
	else {
		horizontal = false;
		amt = end.y - start.y;
	}

	if (amt < 0) { 
		amt = -amt; 
		step = -step;
	}
	
	if (amt % 2 == 1) { --amt; }

	sf::VertexArray line(sf::Lines, amt);
	
	for (int i = 0; i < amt; i += 2) {
		/*
		line[i] = start;
		line[i + 1] = end;
		*/

		if (horizontal) {
			line[i] = start + sf::Vector2f(i, 0);
			line[i + 1] = start + sf::Vector2f(i + 1, 0);
		}
		else {
			line[i] = start + sf::Vector2f(0, i);
			line[i + 1] = start + sf::Vector2f(0, i + 1);
		}
	}

	m_window.draw(line);
}


void DisplayManager::createPointText(PlantPointText& target, const std::string& l_text, const sf::Vector2f& t_pos, const sf::Vector2f& t_dim) {
	target.pointLabel = Label(l_text, m_font, 32);

	target.pointText = TextBox(t_pos, t_dim, m_font);

	target.pointLabel.setCenter(sf::Vector2f(t_pos.x + t_dim.x / 2, t_pos.y - 16));
}

void DisplayManager::drawPointText(PlantPointText& target) {
	target.pointLabel.draw(m_window);
	target.pointText.draw(m_window);
}