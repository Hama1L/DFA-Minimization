#include "Myhill-Nerode.h"
#include "Partition.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

struct Viz
{
    RenderWindow *window;
    Font font;
    Text beforeText;
    Text afterText;
    vector<vector<int>> initial_transition_table;
    vector<vector<int>> final_transition_table;

    Viz() :  font(), beforeText(), afterText(), initial_transition_table(), final_transition_table()
    {
        window = new RenderWindow(sf::VideoMode(1600, 900), "Visualizer");
        Partition machine(2, {1, 0, 1}, {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}});
        Partition machine1(2, {1, 0, 1}, {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}});
        machine1.minimize();

       
        initial_transition_table = machine.transition_table;
        final_transition_table = machine1.transition_table;

        
        font.loadFromFile("assets/fonts/font2.ttf");

     
        beforeText.setFont(font);
        beforeText.setString("Before Minimization:");
        beforeText.setCharacterSize(24);
        beforeText.setFillColor(Color::Yellow);
        beforeText.setPosition(20, 20);

      
        afterText.setFont(font);
        afterText.setString("After Minimization:");
        afterText.setCharacterSize(24);
        afterText.setFillColor(Color::Green);
        afterText.setPosition(20, 250);
    }

    void draw(bool selec)
    {
        if(selec){
        while (window->isOpen())
        {
            Event event;
            while (window->pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window->close();
            }

            
            window->clear();

        
            window->draw(beforeText);

        
            for (int i = 0; i < initial_transition_table.size(); i++)
            {
                for (int j = 0; j < initial_transition_table[i].size(); j++)
                {
                    Text tableEntry(to_string(initial_transition_table[i][j]), font, 18);
                    tableEntry.setPosition(50 + j * 20, 50 + i * 20);
                    window->draw(tableEntry);
                }
            }

            
            window->draw(afterText);

            
            for (int i = 0; i < final_transition_table.size(); i++)
            {
                for (int j = 0; j < final_transition_table[i].size(); j++)
                {
                    Text tableEntry(to_string(final_transition_table[i][j]), font, 18);
                    tableEntry.setPosition(50 + j * 20, 280 + i * 20);
                    window->draw(tableEntry);
                }
            }

            
            window->display();
        }
    }
    else{

    }
    }
};
