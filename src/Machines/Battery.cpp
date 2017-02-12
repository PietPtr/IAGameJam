#include "Line.h"
#include <SFML/Graphics.hpp>
#include "Machines/Battery.h"

using namespace sf;

Battery::Battery(Vector2i coords)
{
	this->coords = coords;
}

void Battery::update(Time dt)
{
	if (broken)
	{
		outPower = 0;
		power = 0;
	}
	else
	{
		outPower = (-DIFFERENCE/100.0) * (100 - charge / maxCharge * 100) + START_CHARGE;
	}

	charge += line->getPower() * dt.asSeconds();
	if (charge > 0)
	{
		charge -= outPower * dt.asSeconds();
	}
	if (charge < 0)
	{
		charge = 0;
	}

	charge = charge > maxCharge ? maxCharge : charge;
}

void Battery::draw(RenderWindow* window, std::vector<Texture>* textures)
{
	if (selected) {
		drawSelected(window, textures);
	}

	RectangleShape switchShape;
	switchShape.setSize(Vector2f(40, charge / maxCharge * 40));
	switchShape.setScale(Vector2f(1, -1));
	switchShape.setPosition(20 + coords.x * 40, 60 + coords.y * 40);
	unsigned int blue = charge / maxCharge * 255;
	switchShape.setFillColor(Color(255 - blue, blue, 0));
	window->draw(switchShape);

    if (broken)
        drawBroken(window, textures);
}

void Battery::drawSelected(RenderWindow* window, std::vector<Texture>* textures)
{
	drawType(window, textures, getMachineType());


	std::string chargeInfo = "CHARGE: " + floatToString(charge / maxCharge * 100, 1) + " PERCENT";
    drawString(window, chargeInfo, Vector2f(502, 233), &textures->at(0), Color(0, 200, 0), 100);

	std::string outInfo = "OUTPUT: " + floatToString(outPower, 1) + "W";
    drawString(window, outInfo, Vector2f(502, 244), &textures->at(0), Color(0, 200, 0), 100);

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
