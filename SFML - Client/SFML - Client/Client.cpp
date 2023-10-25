#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <clocale>
#include <filesystem>
#include <direct.h>
#include <Windows.h>
#include <codecvt>

using namespace std;
// Путь
char pathe1[MAX_PATH];

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(1251);

    setlocale(LC_ALL, "ru");
    // Что будем рисовать?
    int mode = 0;
    int sec_mode = 0;

    // Определяем путь к файлам
    _getcwd(pathe1, MAX_PATH);
    std::string exep(pathe1);

    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML UDP Клиент");

    sf::UdpSocket socket;

    // Текстуры кнопок
    sf::Texture buttonTexture1;
    if (!buttonTexture1.loadFromFile(exep + "\\butons\\rect.png")) {
        std::cerr << "Ошибка при загрузке текстуры кнопки" << std::endl;
        return -1;
    }
    sf::Sprite button1(buttonTexture1);

    sf::Texture buttonTexture2;
    if (!buttonTexture2.loadFromFile(exep + "\\butons\\rect2.png")) {
        std::cerr << "Ошибка при загрузке текстуры кнопки" << std::endl;
        return -1;
    }
    sf::Sprite button2(buttonTexture2);

    sf::Texture buttonTexture3;
    if (!buttonTexture3.loadFromFile(exep + "\\butons\\ellips.png")) {
        std::cerr << "Ошибка при загрузке текстуры кнопки" << std::endl;
        return -1;
    }
    sf::Sprite button3(buttonTexture3);

    sf::Texture buttonTexture4;
    if (!buttonTexture4.loadFromFile(exep + "\\butons\\ellips2.png")) {
        std::cerr << "Ошибка при загрузке текстуры кнопки" << std::endl;
        return -1;
    }
    sf::Sprite button4(buttonTexture4);

    sf::Texture buttonTexture5;
    if (!buttonTexture5.loadFromFile(exep + "\\butons\\hex.png")) {
        std::cerr << "Ошибка при загрузке текстуры кнопки" << std::endl;
        return -1;
    }
    sf::Sprite button5(buttonTexture5);

    sf::Texture buttonTexture6;
    if (!buttonTexture6.loadFromFile(exep + "\\butons\\hex2.png")) {
        std::cerr << "Ошибка при загрузке текстуры кнопки" << std::endl;
        return -1;
    }
    sf::Sprite button6(buttonTexture6);

    sf::Texture buttonTexture7;
    if (!buttonTexture7.loadFromFile(exep + "\\butons\\square.png")) {
        std::cerr << "Ошибка при загрузке текстуры кнопки" << std::endl;
        return -1;
    }
    sf::Sprite button7(buttonTexture7);

    sf::Texture buttonTexture8;
    if (!buttonTexture8.loadFromFile(exep + "\\butons\\square2.png")) {
        std::cerr << "Ошибка при загрузке текстуры кнопки" << std::endl;
        return -1;
    }
    sf::Sprite button8(buttonTexture8);

    sf::Texture buttonTexture9;
    if (!buttonTexture9.loadFromFile(exep + "\\butons\\circle.png")) {
        std::cerr << "Ошибка при загрузке текстуры кнопки" << std::endl;
        return -1;
    }
    sf::Sprite button9(buttonTexture9);

    sf::Texture buttonTexture10;
    if (!buttonTexture10.loadFromFile(exep + "\\butons\\circle2.png")) {
        std::cerr << "Ошибка при загрузке текстуры кнопки" << std::endl;
        return -1;
    }
    sf::Sprite button10(buttonTexture10);

    sf::Texture buttonTexture11;
    if (!buttonTexture11.loadFromFile(exep + "\\butons\\line.png")) {
        std::cerr << "Ошибка при загрузке текстуры кнопки" << std::endl;
        return -1;
    }
    sf::Sprite button11(buttonTexture11);

    sf::Texture buttonTexture12;
    if (!buttonTexture12.loadFromFile(exep + "\\butons\\text.png")) {
        std::cerr << "Ошибка при загрузке текстуры кнопки" << std::endl;
        return -1;
    }
    sf::Sprite button12(buttonTexture12);

    sf::Texture buttonTexture13;
    if (!buttonTexture13.loadFromFile(exep + "\\butons\\img.png")) {
        std::cerr << "Ошибка при загрузке текстуры кнопки" << std::endl;
        return -1;
    }
    sf::Sprite button13(buttonTexture13);

    sf::Texture buttonTexture14;
    if (!buttonTexture14.loadFromFile(exep + "\\butons\\clear.png")) {
        std::cerr << "Ошибка при загрузке текстуры кнопки" << std::endl;
        return -1;
    }
    sf::Sprite button14(buttonTexture14);

    sf::Texture buttonTexture15;
    if (!buttonTexture15.loadFromFile(exep + "\\butons\\white.png")) {
        std::cerr << "Ошибка при загрузке текстуры кнопки" << std::endl;
        return -1;
    }
    sf::Sprite button15(buttonTexture15);

    sf::Texture buttonTexture16;
    if (!buttonTexture16.loadFromFile(exep + "\\butons\\Brown.png")) {
        std::cerr << "Ошибка при загрузке текстуры кнопки" << std::endl;
        return -1;
    }
    sf::Sprite button16(buttonTexture16);

    sf::Texture buttonTexture17;
    if (!buttonTexture17.loadFromFile(exep + "\\butons\\Pink.png")) {
        std::cerr << "Ошибка при загрузке текстуры кнопки" << std::endl;
        return -1;
    }
    sf::Sprite button17(buttonTexture17);

    sf::Texture buttonTexture18;
    if (!buttonTexture18.loadFromFile(exep + "\\butons\\Timer.png")) {
        std::cerr << "Ошибка при загрузке текстуры кнопки" << std::endl;
        return -1;
    }
    sf::Sprite button18(buttonTexture18);

    sf::Texture buttonTexture19;
    if (!buttonTexture19.loadFromFile(exep + "\\butons\\lines.png")) {
        std::cerr << "Ошибка при загрузке текстуры кнопки" << std::endl;
        return -1;
    }
    sf::Sprite button19(buttonTexture19);

    sf::Texture buttonTexture20;
    if (!buttonTexture20.loadFromFile(exep + "\\butons\\get.png")) {
        std::cerr << "Ошибка при загрузке текстуры кнопки" << std::endl;
        return -1;
    }
    sf::Sprite button20(buttonTexture20);


    sf::Texture buttonTexture21;
    if (!buttonTexture21.loadFromFile(exep + "\\butons\\orien.png")) {
        std::cerr << "Ошибка при загрузке текстуры кнопки" << std::endl;
        return -1;
    }
    sf::Sprite button21(buttonTexture21);

    sf::Texture buttonTexture22;
    if (!buttonTexture22.loadFromFile(exep + "\\butons\\load.png")) {
        std::cerr << "Ошибка при загрузке текстуры кнопки" << std::endl;
        return -1;
    }
    sf::Sprite button22(buttonTexture22);

    sf::Texture buttonTexture23;
    if (!buttonTexture23.loadFromFile(exep + "\\butons\\show.png")) {
        std::cerr << "Ошибка при загрузке текстуры кнопки" << std::endl;
        return -1;
    }
    sf::Sprite button23(buttonTexture23);



    sf::Texture buttonTexture24;
    if (!buttonTexture24.loadFromFile(exep + "\\butons\\guess.png")) {
        std::cerr << "Ошибка при загрузке текстуры кнопки" << std::endl;
        return -1;
    }
    sf::Sprite button24(buttonTexture24);

    sf::Texture buttonTexture25;
    if (!buttonTexture25.loadFromFile(exep + "\\butons\\syst.png")) {
        std::cerr << "Ошибка при загрузке текстуры кнопки" << std::endl;
        return -1;
    }
    sf::Sprite button25(buttonTexture25);

    sf::Texture buttonTexture26;
    if (!buttonTexture26.loadFromFile(exep + "\\butons\\rotatoo.png")) {
        std::cerr << "Ошибка при загрузке текстуры кнопки" << std::endl;
        return -1;
    }
    sf::Sprite button26(buttonTexture26);

    sf::Texture buttonTexture27;
    if (!buttonTexture27.loadFromFile(exep + "\\butons\\mus.png")) {
        std::cerr << "Ошибка при загрузке текстуры кнопки" << std::endl;
        return -1;
    }
    sf::Sprite button27(buttonTexture27);


    sf::Clock clock;
    float frameDuration = 0.1f;

    // Позиционирование кнопок (пиксели)
    button1.setPosition(60, 655);
    button2.setPosition(160, 655);
    button3.setPosition(260, 655);
    button4.setPosition(360, 655);
    button5.setPosition(460, 655);
    button6.setPosition(560, 655);
    button7.setPosition(660, 655);
    button8.setPosition(760, 655);
    button9.setPosition(860, 655);

    button10.setPosition(60, 755);
    button11.setPosition(160, 755);
    button12.setPosition(260, 755);
    button13.setPosition(360, 755);
    button14.setPosition(460, 755);
    button15.setPosition(560, 755);
    button16.setPosition(660, 755);
    button17.setPosition(760, 755);
    button18.setPosition(860, 755);

    button19.setPosition(60, 855);
    button20.setPosition(160, 855);
    button21.setPosition(260, 855);
    button22.setPosition(360, 855);
    button23.setPosition(460, 855);
    button24.setPosition(560, 855);
    button25.setPosition(660, 855);
    button26.setPosition(760, 855);
    button27.setPosition(860, 855);

    sf::Texture textu;
    sf::Sprite sprit;

    sf::Image image;

    sprit.setPosition(10, 100);

    std::string path_spirit;


    // IP-адрес и порт сервера, к которому мы хотим подключиться
    sf::IpAddress serverAddress = "127.0.0.1";
    unsigned short serverPort = 12345;

    // Создаем поле ввода для координат и цвета
    sf::RectangleShape inputBox(sf::Vector2f(500, 30));
    inputBox.setPosition(250, 500);
    inputBox.setFillColor(sf::Color::White);

    //Шрифт
    sf::Font font;
    if (!font.loadFromFile(exep + "\\font\\arial.ttf")) {
        std::cerr << "Ошибка при загрузке шрифта" << std::endl;
        return -1;
    }
    
    //Первый параметр
    sf::Text inputText;
    inputText.setFont(font); // Используем шрифт по умолчанию
    inputText.setCharacterSize(20);
    inputText.setPosition(250, 500);
    inputText.setFillColor(sf::Color::Black);
    std::string currentText;

    //Текст-Информация
    sf::Text InfoT;
    InfoT.setFont(font);
    InfoT.setCharacterSize(36);
    InfoT.setFillColor(sf::Color::White);
    InfoT.setString("Your Parametrs");

    sf::Text InfoT2;
    InfoT2.setFont(font);
    InfoT2.setCharacterSize(36);
    InfoT2.setFillColor(sf::Color::White);
    InfoT2.setString("Your Choise: None");
    InfoT2.setPosition(50, 30);

    //Центрируем текст
    sf::FloatRect textBounds;
    textBounds = InfoT.getLocalBounds();
    InfoT.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
    InfoT.setPosition(window.getSize().x / 2, 550);

    // Основной цикл приложения
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                // Проверяем, было ли нажатие на кнопку
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //Прямоугольник
                    // Отправляем сообщение на сервер
                    std::string message = currentText;
                    mode = 1;
                    sec_mode = 1;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button2.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //Заполненный прямоугольник
                    // Отправляем сообщение на сервер
                    std::string message = currentText;
                    mode = 2;
                    sec_mode = 6;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button3.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //Эллипс
                    // Отправляем сообщение на сервер
                    std::string message = currentText;
                    mode = 3;
                    sec_mode = 11;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button4.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //Заполненный Эллипс
                    // Отправляем сообщение на сервер
                    std::string message = currentText;
                    mode = 4;
                    sec_mode = 16;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button5.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //Округленный прямоугольник
                    // Отправляем сообщение на сервер
                    std::string message = currentText;
                    mode = 5;
                    sec_mode = 21;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button6.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //Заполненный Округленный прямоугольник
                    // Отправляем сообщение на сервер
                    std::string message = currentText;
                    mode = 6;
                    sec_mode = 27;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button7.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //Квадрат
                    // Отправляем сообщение на сервер
                    std::string message = currentText;
                    mode = 7;
                    sec_mode = 33;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button8.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //Заполненный квадрат
                    // Отправляем сообщение на сервер
                    std::string message = currentText;
                    mode = 8;
                    sec_mode = 37;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button9.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //Круг
                    // Отправляем сообщение на сервер
                    std::string message = currentText;
                    mode = 9;
                    sec_mode = 41;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button10.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //Заполненный круг
                    // Отправляем сообщение на сервер
                    std::string message = currentText;
                    mode = 10;
                    sec_mode = 45;
                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button11.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //Линия
                    // Отправляем сообщение на сервер
                    std::string message = currentText;
                    mode = 11;
                    sec_mode = 49;
                    std::cout << sec_mode;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button12.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //Текст
                    // Отправляем сообщение на сервер
                    std::string message = currentText;
                    mode = 12;
                    sec_mode = 54;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button13.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //Изображение
                    // Отправляем сообщение на сервер
                    std::string message = currentText;
                    mode = 13;
                    sec_mode = 59;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button14.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //Очистить
                    // Отправляем сообщение на сервер
                    std::string message = currentText;
                    mode = 14;
                    sec_mode = 62;

                }
                ///New Modes
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button15.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //Очистить
                    // Отправляем сообщение на сервер
                    std::string message = currentText;
                    mode = 15;
                    sec_mode = 63;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button16.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //Очистить
                    // Отправляем сообщение на сервер
                    std::string message = currentText;
                    mode = 16;
                    sec_mode = 64;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button17.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //Очистить
                    // Отправляем сообщение на сервер
                    std::string message = currentText;
                    mode = 17;
                    sec_mode = 65;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button18.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //Очистить
                    // Отправляем сообщение на сервер
                    std::string message = currentText;
                    mode = 18;
                    sec_mode = 66;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button19.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //Очистить
                    // Отправляем сообщение на сервер
                    std::string message = currentText;
                    mode = 19;
                    sec_mode = 71;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button20.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //Очистить
                    // Отправляем сообщение на сервер
                    std::string message = currentText;
                    mode = 20;
                    sec_mode = 75;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button21.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //Очистить
                    // Отправляем сообщение на сервер
                    std::string message = currentText;
                    mode = 21;
                    sec_mode = 76;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button22.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //Очистить
                    // Отправляем сообщение на сервер
                    std::string message = currentText;
                    mode = 22;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button23.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //Очистить
                    // Отправляем сообщение на сервер
                    std::string message = currentText;
                    mode = 23;
                    sec_mode = 77;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button24.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //Очистить
                    // Отправляем сообщение на сервер
                    std::string message = currentText;
                    mode = 24;
                    sec_mode = 80;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button25.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //Очистить
                    // Отправляем сообщение на сервер
                    std::string message = currentText;
                    mode = 25;
                    sec_mode = 81;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button26.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //Очистить
                    // Отправляем сообщение на сервер
                    std::string message = currentText;
                    mode = 26;
                    sec_mode = 85;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button27.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //Очистить
                    // Отправляем сообщение на сервер
                    std::string message = currentText;
                    mode = 27;
                    sec_mode = 86;

                }
            }

            // Обработка ввода текста
            if (mode != 0) {
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == 8 && !currentText.empty()) {  // Backspace
                        currentText.pop_back();
                    }
                    else if (event.text.unicode == 13) {  // Enter
                        // Отправляем сообщение на сервер
                        if (!currentText.empty()) {
                            if (mode != 22)
                            {
                                string buf = to_string(sec_mode);
                                std::string mesage;
                                if (mode != 23)
                                {
                                    mesage = (buf + " = " + currentText);
                                    if (socket.send(mesage.c_str(), mesage.size() + 1, serverAddress, serverPort) != sf::Socket::Done) {
                                        std::cerr << "Ошибка при отправке данных" << std::endl;
                                    }
                                    else {
                                        std::cout << "Сообщение успешно отправлено на сервер: " << mesage << std::endl;
                                    }
                                }
                                else {
                                    const sf::Uint8* pixels = image.getPixelsPtr();
                                    socket.send(pixels, image.getSize().x* image.getSize().y * 4, serverAddress, serverPort);
                                }
                                currentText.clear();  // Очищаем текущий текст
                                if (mode == 20)
                                {
                                    char buffer[1024];
                                    std::size_t received;
                                    sf::IpAddress sender;
                                    unsigned short senderPort;
                                    if (socket.receive(buffer, sizeof(buffer), received, sender, senderPort) != sf::Socket::Done) {
                                        std::cout << "Не удалось получить ответ от сервера" << std::endl;
                                        return 1;
                                    }
                                    std::cout << "Ответ от сервера (" << sender.toString() << ":" << senderPort << "): " << buffer << std::endl;
                                    string bufingg = buffer;

                                    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

                                    // Конвертируем std::string в std::wstring
                                    std::wstring wideString = converter.from_bytes(bufingg);

                                    InfoT2.setString(wideString);
                                    mode = 0;
                                }

                            }
                            else {
                                
                                //Текстура
                                if (!image.loadFromFile(exep + "\\your_img\\" + currentText + ".png")) {
                                    std::cerr << "Ошибка при загрузке текстуры кнопки" << std::endl;
                                    return -1;
                                }

                                if (!textu.loadFromFile(exep + "\\your_img\\" + currentText + ".png")) {
                                    std::cerr << "Ошибка при загрузке текстуры кнопки" << std::endl;
                                    return -1;
                                }
                                sprit.setTexture(textu);
                                path_spirit = "\\your_img\\" + currentText + ".png";
                            }
                        }
                    }
                    else if (event.text.unicode < 128) {
                        currentText += static_cast<char>(event.text.unicode);
                    }
                    inputText.setString(currentText);
                }
            }
        }

        switch (mode)
        {
        case 1:
            InfoT2.setString("Your Choise: Rectangle");
            break;
        case 2:
            InfoT2.setString("Your Choise: Filled Rectangle");
            break;
        case 3:
            InfoT2.setString("Your Choise: Ellipse");
            break;
        case 4:
            InfoT2.setString("Your Choise: Filled Ellipse");
            break;
        case 5:
            InfoT2.setString("Your Choise: Hexagon");
            break;
        case 6:
            InfoT2.setString("Your Choise: Filled Hexagon");
            break;
        case 7:
            InfoT2.setString("Your Choise: Square");
            break;
        case 8:
            InfoT2.setString("Your Choise: Filled Square");
            break;
        case 9:
            InfoT2.setString("Your Choise: Circle");
            break;
        case 10:
            InfoT2.setString("Your Choise: Filled Circle");
            break;
        case 11:
            InfoT2.setString("Your Choise: Line");
            break;
        case 12:
            InfoT2.setString("Your Choise: Text");
            break;
        case 13:
            InfoT2.setString("Your Choise: Image");
            break;
        case 14:
            InfoT2.setString("Your Choise: Clear");
            break;
        case 15:
            InfoT2.setString("Your Choise: White Noise");
            break;
        case 16:
            InfoT2.setString("Your Choise: Brown Noise");
            break;
        case 17:
            InfoT2.setString("Your Choise: Pink Noise");
            break;
        case 18:
            InfoT2.setString("Your Choise: Timer");
            break;
        case 19:
            InfoT2.setString("Your Choise: Line Word");
            break;
        case 20:
            InfoT2.setString("Your Choise: Get Info");
            break;
        case 21:
            InfoT2.setString("Your Choise: Set Orientation");
            break;
        case 22:
            InfoT2.setString("Your Choise: Load Sprite");
            break;
        case 23:
            InfoT2.setString("Your Choise: Show Sprite");
            break;
        case 24:
            InfoT2.setString("Your Choise: Guess number");
            break;
        case 25:
            InfoT2.setString("Your Choise: System Time");
            break;
        case 26:
            InfoT2.setString("Your Choise: Rotation Fun");
            break;
        case 27:
            InfoT2.setString("Your Choise: Play Music");
            break;
        }


        // Очищаем окно
        window.clear();

        // Рисуем кнопку
        window.draw(InfoT2);
        window.draw(InfoT);
        window.draw(button1);
        window.draw(button2);
        window.draw(button3);
        window.draw(button4);
        window.draw(button5);
        window.draw(button6);
        window.draw(button7);
        window.draw(button8);
        window.draw(button9);
        window.draw(button10);
        window.draw(button11);
        window.draw(button12);
        window.draw(button13);
        window.draw(button14);
        window.draw(button15);
        window.draw(button16);
        window.draw(button17);
        window.draw(button18);
        window.draw(button19);
        window.draw(button20);
        window.draw(button21);
        window.draw(button22);
        window.draw(button23);
        window.draw(button24);
        window.draw(button25);
        window.draw(button26);
        window.draw(button27);

        if (mode == 22 || mode == 23)
        {
            window.draw(sprit);
        }

        window.draw(inputBox);
        window.draw(inputText);

        // Отображаем содержимое окна
        window.display();
    }

    return 0;
}