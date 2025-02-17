#include "Difficulty.h"
#include <iostream>


int selectDifficulty()
{
    sf::RenderWindow difficultyWindow(sf::VideoMode(400, 300), "Select Difficulty");

    sf::Font font;
    if (!font.loadFromFile("D:\\PROJECT\\GameB\\font\\HomeVideo-BLG6G.ttf")) {
        std::cerr << "Failed to load font!\n";
        return 2;
    }

    sf::Text title("Choose Difficulty", font, 28);
    title.setPosition(80, 10);
    title.setFillColor(sf::Color::White);

    sf::RectangleShape easyButton(sf::Vector2f(200, 50));
    sf::RectangleShape mediumButton(sf::Vector2f(200, 50));
    sf::RectangleShape hardButton(sf::Vector2f(200, 50));

    easyButton.setPosition(100, 60);
    mediumButton.setPosition(100, 140);
    hardButton.setPosition(100, 220);

    easyButton.setFillColor(sf::Color::Green);
    mediumButton.setFillColor(sf::Color::Yellow);
    hardButton.setFillColor(sf::Color::Red);

    sf::Text easyText("Easy", font, 24);
    sf::Text mediumText("Medium", font, 24);
    sf::Text hardText("Hard", font, 24);

    easyText.setPosition(160, 70);
    mediumText.setPosition(140, 150);
    hardText.setPosition(160, 230);

    easyText.setFillColor(sf::Color::Black);
    mediumText.setFillColor(sf::Color::Black);
    hardText.setFillColor(sf::Color::Black);

    while (difficultyWindow.isOpen())
    {
        sf::Event event;
        while (difficultyWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                difficultyWindow.close();

            sf::Vector2i mousePos = sf::Mouse::getPosition(difficultyWindow);

            if (easyButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                easyButton.setFillColor(sf::Color(100, 255, 100));
            else
                easyButton.setFillColor(sf::Color::Green);

            if (mediumButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                mediumButton.setFillColor(sf::Color(255, 255, 100));
            else
                mediumButton.setFillColor(sf::Color::Yellow);

            if (hardButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                hardButton.setFillColor(sf::Color(255, 100, 100));
            else
                hardButton.setFillColor(sf::Color::Red);

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                if (easyButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                    return 1;

                if (mediumButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                    return 2;

                if (hardButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                    return 3;
            }
        }

        difficultyWindow.clear(sf::Color::Black);
        difficultyWindow.draw(title);
        difficultyWindow.draw(easyButton);
        difficultyWindow.draw(mediumButton);
        difficultyWindow.draw(hardButton);
        difficultyWindow.draw(easyText);
        difficultyWindow.draw(mediumText);
        difficultyWindow.draw(hardText);
        difficultyWindow.display();
    }

    return 2;
}
