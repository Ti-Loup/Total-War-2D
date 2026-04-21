//
// Created by Louis-Philippe on 4/20/2026.
//

#ifndef TOTALWAR2D_TILEMAP_H
#define TOTALWAR2D_TILEMAP_H

#pragma once
#include <vector>
#include <SDL3/SDL.h>

//the types of terrain
enum class TileType : uint8_t{
DeepWater,
ShallowWater,
Sand,
Grass,
Forest,
Mountain,
Snow,
Road
};

struct Tile {
    TileType type = TileType::Grass;
    bool hasRoad = false;
    float elevation = 0.0f;
    float moisture = 0.0f;
};


// 0 = floor more its closer to 0 it's down(downWater) and more it's closer to 1 it's up (cold and mountain)
//Biome in function of elevation
inline TileType GetBiome (float elevation, float moisture){
    if (elevation < -0.35f){
        return TileType::DeepWater;
    }
    if (elevation < -0.15f){
        return TileType::ShallowWater;
    }
    if(elevation < -0.05f){
        return TileType::Sand;
    }
    if (elevation > 0.55f) {
        return TileType::Snow;
    }
    if (elevation > 0.30f){
        return TileType::Mountain;
    }
    if (moisture > 0.15f){
        return TileType::Forest;
    }
    return TileType::Grass;
}

//color of the tiles
inline SDL_Color TileColor(TileType tileType){
    switch(tileType){
    case TileType::DeepWater:
        return {20, 70, 160, 255};
    case TileType::ShallowWater:
        return {50, 120, 200, 255};
    case TileType::Sand:
        return {210, 195, 130, 255};
    case TileType::Grass:
        return {80,  160,  55, 255};
    case TileType::Forest:
        return {25, 95, 25, 255};
    case TileType::Mountain:
        return {130,115,100,255};
    case TileType::Snow:
        return {255, 235, 245, 255};
    case TileType::Road:
        return {155,125,70,255};
    default:
        return {0,0,0,255};
    }
}

#endif //TOTALWAR2D_TILEMAP_H
