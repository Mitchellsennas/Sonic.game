class HUD {
    sf::Font font;
    sf::Text hp, score, instructions; // texts
public:
    bool load();
    void update(const Player& p);
    void draw(sf::RenderWindow& w);
};
