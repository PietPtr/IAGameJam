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
        void drawSelected(RenderWindow* window);
        float getPowerForLine(Line* line);
        void setOutputLine(Line* line) { outputLine = line; };
    protected:
    private:
        Line* outputLine;
        /*Current charge of this battery.*/
        float charge = 500;
        /*Loses 5 power per second.*/
        float outPower = 5;
        float maxPower = 750;
};

#endif
