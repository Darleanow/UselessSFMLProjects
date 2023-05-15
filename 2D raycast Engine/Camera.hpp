#pragma once

#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include "Map.hpp"

#include <vector>
#include <math.h>

class camera {
protected:
	map& m_map;
	sf::RenderWindow& m_renderWindow;
	sf::CircleShape m_camera;
	sf::Vector2f m_position, m_intersection;
	sf::Clock m_clock;

	float m_angle, m_fov, m_rayLength;
	float m_radius;
	float m_speedMove, m_speedAngle;

	std::vector<sf::VertexArray>m_vecRays;
public:
	camera(sf::RenderWindow& renderWindow, map& Map);

	void draw();
	void update();
	void projection();
	void checkKeyboardHit(sf::Time dt);
	bool intersect(unsigned int it);

	inline float toRadian(float deg);
	inline float dCos(float deg);
	inline float dSin(float deg);
};