#include "Partition.h"
#include "Myhill-Nerode.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

struct Viz
{
    Font font;
    Text afterText;
    Text beforeText;
    Text betweenText;
    Sprite background;
    RenderWindow *window;
    int cellWidth;
     int cellHeight;

    vector<vector<vector<int>>> intermediate_transition_tables;
    vector<vector<int>> initial_transition_table;
    vector<vector<int>> final_transition_table;

    Partition *m1;
    MyhillNerode *m2;

   

    Viz(RenderWindow *win, Sprite background) : window(win), background(background)
    {
        m1 = new Partition(
            2, {0, 1, 1, 0, 1, 0},
            {
                {3, 1},
                {2, 5},
                {2, 5},
                {0, 4},
                {2, 5},
                {5, 5},
            });

        font.loadFromFile("assets/fonts/font2.ttf");

        
        beforeText.setFont(font);
        beforeText.setString("Before Minimization:");
        beforeText.setCharacterSize(48);
        beforeText.setFillColor(Color::Yellow);
        beforeText.setPosition(20, 20);

        betweenText.setFont(font);
        betweenText.setString("During Minimization:");
        betweenText.setCharacterSize(48);
        betweenText.setFillColor(Color::Yellow);
        betweenText.setPosition(500, 270);

        afterText.setFont(font);
        afterText.setString("After Minimization");
        afterText.setCharacterSize(48);
        afterText.setFillColor(Color::Yellow);
        afterText.setPosition(20, 520);

        
    }

    void draw(bool part)
    {
        initial_transition_table = m1->transition_table;
        m1->minimize();
        final_transition_table = m1->transition_table;
        intermediate_transition_tables = m1->intermediate_transition_tables;

        run();
    }

    void run()
    {
        bool firstTime = true;
        while (window->isOpen())
        {
            Event event;
            while (window->pollEvent(event))
                if (event.type == Event::Closed)
                    window->close();

            window->clear();

            window->draw(background);

            if (firstTime)
            {
                window->display();
                sleep(milliseconds(1000));
            }
            window->draw(beforeText);


            draw_table(50, 100, initial_transition_table);

            if (firstTime)
            {
                sleep(milliseconds(1000));
                window->display();
            }
            window->draw(betweenText);
            

            for (int i = 0; i < intermediate_transition_tables.size(); i++)
                draw_table(500 + i * 400, 350, intermediate_transition_tables[i]);

            if (firstTime)
            {
                sleep(milliseconds(3000));
                window->display();
            }
            window->draw(afterText);

            draw_table(60, 600, final_transition_table);
            if (firstTime)
            {
                sleep(milliseconds(2000));
                window->display();
            }
            window->display();
            firstTime=false;
        }
    }

    void draw_table(int x, int y, vector<vector<int>> &table)
    {
        RectangleShape rowBorder(Vector2f(table[0].size() * 50, 2));
        for (int i = 0; i <= table.size(); i++)
        {
            
            rowBorder.setPosition(x, y + i * 50);
            rowBorder.setFillColor(Color::Black);
            window->draw(rowBorder);
        }

       
        for (int j = 0; j <= table[0].size(); j++)
        {
            RectangleShape colBorder(Vector2f(2, table.size() * 50));
            colBorder.setPosition(x + j * 50, y);
            colBorder.setFillColor(Color::Black);
            window->draw(colBorder);
        }

        
        for (int i = 0; i < table.size(); i++)
        {
            for (int j = 0; j < table[i].size(); j++)
            {
                Text tableEntry(to_string(table[i][j]), font, 24);
                tableEntry.setPosition(x + j * 50 + 5, y + i * 50 + 5);

                if (j >= 2)
                    tableEntry.setColor(Color::Blue);
                else
                    tableEntry.setColor(Color::White);

                window->draw(tableEntry);
            }
        }
    }
};
