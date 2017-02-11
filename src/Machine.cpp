#include <SFML/Graphics.hpp>
#include "Machine.h"
#include <iomanip> // setprecision
#include <sstream> // stringstream

using namespace sf;

int drawString(RenderWindow* window, std::string text, Vector2f position, Texture* fontTexture, Color color, int newLine);

void Machine::drawType(RenderWindow* window, std::vector<Texture>* textures, MachineType type)
{
    std::array<String, 8> machineStrings = { "HEATER", "SOLAR PANEL",
        "BATTERY", "WATER PURIFIER", "CO2REMOVER", "COMPUTER", "DISH", "LIGHT" };

    std::string powerStr = "TYPE: " + machineStrings[type];
    drawString(window, powerStr, Vector2f(502, 222), &textures->at(0), Color(0, 200, 0), 100);
}
