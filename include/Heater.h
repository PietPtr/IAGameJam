#ifndef HEATER_H
#define HEATER_H
#pragma once
#include "Audio.h"
#include "Line.h"
#include "Machine.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Line;

class Heater : public Machine
{
    public:
        Heater(Vector2i coords);
        void update(Time dt);
        void draw(RenderWindow* window);
        float getPowerForLine(Line* line);
    protected:
};

#endif
