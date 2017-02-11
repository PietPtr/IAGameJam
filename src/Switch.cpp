#include <SFML/Graphics.hpp>
#include "Switch.h"

using namespace sf;

Switch::Switch(Vector2i coords)
{
    this->coords = coords;
}

void Switch::update(Time dt)
{

}

void Switch::draw(RenderWindow * window, std::vector<Texture>* textures)
{
    if (selected) {
        drawSelected(window, textures);
    }

    RectangleShape switchShape;
    switchShape.setSize(Vector2f(40, 40));
    switchShape.setPosition(coords.x * 40 + 20, coords.y * 40 + 20);
    switchShape.setFillColor(Color(255, 20, 20));
    window->draw(switchShape);
}


void Switch::drawSelected(RenderWindow* window, std::vector<Texture>* textures)
{
    // port 0 top
    for (int i = 0; i < 3; i++)
    {
        Sprite buttonSprite;
        buttonSprite.setTexture(textures->at(3 + i));
        if (getPortState(0) == i)
        {
            buttonSprite.setPosition(Vector2f(531 + 34 * i, 45));
        }
        else
        {
            buttonSprite.setPosition(Vector2f(531 + 34 * i, 30));
        }
        window->draw(buttonSprite);
    }

    // port 1 right
    for (int i = 0; i < 3; i++)
    {
        Sprite buttonSprite;
        buttonSprite.setTexture(textures->at(3 + i));
        buttonSprite.setRotation(90);
        if (getPortState(1) == i)
        {
            buttonSprite.setPosition(Vector2f(635, 51 + i * 34));
        }
        else
        {
            buttonSprite.setPosition(Vector2f(650, 51 + i * 34));
        }
        window->draw(buttonSprite);
    }

    // port 2 bottom
    for (int i = 0; i < 3; i++)
    {
        Sprite buttonSprite;
        buttonSprite.setTexture(textures->at(3 + i));
        if (getPortState(2) == i)
        {
            buttonSprite.setPosition(Vector2f(599 - 34 * i, 135));
        }
        else
        {
            buttonSprite.setPosition(Vector2f(599 - 34 * i, 150));
        }
        window->draw(buttonSprite);
    }

    // port 3 left
    for (int i = 0; i < 3; i++)
    {
        Sprite buttonSprite;
        buttonSprite.setTexture(textures->at(3 + i));
        buttonSprite.setRotation(90);
        if (getPortState(3) == i)
        {
            buttonSprite.setPosition(Vector2f(545, 119 - i * 34));
        }
        else
        {
            buttonSprite.setPosition(Vector2f(530, 119 - i * 34));
        }
        window->draw(buttonSprite);
    }


    Sprite switchSprite;
    switchSprite.setTexture(textures->at(2));
    switchSprite.setPosition(Vector2f(500, 20));
    window->draw(switchSprite);
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

void Switch::addLine(Line * line)
{
    if (line != NULL)
    {
        portStates[line] = CLOSED;
    }
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
