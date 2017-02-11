#ifndef SWITCH_H
#define SWITCH_H
#pragma once
#include "Audio.h"
#include "Line.h"
#include "Connection.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <array>

using namespace sf;

enum SwitchState { ACTIVE, BROKEN };
enum PortState { INPUT, OUTPUT, CLOSED };

class Switch : public Connection
{
    public:
        Switch(Vector2i coords);
        void draw(RenderWindow* window);
        void update();

        float getPowerForLine(Line* line);
        void setPort(int id, PortState newState);
        PortState getPortState(int id);
        Line* getLine(int id);
        /*Returns the state of this switch.*/
        SwitchState getState();
    protected:
    private:
        float calculatePowerPerLine();
        float calculatePower();
        Vector2i coords;
        /*The amount of power it gets from input.*/
        float power;
        /*The amount of power par output line.*/
        float powerPerLine;
        const float MAX_POWER = 40;
        std::map<Line*, PortState> portStates;
        /*The state this switch is currently in.*/
        SwitchState currentState;
};
#endif
