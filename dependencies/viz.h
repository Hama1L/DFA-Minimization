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
        betweenText.setPosition(20, 270);

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
        while (window->isOpen())
        {
            Event event;
            while (window->pollEvent(event))
                if (event.type == Event::Closed)
                    window->close();

            window->clear();

            window->draw(background);

            window->draw(beforeText);

            draw_table(50, 100, initial_transition_table);

            window->draw(betweenText);

            for (int i = 0; i < intermediate_transition_tables.size(); i++)
                draw_table(50 + i * 200, 350, intermediate_transition_tables[i]);

            window->draw(afterText);

            draw_table(50, 600, final_transition_table);

            window->display();
        }
    }

    void draw_table(int x, int y, vector<vector<int>> &table)
    {
        for (int i = 0; i < table.size(); i++)
        {
            for (int j = 0; j < table[i].size(); j++)
            {
                Text tableEntry(to_string(table[i][j]), font, 24);
                tableEntry.setPosition(50 + j * 30, 280 + i * 30);
                tableEntry.setPosition(x + j * 30, y + i * 30);

                if (j >= 2)
                    tableEntry.setColor(Color::Blue);
                else
                    tableEntry.setColor(Color::White);

                window->draw(tableEntry);
            }
        }
    }
};
