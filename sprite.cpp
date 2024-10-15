#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath> 

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Basic sprite control");

    // Enable VSync
    window.setVerticalSyncEnabled(false);

    sf::Texture texture;
    if (!texture.loadFromFile("assets/sprite.png")) {
        return -1; 
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);

    sf::Vector2u textureSize = texture.getSize();
    float scaleX = 100.0f / textureSize.x;
    float scaleY = 100.0f / textureSize.y;
    sprite.setScale(scaleX, scaleY);

    sf::FloatRect spriteBounds = sprite.getLocalBounds();
    sprite.setOrigin(spriteBounds.width / 2, spriteBounds.height / 2);
    sprite.setPosition(400, 400);

    sf::View view(sf::FloatRect(0, 0, 800, 800));
    view.setCenter(sprite.getPosition());

    float speed = 200.0f;  
    float runSpeed = 300.0f;  
    float stamina = 100.0f;   
    float staminaDecreaseRate = 10.5f;  
    float walkRegenRate = 5.5f;         
    float standRegenRate = 10.5f;       
    float staminaRegenDelay = 2.0f;     
    bool applyRegenDelay = false;       
    sf::Clock regenClock;
    bool isRunning = false;

    float staminaBarMaxWidth = 200.0f;
    float staminaBarHeight = 20.0f;  
    sf::RectangleShape staminaBarBackground(sf::Vector2f(staminaBarMaxWidth, staminaBarHeight));
    staminaBarBackground.setFillColor(sf::Color(105, 105, 105));  
    staminaBarBackground.setPosition(10, 770); 
    
    sf::RectangleShape staminaBar(sf::Vector2f(staminaBarMaxWidth, staminaBarHeight));
    staminaBar.setFillColor(sf::Color(255, 223, 0));  
    staminaBar.setPosition(10, 770); 

    // FPS related variables
    sf::Clock fpsClock;
    int frameCount = 0;
    float fps = 0.0f;

    sf::Font font;
    if (!font.loadFromFile("assets/font.ttf")) { 
        return -1;
    }

    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(24);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(10, 10);

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


        frameCount++;
        if (fpsClock.getElapsedTime().asSeconds() >= 1.0f) {
            fps = frameCount;
            frameCount = 0;
            fpsClock.restart();
        }

        sf::Vector2f movement(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            movement.y -= 1.0f; 
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            movement.y += 1.0f; 
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            movement.x -= 1.0f; 
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            movement.x += 1.0f; 
        }

        float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
        if (length != 0) {
            movement /= length;  
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && stamina > 0) {
            isRunning = true;
            stamina -= staminaDecreaseRate * deltaTime;  
            if (stamina < 0) stamina = 0; 

            if (stamina < 25) {
                applyRegenDelay = true;
                regenClock.restart(); 
            }
        } else {
            isRunning = false;
        }

        bool isWalking = length > 0 && !isRunning;
        bool isStandingStill = length == 0 && !isRunning;

        if (!isRunning) {
            if (applyRegenDelay && stamina < 25 && regenClock.getElapsedTime().asSeconds() < staminaRegenDelay) {

            } else {
                applyRegenDelay = false;
                float regenRate = 0.0f;
                if (isStandingStill) {
                    regenRate = standRegenRate * (1.0f - (stamina / 100.0f)); 
                } else if (isWalking) {
                    regenRate = walkRegenRate * (1.0f - (stamina / 100.0f));  
                }
                stamina += regenRate * deltaTime; 
                if (stamina > 100) stamina = 100;  
            }
        }

        float staminaBarWidth = (stamina / 100.0f) * staminaBarMaxWidth;
        staminaBar.setSize(sf::Vector2f(staminaBarWidth, staminaBarHeight)); 

        float currentSpeed = isRunning ? runSpeed : speed;
        sprite.move(movement * currentSpeed * deltaTime);

        view.setCenter(sprite.getPosition());
        window.setView(view);

        window.clear();

        sf::Vector2f viewCenter = view.getCenter();
        sf::Vector2f viewSize = view.getSize();
        sf::Vector2f topLeft(viewCenter.x - viewSize.x / 2, viewCenter.y - viewSize.y / 2);

        sf::VertexArray grid(sf::Lines);
        int gridSize = 50;
        for (int i = static_cast<int>(topLeft.x) - (static_cast<int>(topLeft.x) % gridSize); i < topLeft.x + viewSize.x; i += gridSize) {
            grid.append(sf::Vertex(sf::Vector2f(i, topLeft.y), sf::Color::White));
            grid.append(sf::Vertex(sf::Vector2f(i, topLeft.y + viewSize.y), sf::Color::White));
        }
        for (int j = static_cast<int>(topLeft.y) - (static_cast<int>(topLeft.y) % gridSize); j < topLeft.y + viewSize.y; j += gridSize) {
            grid.append(sf::Vertex(sf::Vector2f(topLeft.x, j), sf::Color::White));
            grid.append(sf::Vertex(sf::Vector2f(topLeft.x + viewSize.x, j), sf::Color::White));
        }

        sf::Vector2f spritePos = sprite.getPosition();
        int gridX = static_cast<int>(std::floor(spritePos.x / gridSize));
        int gridY = static_cast<int>(std::floor(spritePos.y / gridSize));

        sf::RectangleShape honeyBlock(sf::Vector2f(gridSize, gridSize));
        honeyBlock.setFillColor(sf::Color(255, 223, 0));
        honeyBlock.setPosition(gridX * gridSize, gridY * gridSize);

        window.draw(honeyBlock);
        window.draw(grid);
        window.draw(sprite);

        window.setView(window.getDefaultView());
        window.draw(staminaBarBackground);  
        window.draw(staminaBar);          

        fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));
        window.draw(fpsText);

        window.display();
    }

    return 0;
}
