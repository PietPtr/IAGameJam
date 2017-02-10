#ifndef SWITCH_H
#define SWITCH_H
#include "Audio.h"
#include "Line.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <array>

using namespace sf;

class Switch
{
    public:
        Switch(Vector2i coords);
        void draw(RenderWindow* window);
        void update();
        float getPowerForLine(Line* line); // loop through lines, compare pointers, return power for that line.
    protected:
    private:
        Vector2i coords;
        float power;
        const float MAX_POWER = 40;
        std::array<Line*, 4> lines;
};
#endif