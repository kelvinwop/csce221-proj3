#include "TitleCompare.h"
#include <iostream>

#define DEBUG

bool TitleCompare::operator()(const Song *a, const Song *b)
{
    #ifdef DEBUG
    std::cout << "m1: "<< (a->title) << " " << (a->title.compare(b->title)) << " " << (b->title) << std::endl;
    #endif
    return a->title.compare(b->title) < 0;
}

bool TitleCompare::operator()(const Song *song, const std::string &title)
{
    #ifdef DEBUG
    std::cout << "m2: " << (song->title) << " " << (song->title.compare(title)) << " " << (title) << std::endl;
    #endif
    return song->title.compare(title) < 0;
}

bool TitleCompare::operator()(const std::string &title, const Song *song)
{
    #ifdef DEBUG
    std::cout << "m3: "<< (title) << " " << (title.compare(song->title)) << " " << (song->title) << std::endl;
    #endif
    return title.compare(song->title) < 0;
}
