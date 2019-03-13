//
// Created by grzegorz on 09.03.19.
//

#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "menu.h"
#include "draw_shapes.h"

enum class AppOption {
    none,
    chose_draw_color,
    chose_fill_color,
    draw_line,
    draw_rect,
    draw_whole_rect,
    draw_circle
};

class Window {
public:
    Window() : _window(sf::VideoMode(800, 650), "GFK Lab 01",sf::Style::Titlebar | sf::Style::Close) {
        _window.setFramerateLimit(60);
        _tex.create(793, 534);
        _tex.clear(sf::Color::Black);
    }

    ~Window(){
        for(auto shape : _shapes){
            delete shape;
        }
    }

    void render() {
        procesEvents();
        _window.clear(sf::Color::Black);

        _tex.clear(sf::Color::Black);
        for(auto shape : _shapes){
            _tex.draw(*shape);
        }

        _tex.display();

        sf::Sprite spr(_tex.getTexture());
        spr.setPosition(4.0f, 64.0f);
        _window.draw(_menu);
        _window.draw(spr);
        _window.display();
    }

    bool isOpen() const { return _window.isOpen(); }
private:

    void procesEvents(){
        while (_window.pollEvent(_events))
        {
            if (_events.type == sf::Event::Closed) _window.close();
            if (_events.type == sf::Event::KeyPressed) KeyBoardInputHandle();
            if (_events.type == sf::Event::MouseMoved) MouseMovedHandle();
            if (_events.type == sf::Event::MouseButtonPressed) MouseButtonHandle();
            if (_events.type == sf::Event::MouseButtonReleased) MouseButtonReleasedHandle();
            if (_isDrawing) MouseButtonHoldHandle();
        }
    }

    void MouseMovedHandle(){
        if(_events.mouseMove.x >= 790 || _events.mouseMove.x <= 0) return;
        if(_events.mouseMove.y < 0 || _events.mouseMove.y > 600) return;

        _mouseX = _events.mouseMove.x;
        _mouseY = _events.mouseMove.y;

        _menu.setCurrentMousePosition(std::to_string(_mouseX) + " x " + std::to_string(_mouseY));
    }

    void MouseButtonHoldHandle(){
        if(_mode == AppOption::draw_line){
            continue_drawing_line(dynamic_cast<sf::VertexArray*>(_shapes.back()), _mouseX, _mouseY);
        } else if(_mode == AppOption::draw_rect || _mode == AppOption::draw_whole_rect){
            continue_drawing_rectangle(dynamic_cast<sf::RectangleShape*>(_shapes.back()), _mouseX, _mouseY);
        } else if(_mode == AppOption::draw_circle){
            continue_drawing_circle(dynamic_cast<sf::CircleShape*>(_shapes.back()), _mouseX, _mouseY);
        }
    }

    void MouseButtonHandle(){
        if( _mode == AppOption::chose_draw_color){
            if( _mouseX < 765 && _mouseY < 62){
                _menu.setDrawColor(_mouseX, _mouseY);
            }
        }

        if( _mode == AppOption::chose_fill_color){
            if( _mouseX < 765 && _mouseY < 62){
                _menu.setFillColor(_mouseX, _mouseY);
            }
        }

        if( _mode == AppOption::draw_line){
            if(_mouseY > 62 && _mouseY < 600){
                if(!_isDrawing){
                    _shapes.push_back(start_drawing_line(_mouseX, _mouseY, _menu.getDrawColor(), _menu.getFilingColor()));
                    _isDrawing = true;
                }

            }
        }

        if( _mode == AppOption::draw_rect){
            if(_mouseY > 62 && _mouseY < 600){
                if(!_isDrawing){
                    _shapes.push_back(start_drawing_rectangle(_mouseX, _mouseY, _menu.getDrawColor()));
                    _isDrawing = true;
                }

            }
        }

        if( _mode == AppOption::draw_whole_rect){
            if(_mouseY > 62 && _mouseY < 600){
                if(!_isDrawing){
                    _shapes.push_back(start_drawing_rectangle(_mouseX, _mouseY, _menu.getDrawColor(), _menu.getFilingColor()));
                    _isDrawing = true;
                }

            }
        }

        if( _mode == AppOption::draw_circle){
            if(_mouseY > 62 && _mouseY < 600){
                if(!_isDrawing){
                    _shapes.push_back(start_Drawing_circle(_mouseX, _mouseY, _menu.getDrawColor()));
                    _isDrawing = true;
                }

            }
        }



    }

    void MouseButtonReleasedHandle(){
        _isDrawing = false;
    }

    void KeyBoardInputHandle(){
        sf::Keyboard::Key key_code = _events.key.code;
        if(key_code == sf::Keyboard::Escape) _window.close();

        if(key_code == sf::Keyboard::F){
            _menu.setCurrentState("f");
            _mode = AppOption::chose_draw_color;
        }

        if(key_code == sf::Keyboard::B){
            _menu.setCurrentState("b");
            _mode = AppOption::chose_fill_color;
        }

        if(key_code == sf::Keyboard::L){
            _menu.setCurrentState("l");
            _mode = AppOption::draw_line;
        }

        if(key_code == sf::Keyboard::R){
            _menu.setCurrentState("r");
            _mode = AppOption::draw_rect;
        }

        if(key_code == sf::Keyboard::A){
            _menu.setCurrentState("a");
            _mode = AppOption::draw_whole_rect;
        }

        if(key_code == sf::Keyboard::C){
            _menu.setCurrentState("c");
            _mode = AppOption::draw_circle;
        }

        if(key_code == sf::Keyboard::W){
            _menu.setCurrentState("w");
            _tex.getTexture().copyToImage().saveToFile("shapes.png");
        }

        if(key_code == sf::Keyboard::O){
            _menu.setCurrentState("o");
            if(!_img.loadFromFile("shapes.png")) return;

            while (not _shapes.empty()){
                delete _shapes.back();
                _shapes.pop_back();
            }
            _shapes.push_back(new sf::Sprite(_img));
        }
    }

private:

    sf::RenderWindow _window;
    sf::RenderTexture _tex;
    sf::Event _events = {};
    Menu _menu;
    AppOption _mode = AppOption::none;
    int _mouseX = 0;
    int _mouseY = 0;
    std::vector<sf::Drawable*> _shapes;
    bool _isDrawing = false;
    sf::Texture _img;
};


 //APP_WINDOW_H
