#include <SFML/Graphics.hpp>
#include <iostream>


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Basic sprite control");

    sf::Texture texture;
    if (!texture.loadFromFile("assets/sprite.png")) {
        return -1; 
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);

    sf::Vector2u textureSize = texture.getSize();
    float scaleX = 100.0 / textureSize.x;
    float scaleY = 100.0f / textureSize.y;
    sprite.setScale(scaleX, scaleY);

    sf::FloatRect spriteBounds = sprite.getLocalBounds();
    sprite.setOrigin(spriteBounds.width / 2, spriteBounds.height / 2);
    sprite.setPosition(400, 400);

    sf::View view(sf::FloatRect(0, 0, 800, 800));
    view.setCenter(sprite.getPosition());

    float speed = 200.0f;
    int gridSize = 50;

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::Resized) {
                float aspectRatio = static_cast<float>(event.size.width) / event.size.height;
                view.setSize(800 * aspectRatio, 800);
                window.setView(view);
            }
        }

        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            sprite.move(0, -speed * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            sprite.move(0, speed * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            sprite.move(-speed * deltaTime, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            sprite.move(speed * deltaTime, 0);
        }

        view.setCenter(sprite.getPosition());
        window.setView(view);

        window.clear();

        sf::Vector2f viewCenter = view.getCenter();
        sf::Vector2f viewSize = view.getSize();
        sf::Vector2f topLeft(viewCenter.x - viewSize.x / 2, viewCenter.y - viewSize.y / 2);

        sf::VertexArray grid(sf::Lines);
        for (int i = static_cast<int>(topLeft.x) - (static_cast<int>(topLeft.x) % gridSize); i < topLeft.x + viewSize.x; i += gridSize) {
            grid.append(sf::Vertex(sf::Vector2f(i, topLeft.y), sf::Color::White));
            grid.append(sf::Vertex(sf::Vector2f(i, topLeft.y + viewSize.y), sf::Color::White));
        }
        for (int j = static_cast<int>(topLeft.y) - (static_cast<int>(topLeft.y) % gridSize); j < topLeft.y + viewSize.y; j += gridSize) {
            grid.append(sf::Vertex(sf::Vector2f(topLeft.x, j), sf::Color::White));
            grid.append(sf::Vertex(sf::Vector2f(topLeft.x + viewSize.x, j), sf::Color::White));
        }


        sf::Vector2f spritePos = sprite.getPosition();
        int gridX = static_cast<int>(spritePos.x) / gridSize;
        int gridY = static_cast<int>(spritePos.y) / gridSize; 

        sf::RectangleShape honeyBlock(sf::Vector2f(gridSize, gridSize));
        honeyBlock.setFillColor(sf::Color(255, 223, 0)); 
        honeyBlock.setPosition(gridX * gridSize, gridY * gridSize);

        window.draw(honeyBlock);
        window.draw(grid);
        window.draw(sprite);
        window.display();
    }

    return 0;
}
