#include <SFML/Graphics.hpp>
#include "Machine.h"
#include <iomanip> // setprecision
#include <sstream> // stringstream
#include "Game.h"

using namespace sf;

int drawString(RenderWindow* window, std::string text, Vector2f position, Texture* fontTexture, Color color, int newLine);

void Machine::drawType(RenderWindow* window, std::vector<Texture>* textures, MachineType type)
{
    if (Game::gameInstance->hasActiveComputer())
    {
        std::array<String, 8> machineStrings = { "HEATER", "SOLAR PANEL",
            "BATTERY", "WATER PURIFIER", "CO2REMOVER", "COMPUTER", "DISH", "LIGHT" };

        std::string typeStr = "TYPE: " + machineStrings[type];
        drawString(window, typeStr, Vector2f(502, 222), &textures->at(0), Color(0, 200, 0), 100);

        
    }
}

void Machine::drawBroken(RenderWindow* window, std::vector<Texture>* textures)
{
    Sprite broken(textures->at(9));
    broken.setPosition(20 + coords.x * 40, 20 + coords.y * 40);
    window->draw(broken);
}

void Machine::drawTinyMachine(RenderWindow* window, std::vector<Texture>* textures, int texture)
{
    Sprite sprite(textures->at(texture));
    sprite.setPosition(20 + coords.x * 40, 20 + coords.y * 40);
    window->draw(sprite);
}

void Machine::drawLargeMachine(RenderWindow* window, std::vector<Texture>* textures, int texture)
{
    Sprite sprite(textures->at(texture));
    sprite.setPosition(500, 20);
    sprite.setScale(4,4);
    window->draw(sprite);
}
