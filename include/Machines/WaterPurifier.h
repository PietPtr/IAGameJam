#ifndef WATERPURIFIER_H
#define WATERPURIFIER_H
#pragma once
#include "Audio.h"
#include "Line.h"
#include "Machine.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Line;

class WaterPurifier : public Machine
{
    public:
        WaterPurifier(Vector2i coords);
        void update(Time dt);
        void draw(RenderWindow* window, std::vector<Texture>* textures);
        void drawSelected(RenderWindow* window, std::vector<Texture>* textures);
        float getPowerForLine(Line* line);
        MachineType getMachineType() { return WATERPURIFIER; }
        bool isOn() { return power > 0; }
    protected:
};

#endif
