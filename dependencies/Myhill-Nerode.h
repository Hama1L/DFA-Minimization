#include "helpers.h"

#ifndef HILL
#define HILL

struct MyhillNerode
{
    int inputs;
    vector<int> final;
    vector<vector<int>> table;
    vector<vector<int>> mappings;
    vector<vector<int>> relations;
    bool is_done = false;

    void check_equivalent(vector<vector<int>> &map, int i, int j)
    {
        if (map[i][j] != 1)
        {
            for (int k = 0; k < inputs; k++)
            {
                int b = table[j][k];
                int a = table[i + 1][k];
                if (a - 1 < map.size() && b < map[a - 1].size() && map[a - 1][b])
                {
                    map[i][j] = true;
                    is_done = false;
                    break;
                }
            }
        }
    }

    void build_relations(vector<vector<int>> &map)
    {
        int n = table.size();

        for (int i = 1; i < n; i++)
        {
            vector<int> row;
            for (int j = 0; j < i; j++)
                row.push_back(final[i] != final[j] ? 1 : 0);
            map.push_back(row);
        }

        while (!is_done)
        {
            is_done = true;
            for (int i = 0; i < map.size(); i++)
                for (int j = 0; j < map[i].size(); j++)
                    check_equivalent(map, i, j);
        }
    }

    void build_mappings(vector<vector<int>> &map, vector<vector<int>> &mappings)
    {
        for (int i = 0; i < map.size(); i++)
        {
            if (checkInMap(i, mappings))
                continue;

            bool merged = false;
            for (int j = 0; j < map[i].size(); j++)
            {
                if (!map[i][j])
                {
                    merged = true;
                    mappings.push_back({i, j + 1});
                }
            }

            if (!merged)
                mappings.push_back({i});
        }

        int last = map.size();
        if (!checkInMap(last, mappings))
            mappings.push_back({last});
    }

    void reduce_table(vector<vector<int>> &mappings)
    {
        vector<vector<int>> minimized;
        for (int i = 0; i < table.size(); i++)
        {
            vector<int> newRow;
            for (int j = 0; j < inputs; j++)
                newRow.push_back(findInMap(table[i][j], mappings));
            newRow.push_back(final[i]);

            if (!vectorExists(minimized, newRow))
                minimized.push_back(newRow);
        }

        table.clear();
        final.clear();

        // Update the table
        for (int i = 0; i < minimized.size(); i++)
        {
            vector<int> row;
            for (int j = 0; j < inputs; j++)
                row.push_back(minimized[i][j]);

            row.push_back(minimized[i][inputs]);
            table.push_back(row);
        }
    }

    MyhillNerode(int inputs, vector<int> final_, vector<vector<int>> table_)
        : inputs(inputs), final(final_), table(table_)
    {
        for (int i = 0; i < table.size(); i++)
            table[i].push_back(final[i]);
    }

    void minimize()
    {
        build_relations(relations);

        build_mappings(relations, mappings);

        reduce_table(mappings);
    }
};

#endif
