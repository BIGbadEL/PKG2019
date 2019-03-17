//
// Created by grzegorz on 15.03.19.
//

#pragma once


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <future>
#include <unistd.h>
#include "Menu.h"
#include "circle.h"
#include "slider.h"


class Window {
public:
    Window() :
            _window(sf::VideoMode(750, 600), "GFK Lab 02", sf::Style::Titlebar | sf::Style::Close) {

        _clock.restart().asMilliseconds();

        _menu.setStrings(0.51f);

        _shapes.push_back(new Circle_hsl(40, 40, 125));
        _shapes.push_back(new Circle_hsv(350, 40, 125));
        _shapes.push_back(new Circle_cmy(50, 320, 125));
        _shapes.push_back(new Circle_rgb(350, 320, 125));

    }

    ~Window() {
        for (auto sh : _shapes) {
            delete sh;
        }
    }

    bool isOpen() const {
        return _window.isOpen();
    }

    void update() {
        _window.clear(sf::Color::White);

         processEvents();

        for (auto shape : _shapes) {
            _window.draw(shape->getToDraw());
        }

        auto temp = _slider.getBar();

        for (auto shape : temp) {
            _window.draw(*shape);
        }

        _window.draw(_slider.getToDraw());
        _window.draw(_menu);
        _window.display();



        processTime();
    }

private:
    void processEvents() {
        while (_window.pollEvent(_events)) {
            if (_events.type == sf::Event::Closed) _window.close();
            if (_events.type == sf::Event::MouseMoved) MouseMovedHandle();
            if (_events.type == sf::Event::MouseButtonPressed) MouseButtonPressedHandle();
            if (_events.type == sf::Event::MouseButtonReleased) _mouseButtonHold = false;
        }
    }

    void MouseMovedHandle(){
        _mouseX = _events.mouseMove.x;
        _mouseY = _events.mouseMove.y;

        if ( _mouseButtonHold && _mouseX >= slider_pos_x && _mouseX <= slider_pos_x + size_x){
            if(_mouseY >= slider_pos_y && _mouseY <= slider_pos_y + size_y){
                float ratio = _slider.new_bar_pos(static_cast<float>(_mouseY));
                for(auto el : _shapes){
                    std::async(std::launch::async, [&el, ratio](){
                        el->update(ratio);
                    });

                }
                _menu.setStrings(ratio);
            }
        }

    }

    void MouseButtonPressedHandle(){
        if (_mouseX >= slider_pos_x && _mouseX <= slider_pos_x + size_x){
            if(_mouseY >= slider_pos_y && _mouseY <= slider_pos_y + size_y){
                float ratio = _slider.new_bar_pos(static_cast<float>(_mouseY));
                for(auto el : _shapes){
                    std::async(std::launch::async, [&el, ratio](){
                        el->update(ratio);
                    });
                }
                _menu.setStrings(ratio);
                _mouseButtonHold = true;
            }
        }
    }

    void processTime() {
        if (_clock.getElapsedTime().asSeconds() >= 1.0f) {
            _menu.setFps(_frame_counter);
            _FPS = static_cast<unsigned int>(( static_cast<float>(_frame_counter) / _clock.getElapsedTime().asSeconds()));
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
    Slider _slider = {};
    int _mouseX = 0;
    int _mouseY = 0;
    std::vector<Circle*> _shapes; // przy optymalizacji przerobić na std::array bo znamy ilość elementów z góry !!
    bool _mouseButtonHold = false;
};

//APP_WINDOW_H
