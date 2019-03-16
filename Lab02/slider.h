//
// Created by grzegorz on 16.03.19.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include "colors.h"


#define size_x 38
#define size_y 256

#define slider_pos_x 660
#define slider_pos_y 20

class Slider {
public:
    Slider() {
        _rec->setPosition(660, 20);
        _rec->setSize(sf::Vector2f(size_x, size_y));
        _rec->setOutlineColor(sf::Color::Black);
        _rec->setOutlineThickness(1.0);

        RGB color = {};

        for(int i = 0; i < size_x; ++i){
            for(int j = 0; j < size_y; ++j){
                color.R = static_cast<float>(j);
                color.G = static_cast<float>(j);
                color.B = static_cast<float>(j);
                draw_to_color_pixels(i, j, color, _pixels, size_x);
            }
        }

        _texture->create(size_x, size_y);
        _texture->update(_pixels);
        _rec->setTexture(_texture);

        _bar[0] = new sf::VertexArray(sf::Lines, 2);
        (*_bar[0])[0].position = sf::Vector2f(645, _barPos);
        (*_bar[0])[0].color = sf::Color::Black;
        (*_bar[0])[1].position = sf::Vector2f(655, _barPos);
        (*_bar[0])[1].color = sf::Color::Black;


        _bar[1] = new sf::VertexArray(sf::Lines, 2);
        (*_bar[1])[0].position = sf::Vector2f(660 + 38 + 5, _barPos);
        (*_bar[1])[0].color = sf::Color::Black;
        (*_bar[1])[1].position = sf::Vector2f(660 + 38 + 5 + 10, _barPos);
        (*_bar[1])[1].color = sf::Color::Black;

    }

    ~Slider() {
        delete _rec;
        delete _texture;
        delete[] _pixels;

        for( auto el : _bar){
            delete el;
        }
    }

    sf::RectangleShape& getToDraw() const {
        return *_rec;
    }

    const std::array<sf::VertexArray*, 2>& getBar() const {
        return _bar;
    }

    float new_bar_pos(float pos){
        _barPos = pos;
        (*_bar[0])[0].position = sf::Vector2f(645, _barPos);
        (*_bar[0])[1].position = sf::Vector2f(655, _barPos);

        (*_bar[1])[0].position = sf::Vector2f(660 + 38 + 5, _barPos);
        (*_bar[1])[1].position = sf::Vector2f(660 + 38 + 5 + 10, _barPos);

        return (_barPos - 20) / size_y;

    }

private:
    sf::RectangleShape* _rec = new sf::RectangleShape;
    sf::Texture* _texture = new sf::Texture;
    sf::Uint8* _pixels = new sf::Uint8[size_x * size_y * 4];
    std::array<sf::VertexArray*, 2> _bar;
    float _barPos = 20 + size_y * 0.51f;
};


//APP_SLIDER_H
