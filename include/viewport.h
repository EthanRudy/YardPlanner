#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <SFML/Graphics.hpp>

class Viewport {
public:

	Viewport();

	Viewport(const sf::Vector2i& pixels);

	void changeZoom(float amt);

	float getZoom() { return m_zoom; }

	void changeOffset(const sf::Vector2f& offset);

	sf::Vector2f coordToPix(const sf::Vector2f& coord);

	sf::Vector2i pixToCoord(const sf::Vector2i& pix);
protected:
private:
	sf::Vector2i m_pixels;
	float m_zoom;
	sf::Vector2f m_offset;

	void createPointText(const sf::Vector2f l_center, const std::string& l_text);
};

#endif // !VIEWPORT_H