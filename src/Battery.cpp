#include "Line.h"
#include <SFML/Graphics.hpp>
#include "Battery.h"

using namespace sf;

Battery::Battery(Vector2i coords)
{
    this->coords = coords;
}

void Battery::update(Time dt)
{
    charge += line->getPower() * dt.asSeconds();
    if (charge > 0)
    {
        charge -= outPower * dt.asSeconds();
    }
    if (charge < 0)
    {
        charge = 0;
    }
}

void Battery::draw(RenderWindow* window)
{
    RectangleShape switchShape;
    switchShape.setSize(Vector2f(40, charge / maxPower));
    switchShape.setPosition(20 + coords.x * 40, 20 + coords.y * 40);
    unsigned int redColor = (maxPower / charge) * 255;
    if (redColor > 255)
    {
        redColor = 255;
    }
    switchShape.setFillColor(Color(redColor, 255 - redColor, 0));
    window->draw(switchShape);
}

void Battery::drawSelected(RenderWindow* window)
{

}

float Battery::getPowerForLine(Line* line)
{
    if (line == outputLine && charge > 0) {
        if (charge - outPower <= 0)
        {
            return charge;
        }
        else
        {
            return outPower;
        }
    }
    else
    {
        return 0;
    }
}
