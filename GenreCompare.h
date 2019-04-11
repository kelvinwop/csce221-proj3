//
// Created by kelvin on 4/11/2019.
//

#ifndef CSCE221_PROJ3_GENRECOMPARE_H
#define CSCE221_PROJ3_GENRECOMPARE_H

#include <string>
#include "Song.h"

struct GenreCompare
{
    /* 
     * Return whether or not song a's Genre is 
     * lexicographically less than song b's Genre
     */
    bool operator()(const Song *a, const Song *b);

    /*
     * Return whether or not the song's Genre is
     * lexicographically less than the given Genre
     */
    bool operator()(const Song *song, const std::string &genre);

    /*
     * Return whether or not the given Genre is
     * lexicographically less than the song's Genre
     */
    bool operator()(const std::string &genre, const Song *song);
};

#endif //CSCE221_PROJ3_GENRECOMPARE_H
