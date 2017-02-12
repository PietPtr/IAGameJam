#ifndef LIGHT_H
#define LIGHT_H
#pragma once
#include "Audio.h"
#include "Line.h"
#include "Machine.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Line;

class Light : public Machine
{
    public:
        Light(Vector2i coords);
        void update(Time dt);
        void draw(RenderWindow* window, std::vector<Texture>* textures);
        void drawSelected(RenderWindow* window, std::vector<Texture>* textures);
        float getPowerForLine(Line* line);
        MachineType getMachineType() { return LIGHT; }
        bool isOn() { return power > 0; }
    protected:
};

#endif
