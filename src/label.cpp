#include "../include/label.h"

Label::Label(const std::string& str, sf::Color color, sf::Font& font) {
	m_text = sf::Text(str, font, 48);
	m_text.setFillColor(color);
}

Label::Label(const std::string& str, sf::Font& font, float size) {
	m_text = sf::Text(str, font, size);
	m_text.setFillColor(sf::Color::White);
}

void Label::setCenter(const sf::Vector2f& center) {
	m_text.setOrigin(m_text.getGlobalBounds().getSize() / 2.f + m_text.getLocalBounds().getPosition());
	m_text.setPosition(center);
}

void Label::draw(sf::RenderWindow& window) {
	window.draw(m_text);
}