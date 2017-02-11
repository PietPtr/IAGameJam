#include "Line.h"
#include <SFML/Graphics.hpp>
#include "Battery.h"

using namespace sf;

Battery::Battery(Vector2i coords, Line* _line)
{
    this->coords = coords;
    line = _line;
}

void Battery::update(Time dt)
{
    charge += line->getPower() * dt.asSeconds();
    charge -= outPower * dt.asSeconds();

    
}

void Battery::draw(RenderWindow* window)
{
    RectangleShape switchShape;
    switchShape.setSize(Vector2f(40, 40));
    switchShape.setPosition(coords.x * 40, coords.y * 40);
    switchShape.setFillColor(Color(255, 255, 0));
    window->draw(switchShape);
}

float Battery::getPowerForLine(Line* line)
{
    if (line == outputLine) {
        return outPower;
    }
    else
    {
        return 0;
    }
}
