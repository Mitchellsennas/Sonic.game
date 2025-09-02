Game::Game() : window(sf::VideoMode(World::W, World::H), "Sonic SFML") {
    hud.load();

    // Setup menu
    if (font.loadFromFile("arial.ttf")) {
        menuTitle.setFont(font); menuTitle.setCharacterSize(40); menuTitle.setString("Sonic Game");
        menuTitle.setPosition(250,100);

        menuStart.setFont(font); menuStart.setCharacterSize(30); menuStart.setString("Start Game");
        menuStart.setPosition(300,200);

        menuExit.setFont(font); menuExit.setCharacterSize(30); menuExit.setString("Exit");
        menuExit.setPosition(300,250);

        pauseText.setFont(font); pauseText.setCharacterSize(50);
        pauseText.setString("Game Paused\nPress P to Resume");
        pauseText.setPosition(150,200);
        pauseText.setFillColor(sf::Color::Green);
    }

    // Spawn enemies
    enemies.emplace_back(std::make_unique<MotoBug>(sf::Vector2f(300,420), 200, 600));
    enemies.emplace_back(std::make_unique<BuzzBomber>(sf::Vector2f(500,300), 40, 2, 400, 700));
    enemies.emplace_back(std::make_unique<CrabMeat>(sf::Vector2f(700,420), 50));
}

void Game::run() {
    sf::Clock clk;
    while(window.isOpen()) {
        float dt = clk.restart().asSeconds();
        processEvents();

        if(state == GameState::RUNNING)
            update(dt);

        render();
    }
}

void Game::processEvents() {
    sf::Event e;
    while(window.pollEvent(e)) {
        if(e.type == sf::Event::Closed) window.close();

        if(state == GameState::MENU) handleMenuInput();
        else if(state == GameState::PAUSED) handlePauseInput();
        else if(state == GameState::RUNNING) {
            if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::P)
                state = GameState::PAUSED;
        }
    }
}

void Game::handleMenuInput() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) menuSelection = 0;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) menuSelection = 1;

    // Highlight selection
    menuStart.setFillColor(menuSelection==0 ? sf::Color::Green : sf::Color::White);
    menuExit.setFillColor(menuSelection==1 ? sf::Color::Green : sf::Color::White);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        if(menuSelection==0) state = GameState::RUNNING;
        else window.close();
    }
}

void Game::handlePauseInput() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)) state = GameState::RUNNING;
}

void Game::render() {
    window.clear(sf::Color(135,206,235));

    if(state == GameState::MENU) {
        window.draw(menuTitle);
        window.draw(menuStart);
        window.draw(menuExit);
    }
    else if(state == GameState::RUNNING) {
        world.draw(window);
        player.draw(window);
        for(auto& e:enemies) if(e->alive()) e->draw(window);
        hud.draw(window);
    }
    else if(state == GameState::PAUSED) {
        world.draw(window);
        player.draw(window);
        for(auto& e:enemies) if(e->alive()) e->draw(window);
        hud.draw(window);
        window.draw(pauseText);
    }

    window.display();
}
