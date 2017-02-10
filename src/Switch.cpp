#include <SFML/Graphics.hpp>
#include "Switch.h"

using namespace sf;

Switch::Switch(Vector2i coords)
{
    this->coords = coords;
}

void Switch::update()
{

}

void Switch::draw(RenderWindow * window)
{
    RectangleShape switchShape;
    switchShape.setSize(Vector2f(40, 40));
    switchShape.setPosition(coords.x * 40, coords.y * 40);
    switchShape.setFillColor(Color(255, 20, 20));
    window->draw(switchShape);
}


float Switch::getPowerForLine(Line * line)
{
    if (portStates[line] == OUTPUT) {
        return powerPerLine;
    }
    else
    {
        return 0;
    }
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

Vector2i Switch::
getCoords()
{
    return coords;
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
