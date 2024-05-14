#include "viz.h"
#include <sstream>

struct InputManager
{
    sf::RenderWindow &window;
    std::vector<std::vector<sf::Text>> transitionTableInputs;
    std::vector<std::vector<int>> transitionTable;
    sf::Font font;
    sf::Text userInputText;
    string userInput;
    int selectedState; // Track the selected state for input
    int selectedInput; // Track the selected input for input

    InputManager(sf::RenderWindow &win, int numStates, int numInputs) : window(win), selectedState(0), selectedInput(0)
    {
        font.loadFromFile("assets/fonts/font2.ttf");
        userInputText.setFont(font);
        userInputText.setPosition(20, 70);
        userInputText.setColor(sf::Color::Green);

        // Initialize transition table with zeros
        transitionTable.resize(numStates, std::vector<int>(numInputs, 0));

        // Create transition table inputs
        transitionTableInputs.resize(numStates, std::vector<sf::Text>(numInputs));
        for (int i = 0; i < numStates; ++i)
        {
            for (int j = 0; j < numInputs; ++j)
            {
                sf::Text input("", font, 20);
                input.setPosition(230 + j * 40, 160 + i * 40);
                input.setFillColor(sf::Color::Black);
                transitionTableInputs[i][j] = input;
            }
        }
        highlightSelectedOption();
    }

    std::vector<std::vector<int>> getTransitionTable() const
    {
        return transitionTable;
    }

    void handleInput(sf::Event &event)
    {
        if (event.type == sf::Event::TextEntered && event.text.unicode < 128)
        {
            if (event.text.unicode == '\b')
            { // Backspace
                if (!userInput.empty())
                {
                    userInput.pop_back();
                    updateUserInput();
                }
            }
            else if (event.text.unicode == '\r')
            { // Enter
                // Submit button clicked, save input to transition table
                saveInputToTransitionTable();
            }
            else
            {
                userInput += static_cast<char>(event.text.unicode);
                updateUserInput();
            }
        }
        else if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down))
        {
            // Handle up and down arrow key presses to change selected state
            if (event.key.code == sf::Keyboard::Up)
                selectedState = std::max(0, selectedState - 1);
            else if (event.key.code == sf::Keyboard::Down)
                selectedState = std::min(static_cast<int>(transitionTableInputs.size()) - 1, selectedState + 1);

            highlightSelectedOption();
        }
    }

    void updateUserInput()
    {
        userInputText.setString(userInput);
    }

    void saveInputToTransitionTable()
    {
        // Update the transition table with user input
        transitionTable[selectedState][selectedInput] = stoi(userInput);
        // Clear user input after saving
        userInput.clear();
        updateUserInput();
    }

    void highlightSelectedOption()
    {
        // Update the color of the selected option
        for (size_t i = 0; i < transitionTableInputs.size(); ++i)
        {
            for (size_t j = 0; j < transitionTableInputs[i].size(); ++j)
            {
                if (i == selectedState && j == selectedInput)
                    transitionTableInputs[i][j].setFillColor(sf::Color::Red);
                else
                    transitionTableInputs[i][j].setFillColor(sf::Color::Black);
            }
        }
    }

    void draw()
    {
        window.draw(sf::Text("Transition Table:", font, 18));
        for (size_t i = 0; i < transitionTableInputs.size(); ++i)
        {
            for (size_t j = 0; j < transitionTableInputs[i].size(); ++j)
            {
                window.draw(transitionTableInputs[i][j]);
            }
        }
        window.draw(userInputText);
    }

    void run()
    {
        // Input variables
        int numInputs;
        int numStates;

        // Input text fields
        sf::Text numInputsText("Enter number of inputs:", font, 24);
        numInputsText.setPosition(20, 20);
        numInputsText.setColor(sf::Color::Black);
        sf::Text numStatesText("Enter number of states:", font, 24);
        numStatesText.setPosition(20, 60);
        numStatesText.setColor(sf::Color::Black);

        // Initialization code skipped for brevity

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::TextEntered)
                {
                    handleInput(event);
                }
            }
            window.clear(sf::Color::Yellow);
            window.draw(numInputsText);
            window.draw(numStatesText);
            draw();
            window.display();
        }
    }
};
