#ifndef CONNECTION_H
#define CONNECTION_H
#pragma once
#include "Audio.h"
#include "Line.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Line;

class Connection
{
    public:
        virtual float getPowerForLine(Line* line) = 0;
        Vector2i getCoords() { return coords; }
        float getPower() { return power; }
    protected:
        float power;
        Vector2i coords;
};

#endif
