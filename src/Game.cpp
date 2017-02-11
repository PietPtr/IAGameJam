#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Machines/Battery.h"
#include "Machines/SolarPanel.h"

#include "Machines/Heater.h"
#include "Machines/CO2Remover.h"
#include "Machines/Computer.h"
#include "Machines/Dish.h"
#include "Machines/Light.h"
#include "Machines/WaterPurifier.h"

#include "Connection.h"
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace sf;

int drawString(RenderWindow* window, std::string text, Vector2f position, Texture* fontTexture, Color color, int newLine);

Game::Game(RenderWindow* _window)
{
    window = _window;
}

void Game::initialize()
{
    loadAudio(audioFileNames);
    loadTextures(textureFileNames);
    // code throws errors, can't test with it
    fillRoutingPanel();
    consoleLog("TEST");
    consoleLog("ANOTHER TEST");
}

void Game::update()
{
    Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
        if (event.type == Event::KeyPressed)
        {
            if (event.key.code == Keyboard::Escape)
            {
                window->close();
            }
        }
        if (event.type == Event::LostFocus)
        {
            focus = false;
        }
        if (event.type == Event::GainedFocus)
        {
            focus = true;
        }

        if (event.type == Event::Resized)
        {
            windowWidth = event.size.width;
            windowHeight = event.size.height;
        }

        if (event.type == Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == Mouse::Left)
            {
                Vector2f mousePos = Vector2f(event.mouseButton.x,
                                             event.mouseButton.y);

                Vector2i selectedCoord = Vector2i((int)(mousePos.x - 20) / 40,
                                                  (int)(mousePos.y - 20) / 40);

                // std::cout << selectedCoord.x << " " << selectedCoord.y << " \n";

                if (selectedCoord.x < 11 && selectedCoord.y < 17)
                    determineSelectedConnection(selectedCoord);
            }
        }
    }

    if (!focus)
    {
        return;
    }

    dt = clock.restart();
    totalTime += dt;
    missionTime += dt * TIME_MULTIPLIER;

    if (frame % 120 == 0)
    {
        consoleLog("PING");
    }

    //Update lines
    for (int i = 0; i < lines.size(); i++)
    {
        lines[i]->update(dt);
    }

    for (int i = 0; i < switches.size(); i++)
    {
        switches[i]->update(dt);
    }

    float newTemperature = 0;

    //Update machines
    for (int i = 0; i < machines.size(); i++)
    {
        machines[i]->update(dt);

        switch (machines[i]->getMachineType())
        {
        case SOLARPANEL:
            break;
        case BATTERY:
            break;
        case HEATER:
        {
            break;
        }
        default:
            break;
        }
    }
    //Go to the new temperature.
    //temperature += (newTemperature - temperature)*dt.asSeconds();

    frame++;
}

void Game::draw()
{
    if (!focus)
    {
        return;
    }

    window->clear(Color(35, 35, 35));

    if (drawString(window, log, Vector2f(497,344), &textures.at(0), Color(0, 200, 0), 47) > 33)
    {
        unsigned end = log.find('&');
        log.erase(log.begin(), log.end() - (log.length() - end - 2));
    }

    Sprite bgSprite;
    bgSprite.setTexture(textures.at(1));
    window->draw(bgSprite);

    //Draw all lines
    for (int i = 0; i < lines.size(); i++)
    {
        // coords where undefined and giving segfaults, uncomment when needed again
        lines[i]->draw(window);
    }

    //Draw all switches.
    for (int i = 0; i < switches.size(); i++)
    {
        if (switches[i] != NULL)
        {
            switches[i]->draw(window, &textures);
        }
    }

    //Draw all machines.
    for (int i = 0; i < machines.size(); i++)
    {
        if (machines[i] != NULL)
        {
            machines[i]->draw(window, &textures);
        }
    }

    //Draw status
    drawStatus();

    Sprite scanLines(textures[6]);
    window->draw(scanLines);

    window->display();
}

