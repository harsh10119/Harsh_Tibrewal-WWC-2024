........Games......................
................Fruit Junction..................................
 Code:--


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>

int playerLives = 3;
int score = 0;
bool gameOver = false;
sf::Font font;
sf::Text scoreText;

std::map<std::string, sf::Sprite> fruits;
std::map<std::string, sf::Texture> fruitTextures;
std::map<std::string, sf::Texture> explosionTextures;
sf::Texture backgroundTexture;
sf::Sprite background;
sf::Texture livesIconTexture;
sf::Sprite livesIcon;

// Function to load resources
bool loadResources() {
    if (!font.loadFromFile("comic.ttf"))
        return false;  // Return false if font loading fails
    if (!backgroundTexture.loadFromFile("back.jpg"))
        return false;  // Return false if background loading fails
    if (!livesIconTexture.loadFromFile("images/white_lives.png"))
        return false;  // Return false if lives icon loading fails
    if (!fruitTextures["melon"].loadFromFile("images/melon.png"))
        return false;  // Return false if melon texture loading fails
    if (!fruitTextures["orange"].loadFromFile("images/orange.png"))
        return false;  // Return false if orange texture loading fails
    if (!fruitTextures["pomegranate"].loadFromFile("images/pomegranate.png"))
        return false;  // Return false if pomegranate texture loading fails
    if (!fruitTextures["guava"].loadFromFile("images/guava.png"))
        return false;  // Return false if guava texture loading fails
    if (!fruitTextures["bomb"].loadFromFile("images/bomb.png"))
        return false;  // Return false if bomb texture loading fails
    if (!explosionTextures["bomb"].loadFromFile("images/explosion.png"))
        return false;  // Return false if explosion texture loading fails
    
    return true;
}

// Function to generate random fruits
void generateRandomFruits(std::string fruit) {
    int x = rand() % 400 + 100;  // Random x-coordinate
    int y = 800;                 // Starting y-coordinate
    int speed_x = rand() % 21 - 10; // Random horizontal speed (-10 to 10)
    int speed_y = rand() % 21 - 60; // Random vertical speed (-60 to -80)
    
    sf::Sprite fruitSprite(fruitTextures[fruit]);
    fruitSprite.setPosition(x, y);
    
    fruits[fruit] = fruitSprite;
}

// Function to draw text on the screen
void drawText(sf::RenderWindow& window, std::string text, int size, int x, int y) {
    sf::Text renderText;
    renderText.setFont(font);
    renderText.setString(text);
    renderText.setCharacterSize(size);
    renderText.setFillColor(sf::Color::White);
    renderText.setPosition(x, y);
    window.draw(renderText);
}

// Function to draw the player's lives
void drawLives(sf::RenderWindow& window, int lives, int x, int y) {
    for (int i = 0; i < lives; i++) {
        livesIcon.setPosition(x + 35 * i, y);
        window.draw(livesIcon);
    }
}

int main() {
    srand(time(0));  // Seed for random number generator
    
    // Create the window
    sf::RenderWindow window(sf::VideoMode(800, 500), "Fruit Ninja Game -- DataFlair");
    
    if (!loadResources()) {
        std::cerr << "Failed to load resources!" << std::endl;
        return -1;
    }

    background.setTexture(backgroundTexture);
    
    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (gameOver) {
            window.clear();
            drawText(window, "GAME OVER", 90, 300, 100);
            drawText(window, "Score: " + std::to_string(score), 50, 300, 200);
            drawText(window, "Press any key to restart", 50, 300, 300);
            window.display();
            continue;
        }

        // Game logic
        window.clear();
        window.draw(background);
        drawLives(window, playerLives, 690, 10);
        
        // Handle mouse position and check for fruit hits
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        
        for (auto& fruitPair : fruits) {
            sf::Sprite& fruit = fruitPair.second;
            fruit.move(0, 10);  // Move fruit downward (simulating gravity)

            if (fruit.getPosition().y > 800) {
                fruit.setPosition(rand() % 400 + 100, -100);  // Reset fruit position
            }

            window.draw(fruit);
            
            // Check for fruit click
            if (fruit.getGlobalBounds().contains(mousePos.x, mousePos.y) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (fruitPair.first == "bomb") {
                    playerLives--;
                    if (playerLives == 0) {
                        gameOver = true;
                    }
                } else {
                    score++;
                }

                fruit.setTexture(explosionTextures["bomb"]);
                fruit.setScale(0.5f, 0.5f);
            }
        }

        // Draw score
        scoreText.setString("Score: " + std::to_string(score));
        window.draw(scoreText);
        
        window.display();

        // FPS control
        sf::sleep(sf::seconds(1.f / 12.f)); // 12 FPS (similar to original code)
    }

    return 0;
}

