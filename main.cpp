#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");


    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/test_bg.jpg")) {
        std::cerr << "Error: Could not load background image!" << std::endl;
        return -1;
    }

    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);


    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.clear(sf::Color::Black);

        window.draw(backgroundSprite);

        window.display();
    }

    return 0;
}
