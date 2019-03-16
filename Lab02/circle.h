#include <cmath>

#include <cmath>

//
// Created by grzegorz on 15.03.19.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "colors.h"


class Circle {
public:
    Circle(float x, float y, float r) :
            _circle(new sf::CircleShape) {
        _circle->setPosition(x, y);
        _circle->setRadius(r);
        _circle->setOutlineThickness(10);
    }

    virtual ~Circle() {
        delete _circle;
    }

    sf::CircleShape& getToDraw() {
        return *_circle;
    }

    virtual void update(float l) = 0;

protected:
    sf::CircleShape* _circle{ };
};

class Circle_hsl : public Circle {
public:
    Circle_hsl(float x, float y, float r) :
            Circle(x, y, r), _texture(new sf::Texture), _pixels(new sf::Uint8[colors_size_y * colors_size_x * 4]) {
        float h, radius;
        HSL color1 = { };
        for (int i = -125; i < colors_size_x - 125; i++) {
            for (int j = -125; j < colors_size_y - 125; j++) {
                radius = std::sqrt(static_cast<float > (i * i + j * j));
                h = fmodf(atan2f(static_cast<float >(j), static_cast<float >(i)) * 180.0f / static_cast<float>(M_PI) +
                          180.0f, 360.0f);
                if (radius <= 125) {
                    color1.H = h;
                    color1.S = radius * 0.008f;
                    color1.L = _l;

                    _colors.push_back(color1);

                    draw_to_color_pixels(125 - i, 125 + j, convert(color1), _pixels, colors_size_x);
                }
            }
        }


        _texture->create(colors_size_x, colors_size_y);
        _texture->update(_pixels);

        _circle->setTexture(_texture);
    }

    ~Circle_hsl() override {
        delete _texture;
        delete[] _pixels;
    }

    void update(float l) override {
        if (std::fabs(l - _l) < 0.03f) return;
        _l = l;
        unsigned long x = 0;

        for (int i = -125; i < colors_size_x - 125; i++) {
            for (int j = -125; j < colors_size_y - 125; j++) {
                if (j * j + i * i <= 125 * 125) {
                    _colors.at(x).L = _l;
                    draw_to_color_pixels(125 - i, 125 + j, convert(_colors.at(x)), _pixels, colors_size_x);
                    ++x;
                }
            }
        }

        _texture->update(_pixels);

    }

private:
    sf::Texture* _texture;
    sf::Uint8* _pixels;
    float _l = 0.51f;
    std::vector<HSL> _colors;
};

class Circle_hsv : public Circle {
public:
    Circle_hsv(float x, float y, float r) :
            Circle(x, y, r), _texture(new sf::Texture), _pixels(new sf::Uint8[colors_size_y * colors_size_x * 4]) {
        float h, radius;
        HSV color1 = { };
        for (int i = -125; i < colors_size_x - 125; i++) {
            for (int j = -125; j < colors_size_y - 125; j++) {
                radius = std::sqrt(static_cast<float > (i * i + j * j));
                h = fmodf(atan2f(static_cast<float >(j), static_cast<float >(i)) * 180.0f / static_cast<float>(M_PI) +
                          180.0f, 360.0f);
                if (radius <= 125) {
                    color1.H = h / 360.0f;
                    color1.S = radius * 0.008f;
                    color1.V = _l;

                    _colors.push_back(color1);

                    draw_to_color_pixels(125 - i, 125 + j, convert(color1), _pixels, colors_size_x);
                }
            }
        }


        _texture->create(colors_size_x, colors_size_y);
        _texture->update(_pixels);

        _circle->setTexture(_texture);
    }

    ~Circle_hsv() override {
        delete _texture;
        delete[] _pixels;
    }

    void update(float l) override {
        if (std::fabs(l - _l) < 0.03f) return;
        _l = l;
        unsigned long x = 0;

        for (int i = -125; i < colors_size_x - 125; i++) {
            for (int j = -125; j < colors_size_y - 125; j++) {
                if (i * i + j * j <= 125 * 125) {
                    _colors.at(x).V = l;
                    draw_to_color_pixels(125 - i, 125 + j, convert(_colors.at(x)), _pixels, colors_size_x);
                    ++x;
                }
            }
        }

        _texture->update(_pixels);

    }

private:
    sf::Texture* _texture;
    sf::Uint8* _pixels;
    float _l = 0.51f;
    std::vector<HSV> _colors;
};

