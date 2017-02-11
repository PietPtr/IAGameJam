#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Battery.h"
#include "Heater.h"
#include "SolarPanel.h"
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

                std::cout << selectedCoord.x << " " << selectedCoord.y << " \n";

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

    for (int i = 0; i < lines.size(); i++)
    {
        lines[i]->update(dt);
    }

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

    for (int i = 0; i < lines.size(); i++)
    {
        // coords where undefined and giving segfaults, uncomment when needed again
        lines[i]->draw(window);
    }

    for (int i = 0; i < switches.size(); i++)
    {
        if (switches[i] != NULL)
        {
            switches[i]->draw(window, &textures);
        }
    }

    for (int i = 0; i < machines.size(); i++)
    {
        if (machines[i] != NULL)
        {
            machines[i]->draw(window, &textures);
        }
    }

    window->display();
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
        Battery* test = new Battery(Vector2i(0, 0));
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
        machines[machineNumber] = new Heater(Vector2i(0, 6 + y * 2));
        machineNumber++;
    }

    //Create the right machines.
    for (int y = 0; y < 5; y++)
    {
        machines[machineNumber] = new Heater(Vector2i(10, 6 + y * 2));
        machineNumber++;
    }

    //Create the bottom machines.
    for (int x = 0; x < 4; x++)
    {
        machines[machineNumber] = new Heater(Vector2i(x * 2 + 2, 16));
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
                //Switches to batteries
                lines[lineNumber] = new Line(Vector2i(x * 2 + 2, 5 + y * 2), { switches[x], machines[x + 4] });
            }
            if(y == 1)
            {
                //Batteries to switches
                lines[lineNumber] = new Line(Vector2i(x * 2 + 2, 5 + y * 2), { machines[x + 4], switches[x+4]});
            }
            if (y > 1)
            {
                //Switches to switches
                lines[lineNumber] = new Line(Vector2i(x * 2 + 2, 5 + y * 2), { switches[x+y*4], switches[x + (y+1)*4] });
            }
            lineNumber++;
        }
    }

    //Create last vertical lines connected with machines
    for (int x = 0; x < 4; x++)
    {
        lines[lineNumber] = new Line(Vector2i(x * 2 + 1, 4 + 5 * 2), { switches[20 + x], machines[14 + x] });
        lineNumber++;
    }

    //Create horizontal lines.
    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            if (x == 0)
            {
                lines[lineNumber] = new Line(Vector2i(x * 2 + 1, 6 + y * 2), { machines[8 + y], switches[4 + x] });
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
        lines[lineNumber] = new Line(Vector2i(x * 2 + 2, 15), { switches[4 * 5 + x - 1], machines[17 + x] });
        lineNumber++;
    }

    for (int i = 0; i < switches.size(); i++)
    {
        switches[i]->addLine(getLine(switches[i]->getCoords().x - 1, switches[i]->getCoords().y));
        switches[i]->addLine(getLine(switches[i]->getCoords().x + 1, switches[i]->getCoords().y));
        switches[i]->addLine(getLine(switches[i]->getCoords().x, switches[i]->getCoords().y - 1));
        switches[i]->addLine(getLine(switches[i]->getCoords().x, switches[i]->getCoords().y + 1));
    }
    std::cout << "Created world";
}

void Game::consoleLog(std::string text)
{
    log += getPrettyMissionTime() + " " + text + "& ";
}

void Game::determineSelectedConnection(Vector2i selectedCoords)
{
    bool found = false;
    for (int i = 0; i < switches.size(); i++)
    {
        if (switches[i]->getCoords() == selectedCoords)
        {
            switches[i]->setSelected(true);
            found = true;
        }
        else
        {
            switches[i]->setSelected(false);
        }
    }

    if (found)
        return;

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
