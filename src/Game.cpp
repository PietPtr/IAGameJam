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

Game* Game::gameInstance;

Game::Game(RenderWindow* _window)
{
    Game::gameInstance = this;
    window = _window;
}

void Game::initialize()
{
    machineCountMax[HEATER] = 3;
    machineCountMax[SOLARPANEL] = 0;
    machineCountMax[BATTERY] = 0;
    machineCountMax[WATERPURIFIER] = 1;
    machineCountMax[COMPUTER] = 4;
    machineCountMax[DISH] = 2;
    machineCountMax[LIGHT] = 1;
    machineCountMax[CO2REMOVER] = 3;

    loadAudio(audioFileNames);
    loadTextures(textureFileNames);

    fillRoutingPanel();
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
            Vector2f mousePos = Vector2f(event.mouseButton.x,
                                         event.mouseButton.y);

            if (state == GAME || state == START)
            {
                if (event.mouseButton.button == Mouse::Left)
                {

                    Vector2i selectedCoords = Vector2i((int)(mousePos.x - 20) / 40,
                                                       (int)(mousePos.y - 20) / 40);

                    if (selectedCoords.x < 11 && selectedCoords.y < 17)
                    {
                        determineSelectedConnection(selectedCoords);
                        selectedCoord = selectedCoords;
                    }
                }
            }

            if (state == START && mousePos.x > 500 && mousePos.y > 340)
            {
                state = GAME;
            }

            if (state == GAMEOVER)
            {
                //Restart.
                state = START;
                temperature = 18;
                co2 = 402;
                missionTime = seconds(65536);
                initialize();
                return;
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
    missiondt = dt * TIME_MULTIPLIER;

    if (randint(0, 60) == 0)
    {
        std::string msg = getHoustonStatusMessage();
        if (msg != "NONE")
        {
            consoleLog("HOUSTON: " + msg);
        }
    }

    if (state == START)
    {
        for (int i = 0; i < machines.size(); i++)
        {
            Time zeroTime = seconds(0);
            machines[i]->update(zeroTime);
        }
    }

    //Update lines
    if (state == GAME || state == START)
    {
        for (int i = 0; i < lines.size(); i++)
        {
            lines[i]->update(dt);
        }

        for (int i = 0; i < switches.size(); i++)
        {
            switches[i]->update(dt);
        }
    }

    float newTemperature = 0;

    if (state == GAME)
    {
        std::array<String, 8> machineStrings = { "HEATER", "SOLAR PANEL",
            "BATTERY", "WATER PURIFIER", "CO2REMOVER", "COMPUTER", "DISH", "LIGHT" };

        bool isOneDishWithPower = false;
        bool isOneComputerWithPower = false;
        lights = 0;

        //Update machines
        for (int i = 0; i < machines.size(); i++)
        {
            if (!machines[i]->isBroken())
            {
                if (randint(0, 50000) == 0)
                {
                    machines[i]->setBroken(true);
                    consoleLog("SYSTEM: " + machineStrings[machines[i]->getMachineType()] + " BROKE DOWN");
                }
                machines[i]->update(dt);
            }

            switch (machines[i]->getMachineType())
            {
            case SOLARPANEL:
                break;
            case BATTERY:
                break;
            case HEATER:
                temperature += ((Heater*)(machines[i]))->getHeatOutput(missiondt);
                break;
            case CO2REMOVER:
                co2 -= ((CO2Remover*)(machines[i]))->getRemovedCO2(missiondt);
                co2 = co2 < 0 ? 0 : co2;
                break;
            case DISH:
                if (((Dish*)(machines[i]))->isOn() && !machines[i]->isBroken())
                {
                    isOneDishWithPower = true;
                }
            case COMPUTER:
                if (((Computer*)(machines[i]))->isOn() && !machines[i]->isBroken())
                {
                    isOneComputerWithPower = true;
                }
                break;
            case LIGHT:
            {
                if (!machines[i]->isBroken())
                {
                    lights += machines[i]->getPower();
                }
                break;
            }
            default:
                break;
            }
        }
        if (isOneDishWithPower)
            hasLink = true;
        else
            hasLink = false;

        if (isOneComputerWithPower)
            activeComputer = true;
        else
            activeComputer = false;


        co2 += co2PerSecond * missiondt.asSeconds();
        float temperatureDecrease = heatLeakage * missiondt.asSeconds();
        if (temperature > 0)
        {
            temperatureDecrease *= (temperature / 12 >= 1) ? (temperature/20) : 1;
        }
        else
        {

        }
        temperature -= temperatureDecrease;
    }

    if (temperature > 70)
    {
        state = GAMEOVER;
        gameOverReason = "YOU BURNED TO DEATH...";
    }
    else if (temperature < -40)
    {
        state = GAMEOVER;
        gameOverReason = "YOU FROZE TO DEATH...";
    }
    else if (co2 > 50000)
    {
        state = GAMEOVER;
        gameOverReason = "YOU SUFFOCATE TO DEATH...";
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


    Sprite bgSprite;
    bgSprite.setTexture(textures.at(1));
    window->draw(bgSprite);

    RectangleShape lightOverlay;
    lightOverlay.setSize(Vector2f(856, 720));
    lightOverlay.setScale(Vector2f(1, 1));
    lightOverlay.setPosition(0, 0);
    int transparency = 200 - lights * 15;
    if (state == START)
        transparency = 0;
    lightOverlay.setFillColor(Color(0, 0, 0, transparency < 0 ? 0 : transparency));
    window->draw(lightOverlay);

    if (hasActiveComputer())
    {
        if (drawString(window, log, Vector2f(497,344), &textures.at(0), Color(0, 200, 0), 47) > 32)
        {
            unsigned end = log.find('&');
            log.erase(log.begin(), log.end() - (log.length() - end - 2));
        }
    }

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

    if (selectedCoord.x < 11)
    {
        RectangleShape selector(Vector2f(40, 40));
        selector.setPosition(selectedCoord.x * 40 + 20, selectedCoord.y * 40 + 20);
        selector.setFillColor(Color(0,0,0,0));
        selector.setOutlineColor(Color(255,255,255));
        selector.setOutlineThickness(1);
        window->draw(selector);
    }


    //Draw status
    if (hasActiveComputer())
        drawStatus();

    Sprite scanLines(textures[6]);
    window->draw(scanLines);

    if (state == START)
    {
        Sprite infoOverlay(textures[7]);
        window->draw(infoOverlay);
    }
    if (state == GAMEOVER)
    {
        Sprite gameover(textures[8]);
        window->draw(gameover);

        drawString(window, "REASON: " + gameOverReason, Vector2f(340, 600), &textures.at(0), Color(0,200,0), 100);

        drawString(window, "CLICK ANYWHERE TO PLAY AGAIN", Vector2f(340, 650), &textures.at(0), Color(0, 200, 0), 100);
    }

    Sprite effectOverlay(textures[22]);
    if (temperature < 0)
    {
        int alpha = 70 - temperature * 3;
        effectOverlay.setColor(Color(0, 0, 255, alpha < 200 ? alpha : 200));
        window->draw(effectOverlay);
    }
    else
    {
        if (temperature > 50)
        {
            int alpha = 70 + temperature;
            effectOverlay.setColor(Color(255, 0, 0, alpha < 200 ? alpha : 200));
            window->draw(effectOverlay);
        }
    }

    window->display();
}

void Game::drawStatus()
{
    Color tempColor(0, 200, 0);
    if (temperature > 45)
        tempColor = Color(255, 0, 0);
    if (temperature < 0)
        tempColor = Color(100, 100, 255);

    std::string tempStr = "TEMP:&   " + std::to_string((int)temperature) + " C";
    drawString(window, tempStr, Vector2f(702, 24), &textures.at(0), tempColor, 100);

    Color co2Color(0, 200, 0);
    if (co2 > 20000)
        co2Color = Color(255, 0, 0);

    std::string co2Str = "CO2 LEVEL:&   " + std::to_string((int)co2) + " PPM";
    drawString(window, co2Str, Vector2f(702, 48), &textures.at(0), co2Color, 100);

    std::string timeStr = "MISSION TIME: &   " + getPrettyMissionTime();
    drawString(window, timeStr, Vector2f(702, 72), &textures.at(0), Color(0, 200, 0), 100);

    std::string linkStatus = "DOWN";
    Color linkColor(255, 0, 0);
    if (hasLink)
    {
        linkStatus = "UP";
        linkColor = Color(0, 200, 0);
    }

    std::string commStr = "COMM LINK: &   " + linkStatus;
    drawString(window, commStr, Vector2f(702, 96), &textures.at(0), linkColor, 100);
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
        //if (y == 0)
        //    machines[machineNumber] = new CO2Remover(Vector2i(0, 6 + y * 2));
        //else if (y == 1)
        //    machines[machineNumber] = new Light(Vector2i(0, 6 + y * 2));
        //else
        //    machines[machineNumber] = new Heater(Vector2i(0, 6 + y * 2));
        machines[machineNumber] = createNewMachine(Vector2i(0, 6 + y * 2));
        machineNumber++;
    }

    //Create the right machines.
    for (int y = 0; y < 5; y++)
    {
        //if (y < 4)
        //    machines[machineNumber] = new Computer(Vector2i(10, 6 + y * 2));
        //else
        //    machines[machineNumber] = new WaterPurifier(Vector2i(10, 6 + y * 2));
        machines[machineNumber] = createNewMachine(Vector2i(10, 6 + y * 2));
        machineNumber++;
    }

    //Create the bottom machines.
    for (int x = 0; x < 4; x++)
    {
        //if (x == 0 || x == 3)
        //    machines[machineNumber] = new Dish(Vector2i(x * 2 + 2, 16));
        //else
        //    machines[machineNumber] = new CO2Remover(Vector2i(x * 2 + 2, 16));
        machines[machineNumber] = createNewMachine(Vector2i(x * 2 + 2, 16));
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
                lines[lineNumber] = new Line(Vector2i(x * 2 + 2, 5 + y * 2), { switches[x + 4], machines[x + 4] });
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
        machines[13 + y]->setLine(getLine(machines[13 + y]->getCoords().x - 1, machines[13 + y]->getCoords().y));
    }

    //Create 2 lines and 2 solarpanels at the third row.
    machines[machineNumber] = new SolarPanel(Vector2i(0, 2));
    lines[lineNumber] = new Line(Vector2i(1, 2), { machines[machineNumber], switches[0] });
    machines[machineNumber]->setLine(lines[lineNumber]);
    machineNumber++;
    lineNumber++;
    machines[machineNumber] = new SolarPanel(Vector2i(10, 2));
    lines[lineNumber] = new Line(Vector2i(9, 2), { switches[3], machines[machineNumber] });
    machines[machineNumber]->setLine(lines[lineNumber]);
    machineNumber++;
    lineNumber++;

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

    std::cout << "Created world\n";
}

void Game::consoleLog(std::string text)
{
    log += getPrettyMissionTime() + " " + text + "& ";
    if (!hasActiveComputer())
        log = "";
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

std::string Game::getHoustonStatusMessage()
{
    if (!hasLink)
        return "NONE";

    if (temperature > 35 && !warnedTempHigh)
    {
        warnedTempHigh = true;
        return "BE ADVISED YOUR TEMPERATURE SEEMS TO BE TOO HIGH. TURN OFF HEATERS";
    }
    else if (temperature < 35 && warnedTempHigh)
        warnedTempHigh = false;

    if (co2 > 30000 && !warnedCO2)
    {
        warnedCO2 = true;
        return "CO2 LEVELS ARE NEAR TOXIC. SEND MORE POWER TO THE CO2 REMOVER";
    }
    else if (co2 < 30000 && warnedCO2)
        warnedCO2 = false;

    if (temperature < -10 && !warnedTempLow)
    {
        warnedTempLow = true;
        return "AT THIS TEMPERATURE MACHINES MIGHT FAIL. TURN ON HEATERS";
    }
    else if (temperature > -10 && warnedTempLow)
        warnedTempLow = false;

    return "NONE";
}

Line * Game::getLine(int x, int y)
{
    for (int i = 0; i < lines.size(); i++)
    {
        if (lines[i] != NULL && lines[i]->getCoords().x == x && lines[i]->getCoords().y == y)
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

Machine* Game::createNewMachine(Vector2i coords)
{
    int i = randint(0, machineCountMax.size() - 1);
    int number = 0;
    for (std::map<MachineType, int>::iterator newMachType = machineCountMax.begin(); newMachType != machineCountMax.end(); ++newMachType)
    {
        if (number == i && newMachType->second > 0)
        {
            machineCountMax[newMachType->first] -= 1;
            switch (newMachType->first)
            {
                case HEATER:
                {
                    return new Heater(coords);
                }
                case WATERPURIFIER:
                {
                    return new WaterPurifier(coords);
                }
                case CO2REMOVER:
                {
                    return new CO2Remover(coords);
                }
                case DISH:
                {
                    return new Dish(coords);
                }
                case LIGHT:
                {
                    return new Light(coords);
                }
                case COMPUTER:
                {
                    return new Computer(coords);
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        number++;
    }
    return createNewMachine(coords);
}

int Game::randint(int low, int high)
{
    int value = rand() % (high + 1 - low) + low;
    //srand(totalTime.asMicroseconds() * value * rand());

    return value;
}
