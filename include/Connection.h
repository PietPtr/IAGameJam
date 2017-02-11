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
        virtual void update(Time dt) = 0;
        virtual void draw(RenderWindow* window) = 0;
        virtual void drawSelected(RenderWindow* window) = 0;
        Vector2i getCoords() { return coords; }
        float getPower() { return power; }
        void setSelected(bool selected) { this->selected = selected; }
    protected:
        float power;
        Vector2i coords;
        bool selected = false;
};

#endif
