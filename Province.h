#pragma once
#ifndef TOTALWAR2D_PROVINCE_H
#define TOTALWAR2D_PROVINCE_H

#include <string>
#include <SDL3/SDL.h>

enum class FactionZone : uint8_t {
    Knight,
    Viking,
    Samurai,
    Ocean
};

struct Province {
int id;
std::string name;
FactionZone owner;
bool isCapital = false;
};

#endif //TOTALWAR2D_PROVINCE_H
