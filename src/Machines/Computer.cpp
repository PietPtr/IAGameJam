#include "Line.h"
#include <SFML/Graphics.hpp>
#include "Machines/Computer.h"

using namespace sf;

Computer::Computer(Vector2i coords)
{
    this->coords = coords;
}

void Computer::update(Time dt)
{

}

void Computer::draw(RenderWindow* window, std::vector<Texture>* textures)
{
    if (selected) {
        drawSelected(window, textures);
    }

    RectangleShape switchShape;
    switchShape.setSize(Vector2f(40, 40));
    switchShape.setPosition(20 + coords.x * 40, 20 + coords.y * 40);
    switchShape.setFillColor(Color(0, 255, 0));
    window->draw(switchShape);
}

void Computer::drawSelected(RenderWindow* window, std::vector<Texture>* textures)
{

}

float Computer::getPowerForLine(Line* line)
{
    // This machine only pulls power, so to make sure the line does not explode
    // this method always returns 0.
    return 0;
}
