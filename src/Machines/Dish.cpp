#include "Line.h"
#include <SFML/Graphics.hpp>
#include "Machines/Dish.h"

using namespace sf;

Dish::Dish(Vector2i coords)
{
    this->coords = coords;
}

void Dish::update(Time dt)
{

}

void Dish::draw(RenderWindow* window, std::vector<Texture>* textures)
{
    if (selected) {
        drawSelected(window, textures);
    }

    RectangleShape switchShape;
    switchShape.setSize(Vector2f(40, 40));
    switchShape.setPosition(20 + coords.x * 40, 20 + coords.y * 40);
    switchShape.setFillColor(Color(255, 255, 255));
    window->draw(switchShape);
}

void Dish::drawSelected(RenderWindow* window, std::vector<Texture>* textures)
{

}

float Dish::getPowerForLine(Line* line)
{
    // This machine only pulls power, so to make sure the line does not explode
    // this method always returns 0.
    return 0;
}
