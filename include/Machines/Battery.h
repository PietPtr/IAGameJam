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
        void draw(RenderWindow* window, std::vector<Texture>* textures);
        void drawSelected(RenderWindow* window, std::vector<Texture>* textures);
        float getPowerForLine(Line* line);
        void setOutputLine(Line* line) { outputLine = line; };
        MachineType getMachineType();
    protected:
    private:
        Line* outputLine;
        /*Current charge of this battery.*/
        float charge = 50000;
        /*Loses 5 power per second.*/
        float outPower = 10;
        float maxPower = 75000;
};

#endif
