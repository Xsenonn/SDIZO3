//
// Created by User on 2017-06-03.
//

#include <cstring>
#include "TravellingSalesman.h"

TravellingSalesman::TravellingSalesman()
{
    Init(0);
}
TravellingSalesman::TravellingSalesman(unsigned cities)
{
    Init(cities);
}
void TravellingSalesman::Init(unsigned cities)
{
    this->numbOfCities = cities;
    if(cities) {
        mapOfDistances = new unsigned*[cities];
        for(unsigned i = 0; i < cities; i ++) {
            mapOfDistances[i] = new unsigned[cities];
            for(unsigned j = 0; j < cities; j++)
                mapOfDistances[i][j] = 0;
        }
    }
    else
        mapOfDistances = 0;
}

void TravellingSalesman::Permutate(unsigned k, unsigned *permutation, unsigned *minPermutation, unsigned &minDistance)
{
    if(k == 0) {
        unsigned dist = calculateDistance(permutation);
        if(dist < minDistance) {
            minDistance = dist;
            memcpy(minPermutation, permutation, numbOfCities * 4);
        }
    }
    else
        for(unsigned i = 0; i <= k; i++) {
            unsigned temp = permutation[k];
            permutation[k] = permutation[i];
            permutation[i] = temp;

            Permutate(k - 1, permutation, minPermutation, minDistance);

            temp = permutation[k];
            permutation[k] = permutation[i];
            permutation[i] = temp;
        }
}

void TravellingSalesman::setDistance(unsigned beg, unsigned end, unsigned dist)
{
    mapOfDistances[beg][end] = dist;
}

unsigned TravellingSalesman::getDistance(unsigned beg, unsigned end)
{
    return mapOfDistances[beg][end];
}
void TravellingSalesman::randomizeDistances()
{
    for(unsigned i = 0; i < numbOfCities; i++)
        for(unsigned j = 0; j < numbOfCities; j++) {
            if(i != j) {
                setDistance(i, j, rand()%99 + 1);
            }
        }
}
void TravellingSalesman::buildFromFile(ifstream &in)
{
    unsigned numbOfCities;
    unsigned dist;
    in >> numbOfCities;
    Init(numbOfCities);
    for(unsigned i = 0; i < numbOfCities ; i++)
        for(unsigned j = 0; j < numbOfCities; j++) {
            if(j == i) continue;
            in >> dist;
            setDistance(i, j, dist);
        }
}

unsigned TravellingSalesman::calculateDistance(unsigned *permutation)
{
    unsigned sumOfDistances = 0;
    for(unsigned i = 0; i < numbOfCities - 1; i++)
        sumOfDistances += getDistance(permutation[i], permutation[i+1]);
    return sumOfDistances;

}

unsigned* TravellingSalesman::brutalSalesman()
{
    unsigned *permutation = new unsigned[numbOfCities];
    for(unsigned i = 0; i < numbOfCities; i++)
        permutation[i] = i;
    unsigned minDist = 4294967295u;
    unsigned *minPerm = new unsigned[numbOfCities];

    Permutate(numbOfCities - 1, permutation, minPerm, minDist);

    delete[] permutation;

    return minPerm;
}
void TravellingSalesman::dispPermutation(unsigned *permutation, ostream &out)
{
    for(unsigned i = 0; i < numbOfCities; i++)
    {
        out << permutation[i] << " ";
    }
    out << endl << "Distance: " << calculateDistance(permutation) << endl;
}
void TravellingSalesman::resetVisited()
{
    for(unsigned i = 0; i < numbOfCities; i ++)
        setDistance(i, i, 0);
}
unsigned * TravellingSalesman::markVisited(unsigned start)
{
    unsigned *result = new unsigned[numbOfCities];
    result[0] = start;
    setDistance(start, start, 1);//Marking city as visited

    for(unsigned i = 0; i < numbOfCities - 1; i++)
    {
        unsigned minDist = 4294967295u;
        unsigned minCity = 0;
    //Lookin' for closest unvisited city
        for(unsigned j = 0; j < numbOfCities; j++)
        {
            unsigned dist = getDistance(result[i], j);
            if((getDistance(j, j) == 0)&&(dist < minDist))
            {
                minDist = dist;
                minCity = j;
            }
        }
        setDistance(minCity, minCity, 1);//Marking city as Visited
        result[i+1] = minCity;
    }
    return result;
}
unsigned * TravellingSalesman::greedySalesman()
{
    unsigned * result = 0;
    unsigned minDist = 4294967295u;
    for(unsigned i = 0; i < numbOfCities; i++)
    {
        unsigned * temp = markVisited(i);
        unsigned tempDist = calculateDistance(temp);
        resetVisited();
        if(tempDist < minDist) {
            delete [] result;
            result = temp;
            minDist = tempDist;
        }
        else
            delete[] temp;
    }
    return result;
}

ostream & operator<<(ostream &out, TravellingSalesman &tsp)
{
    out.width(2);
    out << right << "\\";
    for (unsigned i = 0; i < tsp.numbOfCities; i++)
    {
        out.width(4);
        out << right << i;
    }
    out << endl;
    for (unsigned i = 0; i < tsp.numbOfCities; i++)
    {
        out.width(2);
        out << right << i;
        for (unsigned j = 0; j < tsp.numbOfCities; j++)
        {
            out.width(4);
            out << right << tsp.mapOfDistances[i][j];
        }
        out << endl;
    }
    out << endl;
    return out;
}