void Game::drawStatus()
{
    std::string tempStr = "TEMP:&   " + std::to_string((int)temperature) + " C";
    drawString(window, tempStr, Vector2f(702, 24), &textures.at(0), Color(0, 200, 0), 100);

    std::string co2Str = "CO2 LEVEL:&   " + std::to_string((int)co2) + " PPM";
    drawString(window, co2Str, Vector2f(702, 48), &textures.at(0), Color(0, 200, 0), 100);

    std::string timeStr = "MISSION TIME: &   " + getPrettyMissionTime();
    drawString(window, timeStr, Vector2f(702, 72), &textures.at(0), Color(0, 200, 0), 100);

    std::string linkStatus = "DOWN";
    if (hasLink)
        linkStatus = "UP";

    std::string commStr = "COMM LINK: &   " + linkStatus;
    drawString(window, commStr, Vector2f(702, 96), &textures.at(0), Color(0, 200, 0), 100);
}

bool Game::isWindowOpen()
{
    return window->isOpen();
}

void Game::loadAudio(std::vector<std::string> audioFileNames)
{
    for (int i = 0; i < audioFileNames.size(); i++)
    {
        sfx.push_back(new Audio());
        sfx.back()->init(audioFileNames[i]);
    }
}

void Game::loadTextures(std::vector<std::string> textureFileNames)
{
    for (int i = 0; i < textureFileNames.size(); i++)
    {
        Texture texture;
        std::string path = "textures/" + textureFileNames.at(i);
        if (!texture.loadFromFile(path)) {
            window->close();
        }
        textures.push_back(texture);
        std::cout << "Loaded " << path << "\n";
    }
}

void Game::fillRoutingPanel() {
    int lineNumber = 0;
    int switchNumber = 0;
    int machineNumber = 0;

    //Create 4 solar panels
    for (int x = 0; x < 4; x++)
    {
        machines[machineNumber] = new SolarPanel(Vector2i(2 + x * 2, 0));
        machineNumber++;
    }

    //First 4 switches
    for (int x = 0; x < 4; x++)
    {
        switches[switchNumber] = new Switch(Vector2i(2 + x * 2, 2));
        switchNumber++;
    }

    //First 4 lines, from solar to switch.
    for (int x = 0; x < 4; x++)
    {
        lines[lineNumber] = new Line(Vector2i(2 + x * 2, 1), { machines[x], switches[x]});
        lineNumber++;
    }

    //Create 4 batteries
    for (int x = 0; x < 4; x++)
    {
        machines[machineNumber] = new Battery(Vector2i(2 + x * 2, 4));
        machineNumber++;
    }

    //Second 4 lines, from switch to battery.
    for (int x = 0; x < 4; x++)
    {
        lines[lineNumber] = new Line(Vector2i(2 + x * 2, 3), { switches[x], machines[x + 4] });
        lineNumber++;
    }

    //3 lines, between the first 4 switches.
    for (int x = 0; x < 3; x++)
    {
        lines[lineNumber] = new Line(Vector2i(3 + x * 2, 2), { switches[x], switches[x+1] });
        lineNumber++;
    }

    //Create the left machines.
    for (int y = 0; y < 5; y++)
    {
        if (y == 0)
            machines[machineNumber] = new CO2Remover(Vector2i(0, 6 + y * 2));
        else if (y == 1)
            machines[machineNumber] = new Light(Vector2i(0, 6 + y * 2));
        else
            machines[machineNumber] = new Heater(Vector2i(0, 6 + y * 2));

        machineNumber++;
    }

    //Create the right machines.
    for (int y = 0; y < 5; y++)
    {
        if (y < 4)
            machines[machineNumber] = new Computer(Vector2i(10, 6 + y * 2));
        else
            machines[machineNumber] = new WaterPurifier(Vector2i(10, 6 + y * 2));

        machineNumber++;
    }

    //Create the bottom machines.
    for (int x = 0; x < 4; x++)
    {
        if (x == 0 || x == 3)
            machines[machineNumber] = new Dish(Vector2i(x * 2 + 2, 16));
        else
            machines[machineNumber] = new CO2Remover(Vector2i(x * 2 + 2, 16));

        machineNumber++;
    }

    //Create all other switches
    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            switches[switchNumber] = new Switch(Vector2i(2 + x * 2, y * 2 + 6));
            switchNumber++;
        }
    }

    //Create vertical lines.
    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (y == 0)
            {
                //Battery to switch
                lines[lineNumber] = new Line(Vector2i(x * 2 + 2, 5 + y * 2), { switches[x], machines[x + 4] });
            }
            if (y > 0)
            {
                //Switches to switches
                lines[lineNumber] = new Line(Vector2i(x * 2 + 2, 5 + y * 2), { switches[x+y*4], switches[x + (y+1)*4] });
            }
            lineNumber++;
        }
    }

    //Create horizontal lines.
    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            if (x == 0)
            {
                lines[lineNumber] = new Line(Vector2i(1, 6 + y * 2), { machines[8 + y], switches[4 * (y + 1)] });
            }
            if (x == 4)
            {
                lines[lineNumber] = new Line(Vector2i(x * 2 + 1, 6 + y * 2), { switches[4 * (y + 1) + x - 1], machines[13 + y] });
            }
            if (x > 0 && x < 4)
            {
                lines[lineNumber] = new Line(Vector2i(x * 2 + 1, 6 + y * 2), { switches[4 * (y+1) + x - 1], switches[4 * (y + 1) + x]});
            }
            lineNumber++;
        }
    }

    //Create the 4 last lines from switch to bottom machines
    for (int x = 0; x < 4; x++)
    {
        lines[lineNumber] = new Line(Vector2i(x * 2 + 2, 15), { switches[4 * 5 + x], machines[18 + x] });
        lineNumber++;
    }

    //Set lines of all switches
    for (int i = 0; i < switches.size(); i++)
    {
        //Top
        switches[i]->addLine(getLine(switches[i]->getCoords().x, switches[i]->getCoords().y - 1));
        //Right
        switches[i]->addLine(getLine(switches[i]->getCoords().x + 1, switches[i]->getCoords().y));
        //Bottom
        switches[i]->addLine(getLine(switches[i]->getCoords().x, switches[i]->getCoords().y + 1));
        //Left
        switches[i]->addLine(getLine(switches[i]->getCoords().x - 1, switches[i]->getCoords().y));
    }

    //Set lines of the batteries
    for (int x = 0; x < 4; x++)
    {
        machines[x + 4]->setLine(lines[4 + x]);
        ((Battery*)machines[x + 4])->setOutputLine(lines[11 + x]);
    }

    //Set lines for all solarpanels
    for (int x = 0; x < 4; x++)
    {
        machines[x]->setLine(lines[x]);
    }

    //Set lines for left machines
    for (int y = 0; y < 5; y++)
    {
        machines[8 + y]->setLine(getLine(machines[8 + y]->getCoords().x + 1, machines[8 + y]->getCoords().y));
    }

    //Set lines for bottom machines
    for (int x = 0; x < 4; x++)
    {
        machines[18 + x]->setLine(getLine(machines[18 + x]->getCoords().x, machines[18 + x]->getCoords().y - 1));
    }

    //Set lines for right machines
    for (int y = 0; y < 5; y++)
    {
        machines[13 + y]->setLine(getLine(machines[12 + y]->getCoords().x - 1, machines[12 + y]->getCoords().y));
    }

    std::cout << "Created world\n";
}

