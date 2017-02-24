#ifndef LINE_H
#define LINE_H
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include "Connection.h"

using namespace sf;

enum Orientation { HORIZONTAL, VERTICAL };
enum LineState { FINE, FRIED };

class Line
{
public:
    Line(Vector2i coords, std::array<Connection*, 2> switches);
    void draw(RenderWindow* window, std::vector<Texture>* textures);
    void update(Time dt);
    float getPower() { return power; }
    Vector2i getCoords() { return coords; }
    void setSelected(bool s) { selected = s; }
    void drawSelected(RenderWindow* window, std::vector<Texture>* textures);
protected:
private:
    Vector2i coords;

    float power = 0;
    const float maxPower = 40;
    bool selected = false;

    LineState currentState = FINE;

    Orientation orientation = VERTICAL;

    std::array<Connection*, 2> connections;


};

#endif // !LINE_H
