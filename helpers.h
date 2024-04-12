#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#ifndef FUNC
#define FUNC

void print_vector(vector<int> &row)
{
    for (auto input : row)
        cout << input << ' ';
    cout << endl;
}

void print_table(vector<vector<int>> &table)
{
    for (auto row : table)
        print_vector(row);
    cout << endl;
}

bool checkInMap(int i, vector<vector<int>> &map)
{
    for (vector<int> m : map)
        if (find(m.begin(), m.end(), i) != m.end())
            return true;
    return false;
}

bool vectorExists(const vector<vector<int>> &table, const vector<int> &vectorToCheck)
{
    return find(table.begin(), table.end(), vectorToCheck) != table.end();
}

int findInMap(int x, vector<vector<int>> &map)
{
    for (int i = 0; i < map.size(); i++)
        if (find(map[i].begin(), map[i].end(), x) != map[i].end())
            return i;
    return -1;
}

#endif