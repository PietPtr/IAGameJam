#ifndef CONNECTION_H
#define CONNECTION_H
#pragma once
#include "Audio.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Line;

int drawString(RenderWindow* window, std::string text, Vector2f position, Texture* fontTexture, Color color, int newLine);
std::string floatToString(float value, int precision);

class Connection
{
    public:
        virtual float getPowerForLine(Line* line) = 0;
        virtual void update(Time dt) = 0;
        virtual void draw(RenderWindow* window, std::vector<Texture>* textures) = 0;
        virtual void drawSelected(RenderWindow* window, std::vector<Texture>* textures) = 0;
        Vector2i getCoords() { return coords; }
        float getPower() { return power; }
        void setSelected(bool selected) { this->selected = selected; }
        void drawPowerStatus(RenderWindow* window, std::vector<Texture>* textures);
    protected:

        float power = 0;
        Vector2i coords;
        bool selected = false;
};

#endif
