#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <random>
#include <filesystem>
#include <direct.h>
#include <clocale>
#include <sstream>
#include <windows.h>
#include <cmath>
#include <fstream>
#include <vector>
#include <cstdint>
#include <ctime>

const long SAMPLE_RATE = 44100;  // Частота дискретизации
const long DURATION = 5;         // Продолжительность звука (в секундах)
const long SIZEE = SAMPLE_RATE * DURATION;


int tii = 0; //Для таймера

bool is_white = false;
bool is_pink = false;
bool is_brown = false;

bool is_buf = false;
bool erg = false;

bool is_play = false;
bool is_pause = false;

// Глобальные переменные
std::string commanda = "";
sf::Text receivedText;
sf::Mutex mutex;
bool running = true;
char buffer[1024];
std::size_t received;

int rotat = 0;

int mytime = 0;
int mode = 0;
int this_mode = 0;
sf::Color this_color;

int mas_param[8];
std::string mas_param2[2];
std::string mesage2;


char pathe1[MAX_PATH];

sf::Image image;

struct Command {
    std::string name;
    std::vector<std::string> params;
};

float randomFloat()
{
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 3.0f - 1.0f;
}

// Функция для генерации розового шума
std::vector<sf::Int16> generatePinkNoise(unsigned int sampleCount)
{
    std::vector<sf::Int16> pinkNoise(sampleCount, 0);

    const int numFilters = 90; // Количество фильтров
    std::vector<float> filterValues(numFilters, 5.0f);

    // Создаем фильтры
    std::vector<std::vector<float>> filters(numFilters, std::vector<float>(sampleCount, 0.5f));
    for (int i = 0; i < numFilters; ++i)
    {
        for (unsigned int j = 0; j < sampleCount; ++j)
        {
            filters[i][j] = randomFloat();
        }
    }

    // Фильтрация белого шума
    for (unsigned int i = 0; i < sampleCount; ++i)
    {
        float whiteNoise = randomFloat();

        for (int j = 0; j < numFilters; ++j)
        {
            filterValues[j] += (whiteNoise - filters[j][i]);
            whiteNoise = filters[j][i];
        }

        float pinkSample = 0.0f;
        for (int j = 0; j < numFilters; ++j)
        {
            pinkSample += filterValues[j];
        }

        pinkNoise[i] = static_cast<sf::Int16>(pinkSample * 8192); // Масштабируем значения
    }

    return pinkNoise;
}



