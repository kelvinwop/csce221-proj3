//
// Created by kelvin on 4/11/2019.
//

#include "YearCompare.h"
#include <iostream>


bool YearCompare::operator()(const Song *a, const Song *b)
{
#ifdef DEBUG
    std::cout << "m1: "<< (a->year) << " " << (a->year.compare(b->year)) << " " << (b->year) << std::endl;
#endif
    return a->year < (b->year);
}

bool YearCompare::operator()(const Song *song, const unsigned long &year)
{
#ifdef DEBUG
    std::cout << "m2: " << (song->year) << " " << (song->year.compare(year)) << " " << (year) << std::endl;
#endif
    return (song->year) < (year);
}

bool YearCompare::operator()(const unsigned long &year, const Song *song)
{
#ifdef DEBUG
    std::cout << "m3: "<< (year) << " " << (year.compare(song->year)) << " " << (song->year) << std::endl;
#endif
    return year < (song->year);
}