class Circle_cmy : public Circle {
public:
    Circle_cmy(float x, float y, float r) :
            Circle(x, y, r), _texture(new sf::Texture), _pixels(new sf::Uint8[colors_size_y * colors_size_x * 4]) {
        float h, radius;
        CMY color1 = { };
        for (int i = -125; i < colors_size_x - 125; i++) {
            for (int j = -125; j < colors_size_y - 125; j++) {
                radius = std::sqrt(static_cast<float > (i * i + j * j));
                h = fmodf(atan2f(static_cast<float >(j), static_cast<float >(i)) * 180.0f / static_cast<float>(M_PI) +
                          180.0f, 360.0f);
                if (radius <= 125) {
                    color1.C = radius * 0.008f;
                    color1.M = h / 360.0f;
                    color1.Y = _l;

                    draw_to_color_pixels(125 - i, 125 + j, convert(color1), _pixels, colors_size_x);
                }
            }
        }


        _texture->create(colors_size_x, colors_size_y);
        _texture->update(_pixels);

        _circle->setTexture(_texture);
    }

    ~Circle_cmy() override {
        delete _texture;
        delete[] _pixels;
    }

    void update(float l) override {
        if (std::fabs(l - _l) < 0.03f) return;
        _l = l;

        for (int i = -125; i < colors_size_x - 125; i++) {
            for (int j = -125; j < colors_size_y - 125; j++) {
                if (i * i + j * j <= 125 * 125) {

//                    draw_to_color_pixels(125 - i, 125 + j, convert(color1), _pixels, colors_size_x);
                    _pixels[4 * (( j + 125 ) * colors_size_x + 125 - i ) + 2] = static_cast<sf::Uint8>(( 1.0f - _l ) *
                                                                                                       255.0f);
                }
            }
        }

        _texture->update(_pixels);

    }

private:
    sf::Texture* _texture;
    sf::Uint8* _pixels;
    float _l = 0.51f;

};

class Circle_rgb : public Circle {
public:
    Circle_rgb(float x, float y, float r) :
            Circle(x, y, r), _texture(new sf::Texture), _pixels(new sf::Uint8[colors_size_y * colors_size_x * 4]) {
        float h, radius;
        RGB color1 = { };
        for (int i = -125; i < colors_size_x - 125; i++) {
            for (int j = -125; j < colors_size_y - 125; j++) {
                radius = std::sqrt(static_cast<float > (i * i + j * j));
                h = fmodf(atan2f(static_cast<float >(j), static_cast<float >(i)) * 180.0f / static_cast<float>(M_PI) +
                          180.0f, 360.0f);
                if (radius <= 125) {
                    color1.R = radius * 0.008f * 255.0f;
                    color1.G = h / 360.0f * 255.0f;
                    color1.B = _l * 255.0f;

                    draw_to_color_pixels(125 - i, 125 + j, color1, _pixels, colors_size_x);
                }
            }
        }


        _texture->create(colors_size_x, colors_size_y);
        _texture->update(_pixels);

        _circle->setTexture(_texture);
    }

    ~Circle_rgb() override {
        delete _texture;
        delete[] _pixels;
    }

    void update(float l) override {
        if (std::fabs(l - _l) < 0.03f) return;
        _l = l;

        for (int i = -125; i < colors_size_x - 125; i++) {
            for (int j = -125; j < colors_size_y - 125; j++) {
                if (i * i + j * j <= 125 * 125) {

//                    draw_to_color_pixels(125 - i, 125 + j, color1, _pixels, colors_size_x);
                    _pixels[4 * (( j + 125 ) * colors_size_x + 125 - i ) + 2] = static_cast<sf::Uint8>(_l * 255.0f);
                }
            }
        }

        _texture->update(_pixels);

    }

private:
    sf::Texture* _texture;
    sf::Uint8* _pixels;
    float _l = 0.51f;
};

//APP_CIRCLE_H