Command ParseCommand(const std::string& commandStr) {
    Command command;

    int number;

    std::string s_mode;

    std::istringstream ss(commandStr);
    std::string word;

    int j = 0;
    int i = 0;
    while (ss >> word) {
        if (word == "=")
        {
            break;
        }
        else {
            s_mode = word;
            std::cout << word << " === \n";
        }
    }
    std::cout << "s_mode " << s_mode;
    try {
        mode = std::stoi(s_mode);
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    this_mode = mode;
    while (ss >> word) {
        switch (mode)
        {
            //clear display
            ///other
        case 5: case 10: case 15: case 20: case 24: case 30: case 36:
        case 40: case 44: case 48: case 53: case 57: case 58: case 61: case 62: case 70:
        case 73: case 74: case 79: case 84: case 86:
            command.params.push_back(word);
            try {
                number = std::stoi(word);
            }
            catch (const std::invalid_argument& e) {
                mas_param2[j] = word;
                std::cout << j + 1 << " param = " << mas_param2[j];
                j++;
                if (mode == 86)
                {
                    if (mas_param2[0] == "play" || mas_param2[0] == "Play")
                    {
                        is_play = true;
                    }
                    if (mas_param2[0] == "Stop" || mas_param2[0] == "stop")
                    {
                        is_pause = true;
                    }
                }
                if (mode != 57)
                {
                    if (mode != 73)
                    {
                        is_buf = true;
                        return command;
                    }
                }
                else {
                    mode++;
                }
            }
            break;

            ///
            ///numbers
        case 1: case 2: case 3: case 4: case 6: case 7: case 8: case 9: case 11: case 12:
        case 13: case 14: case 16: case 17: case 18: case 19: case 21: case 22: case 23:
        case 27: case 28: case 29: case 33: case 34:
        case 35: case 37: case 38: case 39: case 41: case 42: case 43: case 45: case 46:
        case 47: case 49: case 50: case 51: case 52: case 54: case 55: case 56: case 59:
        case 60: case 63: case 64: case 65: case 66: case 67: case 68: case 69: case 71:
        case 72: case 76: case 77: case 78: case 80: case 81: case 82: case 83: case 85:
            command.params.push_back(word);
            std::cout << std::endl << mode << " ";
            try {
                number = std::stoi(word);
            }
            catch (const std::invalid_argument& e) {
                return command;
            }
            if (mode == 76)
            {
                bool myer = false;
                if (number == 0 && myer == false)
                {
                    number = 0;
                    myer = true;
                }
                if (number == 1 && myer == false)
                {
                    number = 90;
                    myer = true;
                }
                if (number == 2 && myer == false)
                {
                    number = 180;
                    myer = true;
                }
                if (number >= 3 && myer == false)
                {
                    number = 270;
                    myer = true;
                }
                
                rotat = number;
                return command;
            }
            if (mode == 63)
            {
                is_white = true;
            }
            if (mode == 64)
            {
                is_brown = true;
            }
            if (mode == 65)
            {
                is_pink = true;
            }
            if (mode == 69)
            {
                std::cout << "YES";
                mytime = number;
            }
            tii = 0;
            std::cout << i + 1 << " param = " << number;
            mode++;
            mas_param[i] = number;
            i++;
            break;
            ///
        }
    }
    is_buf = true;
    return command;

}
//Цвет
sf::Color MyCol()
{
    if ("red" == mas_param2[0])
    {
        return sf::Color(255, 0, 0);
    }
    else if ("blue" == mas_param2[0])
    {
        return sf::Color(0, 0, 255);
    }
    else if ("black" == mas_param2[0])
    {
        return sf::Color(0, 0, 0);
    }
    else if ("brown" == mas_param2[0])
    {
        return sf::Color(128, 64, 48);
    }
    else if ("green" == mas_param2[0])
    {
        return sf::Color(0, 255, 0);
    }
    else if ("white" == mas_param2[0])
    {
        return sf::Color(255, 255, 255);
    }
    else if ("cyan" == mas_param2[0])
    {
        return sf::Color(0, 255, 255);
    }
    else if ("yellow" == mas_param2[0])
    {
        return sf::Color(255, 255, 0);
    }
    else  if ("magenta" == mas_param2[0])
    {
        return sf::Color(255, 0, 255);
    }
    else  if ("gray" == mas_param2[0])
    {
        return sf::Color(80, 80, 80);
    }
    else if ("lightgray" == mas_param2[0])
    {
        return sf::Color(150, 150, 150);
    }
    else  if ("darkgray" == mas_param2[0])
    {
        return sf::Color(35, 35, 35);
    }
    else if ("orange" == mas_param2[0])
    {
        return sf::Color(255, 165, 0);
    }
    else if ("pink" == mas_param2[0])
    {
        return sf::Color(255, 192, 203);
    }
    else if ("purple" == mas_param2[0])
    {
        return sf::Color(128, 0, 128);
    }
    else {
        return sf::Color(255, 255, 255);
    }
}
////
////LETTERS
////

// Функция для отрисовки буквы "A" линиями
void drawLetterA(sf::RenderWindow& window, float x, float y) {
    sf::VertexArray lines(sf::Lines, 6);

    lines[0].position = sf::Vector2f(x, y + 80);
    lines[1].position = sf::Vector2f(x + 20, y);

    lines[2].position = sf::Vector2f(x + 40, y + 80);
    lines[3].position = sf::Vector2f(x + 20, y);

    lines[4].position = sf::Vector2f(x, y + 40);
    lines[5].position = sf::Vector2f(x + 40, y + 40);
    for (int i = 0; i < 6; i++) {
        lines[i].color = MyCol();
    }
    window.draw(lines);
}

// Функция для отрисовки буквы "B" линиями
void drawLetterB(sf::RenderWindow& window, float x, float y) {
    sf::VertexArray lines(sf::Lines, 10);

    lines[0].position = sf::Vector2f(x, y);
    lines[1].position = sf::Vector2f(x, y + 80);

    lines[2].position = sf::Vector2f(x, y);
    lines[3].position = sf::Vector2f(x + 40, y);

    lines[4].position = sf::Vector2f(x + 40, y);
    lines[5].position = sf::Vector2f(x, y + 40);

    lines[6].position = sf::Vector2f(x, y + 80);
    lines[7].position = sf::Vector2f(x + 40, y + 80);

    lines[8].position = sf::Vector2f(x + 40, y + 80);
    lines[9].position = sf::Vector2f(x, y + 40);
    for (int i = 0; i < 10; i++) {
        lines[i].color = MyCol();
    }
    window.draw(lines);
}

// Функция для отрисовки буквы "C" линиями
void drawLetterC(sf::RenderWindow& window, float x, float y) {
    sf::VertexArray lines(sf::Lines, 8);

    lines[0].position = sf::Vector2f(x, y);
    lines[1].position = sf::Vector2f(x, y + 80);

    lines[2].position = sf::Vector2f(x, y);
    lines[3].position = sf::Vector2f(x + 40, y);

    lines[4].position = sf::Vector2f(x, y + 80);
    lines[5].position = sf::Vector2f(x + 40, y + 80);
    for (int i = 0; i < 6; i++) {
        lines[i].color = MyCol();
    }
    window.draw(lines);
}

// Функция для отрисовки буквы "D" линиями
void drawLetterD(sf::RenderWindow& window, float x, float y) {
    sf::VertexArray lines(sf::Lines, 8);

    lines[0].position = sf::Vector2f(x, y);
    lines[1].position = sf::Vector2f(x, y + 80);

    lines[2].position = sf::Vector2f(x, y);
    lines[3].position = sf::Vector2f(x + 40, y + 10);

    lines[4].position = sf::Vector2f(x, y + 80);
    lines[5].position = sf::Vector2f(x + 40, y + 70);

    lines[6].position = sf::Vector2f(x + 40, y + 10);
    lines[7].position = sf::Vector2f(x + 40, y + 70);
    for (int i = 0; i < 8; i++) {
        lines[i].color = MyCol();
    }
    window.draw(lines);
}
//E
void drawLetterE(sf::RenderWindow& window, float x, float y) {
    sf::VertexArray lines(sf::Lines, 8);

    lines[0].position = sf::Vector2f(x, y);
    lines[1].position = sf::Vector2f(x, y + 80);

    lines[2].position = sf::Vector2f(x, y);
    lines[3].position = sf::Vector2f(x + 40, y);

    lines[4].position = sf::Vector2f(x, y + 80);
    lines[5].position = sf::Vector2f(x + 40, y + 80);

    lines[6].position = sf::Vector2f(x, y + 40);
    lines[7].position = sf::Vector2f(x + 40, y + 40);
    for (int i = 0; i < 8; i++) {
        lines[i].color = MyCol();
    }
    window.draw(lines);
}

//F
void drawLetterF(sf::RenderWindow& window, float x, float y) {
    sf::VertexArray lines(sf::Lines, 8);

    lines[0].position = sf::Vector2f(x, y);
    lines[1].position = sf::Vector2f(x, y + 80);

    lines[2].position = sf::Vector2f(x, y);
    lines[3].position = sf::Vector2f(x + 40, y);

    lines[4].position = sf::Vector2f(x, y + 40);
    lines[5].position = sf::Vector2f(x + 40, y + 40);
    for (int i = 0; i < 6; i++) {
        lines[i].color = MyCol();
    }
    window.draw(lines);
}
//G
void drawLetterG(sf::RenderWindow& window, float x, float y) {
    sf::VertexArray lines(sf::Lines, 10);

    lines[0].position = sf::Vector2f(x, y);
    lines[1].position = sf::Vector2f(x, y + 80);

    lines[2].position = sf::Vector2f(x, y);
    lines[3].position = sf::Vector2f(x + 40, y);

    lines[4].position = sf::Vector2f(x, y + 80);
    lines[5].position = sf::Vector2f(x + 40, y + 80);

    lines[6].position = sf::Vector2f(x + 40, y + 80);
    lines[7].position = sf::Vector2f(x + 40, y + 50);

    lines[8].position = sf::Vector2f(x + 40, y + 50);
    lines[9].position = sf::Vector2f(x + 25, y + 50);
    for (int i = 0; i < 10; i++) {
        lines[i].color = MyCol();
    }
    window.draw(lines);
}
//H
void drawLetterH(sf::RenderWindow& window, float x, float y) {
    sf::VertexArray lines(sf::Lines, 8);

    lines[0].position = sf::Vector2f(x, y);
    lines[1].position = sf::Vector2f(x, y + 80);

    lines[2].position = sf::Vector2f(x + 40, y);
    lines[3].position = sf::Vector2f(x + 40, y + 80);

    lines[4].position = sf::Vector2f(x, y + 40);
    lines[5].position = sf::Vector2f(x + 40, y + 40);
    for (int i = 0; i < 6; i++) {
        lines[i].color = MyCol();
    }
    window.draw(lines);
}
//I
void drawLetterI(sf::RenderWindow& window, float x, float y) {
    sf::VertexArray lines(sf::Lines, 6);

    lines[0].position = sf::Vector2f(x + 10, y);
    lines[1].position = sf::Vector2f(x + 10, y + 80);

    lines[2].position = sf::Vector2f(x, y);
    lines[3].position = sf::Vector2f(x + 20, y);

    lines[4].position = sf::Vector2f(x, y + 80);
    lines[5].position = sf::Vector2f(x + 20, y + 80);
    for (int i = 0; i < 6; i++) {
        lines[i].color = MyCol();
    }
    window.draw(lines);
}
//J
void drawLetterJ(sf::RenderWindow& window, float x, float y) {
    sf::VertexArray lines(sf::Lines, 8);

    lines[0].position = sf::Vector2f(x + 20, y);
    lines[1].position = sf::Vector2f(x + 20, y + 80);

    lines[2].position = sf::Vector2f(x, y);
    lines[3].position = sf::Vector2f(x + 40, y);

    lines[4].position = sf::Vector2f(x + 20, y + 80);
    lines[5].position = sf::Vector2f(x, y + 80);

    lines[6].position = sf::Vector2f(x, y + 80);
    lines[7].position = sf::Vector2f(x, y + 60);
    for (int i = 0; i < 8; i++) {
        lines[i].color = MyCol();
    }
    window.draw(lines);
}

//K
void drawLetterK(sf::RenderWindow& window, float x, float y) {
    sf::VertexArray lines(sf::Lines, 6);

    lines[0].position = sf::Vector2f(x, y);
    lines[1].position = sf::Vector2f(x, y + 80);

    lines[2].position = sf::Vector2f(x, y + 40);
    lines[3].position = sf::Vector2f(x + 40, y);

    lines[4].position = sf::Vector2f(x, y + 40);
    lines[5].position = sf::Vector2f(x + 40, y + 80);

    for (int i = 0; i < 6; i++) {
        lines[i].color = MyCol();
    }
    window.draw(lines);
}
//L
void drawLetterL(sf::RenderWindow& window, float x, float y) {
    sf::VertexArray lines(sf::Lines, 4);

    lines[0].position = sf::Vector2f(x, y);
    lines[1].position = sf::Vector2f(x, y + 80);

    lines[2].position = sf::Vector2f(x, y + 80);
    lines[3].position = sf::Vector2f(x + 40, y + 80);

    for (int i = 0; i < 4; i++) {
        lines[i].color = MyCol();
    }
    window.draw(lines);
}

//M
void drawLetterM(sf::RenderWindow& window, float x, float y) {
    sf::VertexArray lines(sf::Lines, 8);

    lines[0].position = sf::Vector2f(x, y);
    lines[1].position = sf::Vector2f(x, y + 80);

    lines[2].position = sf::Vector2f(x, y);
    lines[3].position = sf::Vector2f(x + 20, y + 60);

    lines[4].position = sf::Vector2f(x + 20, y + 60);
    lines[5].position = sf::Vector2f(x + 40, y);

    lines[6].position = sf::Vector2f(x + 40, y);
    lines[7].position = sf::Vector2f(x + 40, y + 80);

    for (int i = 0; i < 8; i++) {
        lines[i].color = MyCol();
    }
    window.draw(lines);
}

//N
void drawLetterN(sf::RenderWindow& window, float x, float y) {
    sf::VertexArray lines(sf::Lines, 6);

    lines[0].position = sf::Vector2f(x, y);
    lines[1].position = sf::Vector2f(x, y + 80);

    lines[2].position = sf::Vector2f(x, y);
    lines[3].position = sf::Vector2f(x + 40, y + 80);

    lines[4].position = sf::Vector2f(x + 40, y + 80);
    lines[5].position = sf::Vector2f(x + 40, y);

    for (int i = 0; i < 6; i++) {
        lines[i].color = MyCol();
    }
    window.draw(lines);
}
//O
void drawLetterO(sf::RenderWindow& window, float x, float y) {
    sf::VertexArray lines(sf::Lines, 8);

    lines[0].position = sf::Vector2f(x, y);
    lines[1].position = sf::Vector2f(x, y + 80);

    lines[2].position = sf::Vector2f(x, y);
    lines[3].position = sf::Vector2f(x + 40, y);

    lines[4].position = sf::Vector2f(x, y + 80);
    lines[5].position = sf::Vector2f(x + 40, y + 80);

    lines[6].position = sf::Vector2f(x + 40, y);
    lines[7].position = sf::Vector2f(x + 40, y + 80);

    for (int i = 0; i < 8; i++) {
        lines[i].color = MyCol();
    }
    window.draw(lines);
}

//P
void drawLetterP(sf::RenderWindow& window, float x, float y) {
    sf::VertexArray lines(sf::Lines, 6);

    lines[0].position = sf::Vector2f(x, y);
    lines[1].position = sf::Vector2f(x, y + 80);

    lines[2].position = sf::Vector2f(x, y);
    lines[3].position = sf::Vector2f(x + 40, y + 15);

    lines[4].position = sf::Vector2f(x + 40, y + 15);
    lines[5].position = sf::Vector2f(x, y + 30);
    
    for (int i = 0; i < 6; i++) {
        lines[i].color = MyCol();
    }
    window.draw(lines);
}
//Q
void drawLetterQ(sf::RenderWindow& window, float x, float y) {
    sf::VertexArray lines(sf::Lines, 10);

    lines[0].position = sf::Vector2f(x, y);
    lines[1].position = sf::Vector2f(x, y + 70);

    lines[2].position = sf::Vector2f(x, y);
    lines[3].position = sf::Vector2f(x + 40, y);

    lines[4].position = sf::Vector2f(x, y + 70);
    lines[5].position = sf::Vector2f(x + 40, y + 70);

    lines[6].position = sf::Vector2f(x + 40, y);
    lines[7].position = sf::Vector2f(x + 40, y + 70);

    lines[8].position = sf::Vector2f(x + 40, y + 80);
    lines[9].position = sf::Vector2f(x + 20, y + 60);
    for (int i = 0; i < 10; i++) {
        lines[i].color = MyCol();
    }
    window.draw(lines);
}
//R
void drawLetterR(sf::RenderWindow& window, float x, float y) {
    sf::VertexArray lines(sf::Lines, 8);

    lines[0].position = sf::Vector2f(x, y);
    lines[1].position = sf::Vector2f(x, y + 80);

    lines[2].position = sf::Vector2f(x, y);
    lines[3].position = sf::Vector2f(x + 40, y + 15);

    lines[4].position = sf::Vector2f(x + 40, y + 15);
    lines[5].position = sf::Vector2f(x, y + 30);

    lines[6].position = sf::Vector2f(x + 0, y + 30);
    lines[7].position = sf::Vector2f(x + 40, y + 80);

    for (int i = 0; i < 8; i++) {
        lines[i].color = MyCol();
    }
    window.draw(lines);
}

//S
void drawLetterS(sf::RenderWindow& window, float x, float y) {
    sf::VertexArray lines(sf::Lines, 10);

    lines[0].position = sf::Vector2f(x + 40, y);
    lines[1].position = sf::Vector2f(x, y);

    lines[2].position = sf::Vector2f(x, y);
    lines[3].position = sf::Vector2f(x, y + 40);

    lines[4].position = sf::Vector2f(x, y + 40);
    lines[5].position = sf::Vector2f(x + 40, y + 40);

    lines[6].position = sf::Vector2f(x + 40, y + 40);
    lines[7].position = sf::Vector2f(x + 40, y + 80);

    lines[8].position = sf::Vector2f(x + 40, y + 80);
    lines[9].position = sf::Vector2f(x, y + 80);

    for (int i = 0; i < 10; i++) {
        lines[i].color = MyCol();
    }
    window.draw(lines);
}
//T
void drawLetterT(sf::RenderWindow& window, float x, float y) {
    sf::VertexArray lines(sf::Lines, 4);

    lines[0].position = sf::Vector2f(x + 20, y);
    lines[1].position = sf::Vector2f(x + 20, y + 80);

    lines[2].position = sf::Vector2f(x, y);
    lines[3].position = sf::Vector2f(x + 40, y);
    for (int i = 0; i < 4; i++) {
        lines[i].color = MyCol();
    }
    window.draw(lines);
}

//U
void drawLetterU(sf::RenderWindow& window, float x, float y) {
    sf::VertexArray lines(sf::Lines, 6);

    lines[0].position = sf::Vector2f(x, y);
    lines[1].position = sf::Vector2f(x, y + 80);

    lines[2].position = sf::Vector2f(x, y + 80);
    lines[3].position = sf::Vector2f(x + 40, y + 80);

    lines[4].position = sf::Vector2f(x + 40, y);
    lines[5].position = sf::Vector2f(x + 40, y + 80);
    for (int i = 0; i < 6; i++) {
        lines[i].color = MyCol();
    }
    window.draw(lines);
}
//V
void drawLetterV(sf::RenderWindow& window, float x, float y) {
    sf::VertexArray lines(sf::Lines, 4);

    lines[0].position = sf::Vector2f(x, y);
    lines[1].position = sf::Vector2f(x + 20, y + 80);

    lines[2].position = sf::Vector2f(x + 20, y + 80);
    lines[3].position = sf::Vector2f(x + 40, y);
    for (int i = 0; i < 4; i++) {
        lines[i].color = MyCol();
    }
    window.draw(lines);
}
//W
void drawLetterW(sf::RenderWindow& window, float x, float y) {
    sf::VertexArray lines(sf::Lines, 8);

    lines[0].position = sf::Vector2f(x, y);
    lines[1].position = sf::Vector2f(x, y + 80);

    lines[2].position = sf::Vector2f(x, y + 80);
    lines[3].position = sf::Vector2f(x + 20, y + 20);

    lines[4].position = sf::Vector2f(x + 20, y + 20);
    lines[5].position = sf::Vector2f(x + 40, y + 80);

    lines[6].position = sf::Vector2f(x + 40, y);
    lines[7].position = sf::Vector2f(x + 40, y + 80);
    for (int i = 0; i < 8; i++) {
        lines[i].color = MyCol();
    }

    window.draw(lines);
}
//X
void drawLetterX(sf::RenderWindow& window, float x, float y) {
    sf::VertexArray lines(sf::Lines, 4);

    lines[0].position = sf::Vector2f(x, y);
    lines[1].position = sf::Vector2f(x + 40, y + 80);

    lines[2].position = sf::Vector2f(x + 40, y);
    lines[3].position = sf::Vector2f(x, y + 80);

    for (int i = 0; i < 4; i++) {
        lines[i].color = MyCol();
    }
    window.draw(lines);
}
//Y
void drawLetterY(sf::RenderWindow& window, float x, float y) {
    sf::VertexArray lines(sf::Lines, 6);

    lines[0].position = sf::Vector2f(x + 20, y + 80);
    lines[1].position = sf::Vector2f(x + 20, y + 30);

    lines[2].position = sf::Vector2f(x + 20, y + 30);
    lines[3].position = sf::Vector2f(x, y);

    lines[4].position = sf::Vector2f(x + 20, y + 30);
    lines[5].position = sf::Vector2f(x + 40, y);

    for (int i = 0; i < 6; i++) {
        lines[i].color = MyCol();
    }
    window.draw(lines);
}
//Z
void drawLetterZ(sf::RenderWindow& window, float x, float y) {
    sf::VertexArray lines(sf::Lines, 6);

    lines[0].position = sf::Vector2f(x, y);
    lines[1].position = sf::Vector2f(x + 40, y);

    lines[2].position = sf::Vector2f(x + 40, y);
    lines[3].position = sf::Vector2f(x, y + 80);

    lines[4].position = sf::Vector2f(x, y + 80);
    lines[5].position = sf::Vector2f(x + 40, y + 80);

    for (int i = 0; i < 6; i++) {
        lines[i].color = MyCol();
    }


    window.draw(lines);
}


////
////LETTERS
////
// Функция для приема сообщений в отдельном потоке
void receiveMessages(sf::UdpSocket& socket) {
    while (running) {
        sf::IpAddress clientAddress;
        unsigned short clientPort;
        sf::Packet packet;
        std::vector<sf::Uint8> pixelData;

        // Пытаемся принять пакет от клиента
        if (socket.receive(buffer, sizeof(buffer), received, clientAddress, clientPort) == sf::Socket::Done) {
            std::string message(buffer);
            std::cout << "Получено сообщение от клиента (" << clientAddress << ":" << clientPort << "): " << message << std::endl;
            receivedText.setString("Your Command: " + message);
            ParseCommand(message);
            mas_param[1] = rand() % 10 + 1;
            if (mas_param[0] == mas_param[1])
            {
                erg = true;
            }
            else {
                erg = false;
            }
            this_color = MyCol();

        }

        else {
            std::cerr << "Ошибка при приеме данных" << std::endl;
        }
        if (this_mode == 75)
        {
           
            if (socket.send(mesage2.c_str(), mesage2.size() + 1, clientAddress, clientPort) != sf::Socket::Done) {
                std::cout << "Ошибка при отправке ответа" << std::endl;
            }
        }
        if (this_mode == 77)
        {
            image.create(100, 100);
            if (socket.receive(pixelData.data(), pixelData.size(), received, clientAddress, clientPort) == sf::Socket::Done) {
                // Запишите полученные пиксели в изображение
                for (int i = 0; i < image.getSize().x; i++) {
                    for (int j = 0; j < image.getSize().y; j++) {
                        sf::Color color;
                        color.r = pixelData[(i * image.getSize().y + j) * 4];
                        color.g = pixelData[(i * image.getSize().y + j) * 4 + 1];
                        color.b = pixelData[(i * image.getSize().y + j) * 4 + 2];
                        color.a = pixelData[(i * image.getSize().y + j) * 4 + 3];
                        image.setPixel(i, j, color);
                    }
                }
            }
        }
    }
}

int main() {
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, "");
    _getcwd(pathe1, MAX_PATH);

    int lol = 0; //Для громкости
    //Белый шум
    std::random_device rd1;
    std::mt19937 gen1(rd1());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

    // Создаем буфер для звука с установленной частотой дискретизации
    sf::SoundBuffer buffer1;
    buffer1.loadFromSamples(nullptr, 0, 1, SAMPLE_RATE); // 1 канал, частота дискретизации

    // Вычисляем количество сэмплов на основе частоты дискретизации и продолжительности
    int numSamples1 = SAMPLE_RATE * DURATION;
    std::vector<sf::Int16> samples1(numSamples1);

    // Заполняем буфер случайными значениями для создания белого шума
    for (int i = 0; i < numSamples1; i++) {
        sf::Int16 sampleValue = static_cast<sf::Int16>(dist(gen1) * 32767); // Преобразование в 16-битное целое число
        samples1[i] = sampleValue;
    }
    buffer1.loadFromSamples(samples1.data(), numSamples1, 1, SAMPLE_RATE);
    /////


    // Создаем объект звука и воспроизводим белый шум
    sf::Sound sound(buffer1);


    ///////Корич 
    sf::SoundBuffer buffer3;
    sf::Sound sound3;
    // Создаем буфер для аудио
    std::vector<sf::Int16> audioData2(SIZEE);

    // Устанавливаем начальное зерно для генератора случайных чисел
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Генерируем коричневый шум
    sf::Int16 lastValue = 0;
    for (unsigned int i = 0; i < SIZEE; ++i)
    {
        // Генерируем случайное значение
        sf::Int16 randomValue = static_cast<sf::Int16>(std::rand() % 65536 - 32768);

        // Применяем фильтр для создания коричневого шума
        lastValue = static_cast<sf::Int16>(0.02 * randomValue + 0.98 * lastValue);

        // Записываем значение в аудио-буфер
        audioData2[i] = lastValue;
    }

    // Загружаем данные в буфер аудио
    if (!buffer3.loadFromSamples(audioData2.data(), SIZEE, 1, SAMPLE_RATE))
    {
        return 1;
    }
    sound3.setBuffer(buffer3);
    //////Розовый

    std::vector<sf::Int16> pinkNoise = generatePinkNoise(SAMPLE_RATE);

    // Создаем звуковой буфер и загружаем в него аудиоданные
    sf::SoundBuffer buffer2;
    buffer2.loadFromSamples(pinkNoise.data(), SAMPLE_RATE, 1, SAMPLE_RATE);

    // Создаем звуковой буфер и загружаем в него аудиоданные

    sf::Sound sound2(buffer2);


    sf::Clock clock; //Часы для таймера
    sf::Clock clocke;

    //Путь
    sf::RenderWindow serverWindow(sf::VideoMode(800, 600), "SFML UDP Сервер");

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int screenWidth = desktopMode.width;
    unsigned int screenHeight = desktopMode.height;

    unsigned int windowWidth = serverWindow.getSize().x;
    unsigned int windowHeight = serverWindow.getSize().y;

    std::string buf1 = std::to_string(screenWidth);
    std::string buf2 = std::to_string(screenHeight);
    std::string buf3 = std::to_string(windowWidth);
    std::string buf4 = std::to_string(windowHeight);

    mesage2 = "screenWidth: " + buf1 + "\nscreenHeight: " + buf2 +
        "\nwindowWidth: " + buf3 + "\nwindowHeight: " + buf4;


    std::string exep(pathe1);
    sf::UdpSocket socket;
    unsigned short serverPort = 12345;

    if (socket.bind(serverPort) != sf::Socket::Done) {
        std::cerr << "Ошибка при привязке к порту " << serverPort << std::endl;
        return -1;
    }

    sf::Font font;
    if (!font.loadFromFile(exep + "\\font\\arial.ttf")) {
        std::cerr << "Ошибка при загрузке шрифта" << std::endl;
        return -1;
    }

    sf::RectangleShape rectangle;

    receivedText.setFont(font);
    receivedText.setCharacterSize(24);
    receivedText.setFillColor(sf::Color::White);
    receivedText.setPosition(20, 20);
    std::cout << "Сервер запущен. Ожидание команд..." << std::endl;
    sf::Color backgroundColor = sf::Color::Black;
    // Запускаем поток для приема сообщений
    std::thread receiveThread(receiveMessages, std::ref(socket));

    sf::Music music;

    if (!music.openFromFile(exep + "\\exm.mp3")) {
        return -1;
    }
    music.setLoop(true);
    music.setVolume(5);

    while (serverWindow.isOpen()) {
        sf::Event event;
        while (serverWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                running = false;
                receiveThread.join(); // Дожидаемся завершения потока
                serverWindow.close();
            }
        }
        // Выводим текст на окно сервера
        serverWindow.clear(backgroundColor);
        mutex.lock();
        serverWindow.draw(receivedText);
        if (this_mode == 1)
        {

            sf::RectangleShape rectangle(sf::Vector2f(mas_param[2], mas_param[3]));
            rectangle.setPosition(mas_param[0], mas_param[1]);//Прямоугольник
            rectangle.setFillColor(sf::Color::Transparent); //Заливка без цвета
            rectangle.setOutlineColor(this_color);
            rectangle.setOutlineThickness(2.0f);
            rectangle.setRotation(rotat);
            serverWindow.draw(rectangle);
        }
        if (this_mode == 6)
        {
            sf::RectangleShape rectangle2(sf::Vector2f(mas_param[2], mas_param[3]));
            rectangle2.setPosition(mas_param[0], mas_param[1]);//Прямоугольник
            rectangle2.setFillColor(this_color); //Заливка цвета
            rectangle2.setRotation(rotat);
            serverWindow.draw(rectangle2);
        }
        if (this_mode == 11)
        {
            //Элипс создание
            sf::ConvexShape ellipse;

            int numPoints = 100; //Кол-во точек
            ellipse.setPointCount(numPoints);

            float horizontalRadius = mas_param[2];
            float verticalRadius = mas_param[3];

            for (int i = 0; i < numPoints; ++i)
            {
                float angle = i * 2 * 3.14 / numPoints;
                float x = horizontalRadius * std::cos(angle);
                float y = verticalRadius * std::sin(angle);

                ellipse.setPoint(i, sf::Vector2f(x, y));
            }
            //Ну и параметры :)
            ellipse.setPosition(mas_param[0], mas_param[1]);

            ellipse.setFillColor(sf::Color::Transparent);
            ellipse.setOutlineColor(this_color);
            ellipse.setOutlineThickness(2.0f);
            ellipse.setRotation(rotat);


            serverWindow.draw(ellipse);
        }
        if (this_mode == 16)
        {
            //Заполненный эллипс
            sf::ConvexShape ellipse;

            int numPoints = 100;
            ellipse.setPointCount(numPoints);

            float horizontalRadius = mas_param[2];
            float verticalRadius = mas_param[3];

            for (int i = 0; i < numPoints; ++i)
            {
                float angle = i * 2 * 3.14 / numPoints;
                float x = horizontalRadius * std::cos(angle);
                float y = verticalRadius * std::sin(angle);

                ellipse.setPoint(i, sf::Vector2f(x, y));
            }

            ellipse.setPosition(mas_param[0], mas_param[1]);

            ellipse.setFillColor(this_color);
            ellipse.setOutlineColor(this_color);
            ellipse.setOutlineThickness(2.0f);
            ellipse.setRotation(rotat);


            serverWindow.draw(ellipse);
        }

        if (this_mode == 21)
        {
            sf::ConvexShape hexagon;
            hexagon.setPointCount(6); // Устанавливаем количество вершин (6 для шестиугольника)

            // Радиус шестиугольника
            float radius = mas_param[0];

            // Устанавливаем координаты вершин
            for (int i = 0; i < 6; ++i)
            {
                float angle = i * 2 * 3.14 / 6; // Угол между вершинами
                float x = radius * std::cos(angle);
                float y = radius * std::sin(angle);
                hexagon.setPoint(i, sf::Vector2f(x, y));
            }

            hexagon.setFillColor(sf::Color::Transparent); // Задаем цвет заливки
            hexagon.setOutlineColor(this_color); // Задаем цвет контура
            hexagon.setOutlineThickness(2); // Задаем толщину контура
            hexagon.setPosition(mas_param[1], mas_param[2]);
            hexagon.setRotation(rotat);
            serverWindow.draw(hexagon);
        }
        if (this_mode == 27)
        {
            sf::ConvexShape hexagon2;
            hexagon2.setPointCount(6); // Устанавливаем количество вершин (6 для шестиугольника)

            // Радиус шестиугольника
            float radius = mas_param[0];

            // Устанавливаем координаты вершин
            for (int i = 0; i < 6; ++i)
            {
                float angle = i * 2 * 3.14 / 6; // Угол между вершинами
                float x = radius * std::cos(angle);
                float y = radius * std::sin(angle);
                hexagon2.setPoint(i, sf::Vector2f(x, y));
            }

            hexagon2.setFillColor(this_color); // Задаем цвет заливки
            hexagon2.setOutlineColor(this_color); // Задаем цвет контура
            hexagon2.setOutlineThickness(2); // Задаем толщину контура
            hexagon2.setPosition(mas_param[1], mas_param[2]);
            hexagon2.setRotation(rotat);
            serverWindow.draw(hexagon2);
        }
        if (this_mode == 33)
        {

            sf::RectangleShape square(sf::Vector2f(mas_param[2], mas_param[2]));
            square.setPosition(mas_param[0], mas_param[1]);//Квадрат
            square.setFillColor(sf::Color::Transparent); //Заливка без цвета
            square.setOutlineColor(this_color);
            square.setOutlineThickness(2.0f);
            square.setRotation(rotat);
            serverWindow.draw(square);
        }
        if (this_mode == 37)
        {
            sf::RectangleShape square2(sf::Vector2f(mas_param[2], mas_param[2]));
            square2.setPosition(mas_param[0], mas_param[1]);//Квадрат
            square2.setFillColor(this_color); //Заливка цвета
            square2.setRotation(rotat);
            serverWindow.draw(square2);
        }
        if (this_mode == 41)
        {
            sf::CircleShape circle;
            float radius = mas_param[2];
            circle.setRadius(radius);

            circle.setPosition(mas_param[0], mas_param[1]);

            circle.setFillColor(sf::Color::Transparent); //Заливка без цвета
            circle.setOutlineColor(this_color);
            circle.setOutlineThickness(2.0f);
            circle.setRotation(rotat);
            serverWindow.draw(circle);
        }
        if (this_mode == 45)
        {
            sf::CircleShape circle2;
            float radius = mas_param[2];
            circle2.setRadius(radius);

            circle2.setPosition(mas_param[0], mas_param[1]);

            circle2.setFillColor(this_color); //Заливка без цвета
            circle2.setRotation(rotat);
            serverWindow.draw(circle2);
        }
        if (this_mode == 49)
        {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(mas_param[0], mas_param[1]), this_color),    // начальная точка
                sf::Vertex(sf::Vector2f(mas_param[2], mas_param[3]), this_color)    // конечная точка
            };
            serverWindow.draw(line, 2, sf::Lines);
        }
        if (this_mode == 54)
        {
            sf::Text text2;
            text2.setPosition(mas_param[0], mas_param[1]);
            text2.setCharacterSize(mas_param[2]);
            text2.setFont(font);
            text2.setFillColor(this_color);
            text2.setString(mas_param2[1]);
            text2.setRotation(rotat);
            std::cout << std::endl << rotat << std::endl;
            serverWindow.draw(text2);
        }
        if (this_mode == 59)
        {
            sf::Texture texture3;
            if (!texture3.loadFromFile(exep + "\\your_image\\" + mas_param2[0] + ".png")) {
                //if (!texture3.loadFromFile(exep + "\\your_image\\" + mas_param2[0] + ".png")) {
                    // Обработка ошибки загрузки текстуры
                std::cerr << "Ошибка загрузки текстуры!" << std::endl;
                return -1;
            }
            sf::Sprite sprite3(texture3);
            sprite3.setPosition(mas_param[0], mas_param[1]);
            sprite3.setRotation(rotat);
            serverWindow.draw(sprite3);
        }
        if (this_mode == 62) {
            backgroundColor = this_color;
        }
        if (this_mode == 63 && is_white == true)
        {
            lol = mas_param[0];
            if (mas_param[0] > 100)
            {
                lol = 100;
            }
            int lol = 30;
            sound.setVolume(lol);
            sound.play();
            is_white = false;
        }
        if (this_mode == 64 && is_brown == true)
        {
            lol = mas_param[0];
            if (mas_param[0] > 100)
            {
                lol = 100;
            }
            sound3.setVolume(lol);
            sound3.play();
            is_brown = false;
        }
        if (this_mode == 65 && is_pink == true)
        {
            lol = mas_param[0];
            if (mas_param[0] > 100)
            {
                lol = 100;
            }
            sound2.setVolume(50);
            sound2.play();
            is_pink = false;
        }
        if (this_mode == 66)
        {
            sf::Text text2;
            text2.setPosition(mas_param[0], mas_param[1]);
            text2.setCharacterSize(mas_param[2]);
            text2.setFont(font);
            text2.setFillColor(this_color);
            if (tii < mytime)
            {

                std::string textee = "Time: " + std::to_string(tii);
                if (clock.getElapsedTime() >= sf::seconds(1.0f))
                {
                    std::cout << tii << std::endl;
                    tii++;
                    clock.restart();
                }
                text2.setString(textee);
            }
            text2.setRotation(rotat);

            serverWindow.draw(text2);
        }


        if (this_mode == 71)
        {
            int x = mas_param[0];
            int y = mas_param[1];
            std::string wordo = mas_param2[1];
            for (char letter : wordo) {
                if (letter == 'A' || letter == 'a') {
                    drawLetterA(serverWindow, x, y);
                }
                else if (letter == 'B' || letter == 'b') {
                    drawLetterB(serverWindow, x, y);
                }
                else if (letter == 'C' || letter == 'c') {
                    drawLetterC(serverWindow, x, y);
                }
                else if (letter == 'D' || letter == 'd') {
                    drawLetterD(serverWindow, x, y);
                }
                else if (letter == 'E' || letter == 'e') {
                    drawLetterE(serverWindow, x, y);
                }
                else if (letter == 'F' || letter == 'f') {
                    drawLetterF(serverWindow, x, y);
                }
                else if (letter == 'G' || letter == 'g') {
                    drawLetterG(serverWindow, x, y);
                }
                else if (letter == 'H' || letter == 'h') {
                    drawLetterH(serverWindow, x, y);
                }
                else if (letter == 'I' || letter == 'i') {
                    drawLetterI(serverWindow, x, y);
                }
                else if (letter == 'J' || letter == 'j') {
                    drawLetterJ(serverWindow, x, y);
                }
                else if (letter == 'K' || letter == 'k') {
                    drawLetterK(serverWindow, x, y);
                }
                else if (letter == 'L' || letter == 'l') {
                    drawLetterL(serverWindow, x, y);
                }
                else if (letter == 'M' || letter == 'm') {
                    drawLetterM(serverWindow, x, y);
                }
                else if (letter == 'N' || letter == 'n') {
                    drawLetterN(serverWindow, x, y);
                }
                else if (letter == 'O' || letter == 'o') {
                    drawLetterO(serverWindow, x, y);
                }
                else if (letter == 'P' || letter == 'p') {
                    drawLetterP(serverWindow, x, y);
                }
                else if (letter == 'Q' || letter == 'q') {
                    drawLetterQ(serverWindow, x, y);
                }
                else if (letter == 'R' || letter == 'r') {
                    drawLetterR(serverWindow, x, y);
                }
                else if (letter == 'S' || letter == 's') {
                    drawLetterS(serverWindow, x, y);
                }
                else if (letter == 'T' || letter == 't') {
                    drawLetterT(serverWindow, x, y);
                }
                else if (letter == 'U' || letter == 'u') {
                    drawLetterU(serverWindow, x, y);
                }
                else if (letter == 'V' || letter == 'v') {
                    drawLetterV(serverWindow, x, y);
                }
                else if (letter == 'W' || letter == 'w') {
                    drawLetterW(serverWindow, x, y);
                }
                else if (letter == 'X' || letter == 'x') {
                    drawLetterX(serverWindow, x, y);
                }
                else if (letter == 'Y' || letter == 'y') {
                    drawLetterY(serverWindow, x, y);
                }
                else if (letter == 'Z' || letter == 'z') {
                    drawLetterZ(serverWindow, x, y);
                }
                x += 60;
            }

        }
        if (this_mode == 77 && is_buf == true)
        {
            sf::Texture texture;
            if (!texture.loadFromFile(exep + "\\buf3.png")) {
                return -1;
            }
            sf::Sprite sprite;
            sprite.setTexture(texture);
            sprite.setPosition(mas_param[0], mas_param[1]);
            serverWindow.draw(sprite);
        }
        if (this_mode == 80)
        {
            sf::Text text2;
            text2.setPosition(100, 100);
            text2.setCharacterSize(24);
            text2.setFont(font);
            int random_n = rand() % 10 + 1;
            if (erg == true)
            {
                std::cout << std::endl << mas_param[0] << "  " << erg << std::endl;
                text2.setFillColor(sf::Color::Green);
                text2.setString("You guess! It's " + std::to_string(mas_param[0]));
            }
            if (erg == false)
            {
                std::cout << std::endl << mas_param[0] << "  " << erg << std::endl;
                text2.setFillColor(sf::Color::Red);
                text2.setString("You wrong! It's " + std::to_string(mas_param[1]));
            }
            serverWindow.draw(text2);
        }
        if (this_mode == 81)
        {
            sf::Text text2;
            text2.setCharacterSize(mas_param[2]);
            text2.setFont(font);
            text2.setFillColor(this_color);
            
            std::time_t currentTime;
            std::tm timeInfo;
            time(&currentTime);

            if (localtime_s(&timeInfo, &currentTime) != 0) {
                std::cerr << "Failed to get local time" << std::endl;
                return 1;
            }

            char timeStr[9]; // Место для форматированной строки времени (HH:MM:SS)
            if (strftime(timeStr, sizeof(timeStr), "%H:%M:%S", &timeInfo) == 0) {
                std::cerr << "Failed to format time" << std::endl;
                return 1;
            }
            text2.setPosition(sf::Vector2f(serverWindow.getSize().x / 2 - text2.getLocalBounds().width / 2, serverWindow.getSize().y / 2 - text2.getLocalBounds().height / 2));
            text2.setString("Your time: " + std::string(timeStr));
            serverWindow.draw(text2);

        }
        if (this_mode == 85)
        {
            sf::RectangleShape square(sf::Vector2f(mas_param[0], mas_param[0]));
            square.setPosition(sf::Vector2f(serverWindow.getSize().x / 2 - square.getLocalBounds().width / 2, serverWindow.getSize().y / 2 - square.getLocalBounds().height / 2));//Квадрат
            square.setFillColor(sf::Color::Transparent); //Заливка без цвета
            square.setOutlineColor(sf::Color::Red);
            square.setOutlineThickness(2.0f);

            sf::RectangleShape square2(sf::Vector2f((mas_param[0]), (mas_param[0])));
            square2.setPosition(sf::Vector2f(serverWindow.getSize().x / 2 - square2.getLocalBounds().width / 2, serverWindow.getSize().y / 2 - square2.getLocalBounds().height / 2));//Квадрат
            square2.setFillColor(sf::Color::Transparent); //Заливка без цвета
            square2.setOutlineColor(sf::Color(255, 165, 0));
            square2.setOutlineThickness(2.0f);

            sf::RectangleShape square3(sf::Vector2f((mas_param[0]), (mas_param[0])));
            square3.setPosition(sf::Vector2f(serverWindow.getSize().x / 2 - square2.getLocalBounds().width / 2, serverWindow.getSize().y / 2 - square2.getLocalBounds().height / 2));//Квадрат
            square3.setFillColor(sf::Color::Transparent); //Заливка без цвета
            square3.setOutlineColor(sf::Color::Green);
            square3.setOutlineThickness(2.0f);

            sf::RectangleShape square4(sf::Vector2f((mas_param[0]), (mas_param[0])));
            square4.setPosition(sf::Vector2f(serverWindow.getSize().x / 2 - square2.getLocalBounds().width / 2, serverWindow.getSize().y / 2 - square2.getLocalBounds().height / 2));//Квадрат
            square4.setFillColor(sf::Color::Transparent); //Заливка без цвета
            square4.setOutlineColor(sf::Color::Blue);
            square4.setOutlineThickness(2.0f);

            sf::RectangleShape square5(sf::Vector2f((mas_param[0]), (mas_param[0])));
            square5.setPosition(sf::Vector2f(serverWindow.getSize().x / 2 - square2.getLocalBounds().width / 2, serverWindow.getSize().y / 2 - square2.getLocalBounds().height / 2));//Квадрат
            square5.setFillColor(sf::Color::Transparent); //Заливка без цвета
            square5.setOutlineColor(sf::Color::Cyan);
            square5.setOutlineThickness(2.0f);

            sf::RectangleShape square6(sf::Vector2f((mas_param[0]), (mas_param[0])));
            square6.setPosition(sf::Vector2f(serverWindow.getSize().x / 2 - square2.getLocalBounds().width / 2, serverWindow.getSize().y / 2 - square2.getLocalBounds().height / 2));//Квадрат
            square6.setFillColor(sf::Color::Transparent); //Заливка без цвета
            square6.setOutlineColor(sf::Color::Magenta);
            square6.setOutlineThickness(2.0f);

            sf::RectangleShape square7(sf::Vector2f((mas_param[0]), (mas_param[0])));
            square7.setPosition(sf::Vector2f(serverWindow.getSize().x / 2 - square2.getLocalBounds().width / 2, serverWindow.getSize().y / 2 - square2.getLocalBounds().height / 2));//Квадрат
            square7.setFillColor(sf::Color::Transparent); //Заливка без цвета
            square7.setOutlineColor(sf::Color(128, 0, 128));
            square7.setOutlineThickness(2.0f);

            sf::RectangleShape square8(sf::Vector2f((mas_param[0]), (mas_param[0])));
            square8.setPosition(sf::Vector2f(serverWindow.getSize().x / 2 - square2.getLocalBounds().width / 2, serverWindow.getSize().y / 2 - square2.getLocalBounds().height / 2));//Квадрат
            square8.setFillColor(sf::Color::Transparent); //Заливка без цвета
            square8.setOutlineColor(sf::Color::Yellow);
            square8.setOutlineThickness(2.0f);

            sf::RectangleShape square9(sf::Vector2f((mas_param[0]), (mas_param[0])));
            square9.setPosition(sf::Vector2f(serverWindow.getSize().x / 2 - square2.getLocalBounds().width / 2, serverWindow.getSize().y / 2 - square2.getLocalBounds().height / 2));//Квадрат
            square9.setFillColor(sf::Color::Transparent); //Заливка без цвета
            square9.setOutlineColor(sf::Color::White);
            square9.setOutlineThickness(2.0f);
            
            sf::RectangleShape square10(sf::Vector2f((mas_param[0]), (mas_param[0])));
            square10.setPosition(sf::Vector2f(serverWindow.getSize().x / 2 - square2.getLocalBounds().width / 2, serverWindow.getSize().y / 2 - square2.getLocalBounds().height / 2));//Квадрат
            square10.setFillColor(sf::Color::Transparent); //Заливка без цвета
            square10.setOutlineColor(sf::Color(255, 192, 203));
            square10.setOutlineThickness(2.0f);
            
            sf::RectangleShape square11(sf::Vector2f((mas_param[0]), (mas_param[0])));
            square11.setPosition(sf::Vector2f(serverWindow.getSize().x / 2 - square2.getLocalBounds().width / 2, serverWindow.getSize().y / 2 - square2.getLocalBounds().height / 2));//Квадрат
            square11.setFillColor(sf::Color::Transparent); //Заливка без цвета
            square11.setOutlineColor(sf::Color(35, 35, 35));
            square11.setOutlineThickness(2.0f);

            sf::RectangleShape square12(sf::Vector2f((mas_param[0]), (mas_param[0])));
            square12.setPosition(sf::Vector2f(serverWindow.getSize().x / 2 - square2.getLocalBounds().width / 2, serverWindow.getSize().y / 2 - square2.getLocalBounds().height / 2));//Квадрат
            square12.setFillColor(sf::Color::Transparent); //Заливка без цвета
            square12.setOutlineColor(sf::Color(128, 64, 48));
            square12.setOutlineThickness(2.0f);
            if (clocke.getElapsedTime() >= sf::seconds(0.003f))
            {
                rotat++;
                clocke.restart();
            }
            square2.setRotation(rotat - 60);
            square.setRotation(rotat);
            square3.setRotation(rotat- 120);
            square4.setRotation(rotat - 150);
            square5.setRotation(rotat - 180);
            square6.setRotation(rotat - 210);
            square7.setRotation(rotat - 240);
            square8.setRotation(rotat - 90);
            square9.setRotation(rotat - 300);
            square10.setRotation(rotat - 270);
            square11.setRotation(rotat - 330);
            square12.setRotation(rotat - 30);
            serverWindow.draw(square12);
            serverWindow.draw(square11);
            serverWindow.draw(square10);
            serverWindow.draw(square9);
            serverWindow.draw(square8);
            serverWindow.draw(square7);
            serverWindow.draw(square6);
            serverWindow.draw(square5);
            serverWindow.draw(square4);
            serverWindow.draw(square3);
            serverWindow.draw(square);
            serverWindow.draw(square2);
        }

        if (this_mode == 86)
        {
            if (is_play == true)
            {
                music.play();
                is_play = false;
            }
            if (is_pause == true)
            {
                music.stop();
                is_pause = false;
            }
        }
        mutex.unlock();
        serverWindow.display();
    }

    return 0;
}
