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

    bool myh;

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
        m2 = new MyhillNerode(
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

        myh = false;
    }

    void draw(bool part)
    {
        if(part){
        initial_transition_table = m1->transition_table;
        m1->minimize();
        final_transition_table = m1->transition_table;
        intermediate_transition_tables = m1->intermediate_transition_tables;
        }
        else
        {
            initial_transition_table=m2->table;
            m2->minimize();
            final_transition_table=m2->table;
            myh=true;
        }
        run();
    }

    void run()
    {
        bool firstTime = true;
        int tableIndex = 0;

        while (window->isOpen())
        {
            sf::Event event;
            while (window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window->close();
                }
                else if (event.type == sf::Event::MouseButtonPressed)
                {
                    tableIndex++;
                }
            }

            window->clear();
            window->draw(background);

            if (firstTime)
            {
                window->display();
                sf::sleep(sf::milliseconds(1000));
                firstTime = false;
            }

            window->draw(beforeText);
            draw_table(50, 100, initial_transition_table);

            if (tableIndex >= 1 && !myh)
            {
                window->draw(betweenText);
                for (int i = 0; i < intermediate_transition_tables.size(); i++)
                {
                    draw_table(500 + i * 400, 350, intermediate_transition_tables[i]);
                }
            }

            if (tableIndex > 1)
            {
                window->draw(afterText);
                draw_table(60, 600, final_transition_table);
            }

            window->display();
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

        RectangleShape colBorder(Vector2f(2, table.size() * 50));
        for (int j = 0; j <= table[0].size(); j++)
        {
            colBorder.setPosition(x + j * 50, y);
            colBorder.setFillColor(Color::Black);
            window->draw(colBorder);
        }

        for (int i = 0; i < table.size(); i++)
        {
            for (int j = 0; j < table[i].size(); j++)
            {
                Text tableEntry(to_string(table[i][j]), font, 24);
                tableEntry.setPosition(x + 15 + j * 50, y + 15 + i * 50);

                if (j >= 2)
                    tableEntry.setColor(Color::Blue);
                else
                    tableEntry.setColor(Color::White);

                window->draw(tableEntry);
            }
        }
    }
};
