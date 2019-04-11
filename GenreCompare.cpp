//
// Created by kelvin on 4/11/2019.
//

#include "GenreCompare.h"
#include <iostream>


bool GenreCompare::operator()(const Song *a, const Song *b)
{
#ifdef DEBUG
    std::cout << "m1: "<< (a->genre) << " " << (a->genre.compare(b->genre)) << " " << (b->genre) << std::endl;
#endif
    return a->genre.compare(b->genre) < 0;
}

bool GenreCompare::operator()(const Song *song, const std::string &genre)
{
#ifdef DEBUG
    std::cout << "m2: " << (song->genre) << " " << (song->genre.compare(genre)) << " " << (genre) << std::endl;
#endif
    return song->genre.compare(genre) < 0;
}

bool GenreCompare::operator()(const std::string &genre, const Song *song)
{
#ifdef DEBUG
    std::cout << "m3: "<< (genre) << " " << (genre.compare(song->genre)) << " " << (song->genre) << std::endl;
#endif
    return genre.compare(song->genre) < 0;
}
