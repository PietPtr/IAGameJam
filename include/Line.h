#ifndef LINE_H
#define LINE_H
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include "Connection.h"

using namespace sf;

enum Orientation { HORIZONTAL, VERTICAL };

class Line
{
public:
    Line(Vector2i coords, std::array<Connection*, 2> switches);
    void draw(RenderWindow* window);
    void update(Time dt);
    float getPower() { return power; }
    Vector2i getCoords() { return coords; };
protected:
private:
    Vector2i coords;

    float power = 0;
    const float MAX_POWER = 40;

    Orientation orientation = VERTICAL;

    std::array<Connection*, 2> connections;


};

#endif // !LINE_H
