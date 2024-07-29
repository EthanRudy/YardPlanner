#include "../include/viewport.h"

Viewport::Viewport() = default;

Viewport::Viewport(const sf::Vector2i& pixels) {
	m_pixels = pixels;
	m_zoom = 7;
	m_offset = { 10, 10 };
}

void Viewport::changeZoom(float amt) {
	m_zoom += amt;
}

void Viewport::changeOffset(const sf::Vector2f& offset) {
	m_offset += offset;
}

sf::Vector2f Viewport::coordToPix(const sf::Vector2f& coord) {
	sf::Vector2f newCoord = coord;
	newCoord = {newCoord.x* m_zoom, newCoord.y* m_zoom};
	newCoord += m_offset;

	return newCoord;
}

sf::Vector2i Viewport::pixToCoord(const sf::Vector2i& pix) {
	sf::Vector2i newPix = pix;
	newPix -= sf::Vector2i(m_offset.x, m_offset.y);
	newPix = sf::Vector2i(newPix.x / m_zoom, newPix.y / m_zoom);

	return newPix;
}