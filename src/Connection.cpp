#include <SFML/Graphics.hpp>
#include "Connection.h"
#include <iomanip> // setprecision
#include <sstream> // stringstream

using namespace sf;

int drawString(RenderWindow* window, std::string text, Vector2f position, Texture* fontTexture, Color color, int newLine);

void Connection::drawPowerStatus(RenderWindow* window, std::vector<Texture>* textures)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << power;
    std::string valueStr = stream.str();

    std::string powerStr = "POWER: " + valueStr + " W";
    drawString(window, powerStr, Vector2f(502, 233), &textures->at(0), Color(0, 200, 0), 100);
}
