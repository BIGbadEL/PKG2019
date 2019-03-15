//
// Created by grzegorz on 15.03.19.
//

#pragma once


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "circle.h"

class Window {
public:
    Window() :
            _window(sf::VideoMode(750, 600), "GFK Lab 02", sf::Style::Titlebar | sf::Style::Close) {

        _clock.restart().asMilliseconds();

    }

    bool isOpen() const {
        return _window.isOpen();
    }

    void update() {
        _window.clear(sf::Color::White);
        processEvents();
        _window.draw(_menu);
        _window.display();
        processTime();
    }

private:

    void processEvents() {
        while (_window.pollEvent(_events)) {
            if (_events.type == sf::Event::Closed) _window.close();
        }
    }

    void processTime() {
        if (_clock.getElapsedTime().asSeconds() >= 1.0f) {
            _menu.setFps(_frame_counter);
            _FPS = (unsigned int) ((float) _frame_counter / _clock.getElapsedTime().asSeconds());
            _clock.restart();
            _frame_counter = 0;
        }
        _frame_counter++;

//        float frames = 1.0f / _clock.getElapsedTime().asSeconds();
//        _menu.setFps(static_cast<int>(frames));
//        _clock.restart();
    }

private:

    sf::RenderWindow _window;
    sf::Event _events = { };
    Menu _menu = { };
    sf::Clock _clock = { };
    unsigned int _FPS = 0;
    unsigned int _frame_counter = 0;
    std::vector<Circle*> _shapes; // przy optymalizacji przerobić na std::array bo znamy ilość elementów z góry !!
};

//APP_WINDOW_H
