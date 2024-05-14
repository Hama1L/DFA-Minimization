#include "viz.h"
#include <sstream>
#include <bits/stdc++.h>

struct Input
{

  int draw(){
            sf::RenderWindow window(sf::VideoMode(800, 600), "User Input Table");

            std::vector<std::vector<int>> table;
            sf::Font font;
            font.loadFromFile("assets/fonts/font2.ttf");

            // Get number of inputs
            int numInputs;
            std::cout << "Enter the number of inputs: ";
            std::cin >> numInputs;

            // Get final states
            std::vector<int> finalStates(numInputs);
            std::cout << "Enter final states: ";
            for (int i = 0; i < numInputs; ++i)
            {
                std::cin >> finalStates[i];
            }

            // Get transition table
            std::cout << "Enter transition table:\n";
            for (int i = 0; i < numInputs; ++i)
            {
                std::vector<int> row(numInputs);
                for (int j = 0; j < numInputs; ++j)
                {
                    std::cin >> row[j];
                }
                table.push_back(row);
            }

            while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                    else if (event.type == sf::Event::TextEntered)
                    {
                        int input = event.text.unicode - '0'; 
                        table.push_back({input});             
                    }
                }

                window.clear();

                // Display table
                for (int i = 0; i < table.size(); i++)
                {
                    for (int j = 0; j < table[i].size(); j++)
                    {
                        sf::Text tableEntry(std::to_string(table[i][j]), font, 18);
                        tableEntry.setPosition(50 + j * 20, 280 + i * 20);
                        window.draw(tableEntry);
                    }
                }

                window.display();
            }

            // Output the transition table
            std::cout << "Transition table:\n";
            for (int i = 0; i < table.size(); ++i)
            {
                for (int j = 0; j < table[i].size(); ++j)
                {
                    std::cout << table[i][j] << " ";
                }
                std::cout << std::endl;
            }

            return 0;
        }
    
};