#ifndef LABEL_H
#define LABEL_H

#include <SFML/Graphics.hpp>

class Label {
public:

	Label() = default;

	Label(const std::string& str, sf::Color color, sf::Font& font);

	Label(const std::string& str, sf::Font& font, float size);

	void setCenter(const sf::Vector2f& center);

	void draw(sf::RenderWindow& window);

protected:
private:

	sf::Text m_text;
};

#endif // !LABEL_H