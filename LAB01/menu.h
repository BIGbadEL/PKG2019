#include <utility>

//
// Created by grzegorz on 09.03.19.
//

#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "font.h"



class Menu : public sf::Drawable
{
private:
    sf::Font font;
    sf::Text *text;
    sf::RectangleShape *rectangle;
    std::string current_key_state = "";
    std::string current_mouse_pos = "";

    sf::RectangleShape *drawColor;
    sf::Color drawingColor = sf::Color::Transparent;
    sf::RectangleShape *fillColor;
    sf::Color fillingColor = sf::Color::Transparent;

    sf::Texture *colors_texture;
    sf::Sprite *colors_sprite;
    sf::Uint8 *colors_pixels;
    const unsigned int colors_size_x = 765;
    const unsigned int colors_size_y = 60;
    inline void draw_to_color_pixels(unsigned int x, unsigned int y,unsigned char r, unsigned char g, unsigned char b)
    {
        colors_pixels[4 * (y * colors_size_x + x) + 0] = r;
        colors_pixels[4 * (y * colors_size_x + x) + 1] = g;
        colors_pixels[4 * (y * colors_size_x + x) + 2] = b;
        colors_pixels[4 * (y * colors_size_x + x) + 3] = 255;
    }

public:
    Menu()
    {
        font.loadFromMemory(font_data, font_data_size);
        text = new sf::Text;
        text->setFont(font);
        text->setCharacterSize(12);
        text->setFillColor(sf::Color::White);

        rectangle = new sf::RectangleShape(sf::Vector2f(796, 536));
        rectangle->setFillColor(sf::Color::Transparent);
        rectangle->setOutlineColor(sf::Color::White);
        rectangle->setOutlineThickness(1.0f);
        rectangle->setPosition(2, 62);

        unsigned int x, y;
        colors_pixels = new sf::Uint8[colors_size_x * colors_size_y * 4];
        for (x = 0; x<255; x++)
            for (y = 0; y < 30; y++)
            {
                draw_to_color_pixels(x, y, static_cast<unsigned char>(x), 255, 0);
                draw_to_color_pixels(x+255, y, 255, static_cast<unsigned char>(255 - x), 0);
                draw_to_color_pixels(x + 510, y, 255, 0, static_cast<unsigned char>(x));
                draw_to_color_pixels(254 - x, y + 30, 0, 255, static_cast<unsigned char>(255 - x));
                draw_to_color_pixels(509 - x, y + 30, 0, static_cast<unsigned char>(x), 255 );
                draw_to_color_pixels(764 - x, y + 30, static_cast<unsigned char>(255 - x), 0, 255);
            }

        colors_texture = new sf::Texture();
        colors_texture->create(colors_size_x, colors_size_y);
        colors_texture->update(colors_pixels);

        drawColor = new sf::RectangleShape(sf::Vector2f(30, 30));
        drawColor->setFillColor(drawingColor);
        drawColor->setOutlineColor(drawingColor);
        drawColor->setPosition(768.0f, 1.0f);

        fillColor = new sf::RectangleShape(sf::Vector2f(30, 30));
        fillColor->setFillColor(fillingColor);
        fillColor->setOutlineColor(fillingColor);
        fillColor->setPosition(768.0f, 31.0f);

        colors_sprite = new sf::Sprite();
        colors_sprite->setTexture(*colors_texture);
        colors_sprite->setPosition(1, 1);
    }

    ~Menu() {
        delete[] colors_pixels;
        delete colors_sprite;
        delete drawColor;
        delete fillColor;
        delete text;
        delete rectangle;
        delete colors_texture;
    }

    void setCurrentState(std::string new_state){
        current_key_state = std::move(new_state);
    }

    void setCurrentMousePosition(std::string new_pos){
        current_mouse_pos = std::move(new_pos);
    }

    void outtextxy(sf::RenderTarget& target, float x, float y, wchar_t *str) const
    {
        text->setPosition(x, y);
        text->setString(str);
        target.draw(*text);
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        std::wstring state = std::wstring(current_key_state.begin(), current_key_state.end());

        std::wstring mouse_pos = std::wstring(current_mouse_pos.begin(), current_mouse_pos.end());
        outtextxy(target,5, 600, L"f - wybor koloru rysowania");
        outtextxy(target, 5, 615, L"b - wybor koloru wypelniania");
        outtextxy(target, 5, 630, L"l - rysowanie linii");

        outtextxy(target, 200, 600, L"r - rysowanie prostokata");
        outtextxy(target, 200, 615, L"a - rysowanie wypelnionego prostokata");
        outtextxy(target, 200, 630, L"c - rysowanie okregu");

        outtextxy(target, 470, 600, L"w - zapis do pliku");
        outtextxy(target, 470, 615, L"o - odczyt z pliku");
        outtextxy(target, 470, 630, L"esc - wyjacie");

        outtextxy(target, 620, 615, L"Aktualne:");
        outtextxy(target, 695, 615, const_cast<wchar_t*>(state.c_str()));
        outtextxy(target, 620, 630, L"Poz. kursora: " );
        outtextxy(target, 700, 630, const_cast<wchar_t*>(mouse_pos.c_str()));

        target.draw(*rectangle);
        target.draw(*fillColor);
        target.draw(*drawColor);
        target.draw(*colors_sprite);
    }

    void setDrawColor(int x, int y) {
        const int index = (x + colors_size_x * y) * 4;
        drawingColor = sf::Color(colors_pixels[index + 0], colors_pixels[index + 1], colors_pixels[index + 2]);
        drawColor->setFillColor(drawingColor);
        drawColor->setOutlineColor(drawingColor);
    }

    void setFillColor(int x, int y) {
        const int index = (x + colors_size_x * y) * 4;
        fillingColor = sf::Color(colors_pixels[index + 0], colors_pixels[index + 1], colors_pixels[index + 2]);
        fillColor->setFillColor(fillingColor);
        fillColor->setOutlineColor(fillingColor);
    }

    sf::Color getDrawColor() const {
        return drawingColor;
    }

    sf::Color getFilingColor() const {
        return fillingColor;
    }

};




//APP_MENU_H
