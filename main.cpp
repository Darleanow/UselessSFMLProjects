#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <random>

sf::Color getRandomColor() {
    static std::random_device rd;  // Will be used to obtain a seed for the random number engine
    static std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    static std::uniform_int_distribution<> distrib(0, 255);

    sf::Color color;
    color.r = distrib(gen); // Generate a random red component
    color.g = distrib(gen); // Generate a random green component
    color.b = distrib(gen); // Generate a random blue component
    color.a = 255; // Set alpha to maximum 

    return color;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    sf::Texture texture;
    if (!texture.loadFromFile("Assets/dvd.png"))
    {
        //error handle
    }
    sf::Sprite sprite;
    sprite.setTexture(texture, true);
    sf::Vector2u size = texture.getSize();
    sprite.setOrigin(size.x / 2, size.y / 2);
    sf::Vector2f increment(0.04f, 0.04f);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if ((sprite.getPosition().x + (size.x / 2) >
            window.getSize().x && increment.x > 0) ||
            (sprite.getPosition().x - (size.x / 2) < 0 &&
            increment.x < 0))
        {
            // Reverse the direction on X axis.
            sprite.setColor(getRandomColor());
            increment.x = -increment.x;
        }

        if ((sprite.getPosition().y + (size.y / 2) >
            window.getSize().y && increment.y > 0) ||
            (sprite.getPosition().y - (size.y / 2) < 0 &&
            increment.y < 0))
        {
             // Reverse the direction on Y axis.
            sprite.setColor(getRandomColor());
            increment.y = -increment.y;
        }

        sprite.setPosition(sprite.getPosition() + increment);
        
        window.clear(sf::Color(16, 16, 16, 255)); // Dark gray.
        window.draw(sprite); // Drawing our sprite.
        window.display();
    }

    return 0;
}
