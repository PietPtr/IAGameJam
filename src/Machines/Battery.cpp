#include "Line.h"
#include <SFML/Graphics.hpp>
#include "Machines/Battery.h"
#include "Game.h"

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
		outPower = (-DIFFERENCE/100.0) * (100 - charge / maxCharge * 100) +
			(START_CHARGE - powerDampening);
	}
	outPower = outPower < 0 ? 0 : outPower;
    outPower = outPower > 40 ? 40 : outPower;

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
    if (selected && Mouse::isButtonPressed(Mouse::Left))
    {
        if (increaseButton.contains(Mouse::getPosition(*window)))
        {
            powerDampening -= 0.1;

        }
        if (decreaseButton.contains(Mouse::getPosition(*window)))
        {
            powerDampening += 0.1;
        }
    }

    powerDampening = powerDampening > START_CHARGE ? START_CHARGE : powerDampening;

    if (selected) {
        drawSelected(window, textures);
    }

    RectangleShape switchShape;
    switchShape.setSize(Vector2f(18, charge / maxCharge * 32));
    switchShape.setScale(Vector2f(1, -1));
    switchShape.setPosition(31 + coords.x * 40, 54 + coords.y * 40);
    unsigned int blue = charge / maxCharge * 255;
    switchShape.setFillColor(Color(255 - blue, blue, 0));
    window->draw(switchShape);

    drawTinyMachine(window, textures, 10);

    if (broken)
        drawBroken(window, textures);
}

void Battery::drawSelected(RenderWindow* window, std::vector<Texture>* textures)
{
    drawType(window, textures, getMachineType());

    if (Game::gameInstance->hasActiveComputer())
    {
        std::string chargeInfo = "CHARGE: " + floatToString(charge / maxCharge * 100, 1) + " PERCENT";
        drawString(window, chargeInfo, Vector2f(502, 233), &textures->at(0), Color(0, 200, 0), 100);

        std::string outInfo = "OUTPUT: " + floatToString(outPower, 1) + "W";
        drawString(window, outInfo, Vector2f(502, 244), &textures->at(0), Color(0, 200, 0), 100);
    }

    RectangleShape switchShape;
    switchShape.setSize(Vector2f(18, charge / maxCharge * 32));
    switchShape.setScale(Vector2f(4, -4));
    switchShape.setPosition(544, 156);
    unsigned int blue = charge / maxCharge * 255;
    switchShape.setFillColor(Color(255 - blue, blue, 0));
    window->draw(switchShape);

    Sprite sprite(textures->at(21));
    sprite.setPosition(500, 20);
    window->draw(sprite);

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
