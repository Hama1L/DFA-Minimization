#include <vector>
#include <iostream>
using namespace std;

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

bool compare_vectors(vector<int> vec1, vector<int> vec2)
{
    for (int i = 0; i < vec1.size(); i++)
        if (vec1[i] != vec2[i])
            return false;
    return true;
}

class Partition
{
    int inputs;
    vector<int> final;
    vector<vector<int>> table;
    bool done = false;

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
                    if (compare_vectors(reference, new_table[j]))
                        new_table[j][inputs + 1] = counter;
                counter++;
            }
        }

        done = true;
        for (int i = 0; i < new_table.size(); i++)
            if (old_table[i][inputs] != new_table[i][inputs + 1])
                done = false;

        for (int i = 0; i < new_table.size(); i++)
            old_table[i][inputs] = new_table[i][inputs + 1];
    }

    void reduce_table(vector<vector<int>> &mappings)
    {

        for (int i = 0; i < mappings.size(); i++)
            mappings[i][inputs + 1] = final[i];

        vector<vector<int>> minimized;
        for (int i = 0; i < mappings.size(); i++)
        {
            bool unique = true;
            for (int j = i + 1; j < mappings.size(); j++)
                if (compare_vectors(mappings[i], mappings[j]))
                    unique = false;

            if (unique)
                minimized.push_back(mappings[i]);
        }

        table.clear();
        final.clear();

        for (int i = 0; i < minimized.size(); i++)
        {
            vector<int> row = {minimized[i][0],
                               minimized[i][1]};
            table.push_back(row);
            final.push_back(minimized[i][3]);
        }
    }

public:
    Partition(int inputs, vector<int> final, vector<vector<int>> table)
        : inputs(inputs), final(final), table(table) {}

    void minimize()
    {
        vector<vector<int>> old_table(table.size(), vector<int>(inputs + 2));

        for (int i = 0; i < table.size(); i++)
        {
            for (int j = 0; j < inputs; j++)
                old_table[i][j] = table[i][j];
            old_table[i][inputs] = final[i];
            old_table[i][inputs + 1] = -1;
        }

        while (!done)
        {
            vector<vector<int>> new_table = old_table;
            map_table(old_table, new_table);
            update_table(old_table, new_table);
        }

        vector<vector<int>> mappings = old_table;
        map_table(old_table, mappings);
        reduce_table(mappings);
    }

    void printTable()
    {
        print_table(table);
        print_vector(final);
    }
};

int main()
{
    int inputs = 2;

    vector<vector<int>> table = {

        {1, 2},
        {0, 3},
        {4, 5},
        {4, 5},
        {4, 5},
        {5, 5},
    };

    vector<int> final = {0, 1, 1, 1, 0, 0};

    auto algo = Partition(inputs, final, table);
    algo.minimize();
    algo.printTable();
}