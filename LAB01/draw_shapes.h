#include <cmath>

//
// Created by grzegorz on 09.03.19.
//
#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

float len(float x1 , float x2, float y1, float y2){
    return std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

sf::VertexArray* start_drawing_line(float posX, float posY, sf::Color start, sf::Color end = sf::Color::Transparent){

    if(end == sf::Color::Transparent){
        end = start;
    }

    auto result = new sf::VertexArray(sf::Lines, 2);
    (*result)[0].position = sf::Vector2f(posX, posY - 62);
    (*result)[0].color = start;
    (*result)[1].position = sf::Vector2f(posX, posY);
    (*result)[1].color = end;
    return result;
}

void continue_drawing_line(sf::VertexArray* line, float posX, float posY){
    if( posY <= 62 ) return;
    (*line)[1].position = sf::Vector2f(posX, posY - 62);
}

sf::RectangleShape* start_drawing_rectangle(float posX, float posY, sf::Color border, sf::Color inside = sf::Color::Transparent){
    auto result = new sf::RectangleShape{};
    result->setPosition(sf::Vector2f(posX, posY - 62));
    result->setOutlineColor(border);
    result->setOutlineThickness(3.0f);
    result->setFillColor(inside);
    result->setSize(sf::Vector2f(0.0f, 0.0f));
    return result;
}

void continue_drawing_rectangle(sf::RectangleShape* rectangle, float posX, float posY){
    if( posY <= 62 ) return;
    auto pos = rectangle->getPosition();
    rectangle->setSize(sf::Vector2f(posX - pos.x, posY - 62 - pos.y));
}

sf::CircleShape* start_Drawing_circle(float posX, float posY, sf::Color border){
    auto result = new sf::CircleShape{};
    result->setPosition(posX, posY - 62);
    result->setRadius(0.0f);
    result->setOutlineColor(border);
    result->setFillColor(sf::Color::Transparent);
    result->setOutlineThickness(2.0f);
    return result;
}

void continue_drawing_circle(sf::CircleShape* circle, float posX, float posY){
    if( posY <= 62 ) return;
    auto pos = circle->getPosition();
    posY-= 62;
    static float Y = posY;
    static float X = posX;

    auto r = static_cast<float>(len(pos.x, posX, pos.y, posY) / 2.5);
    sf::Vector2f AB(X - pos.x, Y - pos.y);
    sf::Vector2f AC(posX - pos.x, posY - pos.y);
//    std::cout << "vectors : " << AB.x << " " << AB.y << " " << AC.x << " " << AC.y << " " << pos.x << " " << pos.y << '\n';
//    std::cout << "tan : "<< std::atan2(AB.x, AB.y) - std::atan2(AC.y, AC.x) * 180 / M_PI << '\n';
    circle->setRotation(- static_cast<float>(( std::atan2(AB.y, AB.x) - std::atan2(AC.y, AC.x)) * 180 / M_PI + 45));
    circle->setRadius(r);
//    X = posX;
//    Y = posY;
}

//APP_DRAW_SHAPES_H
