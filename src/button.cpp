#include "../include/button.h"

Button::Button(const sf::Vector2f& pos, const sf::Vector2f& dim, const std::string& text, sf::Font& font) {
	m_pos = pos;
	m_dim = dim;

	m_shape = sf::RectangleShape(m_dim);
	m_shape.setPosition(m_pos);

	m_shape.setFillColor(sf::Color(7, 100, 255));

	m_label = Label(text, sf::Color::White, font);
	m_label.setCenter(sf::Vector2f(m_pos.x + m_dim.x / 2, m_pos.y + m_dim.y / 2));
}

bool Button::isHovered(const sf::Vector2i& mousePos) {
	if (mousePos.x > m_pos.x && mousePos.x < m_pos.x + m_dim.x) {
		if (mousePos.y > m_pos.y && mousePos.y < m_pos.y + m_dim.y) {
			return true;
		}
	}

	return false;
}

void Button::draw(sf::RenderWindow& window) {
	window.draw(m_shape);
	m_label.draw(window);
}