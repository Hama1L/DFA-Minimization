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

    bool part;
    int cellWidth;
    int cellHeight;

    Viz(RenderWindow *win, Sprite background) : window(win), background(background)
    {
        m1 = new Partition(
            2, {0, 1, 1, 0, 0, 1},
            {
                {1, 2},
                {3, 4},
                {4, 3},
                {5, 5},
                {5, 5},
                {5, 5},
            });

        m2 = new MyhillNerode(
            2, {0, 1, 1, 0, 0, 1},
            {
                {1, 2},
                {3, 4},
                {4, 3},
                {5, 5},
                {5, 5},
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
        part = part;

        if (part)
        {
            initial_transition_table = m1->table;
            m1->minimize();
            final_transition_table = m1->table;
            intermediate_transition_tables = m1->intermediate_transition_tables;
        }

        else
        {
            initial_transition_table = m2->table;
            m2->minimize();
            final_transition_table = m2->table;
            intermediate_transition_tables.push_back(m2->relations);
        }

        run();
    }

    void run()
    {
        int tableIndex = 0;

        while (window->isOpen())
        {
            Event event;
            while (window->pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window->close();
                else if (event.type == Event::MouseButtonPressed)
                    tableIndex++;
            }

            window->clear();
            window->draw(background);

            window->draw(beforeText);
            draw_table(50, 100, initial_transition_table);

            if (tableIndex >= 1)
            {
                window->draw(betweenText);
                for (int i = 0; i < intermediate_transition_tables.size(); i++)
                    draw_table(500 + i * 300, 350, intermediate_transition_tables[i], true);
            }

            if (tableIndex > 1)
            {
                window->draw(afterText);
                draw_table(60, 600, final_transition_table);
            }

            window->display();
        }
    }

    void draw_table(int x, int y, vector<vector<int>> &table, bool inter = false)
    {
        int sw = 4;

        for (int i = 0; i <= table.size(); i++)
        {
            int index = (i < table.size() ? i : i - 1);

            RectangleShape rowBorder(Vector2f(table[index].size() * 50, sw));
            rowBorder.setPosition(x, y + i * 50);
            rowBorder.setFillColor(Color::Black);
            window->draw(rowBorder);

            RectangleShape colBorder(Vector2f(sw, table.size() * 50));
            for (int j = 0; j <= table[index].size(); j++)
            {
                colBorder.setPosition(x + j * 50, y);
                colBorder.setFillColor(Color::Black);
                window->draw(colBorder);
            }
        }

        for (int i = 0; i < table.size(); i++)
        {
            for (int j = 0; j < table[i].size(); j++)
            {
                Text tableEntry(to_string(table[i][j]), font, 24);
                tableEntry.setPosition(x + 15 + j * 50, y + 15 + i * 50);

                if (j >= 2 && !inter)
                    tableEntry.setFillColor(Color::Magenta);
                else
                    tableEntry.setFillColor(Color::White);

                window->draw(tableEntry);
            }
        }
    }
};
