#include "viz.h"
#include <SFML/Audio.hpp>
using namespace sf;

#ifndef MENU
#define MENU

struct Menu
{
    RenderWindow *window;

    Texture background_image;
    Sprite background;

    Music music;
    Font font;

    Text selectedOption;
    bool Partitionselected = true;
    Vector2f scaleFactors;

    Menu()
    {
        background_image.loadFromFile("assets/images/back.jpg");
        background.setTexture(background_image);
        background.setColor(Color(255, 255, 255, 125));

        font.loadFromFile("assets/fonts/font2.ttf");
        window = new RenderWindow(VideoMode(1600, 900), "Menu");
        music.openFromFile("assets/sounds/gottrim.wav");
        Vector2u windowSize = window->getSize();
        scaleFactors.x = (float)windowSize.x / background.getLocalBounds().width;
        scaleFactors.y = (float)windowSize.y / background.getLocalBounds().height;
        background.setScale(scaleFactors);
    }

    void draw()
    {
        // music.setLoop(true);
        // music.play();
        // music.setPitch(1.3);

        Text Partition("Partition", font, 60);
        Partition.setPosition(350, 200);
        Partition.setFillColor(Color::White);

        Text MyhillNerodeText("Myhill-Nerode", font, 60);
        MyhillNerodeText.setPosition(350, 350);
        MyhillNerodeText.setFillColor(Color::White);

        Text selectedOption;
        bool partitionSelected = false;
        while (window->isOpen())
        {

            Event event;
            while (window->pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window->close();
                else if (event.type == Event::MouseButtonPressed)
                {
                    FloatRect PartitionBounds = Partition.getGlobalBounds();
                    FloatRect MyhillNerodeBounds = MyhillNerodeText.getGlobalBounds();

                    if (PartitionBounds.contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        partitionSelected = true;
                        selectedOption = Partition;
                        Viz viz(window, background);
                        viz.draw(true);
                        window->close();
                    }
                    else if (MyhillNerodeBounds.contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        Partitionselected = false;
                        selectedOption = MyhillNerodeText;
                        Viz viz(window, background);
                        viz.draw(false);
                        window->close();
                    }
                }
                else if (event.type == Event::MouseMoved)
                {
                    FloatRect PartitionBounds = Partition.getGlobalBounds();
                    FloatRect MyhillNerodeBounds = MyhillNerodeText.getGlobalBounds();

                    if (PartitionBounds.contains(event.mouseMove.x, event.mouseMove.y))
                    {
                        Partition.setFillColor(Color::Yellow);
                        window->draw(Partition);
                    }
                    else if (MyhillNerodeBounds.contains(event.mouseMove.x, event.mouseMove.y))
                    {
                        MyhillNerodeText.setFillColor(Color::Yellow);
                        window->draw(MyhillNerodeText);
                    }
                    else
                    {
                        Partition.setFillColor(Color::White);
                        MyhillNerodeText.setFillColor(Color::White);
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
