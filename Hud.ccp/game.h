#include "Game.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

Game::Game() : window(sf::VideoMode(800, 520), "Sonic SFML") {
    hud.load();

    camera = window.getDefaultView();

    // Load font for menu and pause
    font.loadFromFile("assets/arial.ttf");

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

    level.spawnEnemies(enemies);
}

void Game::run(){
    sf::Clock clk;
    while(window.isOpen()){
        float dt = clk.restart().asSeconds();
        processEvents();

        if(state == GameState::RUNNING) update(dt);
        render();
    }
}

void Game::processEvents(){
    sf::Event e;
    while(window.pollEvent(e)){
        if(e.type == sf::Event::Closed) window.close();

        if(state == GameState::MENU) handleMenuInput();
        else if(state == GameState::PAUSED) handlePauseInput();
        else if(state == GameState::RUNNING){
            if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::P)
                state = GameState::PAUSED;
        }
    }
}

void Game::handleMenuInput(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) menuSelection = 0;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) menuSelection = 1;

    menuStart.setFillColor(menuSelection==0 ? sf::Color::Green : sf::Color::White);
    menuExit.setFillColor(menuSelection==1 ? sf::Color::Green : sf::Color::White);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
        if(menuSelection==0) state = GameState::RUNNING;
        else window.close();
    }
}

void Game::handlePauseInput(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)) state = GameState::RUNNING;
}

void Game::update(float dt){
    player.update(dt);

    for(auto& e: enemies) if(e->alive()) e->update(dt);

    // Collision
    for(auto& e: enemies) if(e->alive()){
        if(player.bounds().intersects(e->bounds())){
            if(player.isDescending()) e->onStomped(player);
            else e->onTouch(player);
        }
    }

    // Camera follows player
    sf::Vector2f center = player.center();
    center.x = std::max(center.x, 400.f); // don't go left of start
    camera.setCenter(center, 260.f);
    window.setView(camera);

    hud.update(player);
}

void Game::render(){
    window.clear(sf::Color(135,206,235));

    if(state == GameState::MENU){
        window.draw(menuTitle);
        window.draw(menuStart);
        window.draw(menuExit);
    } else if(state == GameState::RUNNING){
        level.draw(window);
        player.draw(window);
        for(auto& e: enemies) if(e->alive()) e->draw(window);
        hud.draw(window);
    } else if(state == GameState::PAUSED){
        level.draw(window);
        player.draw(window);
        for(auto& e: enemies) if(e->alive()) e->draw(window);
        hud.draw(window);
        window.draw(pauseText);
    }

    window.display();
}
