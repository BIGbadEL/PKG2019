//
// Created by grzegorz on 15.03.19.
//

#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "font.h"

class Menu : public sf::Drawable {
public:
    Menu() {
        font.loadFromMemory(font_data, font_data_size);
        text = new sf::Text;
        text->setFont(font);
        text->setCharacterSize(12);
        text->setFillColor(sf::Color::Black);
    }

    ~Menu() override {
        delete text;
    }

    void outtextxy(sf::RenderTarget& target, float x, float y, const std::string& str) const {
        text->setPosition(x, y);
        text->setString(str.c_str());
        target.draw(*text);
    }

    void draw(sf::RenderTarget& target, [[maybe_unused]]  sf::RenderStates states) const override {
        outtextxy(target, 650, 280, _fps + " FPS");
        outtextxy(target, 40, 40, "HSL");
        outtextxy(target, 290, 290, "L = " + _L);
        outtextxy(target, 350, 40, "HSV");
        outtextxy(target, 600, 290, "V = " + _L);
        outtextxy(target, 50, 320, "CMY");
        outtextxy(target, 300, 570, "Y = " + _Y + " %");
        outtextxy(target, 350,320, "RGB");
        outtextxy(target, 600, 570, "B = " + _B);
    }

    void setFps(unsigned int fps) {
        _fps = std::to_string(fps);
    }

    void setStrings(float l){
        _L = std::to_string(l);
        _B = std::to_string(static_cast<int>(l * 255));
        _Y = std::to_string(static_cast<int>(l * 100));
    }

private:
    sf::Font font;
    sf::Text* text;
    std::string _fps;
    std::string _L;
    std::string _B;
    std::string _Y;
};

//APP_MENU_H
