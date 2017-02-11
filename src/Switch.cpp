#include <SFML/Graphics.hpp>
#include "Switch.h"

using namespace sf;

Switch::Switch(Vector2i coords)
{
    this->coords = coords;

    for (int i = 0; i < 3; i++)
    {
        IntRect rect(531 + 34 * i, 30, 30, 20);
        buttonRectangles[i] = rect;
    }

    for (int i = 0; i < 3; i++)
    {
        IntRect rect(630, 51 + i * 34, 20, 30);
        buttonRectangles[3 + i] = rect;
    }

    for (int i = 0; i < 3; i++)
    {
        IntRect rect(599 - 34 * i, 150, 30, 20);
        buttonRectangles[6 + i] = rect;
    }

    for (int i = 0; i < 3; i++)
    {
        IntRect rect(510, 119 - i * 34, 20, 30);
        buttonRectangles[9 + i] = rect;
    }
}

void Switch::update(Time dt)
{

}

void Switch::draw(RenderWindow * window, std::vector<Texture>* textures)
{
    // click detection in draw should be in update. I need window though.
    if (selected && Mouse::isButtonPressed(Mouse::Left))
    {
        for (int i = 0; i < buttonRectangles.size(); i++)
        {
            if (buttonRectangles[i].contains(Mouse::getPosition(*window)))
            {
                setPort((int)(i / 3), (PortState)(i % 3));
            }
        }
    }

    if (selected)
    {
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
            buttonSprite.setPosition(Vector2f(buttonRectangles[i].left,
                                              buttonRectangles[i].top + 15));
        }
        else
        {
            buttonSprite.setPosition(Vector2f(buttonRectangles[i].left,
                                              buttonRectangles[i].top));
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
            buttonSprite.setPosition(Vector2f(buttonRectangles[3+i].left + 5,
                                              buttonRectangles[3+i].top));
        }
        else
        {
            buttonSprite.setPosition(Vector2f(buttonRectangles[3+i].left + 20,
                                              buttonRectangles[3+i].top));
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
            buttonSprite.setPosition(Vector2f(buttonRectangles[6+i].left,
                                              buttonRectangles[6+i].top - 15));
        }
        else
        {
            buttonSprite.setPosition(Vector2f(buttonRectangles[6+i].left,
                                              buttonRectangles[6+i].top));
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
            buttonSprite.setPosition(Vector2f(buttonRectangles[9+i].left + 35,
                                              buttonRectangles[9+i].top));
        }
        else
        {
            buttonSprite.setPosition(Vector2f(buttonRectangles[9+i].left + 20,
                                              buttonRectangles[9+i].top));
        }
        window->draw(buttonSprite);
    }


    Sprite switchSprite;
    switchSprite.setTexture(textures->at(2));
    switchSprite.setPosition(Vector2f(500, 20));
    window->draw(switchSprite);

    for (int i = 0; i < 12; i++)
    {
        RectangleShape test(Vector2f(buttonRectangles[i].width,
                                     buttonRectangles[i].height));
        test.setFillColor(Color(255, 255, 0, 100));
        test.setPosition(Vector2f(buttonRectangles[i].left, buttonRectangles[i].top));
        window->draw(test);
    }
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
    std::cout << "setting port id=" << id << " to state " << newState << "\n";

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
