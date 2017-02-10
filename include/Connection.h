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
        virtual float calculatePowerParLine() = 0;
    protected:
        float power;
};

#endif
