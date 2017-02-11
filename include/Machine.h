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
    protected:
        float power;
        
};

#endif
