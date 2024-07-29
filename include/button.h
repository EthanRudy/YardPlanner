#ifndef BUTTON_H
#define BUTTON_H

#include "label.h"

class Button {
public:

	Button() = default;

	Button(const sf::Vector2f& pos, const sf::Vector2f& dim, const std::string& text, sf::Font& font);

	bool isHovered(const sf::Vector2i& mousePos);

	void draw(sf::RenderWindow& window);
protected:
private:

	sf::RectangleShape m_shape;
	Label m_label;
	sf::Vector2f m_pos;
	sf::Vector2f m_dim;
};

#endif // !BUTTON_H