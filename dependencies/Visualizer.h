#include <vector>
#include <bits/stdc++.h>
using namespace std;
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
struct Input
{
    Font font;
    int inputs = 0;
    std::vector<std::vector<int>> transitions;
    std::vector<int> finalStates;

    RenderWindow *window;
    Input()
    {
        window = new RenderWindow(
            VideoMode(1600, 900),
            "Ice Cream Factory",
            Style::Titlebar | Style::Close);
        font.loadFromFile("assets/fints/font2.tff");
        sf::Text title("DFA Minimization Menu", font, 30);
        title.setPosition(200, 50);

        sf::Text transitionsText("Enter the DFA transition table (separated by spaces):", font, 20);
        transitionsText.setPosition(50, 200);

        sf::Text finalStatesText("Enter the final states (separated by spaces):", font, 20);
        finalStatesText.setPosition(50, 400);

        sf::Text minimizeText("Press 'M' to minimize using Partition method", font, 20);
        minimizeText.setPosition(50, 500);

        // Input variables

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
    }

    void draw()
    {
        sf::Text inputText("Enter the number of inputs (transitions per state):", font, 20);
        inputText.setPosition(50, 100);

        while (window->isOpen())
        {
            Event event;
            if (event.type == sf::Event::Closed)
                window->close();
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
};

class Node
{
public:
    int id;
    int x, y;
    Font font;
    string label;
    CircleShape shape;
    Text text;

    Node(int id, int x, int y, string label) : id(id), x(x), y(y), label(label)
    {
        shape.setRadius(20);
        shape.setFillColor(sf::Color::White);
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(2);
        shape.setPosition(x, y);

        text.setString(label);
        text.setFont(font);
        text.setCharacterSize(12);
        text.setFillColor(sf::Color::Black);
    }
};
class Transition
{
public:
    Node *from;
    Node *to;

    Transition(Node *from, Node *to) : from(from), to(to)
    {
    }
};
