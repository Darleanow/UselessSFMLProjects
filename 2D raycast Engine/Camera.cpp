#include "Camera.hpp"

/*
camera(sf::RenderWindow& renderWindow);

	void draw();
	void update();
	void projection();

	inline void toRadian(float deg);
*/
#include <iostream>

camera::camera(sf::RenderWindow& renderWindow, map& Map) :
	m_renderWindow(renderWindow), m_map(Map)
{
	m_radius = 5;
	m_camera.setRadius(m_radius);
	m_camera.setFillColor(sf::Color(0, 255, 0));
	m_camera.setOrigin(sf::Vector2f(m_radius, m_radius));

	m_speedMove = 150.0f;
	m_speedAngle = 100.0f;

	m_position = { 128, 128 };

	m_fov = 60;
	m_rayLength = 200;

	for (unsigned int i = 0; i < SCREENWIDTH; i++)
	{
		sf::VertexArray ray(sf::Lines, 2);
		ray[0].color = sf::Color::Red;
		ray[1].color = sf::Color::Red;
		m_vecRays.push_back(ray);
	}


}

void camera::draw()
{
	for (auto& vvec : m_vecRays)
	{
		m_renderWindow.draw(vvec);
	}

	m_renderWindow.draw(m_camera);
}

void camera::update()
{
	sf::Time dt = m_clock.restart();
	checkKeyboardHit(dt);
	projection();
}

void camera::projection()
{
	for (unsigned int i = 0; i < m_vecRays.size(); i++)
	{
		m_vecRays[i][0].position = m_position;

		if (intersect(i))
		{
			m_vecRays[i][1].position = m_intersection;
		}
		else
		{
			m_vecRays[i][1].position = { m_position.x + m_rayLength * dCos((m_angle + m_fov / 2) - i * (m_fov / SCREENWIDTH)),
										 m_position.y + m_rayLength * dSin((m_angle + m_fov / 2) - i * (m_fov / SCREENWIDTH)) };
		}		
		
	}
}

void camera::checkKeyboardHit(sf::Time dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_position.x += dCos(m_angle * m_speedMove * dt.asSeconds());
		m_position.y += dSin(m_angle * m_speedMove * dt.asSeconds());
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_position.x -= dCos(m_angle * m_speedMove * dt.asSeconds());
		m_position.y -= dSin(m_angle * m_speedMove * dt.asSeconds());
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_angle -= m_speedAngle * dt.asSeconds();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_angle += m_speedAngle * dt.asSeconds();
	}

	if (m_angle > 360)
		m_angle = 0;
	else if (m_angle < 0)
		m_angle = 360;

	m_camera.setPosition(m_position);
	m_camera.setRotation(m_angle);

}

bool camera::intersect(unsigned int it)
{
	float fAngle = (m_angle + m_fov / 2 - it * (m_fov / SCREENWIDTH));

	sf::Vector2f direction = { dCos(fAngle), dSin(fAngle) };

	for (unsigned int length = 0; length < m_rayLength; length++)
	{
		int dx = static_cast<int>(m_position.x + length * direction.x);
		int dy = static_cast<int>(m_position.y + length * direction.y);

		if (dx / blocSize < m_map.getWidth() && dy / blocSize < m_map.getHeight() && m_map.checkMapCase(dx / blocSize, dy / blocSize))
		{
			m_intersection.x = dx;
			m_intersection.y = dy;
			return true;
		}
	}
	return false;
}


inline float camera::toRadian(float deg)
{
	return (3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679 / 180) * deg;
}

inline float camera::dCos(float deg)
{
	return cos(toRadian(deg));
}

inline float camera::dSin(float deg)
{
	return sin(toRadian(deg));
}