#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool checkInMap(int i, vector<vector<int>> &map)
{
    for (vector<int> m : map)
        for (int s : m)
            if (s == i)
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
        for (int j = 0; j < map[i].size(); j++)
            if (map[i][j] == x)
                return i;
    return -1;
}

int main()
{
    vector<vector<int>> table = {
        {1, 2},
        {3, 4},
        {4, 3},
        {5, 5},
        {5, 5},
        {5, 5},
    };

    vector<bool> final = {0, 1, 1, 0, 0, 1};

    vector<vector<bool>> rel;

    for (int i = 1; i < table.size(); i++)
    {
        vector<bool> row;
        for (int j = 0; j < i; j++)
            row.push_back(final[i] != final[j] ? 1 : 0);
        rel.push_back(row);
    }

    bool marked = true;
    while (marked)
    {
        marked = false;
        for (int i = 0; i < rel.size(); i++)
        {
            for (int j = 0; j < rel[i].size(); j++)
            {
                if (rel[i][j] != 1)
                {
                    int a = table[i + 1][0];
                    int b = table[j][0];

                    if (a - 1 < rel.size() && b < rel[a - 1].size() && rel[a - 1][b])
                        rel[i][j] = true;
                }
            }
        }
    }

    vector<vector<int>> mapping;
    for (int i = 0; i < rel.size(); i++)
    {
        if (checkInMap(i, mapping))
            continue;

        bool merged = false;
        for (int j = 0; j < rel[i].size(); j++)
        {
            if (rel[i][j] == 0)
            {
                merged = true;
                mapping.push_back({i, j + 1});
            }
        }

        if (!merged)
            mapping.push_back({i});
    }

    int last = rel.size();
    if (!checkInMap(last, mapping))
        mapping.push_back({last});

    vector<vector<int>> newTable;
    for (int i = 0; i < table.size(); i++)
    {
        vector<int> newRow;
        newRow.push_back(findInMap(table[i][0], mapping));
        newRow.push_back(findInMap(table[i][1], mapping));
        newRow.push_back(final[i]);

        if (!vectorExists(newTable, newRow))
            newTable.push_back(newRow);
    }

    // Display the new table
    for (int i = 0; i < newTable.size(); i++)
    {
        for (int j = 0; j < newTable[i].size(); j++)
            cout << newTable[i][j] << ' ';
        cout << endl;
    }

    return 0;
}
