#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML/Graphics.hpp>

// Needs button AND label functionality
class TextBox {
public:

	TextBox();

	TextBox(const sf::Vector2f& pos, const sf::Vector2f& dim, sf::Font& font);

	bool isHovered(const sf::Vector2i& mousePos);

	void addChar(char c);

	void removeChar();

	void clear();

	std::string getChars();

	void setChars(const std::string& str);

	void draw(sf::RenderWindow& window);
protected:
private:
	
	std::string m_chars;
	sf::Text m_text;
	sf::Font m_font;
	sf::RectangleShape m_box;

	sf::Vector2f m_pos;
	sf::Vector2f m_dim;
};

#endif // !TEXTBOX_H