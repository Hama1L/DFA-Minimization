#include "Partition.h"
#include "Myhill-Nerode.h"

int main()
{
    int inputs = 2;

    vector<int> final = {0, 1, 1, 1, 0, 0};

    vector<vector<int>> table = {

        {1, 2},
        {0, 3},
        {4, 5},
        {4, 5},
        {4, 5},
        {5, 5},
    };

    auto algo1 = Partition(inputs, final, table);
    auto algo2 = MyhillNerode(inputs, final, table);

    algo1.minimize();
    algo2.minimize();

    cout << "Minimized by Partition Method:-" << endl;
    algo1.printTable();

    cout << endl
         << endl;

    cout << "Minimized by Myhill-Nerode Method:-" << endl;
    algo2.printTable();
}