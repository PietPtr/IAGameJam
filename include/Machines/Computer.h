#ifndef COMPUTER_H
#define COMPUTER_H
#pragma once
#include "Audio.h"
#include "Line.h"
#include "Machine.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Line;

class Computer : public Machine
{
    public:
        Computer(Vector2i coords);
        void update(Time dt);
        void draw(RenderWindow* window, std::vector<Texture>* textures);
        void drawSelected(RenderWindow* window, std::vector<Texture>* textures);
        float getPowerForLine(Line* line);
        MachineType getMachineType() { return COMPUTER; }
        bool isOn() { return power >= minimumPower; }
    protected:
};

#endif
