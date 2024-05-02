#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include "Partition.h"
#include "Myhill-Nerode.h"

int main()
{
    // SFML window setup
    sf::RenderWindow window(sf::VideoMode(800, 600), "DFA Minimization Menu");

    // Fonts for text rendering
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Error loading font file!" << std::endl;
        return 1;
    }

    // Text setup
    sf::Text title("DFA Minimization Menu", font, 30);
    title.setPosition(200, 50);

    sf::Text inputText("Enter the number of inputs (transitions per state):", font, 20);
    inputText.setPosition(50, 100);

    sf::Text transitionsText("Enter the DFA transition table (separated by spaces):", font, 20);
    transitionsText.setPosition(50, 200);

    sf::Text finalStatesText("Enter the final states (separated by spaces):", font, 20);
    finalStatesText.setPosition(50, 400);

    sf::Text minimizeText("Press 'M' to minimize using Partition method", font, 20);
    minimizeText.setPosition(50, 500);

    // Input variables
    int inputs = 0;
    std::vector<std::vector<int>> transitions;
    std::vector<int> finalStates;

    // Input fields
    sf::RectangleShape inputField(sf::Vector2f(50, 30));
    inputField.setPosition(400, 100);
    inputField.setFillColor(sf::Color::White);
    inputField.setOutlineColor(sf::Color::Black);
    inputField.setOutlineThickness(2);

    sf::RectangleShape transitionsField(sf::Vector2f(500, 30));
    transitionsField.setPosition(50, 250);
    transitionsField.setFillColor(sf::Color::White);
    transitionsField.setOutlineColor(sf::Color::Black);
    transitionsField.setOutlineThickness(2);

    sf::RectangleShape finalStatesField(sf::Vector2f(500, 30));
    finalStatesField.setPosition(50, 450);
    finalStatesField.setFillColor(sf::Color::White);
    finalStatesField.setOutlineColor(sf::Color::Black);
    finalStatesField.setOutlineThickness(2);

    // Event loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == 13) // Enter key pressed
                {
                    if (inputs == 0)
                    {
                        // Parse inputs for number of transitions per state
                        std::istringstream iss(inputText.getString());
                        iss >> inputs;
                        // Prepare transitions vector with the correct size
                        transitions.resize(inputs);
                    }
                    else if (transitions.empty())
                    {
                        // Parse transition table
                        std::istringstream iss(transitionsText.getString());
                        std::string line;
                        while (std::getline(iss, line))
                        {
                            std::istringstream lineStream(line);
                            int state;
                            while (lineStream >> state)
                            {
                                transitions.back().push_back(state);
                            }
                        }
                    }
                    else
                    {
                        // Parse final states
                        std::istringstream iss(finalStatesText.getString());
                        int state;
                        while (iss >> state)
                        {
                            finalStates.push_back(state);
                        }
                    }
                }
            }
        }

        // Clear the window
        window.clear();

        // Draw all the text and input fields
        window.draw(title);
        window.draw(inputText);
        window.draw(transitionsText);
        window.draw(finalStatesText);
        window.draw(minimizeText);
        window.draw(inputField);
        window.draw(transitionsField);
        window.draw(finalStatesField);

        // Display everything
        window.display();
    }

    return 0;
}
