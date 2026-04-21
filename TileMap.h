//
// TileMap.h — Three-Faction World Map (Knights / Vikings / Samurai)
// Inspired by the For Honor map layout
//
#ifndef TOTALWAR2D_TILEMAP_H
#define TOTALWAR2D_TILEMAP_H

#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
#include <SDL3/SDL.h>
#include "FastNoiseLite.h"

enum class TileType : uint8_t {
    DeepWater,
    ShallowWater,
    Sand,
    Grass,
    Forest,
    Mountain,
    Snow,
};

enum class FactionZone : uint8_t {
    Knight,
    Viking,
    Samurai,
    Ocean
};

struct Tile {
    TileType    type      = TileType::Grass;
    FactionZone zone      = FactionZone::Ocean;
    float       elevation = 0.0f;
    float       moisture  = 0.0f;
};

//color of tiles
inline SDL_Color TileColor(TileType t, FactionZone zone) {
    switch (t) {
        case TileType::DeepWater:    return {15,  55,  140, 255};
        case TileType::ShallowWater: return {45,  110, 190, 255};
        case TileType::Sand:
            // Knights
            return (zone == FactionZone::Knight)? SDL_Color{215, 190, 110, 255}: SDL_Color{200, 185, 140, 255};
        case TileType::Grass:
            if (zone == FactionZone::Samurai) return {65,  130,  50, 255};
            if (zone == FactionZone::Viking)  return {90,  145,  70, 255};
            return {100, 175,  60, 255};
        case TileType::Forest:
            // Samurai
            return (zone == FactionZone::Samurai)
                ? SDL_Color{20,  75,  20, 255}
                : SDL_Color{30, 100,  30, 255};
        case TileType::Mountain:
            // Viking
            return (zone == FactionZone::Viking)
                ? SDL_Color{105, 115, 130, 255}
                : SDL_Color{125, 110,  95, 255};
        case TileType::Snow:         return {240, 248, 255, 255};
        default:                     return {  0,   0,   0, 255};
    }
}


class TileMap {
public:

};

#endif // TOTALWAR2D_TILEMAP_H