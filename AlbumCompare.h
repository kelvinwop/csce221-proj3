//
// Created by kelvin on 4/11/2019.
//

#ifndef CSCE221_PROJ3_ALBUMCOMPARE_H
#define CSCE221_PROJ3_ALBUMCOMPARE_H

#include <string>
#include "Song.h"

struct AlbumCompare
{
    /* 
     * Return whether or not song a's Album is 
     * lexicographically less than song b's Album
     */
    bool operator()(const Song *a, const Song *b);

    /*
     * Return whether or not the song's Album is
     * lexicographically less than the given Album
     */
    bool operator()(const Song *song, const std::string &album);

    /*
     * Return whether or not the given Album is
     * lexicographically less than the song's Album
     */
    bool operator()(const std::string &album, const Song *song);
};

#endif //CSCE221_PROJ3_ALBUMCOMPARE_H
