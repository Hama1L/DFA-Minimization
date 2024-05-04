#include <vector>
#include <bits/stdc++.h>
using namespace std;
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
class Visualizer
{
public:
    int id;
    int x, y;
    Font font;
    string label;
    CircleShape shape;
    Text text;

    Visualizer(int id, int x, int y, string label) : id(id), x(x), y(y), label(label)
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
    Visualizer *from;
    Visualizer *to;

    Transition(Visualizer *from, Visualizer *to) : from(from), to(to)
    {
    }
};
