#include "helpers.h"

#ifndef PART
#define PART

struct Partition
{
    int inputs;
    vector<int> final_states;
    vector<vector<int>> transition_table;
    vector<vector<vector<int>>> intermediate_transition_tables;
    bool is_done = false;

    void map_table(vector<vector<int>> &old_table, vector<vector<int>> &new_table)
    {
        for (int i = 0; i < old_table.size(); i++)
            for (int j = 0; j < inputs; j++)
                new_table[i][j] = old_table[new_table[i][j]][inputs];
    }

    void update_table(vector<vector<int>> &old_table, vector<vector<int>> &new_table)
    {
        int counter = 0;
        for (int i = 0; i < new_table.size(); i++)
        {
            if (new_table[i][inputs + 1] == -1)
            {
                vector<int> reference = new_table[i];
                for (int j = i; j < new_table.size(); j++)
                    if (reference == new_table[j])
                        new_table[j][inputs + 1] = counter;
                counter++;
            }
        }

        is_done = true;
        for (int i = 0; i < new_table.size(); i++)
            if (old_table[i][inputs] != new_table[i][inputs + 1])
                is_done = false;

        for (int i = 0; i < new_table.size(); i++)
            old_table[i][inputs] = new_table[i][inputs + 1];
    }

    void reduce_table(vector<vector<int>> &mappings)
    {
        for (int i = 0; i < mappings.size(); i++)
            mappings[i][inputs + 1] = final_states[i];

        vector<vector<int>> minimized;
        for (int i = 0; i < mappings.size(); i++)
        {
            if (!vectorExists(minimized, mappings[i]))
                minimized.push_back(mappings[i]);
        }

        transition_table.clear();
        final_states.clear();

        for (int i = 0; i < minimized.size(); i++)
        {
            vector<int> row;
            for (int j = 0; j < inputs; j++)
                row.push_back(minimized[i][j]);
            row.push_back(minimized[i][inputs + 1]);
            transition_table.push_back(row);
        }
    }

public:
    Partition(int inputs, vector<int> final, vector<vector<int>> table)
        : inputs(inputs), final_states(final), transition_table(table)
    {
        for (int i = 0; i < transition_table.size(); i++)
            transition_table[i].push_back(final_states[i]);
    }

    void minimize()
    {
        vector<vector<int>> old_table(transition_table.size(), vector<int>(inputs + 2));

        for (int i = 0; i < transition_table.size(); i++)
        {
            for (int j = 0; j < inputs; j++)
                old_table[i][j] = transition_table[i][j];
            old_table[i][inputs] = final_states[i];
            old_table[i][inputs + 1] = -1;
        }

        while (!is_done)
        {
            vector<vector<int>> new_table = old_table;
            map_table(old_table, new_table);
            update_table(old_table, new_table);
            intermediate_transition_tables.push_back(new_table);
        }

        vector<vector<int>> mappings = old_table;
        map_table(old_table, mappings);
        reduce_table(mappings);
    }

    void printTable()
    {
        print_table(transition_table);
    }
};

#endif
