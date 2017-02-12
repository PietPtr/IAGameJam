#ifndef MACHINE_H
#define MACHINE_H
#pragma once
#include "Audio.h"
#include "Line.h"
#include "Connection.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Line;

enum MachineType { HEATER, SOLARPANEL, BATTERY, WATERPURIFIER, CO2REMOVER, COMPUTER, DISH, LIGHT };

class Machine : public Connection
{
    public:
        virtual float getPowerForLine(Line* line) = 0;
        virtual void update(Time dt) = 0;
        virtual void draw(RenderWindow* window, std::vector<Texture>* textures) = 0;
        virtual void drawSelected(RenderWindow* window, std::vector<Texture>* textures) = 0;
        virtual MachineType getMachineType() = 0;
        void setLine(Line* line) { this->line = line; }
        void drawType(RenderWindow* window, std::vector<Texture>* textures, MachineType type);
        void drawBroken(RenderWindow* window, std::vector<Texture>* textures);
        void setBroken(bool broken) { this->broken = broken; power = 0; }
        bool isBroken() { return broken; }
        void drawTinyMachine(RenderWindow* window, std::vector<Texture>* textures, int texture);
    protected:
        Line* line;
        bool broken = false;
};

#endif
