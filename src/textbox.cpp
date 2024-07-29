#include "../include/textbox.h"

TextBox::TextBox() = default;

TextBox::TextBox(const sf::Vector2f& pos, const sf::Vector2f& dim, sf::Font& font) {
	m_pos = pos;
	m_dim = dim;
	m_font = font;

	m_chars = "";

	m_text = sf::Text(m_chars, font, 32);
	m_text.setPosition(m_pos);
	m_text.setFillColor(sf::Color::Black);

	m_box = sf::RectangleShape(m_dim);
	m_box.setPosition(m_pos);
	m_box.setFillColor({ 200, 200, 200 });
}

bool TextBox::isHovered(const sf::Vector2i& mousePos) {
	if (mousePos.x > m_pos.x && mousePos.x < m_pos.x + m_dim.x) {
		if (mousePos.y > m_pos.y && mousePos.y < m_pos.y + m_dim.y) {
			return true;
		}
	}

	return false;
}

void TextBox::addChar(char c) {
	m_chars += c;

	m_text.setString(m_chars);
}

void TextBox::removeChar() {
	m_chars = m_chars.substr(0, m_chars.size() - 1);

	m_text.setString(m_chars);
}

void TextBox::clear() {
	m_chars = "";

	m_text.setString(m_chars);
}

std::string TextBox::getChars() {
	return m_chars;
}

void TextBox::setChars(const std::string& str) {
	m_chars = str;

	m_text.setString(m_chars);
}

void TextBox::draw(sf::RenderWindow& window) {
	window.draw(m_box);
	window.draw(m_text);
}