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
    if (line != 0) {
        this->power = line->getPower();
    }
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

    if (power == 0 || broken)
        drawTinyMachine(window, textures, 13);
    else
        drawTinyMachine(window, textures, 12);

    if (broken)
        drawBroken(window, textures);
}

void Computer::drawSelected(RenderWindow* window, std::vector<Texture>* textures)
{

    drawType(window, textures, getMachineType());
    drawPowerStatus(window, textures);
}

float Computer::getPowerForLine(Line* line)
{
    // This machine only pulls power, so to make sure the line does not explode
    // this method always returns 0.
    return 0;
}
