//
// Created by kelvin on 4/11/2019.
//

#ifndef CSCE221_PROJ3_ARTISTCOMPARE_H
#define CSCE221_PROJ3_ARTISTCOMPARE_H

#include <string>
#include "Song.h"

struct ArtistCompare
{
    /* 
     * Return whether or not song a's Artist is 
     * lexicographically less than song b's Artist
     */
    bool operator()(const Song *a, const Song *b);

    /*
     * Return whether or not the song's Artist is
     * lexicographically less than the given Artist
     */
    bool operator()(const Song *song, const std::string &artist);

    /*
     * Return whether or not the given Artist is
     * lexicographically less than the song's Artist
     */
    bool operator()(const std::string &artist, const Song *song);
};

#endif //CSCE221_PROJ3_ARTISTCOMPARE_H
