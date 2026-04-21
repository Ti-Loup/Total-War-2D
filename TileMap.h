
#ifndef TOTALWAR2D_TILEMAP_H
#define TOTALWAR2D_TILEMAP_H

#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "FastNoiseLite.h"
#include "Camera.h"

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
    TileType    type = TileType::Grass;
    FactionZone zone = FactionZone::Ocean;
};

struct ColorEntry {
    Uint8 r, g, b;
    TileType type;
    FactionZone zone;
};
//Color of the tiles based on the faction
static const ColorEntry COLOR_TABLE[] = {
    // EAU
    {  0,   0, 255, TileType::DeepWater, FactionZone::Ocean   },
    {  0, 150, 255, TileType::ShallowWater, FactionZone::Ocean   },

    // VIKINGS
    { 90, 130,  80, TileType::Grass, FactionZone::Viking  },
    { 40,  80,  60, TileType::Forest, FactionZone::Viking  },
    {100, 110, 125, TileType::Mountain, FactionZone::Viking  },
    {240, 245, 255, TileType::Snow, FactionZone::Viking  },

    // KNIGHTS
    {100, 175,  60, TileType::Grass, FactionZone::Knight  },
    { 45, 110,  35, TileType::Forest, FactionZone::Knight  },
    {130, 110,  90, TileType::Mountain, FactionZone::Knight  },
    {210, 190, 120, TileType::Sand, FactionZone::Knight  },

    // SAMURAI
    { 85, 140,  55, TileType::Grass, FactionZone::Samurai },
    { 20,  70,  30, TileType::Forest, FactionZone::Samurai },
    { 80,  75,  70, TileType::Mountain, FactionZone::Samurai },
    {200, 175, 140, TileType::Sand, FactionZone::Samurai },
    { 40, 130, 140, TileType::ShallowWater, FactionZone::Samurai },
};

inline SDL_Color TileColor(TileType type, FactionZone zone) {
    switch (type) {
        case TileType::DeepWater:
            return {15, 55, 140, 255};
        case TileType::ShallowWater:
            if (zone == FactionZone::Samurai) return {40, 130, 140, 255};
            return {45, 110, 190, 255};
        case TileType::Sand:
            if (zone == FactionZone::Samurai) return {200, 175, 140, 255};
            return {210, 190, 120, 255};
        case TileType::Grass:
            if (zone == FactionZone::Viking)  return { 90, 130,  80, 255};
            if (zone == FactionZone::Samurai) return { 85, 140,  55, 255};
            return {100, 175,  60, 255};
        case TileType::Forest:
            if (zone == FactionZone::Viking)  return { 40,  80,  60, 255};
            if (zone == FactionZone::Samurai) return { 20,  70,  30, 255};
            return { 45, 110,  35, 255};
        case TileType::Mountain:
            if (zone == FactionZone::Viking)  return {100, 110, 125, 255};
            if (zone == FactionZone::Samurai) return { 80,  75,  70, 255};
            return {130, 110,  90, 255};
        case TileType::Snow:
            return {240, 245, 255, 255};
        default:
            return {255, 0, 255, 255}; // if not recognized
    }
}
class TileMap {
public:
    int cols, rows, tileSize;
    std::vector<std::vector<Tile>> tiles;
    SDL_Texture* mapTexture = nullptr;

    TileMap(const char* imagePath, int tileSize = 16): tileSize(tileSize), cols(0), rows(0)
    {
        LoadFromImage(imagePath);
    }

    ~TileMap() {
        if (mapTexture) SDL_DestroyTexture(mapTexture);
    }

    void LoadFromImage(const char* imagePath) {
        SDL_Surface* surface = IMG_Load(imagePath);
        if (!surface) {
            SDL_LogCritical(1, "Failed to load TileMap image: %s", SDL_GetError());
            return;
        }

        SDL_Surface* converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA8888);
        SDL_DestroySurface(surface);
        if (!converted) return;

        cols = converted->w;
        rows = converted->h;
        tiles.assign(rows, std::vector<Tile>(cols));

        Uint8* pixels = (Uint8*)converted->pixels;
        int pitch = converted->pitch;

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                Uint8* pixel = pixels + r * pitch + c * 4;
                // RGBA8888 → R=pixel[3], G=pixel[2], B=pixel[1], A=pixel[0]
                Uint8 pr = pixel[3];
                Uint8 pg = pixel[2];
                Uint8 pb = pixel[1];

                tiles[r][c] = MatchColor(pr, pg, pb);
            }
        }
        SDL_DestroySurface(converted);
    }

    // find closer color from the color table above
    Tile MatchColor(Uint8 r, Uint8 g, Uint8 b) {
        int bestDist = INT_MAX;
        const ColorEntry* best = &COLOR_TABLE[0];

        for (const auto& entry : COLOR_TABLE) {
            int dr = (int)r - entry.r;
            int dg = (int)g - entry.g;
            int db = (int)b - entry.b;
            int dist = dr*dr + dg*dg + db*db;
            if (dist < bestDist) {
                bestDist = dist;
                best = &entry;
            }
        }

        Tile t;
        t.type = best->type;
        t.zone = best->zone;
        return t;
    }

    void BakeToTexture(SDL_Renderer* renderer) {
        mapTexture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET,
            cols * tileSize,
            rows * tileSize
        );
        if (!mapTexture) return;

        SDL_SetRenderTarget(renderer, mapTexture);
        RenderAllTiles(renderer);
        SDL_SetRenderTarget(renderer, nullptr);
    }

    void RenderAllTiles(SDL_Renderer* renderer) const {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                const Tile& tile = tiles[r][c];

                SDL_FRect rect = {
                    (float)(c * tileSize),
                    (float)(r * tileSize),
                    (float)tileSize,
                    (float)tileSize
                };

                // color variation
                int var = (c * 13 + r * 7) % 10 - 5;

                SDL_Color col = TileColor(tile.type, tile.zone);
                SDL_SetRenderDrawColor(renderer,
                    (Uint8)std::clamp(col.r + var, 0, 255),
                    (Uint8)std::clamp(col.g + var, 0, 255),
                    (Uint8)std::clamp(col.b + var, 0, 255),
                    255);
                SDL_RenderFillRect(renderer, &rect);

                // the grid that is showing
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 15);
                SDL_RenderRect(renderer, &rect);
            }
        }
    }

    void Render(SDL_Renderer* renderer, const Camera &camera) const {
        if (!mapTexture) return;
        SDL_FRect dst = {
            -camera.startX * camera.zoom,
             -camera.startY * camera.zoom,
            (float)(cols * tileSize) * camera.zoom,
            (float)(rows * tileSize) * camera.zoom
        };
        SDL_RenderTexture(renderer, mapTexture, nullptr, &dst);
    }
};


#endif // TOTALWAR2D_TILEMAP_H