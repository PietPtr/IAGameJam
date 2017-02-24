#ifndef CO2REMOVER_H
#define CO2REMOVER_H
#pragma once
#include "Audio.h"
#include "Line.h"
#include "Machine.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Line;

class CO2Remover : public Machine
{
    public:
        CO2Remover(Vector2i coords);
        void update(Time dt);
        void draw(RenderWindow* window, std::vector<Texture>* textures);
        void drawSelected(RenderWindow* window, std::vector<Texture>* textures);
        float getPowerForLine(Line* line);
        MachineType getMachineType() { return CO2REMOVER; }
        float getRemovedCO2(Time dt) { return CO2REMOVER_SPEED * power * dt.asSeconds(); }
        bool isOn() { return power > 0; }
    protected:
    private:
        // multiplied with power supplied.
        const float CO2REMOVER_SPEED = 0.4; // ppm CO2 per second per watt
};

#endif
