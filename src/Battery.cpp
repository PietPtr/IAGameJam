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
    charge -= outPower * dt.asSeconds();


}

void Battery::draw(RenderWindow* window, std::vector<Texture>* textures)
{
    if (selected) {
        drawSelected(window, textures);
    }

    RectangleShape switchShape;
    switchShape.setSize(Vector2f(40, 40));
    switchShape.setPosition(20 + coords.x * 40, 20 + coords.y * 40);
    switchShape.setFillColor(Color(255, 255, 0));
    window->draw(switchShape);
}

void Battery::drawSelected(RenderWindow* window, std::vector<Texture>* textures)
{

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
