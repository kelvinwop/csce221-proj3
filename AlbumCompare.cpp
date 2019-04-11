//
// Created by kelvin on 4/11/2019.
//

#include "AlbumCompare.h"
#include <iostream>

bool AlbumCompare::operator()(const Song *a, const Song *b)
{
#ifdef DEBUG
    std::cout << "m1: "<< (a->album) << " " << (a->album.compare(b->album)) << " " << (b->album) << std::endl;
#endif
    return a->album.compare(b->album) < 0;
}

bool AlbumCompare::operator()(const Song *song, const std::string &album)
{
#ifdef DEBUG
    std::cout << "m2: " << (song->album) << " " << (song->album.compare(album)) << " " << (album) << std::endl;
#endif
    return song->album.compare(album) < 0;
}

bool AlbumCompare::operator()(const std::string &album, const Song *song)
{
#ifdef DEBUG
    std::cout << "m3: "<< (album) << " " << (album.compare(song->album)) << " " << (song->album) << std::endl;
#endif
    return album.compare(song->album) < 0;
}
