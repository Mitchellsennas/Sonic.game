#include "HUD.h"

bool HUD::load() {
    return font.loadFromFile("assets/arial.ttf");
}

void HUD::update(const Player& p) {
    hp.setFont(font);
    hp.setCharacterSize(20);
    hp.setPosition(10,10);
    hp.setString("HP: " + std::to_string(p.getHP()));
    hp.setFillColor(sf::Color::White);

    score.setFont(font);
    score.setCharacterSize(20);
    score.setPosition(10,40);
    score.setString("Score: " + std::to_string(p.getScore()));
    score.setFillColor(sf::Color::White);

    instructions.setFont(font);
    instructions.setCharacterSize(16);
    instructions.setFillColor(sf::Color::Green);
    instructions.setPosition(10,70);
    instructions.setString(
        "Controls:\n"
        "A/D or Arrows: Move\n"
        "W/Up/Space: Jump\n"
        "Stomp enemies to defeat them\n"
        "Touching enemies hurts you"
    );
}

void HUD::draw(sf::RenderWindow& w) {
    w.draw(hp);
    w.draw(score);
    w.draw(instructions);
}