void Game::consoleLog(std::string text)
{
    log += getPrettyMissionTime() + " " + text + "& ";
}

void Game::determineSelectedConnection(Vector2i selectedCoords)
{
    for (int i = 0; i < switches.size(); i++)
    {
        if (switches[i]->getCoords() == selectedCoords)
        {
            switches[i]->setSelected(true);
            selectedSwitch = switches[i];
        }
        else
        {
            switches[i]->setSelected(false);
        }
    }

    for (int i = 0; i < machines.size(); i++)
    {
        if (machines[i]->getCoords() == selectedCoords)
        {
            machines[i]->setSelected(true);
        }
        else
        {
            machines[i]->setSelected(false);
        }
    }
}

std::string Game::getPrettyMissionTime()
{

    std::string result = "";
    int missionSeconds = missionTime.asSeconds();

    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0')
       << (int)(missionTime.asSeconds() / 60 / 60) << ":"
       << std::setw(2) << std::setfill('0')
       << (int)(missionTime.asSeconds() / 60) % 60 << ":"
       << std::setw(2) << std::setfill('0')
       << ((int)(missionTime.asSeconds()) % 60);

    return ss.str();
}

Line * Game::getLine(int x, int y)
{
    for (int i = 0; i < lines.size(); i++)
    {
        if (lines[i]->getCoords().x == x && lines[i]->getCoords().y == y)
        {
            return lines[i];
        }
    }
    return NULL;
}

Line * Game::getLine(Vector2i coords)
{
    return getLine(coords.x, coords.y);
}

int Game::randint(int low, int high)
{
    int value = rand() % (high + 1 - low) + low;
    srand(totalTime.asMicroseconds() * value * rand());

    return value;
}
