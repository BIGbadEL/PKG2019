//
// Created by grzegorz on 15.03.19.
//

#pragma once

#include <SFML/Graphics.hpp>

class Circle {
public:
    Circle (float x, float y, float r): _circle(new sf::CircleShape), _texture(){

        _circle = {};
        _circle->setPosition(x, y);
        _circle->setRadius(r);
//        _circle->setTexture(_texture);
        _circle->setFillColor(sf::Color::Black);
    }

    sf::CircleShape* getToDraw() {
        return _circle;
    }

private:
    sf::CircleShape* _circle{ };
    sf::Texture* _texture{ };
};

 //APP_CIRCLE_H
