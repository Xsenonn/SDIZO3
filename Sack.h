//
// Created by User on 2017-06-03.
//

#ifndef PROJEKT3_12_SACK_H
#define PROJEKT3_12_SACK_H

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cmath>

using namespace std;

class Sack
{
public:
    unsigned numbOfElements;
    unsigned size;

    unsigned *ItemSizes;
    unsigned *ItemWeights;

    Sack();
    Sack(unsigned numbOfElements, unsigned size);
    void Init(unsigned numbOfElements, unsigned size);
    virtual ~Sack()
    {
        delete[] ItemSizes;
        delete[] ItemWeights;
        ItemSizes = 0;
        ItemWeights = 0;
    }
    void randomizeItems();
    void buildFromFile(ifstream &in);
    friend ostream & operator<<(ostream &out, Sack &s);

    unsigned GetWeights(unsigned long long numbOfSets);
    void displaySubset(unsigned long long numbOfSets , ostream &out);
    void displaySubset(int *result, ostream &out);

    unsigned long long brutalSack();
    int* greedySack();



};


#endif //PROJEKT3_12_SACK_H
