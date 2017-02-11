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
        virtual void update(Time dt) = 0;
        virtual void draw(RenderWindow* window, std::vector<Texture>* textures) = 0;
        virtual void drawSelected(RenderWindow* window, std::vector<Texture>* textures) = 0;
        void setLine(Line* line) { this->line = line; }
    protected:
        Line* line;
};

#endif
