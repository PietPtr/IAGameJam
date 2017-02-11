#ifndef MACHINE_H
#define MACHINE_H
#pragma once
#include "Audio.h"
#include "Line.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Line;

class Machine : public Connection
{
    public:
        virtual float getPowerForLine(Line* line) = 0;
        virtual void update() = 0;
        virtual void draw(RenderWindow* window) = 0;
    protected:
        Line* line;
};

#endif
