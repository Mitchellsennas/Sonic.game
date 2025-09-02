enum class GameState { MENU, RUNNING, PAUSED, GAME_OVER };

class Game {
public:
    Game();
    void run();
private:
    void update(float dt);
    void render();
    void processEvents();
    void handleMenuInput();
    void handlePauseInput();

    GameState state = GameState::MENU;  // Track current state

    // Menu texts
    sf::Text menuTitle;
    sf::Text menuStart;
    sf::Text menuExit;
    int menuSelection = 0; // 0 = Start, 1 = Exit

    // Pause text
    sf::Text pauseText;
};
