#ifndef BATTERY_H
#define BATTERY_H
#pragma once
#include "Audio.h"
#include "Line.h"
#include "Machine.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Line;

class Battery : public Machine
{
    public:
        Battery(Vector2i coords);
        void update(Time dt);
        void draw(RenderWindow* window);
        float getPowerForLine(Line* line);
        void setOutputLine(Line* line) { outputLine = line; };
    protected:
    private:
        Line* outputLine;
        float charge;
        float outPower = 5;
};

#endif
