#include "viz.h"
#include <SFML/Audio.hpp>
using namespace sf;

#ifndef MENU
#define MENU

struct Menu
{
    RectangleShape menu;
    RenderWindow *window;

    Texture image;
    Music music;

    Font font;
    Sprite background;

    Text selectedOption;
    bool Partitionselected = true;

    Menu()
    {
        image.loadFromFile("assets/images/back.jpg");
        background.setTexture(image);
        font.loadFromFile("assets/fonts/font2.ttf");
        window = new RenderWindow(sf::VideoMode(1600, 900), "Menu");
        music.openFromFile("assets/sounds/gottrim.wav");
    }

    void draw()
    {
        music.setLoop(true);
        music.play();
        music.setPitch(1.3);

        sf::Text Partition("Partition", font, 60);
        Partition.setPosition(350, 200);
        Partition.setFillColor(sf::Color::White);

        Text MyhillNerodeText("Myhill-Nerode", font, 60);
        MyhillNerodeText.setPosition(350, 350);
        MyhillNerodeText.setFillColor(sf::Color::White);

        Text selectedOption;
        bool partitionSelected = false;
        while (window->isOpen())
        {

            sf::Event event;
            while (window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window->close();
                else if (event.type == sf::Event::MouseButtonPressed)
                {
                    sf::FloatRect PartitionBounds = Partition.getGlobalBounds();
                    FloatRect MyhillNerodeBounds = MyhillNerodeText.getGlobalBounds();

                    if (PartitionBounds.contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        partitionSelected = true;
                        selectedOption = Partition;
                        Viz viz(window);
                        viz.draw(true);
                        window->close();
                    }
                    else if (MyhillNerodeBounds.contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        Partitionselected = false;
                        selectedOption = MyhillNerodeText;
                        Viz viz(window);
                        viz.draw(false);
                        
                    }
                }
                else if (event.type == sf::Event::MouseMoved)
                {
                    sf::FloatRect PartitionBounds = Partition.getGlobalBounds();
                    sf::FloatRect MyhillNerodeBounds = MyhillNerodeText.getGlobalBounds();

                    if (PartitionBounds.contains(event.mouseMove.x, event.mouseMove.y))
                    {
                        Partition.setFillColor(sf::Color::Yellow);
                        window->draw(Partition);
                    }
                    else if (MyhillNerodeBounds.contains(event.mouseMove.x, event.mouseMove.y))
                    {
                        MyhillNerodeText.setFillColor(sf::Color::Yellow);
                        window->draw(MyhillNerodeText);
                    }
                    else
                    {
                        Partition.setFillColor(sf::Color::White);
                        MyhillNerodeText.setFillColor(sf::Color::White);
                        window->draw(Partition);
                        window->draw(MyhillNerodeText);
                    }
                }
            }
            window->clear();
            window->draw(background);

            window->draw(Partition);
            window->draw(MyhillNerodeText);
            window->display();
        }
    }
};
#endif
