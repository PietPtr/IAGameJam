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
        void draw(RenderWindow* window, std::vector<Texture>* textures);
        void drawSelected(RenderWindow* window, std::vector<Texture>* textures);
        float getPowerForLine(Line* line);
        MachineType getMachineType();
        float getHeatOutput(Time dt) { return HEAT_PRODUCTION_MULTIPLIER * power * dt.asSeconds(); }
        bool isOn() { return power > 0; }
    protected:
    private:
        const float HEAT_PRODUCTION_MULTIPLIER = 0.001;
};

#endif
