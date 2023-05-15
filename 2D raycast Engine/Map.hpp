#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class map
{
protected:
	sf::RenderWindow& m_renderWindow;
	std::vector<std::vector<unsigned int>> m_vecMap;
	std::vector <sf::RectangleShape> m_vecBox;
public:
	map(sf::RenderWindow& m_renderWindow);

	void draw();
	bool checkMapCase(unsigned int dx, unsigned int dy);

	unsigned int getWidth();
	unsigned int getHeight();
};

