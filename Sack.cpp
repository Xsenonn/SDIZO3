//
// Created by User on 2017-06-03.
//

#include "Sack.h"

Sack::Sack()
{
    Init(0, 0);
}
Sack::Sack(unsigned numbOfElements, unsigned size)
{
    Init(numbOfElements, size);
}

void Sack::randomizeItems()
{
    unsigned sizeSum = 0;
    for(unsigned i = 0; i < numbOfElements; i++) {
        ItemSizes[i] = rand()%98+1;
        sizeSum += ItemSizes[i];
        ItemWeights[i] = rand()%98+1;
    }
    while(sizeSum < size + size / 10 * 3) {
        for(unsigned i = 0; i < numbOfElements; i++) {
            unsigned size = rand()%30;
            ItemSizes[i] += size;
            sizeSum += size;
        }
    }
}

void Sack::Init(unsigned numbOfElements, unsigned size)
{
    this->size = size;
    this->numbOfElements = numbOfElements;

    if(size)
    {
        this->ItemSizes = new unsigned[numbOfElements];
        this->ItemWeights = new unsigned[numbOfElements];
    }
    else
    {
        this->ItemSizes = 0;
        this->ItemWeights = 0;
    }
}

void Sack::buildFromFile(ifstream &in)
{
    delete[] ItemSizes;
    delete[] ItemWeights;
    in >> size;
    in >> numbOfElements;
    Init(numbOfElements, size);
    for(int i = 0; i < numbOfElements; i++)
    {
        in >> ItemSizes[i];
        in >> ItemWeights[i];
    }
}

ostream & operator << (ostream &out, Sack &s)
{
    int sumOfSizes = 0, sumOfWeights = 0;
    out << "s/w: ";
    for(unsigned i = 0; i < s.numbOfElements; i++)
    {
        out << i << ":" << s.ItemSizes[i] << "/" << s.ItemWeights[i] << " ";
        sumOfSizes += s.ItemSizes[i];
        sumOfWeights += s.ItemWeights[i];
    }
    out << endl;
    out << "Capacity: " << s.size << " Sum of sizes: " << sumOfSizes << " Sum of weights: " << sumOfWeights << endl;
    return out;
}

unsigned Sack::GetWeights(unsigned long long numbOfSets)
{
    unsigned sumOfSizes = 0, sumOfWeights = 0;
    for(unsigned i = 0; i < numbOfElements; i++)
    {
        if(numbOfSets % 2)
        {
            sumOfSizes += ItemSizes[i];
            sumOfWeights += ItemWeights[i];
        }
        numbOfSets /= 2; //Z jakiegos powodu w srodowisku nie dziala mi przesuniecie bitowe
    }
    if(sumOfSizes <= size)
    {
        return sumOfWeights;
    }
    return 0;

}

void Sack::displaySubset(unsigned long long numbOfSets, ostream &out)
{
    unsigned sumOfSizes = 0, sumOfWeights = 0;
    out << "s/w: ";
    for(unsigned i = 0; i < numbOfElements; i++) {
        if(numbOfSets % 2) {
            sumOfSizes += ItemSizes[i];
            sumOfWeights += ItemWeights[i];
            out << i << ":" << ItemSizes[i] << "/" << ItemWeights[i] << " ";
        }
        numbOfSets /= 2;
    }
    out << endl << "Capacity: " << size << " Sum of Sizes: " << sumOfSizes << " Sum of Weights: " << sumOfWeights << endl;
}

void Sack::displaySubset(int *result, ostream &out)
{
    unsigned sumOfSizes = 0, sumOfWeights = 0;
    out << "s/w: ";
    for(unsigned i = 0 ; i < numbOfElements; i++)
    {
        if(result[i] < 0)
            break;
        out << result[i] << ":" << ItemSizes[result[i]] << "/" << ItemWeights[result[i]] << " ";
        sumOfSizes += ItemSizes[result[i]];
        sumOfWeights += ItemWeights[result[i]];
    }
    out << endl << "Capacity: " << size << " Sum of Sizes: " << sumOfSizes << " Sum of Weights: " << sumOfWeights << endl;
}


unsigned long long Sack::brutalSack()
{
    unsigned long long setCount = 1;
    for(unsigned int i = 0; i < numbOfElements; i++)
    {
        setCount *= 2;
    }
    unsigned maxSubSet = 0;
    unsigned maxWeight = 0;
    for( unsigned long long i = 0; i <= setCount; i++)
    {
        unsigned sumWeight = GetWeights(i);
        if(sumWeight > maxWeight)
        {
            maxWeight = sumWeight;
            maxSubSet = i;
        }
    }
    return maxSubSet;
}

int* Sack::greedySack()
{
    unsigned *sorting = new unsigned[numbOfElements];
    for(unsigned i = 0; i < numbOfElements; i++)
        sorting[i] = i;
    for(unsigned i = 0; i < numbOfElements - 1; i++)
        for(unsigned j = 0; j < numbOfElements - 1 - i; j++)
        {
            double element_h = ((double)ItemWeights[sorting[j]])/ItemSizes[sorting[j]];
            double next_h = ((double)ItemWeights[sorting[j+1]])/ItemSizes[sorting[j+1]];
            if(element_h < next_h)
            {
                unsigned temp = sorting[j];
                sorting[j] = sorting[j+1];
                sorting[j+1] = temp;
            }
        }

    int *result = new int[numbOfElements];
    for(unsigned i = 0; i < numbOfElements; i++)
        result[i] = -1;

    unsigned resultIndex = 0;
    unsigned sizeSum = 0;
    for(unsigned i = 0; i < numbOfElements; i++)
    {
        if(sizeSum + ItemSizes[sorting[i]] < size)
        {
            result[resultIndex] = sorting[i];
            resultIndex++;
            sizeSum += ItemSizes[sorting[i]];
        }
    }
    delete[] sorting;

    return result;
}