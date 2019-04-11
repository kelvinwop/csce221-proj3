//
// Created by kelvin on 4/11/2019.
//

#include "ArtistCompare.h"
#include <iostream>

#define DEBUG

bool ArtistCompare::operator()(const Song *a, const Song *b)
{
#ifdef DEBUG
    std::cout << "m1: "<< (a->artist) << " " << (a->artist.compare(b->artist)) << " " << (b->artist) << std::endl;
#endif
    return a->artist.compare(b->artist) < 0;
}

bool ArtistCompare::operator()(const Song *song, const std::string &artist)
{
#ifdef DEBUG
    std::cout << "m2: " << (song->artist) << " " << (song->artist.compare(artist)) << " " << (artist) << std::endl;
#endif
    return song->artist.compare(artist) < 0;
}

bool ArtistCompare::operator()(const std::string &artist, const Song *song)
{
#ifdef DEBUG
    std::cout << "m3: "<< (artist) << " " << (artist.compare(song->artist)) << " " << (song->artist) << std::endl;
#endif
    return artist.compare(song->artist) < 0;
}
