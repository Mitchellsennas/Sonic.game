#include "Level.h"

Level::Level() {
    // Ground
    sf::RectangleShape ground;
    ground.setSize({width, 100.f});
    ground.setFillColor(sf::Color(100,200,100));
    ground.setPosition(0, height - 100.f);
    platforms.push_back(ground);

    // Elevated platforms
    for(int i=0; i<5; i++){
        sf::RectangleShape plat;
        plat.setSize({150.f, 20.f});
        plat.setFillColor(sf::Color(120,120,200));
        plat.setPosition(250.f + i*300.f, height - 200.f - i*30.f);
        platforms.push_back(plat);
    }

    // Goal flag at the far right
    goal.setSize({40, 80});                    // flag size
    goal.setFillColor(sf::Color::Green);       // green color
    goal.setPosition(width - 60, height - 180); // place on top of ground
}

void Level::draw(sf::RenderWindow& window){
    // Draw all platforms
    for(auto& p : platforms) window.draw(p);

    // Draw goal flag
    window.draw(goal);
}

void Level::spawnEnemies(std::vector<std::unique_ptr<Enemy>>& enemies){
    enemies.emplace_back(std::make_unique<MotoBug>(sf::Vector2f(400, height - 120), 350, 450));
    enemies.emplace_back(std::make_unique<BuzzBomber>(sf::Vector2f(700, height - 250), 40, 2, 600, 800));
    enemies.emplace_back(std::make_unique<CrabMeat>(sf::Vector2f(1000, height - 120), 50));
    enemies.emplace_back(std::make_unique<MotoBug>(sf::Vector2f(1200, height - 120), 1150, 1250));
    enemies.emplace_back(std::make_unique<BuzzBomber>(sf::Vector2f(1500, height - 250), 50, 2.5, 1450, 1550));
    enemies.emplace_back(std::make_unique<CrabMeat>(sf::Vector2f(1800, height - 120), 50));
}

// Getter for goal collision
sf::FloatRect Level::getGoalBounds() const {
    return goal.getGlobalBounds();
}
