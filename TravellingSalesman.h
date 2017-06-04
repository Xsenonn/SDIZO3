//
// Created by User on 2017-06-03.
//

#ifndef PROJEKT3_12_TRAVELLINGSALESMAN_H
#define PROJEKT3_12_TRAVELLINGSALESMAN_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>

using namespace std;

class TravellingSalesman
{
public:
    unsigned **mapOfDistances;
    unsigned numbOfCities;

    TravellingSalesman();
    TravellingSalesman(unsigned cities);
    void Init(unsigned cities);
    virtual ~TravellingSalesman()
    {
        if(numbOfCities) {
            for(unsigned i = 0; i < numbOfCities; i++)
                delete[] mapOfDistances[i];
            delete[] mapOfDistances;
        }
        mapOfDistances = 0;
    }
    void setDistance(unsigned beg, unsigned end, unsigned dist);
    unsigned getDistance(unsigned beg, unsigned end);
    void randomizeDistances();
    void buildFromFile(ifstream &in);
    unsigned calculateDistance(unsigned *permutation);
    void Permutate(unsigned k, unsigned *permutation, unsigned *minPermutation, unsigned &minDistance);
    unsigned * brutalSalesman();
    void dispPermutation(unsigned *permutation, ostream &out);
    void resetVisited();
    unsigned * markVisited(unsigned start);
    unsigned* greedySalesman();
    friend ostream & operator<<(ostream &out, TravellingSalesman &tsp);

};

#endif //PROJEKT3_12_TRAVELLINGSALESMAN_H
