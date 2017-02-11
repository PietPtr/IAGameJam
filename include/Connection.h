#ifndef CONNECTION_H
#define CONNECTION_H
#pragma once
#include "Audio.h"
#include "Line.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Connection
{
    public:
    protected:
        virtual float calculatePowerPerLine() = 0;
        float power;
};

#endif
