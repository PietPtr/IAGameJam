#include <SFML/Graphics.hpp>
#include "Switch.h"

using namespace sf;

Switch::Switch(Vector2i coords)
{
    this->coords = coords;
}

void Switch::draw(RenderWindow * window)
{

}

void Switch::update()
{
}

float Switch::getPowerForLine(Line * line)
{
    //Can be changed later to be affected by the type of line.
    return powerPerLine;
}

void Switch::setPort(int id, PortState newState)
{
    portStates[getLine(id)] = newState;
    powerPerLine = calculatePowerPerLine();
    power = calculatePower();

    if (power > MAX_POWER)
    {
        currentState = BROKEN;
    }
}

PortState Switch::getPortState(int id)
{
    return portStates[getLine(id)];
}

Line * Switch::getLine(int id)
{
    int counter = 0;
    for (std::map<Line*, PortState>::iterator portState = portStates.begin(); portState != portStates.end(); ++portState)
    {
        if (id == counter)
        {
            return portState->first;
        }
        counter += 1;
    }
}

SwitchState Switch::getState()
{
    return currentState;
}

float Switch::calculatePowerPerLine()
{
    int outputs = 0;
    for (std::map<Line*, PortState>::iterator portState = portStates.begin(); portState != portStates.end(); ++portState)
    {
        if (portState->second == OUTPUT)
        {
            outputs += 1;
        }
    }
    return power / outputs;
}

float Switch::calculatePower()
{
    float result = 0;
    for (std::map<Line*, PortState>::iterator portState = portStates.begin(); portState != portStates.end(); ++portState)
    {
        if (portState->second == INPUT)
        {
            result += portState->first->getPower();
        }
    }
    return result;
}
