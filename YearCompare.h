//
// Created by kelvin on 4/11/2019.
//

#ifndef CSCE221_PROJ3_YEARCOMPARE_H
#define CSCE221_PROJ3_YEARCOMPARE_H

#include <string>
#include "Song.h"

struct YearCompare
{
    /* 
     * Return whether or not song a's Year is 
     * lexicographically less than song b's Year
     */
    bool operator()(const Song *a, const Song *b);

    /*
     * Return whether or not the song's Year is
     * lexicographically less than the given Year
     */
    bool operator()(const Song *song, const unsigned long &year);

    /*
     * Return whether or not the given Year is
     * lexicographically less than the song's Year
     */
    bool operator()(const unsigned long &year, const Song *song);
};

#endif //CSCE221_PROJ3_YEARCOMPARE_H
