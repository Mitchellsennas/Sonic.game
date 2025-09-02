#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Enemy.h"
#include "MotoBug.h"
#include "BuzzBomber.h"
#include "CrabMeat.h"

class Level {
public:
    Level();
    void draw(sf::RenderWindow& window);
    void spawnEnemies(std::vector<std::unique_ptr<Enemy>>& enemies);

    sf::FloatRect getBounds() const { return sf::FloatRect(0, 0, width, height); }
    std::vector<sf::RectangleShape>& getPlatforms() { return platforms; }

private:
    float width = 2000.f; // level width
    float height = 520.f;
    std::vector<sf::RectangleShape> platforms;
};
