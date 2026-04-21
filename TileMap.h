//
// Created by Louis-Philippe on 4/20/2026.
//
#ifndef TOTALWAR2D_TILEMAP_H
#define TOTALWAR2D_TILEMAP_H

#pragma once
#include <vector>

#include <SDL3/SDL.h>
#include "FastNoiseLite.h"
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
        return {80, 160, 55, 255};
    case TileType::Forest:
        return {25, 95, 25, 255};
    case TileType::Mountain:
        return {130, 115, 100, 255};
    case TileType::Snow:
        return {255, 235, 245, 255};
    case TileType::Road:
        return {155, 125, 70, 255};
    default:
        return {0, 0, 0,255};
    }
}
//class TileMap
class TileMap {
public:
    int cols, rows, tileSize;
    std::vector<std::vector<Tile>> tiles;

    TileMap(int cols, int rows, int tileSize = 64, unsigned int seed = 1337)
        : cols(cols), rows(rows), tileSize(tileSize),
          tiles(rows, std::vector<Tile>(cols))
    {
        GenerateMap(seed);
    }

    void GenerateMap(unsigned int seed) {
        FastNoiseLite elevationNoise;
        elevationNoise.SetSeed(seed);
        elevationNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        elevationNoise.SetFractalType(FastNoiseLite::FractalType_FBm);
        elevationNoise.SetFractalOctaves(4);
        elevationNoise.SetFrequency(0.008f);

        FastNoiseLite moistureNoise;
        moistureNoise.SetSeed(seed + 999);
        moistureNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        moistureNoise.SetFractalType(FastNoiseLite::FractalType_FBm);
        moistureNoise.SetFractalOctaves(3);
        moistureNoise.SetFrequency(0.006f);

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                float elev  = elevationNoise.GetNoise((float)c, (float)r);
                float moist = moistureNoise.GetNoise((float)c, (float)r);

                // Gradient circulaire — eau sur les bords
                float nx = (float)c / cols * 2.f - 1.f;
                float ny = (float)r / rows * 2.f - 1.f;
                elev -= std::sqrt(nx*nx + ny*ny) * 0.6f;

                tiles[r][c].elevation = elev;
                tiles[r][c].moisture  = moist;
                tiles[r][c].type      = GetBiome(elev, moist);
            }
        }
        GenerateRoads();
    }

    void GenerateRoads() {
        int midRow = rows / 2;
        int startC = -1, endC = -1;

        for (int c = 0; c < cols; c++) {
            if (IsLand(midRow, c) && startC == -1) startC = c;
            if (IsLand(midRow, cols - 1 - c) && endC == -1) endC = cols - 1 - c;
        }
        if (startC == -1 || endC == -1) return;

        for (int c = startC; c <= endC; c++)
            if (IsLand(midRow, c))
                tiles[midRow][c].hasRoad = true;
    }

    bool IsLand(int r, int c) const {
        TileType t = tiles[r][c].type;
        return t != TileType::DeepWater && t != TileType::ShallowWater;
    }

    void Render(SDL_Renderer *renderer) const {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                const Tile &tile = tiles[r][c];

                SDL_FRect rect = {
                    (float)(c * tileSize),
                    (float)(r * tileSize),
                    (float)tileSize,
                    (float)tileSize
                };

                // Tile de base
                SDL_Color col = TileColor(tile.type);
                SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
                SDL_RenderFillRect(renderer, &rect);

                // Overlay route
                if (tile.hasRoad) {
                    SDL_FRect road = {
                        rect.x,
                        rect.y + tileSize * 0.35f,
                        (float)tileSize,
                        tileSize * 0.30f
                    };
                    SDL_SetRenderDrawColor(renderer, 155, 125, 70, 255);
                    SDL_RenderFillRect(renderer, &road);
                }

                // Grid légère
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 20);
                SDL_RenderRect(renderer, &rect);
            }
        }
    }
};

//RENDER TO DO

#endif //TOTALWAR2D_TILEMAP_H
