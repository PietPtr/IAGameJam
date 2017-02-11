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

void Battery::draw(RenderWindow* window, std::vector<Texture>* textures)
{
	if (selected) {
		drawSelected(window, textures);
	}

	RectangleShape switchShape;
	switchShape.setSize(Vector2f(40, charge / maxPower * 40));
	switchShape.setScale(Vector2f(1, -1));
	switchShape.setPosition(20 + coords.x * 40, 60 + coords.y * 40);
	unsigned int blue = charge / maxPower * 255;
	switchShape.setFillColor(Color(255 - blue, blue, 0));
	window->draw(switchShape);
}

void Battery::drawSelected(RenderWindow* window, std::vector<Texture>* textures)
{

}

float Battery::getPowerForLine(Line* line)
{
	if (line == outputLine && charge > 0) {
		if (charge - outPower <= 0)
		{
			return 0;
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

MachineType Battery::getMachineType()
{
	return BATTERY;
}
