//
// Created by grzegorz on 15.03.19.
//

#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "font.h"

class Menu : public sf::Drawable{
public:
    Menu(){
        font.loadFromMemory(font_data, font_data_size);
        text = new sf::Text;
        text->setFont(font);
        text->setCharacterSize(12);
        text->setFillColor(sf::Color::Black);
    }

    ~Menu() override {
        delete text;
    }

    void outtextxy(sf::RenderTarget& target, float x, float y, const std::string& str) const
    {
        text->setPosition(x, y);
        text->setString(str.c_str());
        target.draw(*text);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        outtextxy(target, 650, 280, _fps + " FPS");
    }

    void setFps(int fps){
        _fps = std::to_string(fps);
    }

private:
    sf::Font font;
    sf::Text *text;
    std::string _fps;
};

 //APP_MENU_H
