#include <iostream>
#include<stdlib.h>
#include<math.h>
#include <fstream>
#include "Sack.h"
#include "TravellingSalesman.h"
#include <ctime>

using namespace std;



int main()
{
    srand(0);
int option;

    do {

        cout << "Main Menu" << endl;
        cout << "===============================" << endl;
        cout << "1. Knapsack Problem" << endl;
        cout << "2. Travelling Salesman's problem" << endl;
        cout << "0. Exit" << endl;
        cout << "?>";
        cin >> option;

        switch(option)
        {

            case 1:
            {
                Sack *sack = 0;

                int opt;

                do
                {
                    cout << "Knapsack Problem" << endl;
                    cout << "===============================" << endl;
                    cout << "1. Generate Random Sack" << endl;
                    cout << "2. Load Sack from file" << endl;
                    cout << "3. Brutal Sack" << endl;
                    cout << "4. Greedy Sack" << endl;
                    cout << "0. Exit" << endl;
                    cout << "?>";
                    cin >> opt;

                    switch (opt)
                    {

                        case 1:
                        {
                            unsigned size, elementCount;
                            cout << "Enter size of your Sack: ";
                            cin >> size;
                            cout << "Enter number of elements: ";
                            cin >> elementCount;
                            delete sack;
                            sack = new Sack(elementCount, size);
                            sack->randomizeItems();
                            cout << *sack;
                            break;
                        }
                        case 2:
                        {
                            string filename;
                            delete sack;
                            sack = new Sack();
                            cout << "Enter name of file you'd like to load from: ";
                            cin >> filename;
                            filename = filename + ".txt";
                            ifstream file(filename, ios::in);
                            sack->buildFromFile(file);
                            file.close();
                            cout << *sack;
                            break;
                        }
                        case 3:
                        {
                            if (sack)
                            {
                                unsigned long long subSet = sack->brutalSack();
                                sack->displaySubset(subSet, cout);
                            }
                            break;
                        }
                        case 4:
                        {
                            if (sack)
                            {
                                int* subSet = sack->greedySack();
                                sack->displaySubset(subSet, cout);
                                delete[] subSet;
                            }
                            break;
                        }
                        case 0:
                        {
                            break;
                        }
                        default:
                            cout << "Invalid Option!" << endl;
                    }


                } while (opt != 0);
            }

                break;
            case 2:
            {
                TravellingSalesman *tsp = 0;
                int opt1;

                do
                {
                    cout << "Travelling Salesman Problem" << endl;
                    cout << "===============================" << endl;
                    cout << "1. Build random Graph" << endl;
                    cout << "2. Load Graph from file" << endl;
                    cout << "3. Brutal Salesman" << endl;
                    cout << "4. Greedy Salesman" << endl;
                    cout << "0. Exit" << endl;
                    cout << "?>";
                    cin >> opt1;

                    switch (opt1)
                    {

                        case 1:
                        {
                            unsigned size;
                            cout << "Enter Number of Cities: ";
                            cin >> size;
                            delete tsp;
                            tsp = new TravellingSalesman(size);
                            tsp->randomizeDistances();
                            cout << *tsp;
                            break;
                        }
                        case 2:
                        {
                            string filename;
                            delete tsp;
                            tsp = new TravellingSalesman();
                            cout << "Enter name of file you'd like to load from: ";
                            cin >> filename;
                            filename = filename + ".txt";
                            ifstream file(filename, ios::in);
                            tsp->buildFromFile(file);
                            file.close();
                            cout << *tsp;
                            break;
                        }
                        case 3:
                        {
                            if (tsp)
                            {
                                unsigned *perm = tsp->brutalSalesman();
                                tsp->dispPermutation(perm, cout);
                                delete[] perm;
                            }
                            break;
                        }
                        case 4:
                        {
                            if (tsp)
                            {
                                unsigned *perm = tsp->greedySalesman();
                                tsp->dispPermutation(perm, cout);
                                delete[] perm;
                            }
                            break;
                        }
                        case 0:
                        {
                            break;
                        }
                        default:
                            cout << "Invalid Option!" << endl;
                    }


                } while (opt1 != 0);
            }
                break;
            case 0:
                break;
            default:
                cout << "Invalid option!" << endl;

        }
    }while(option != 0);



system("pause");
return 0;
}