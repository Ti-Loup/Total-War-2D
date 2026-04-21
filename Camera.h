#pragma once
#include <SDL3/SDL.h>
#include <algorithm>
#ifndef TOTALWAR2D_CAMERA_H
#define TOTALWAR2D_CAMERA_H

class Camera {
public:
float startX = 0.f;
float startY = 0.f;
float zoom = 1.f;

static constexpr float MIN_ZOOM = 0.5f;
static constexpr float MAX_ZOOM = 4.f;

    //Zoom multiply by the factor and his restricted between 0.5 and 4
    void Zoom(float factor,float screenW = 1920.f, float screenH = 1080.f){
    //Center of map for zoom
    float worldCenterX = startX + (screenW / 2.f) / zoom;
    float worldCenterY = startY + (screenH / 2.f) / zoom;
        zoom = std::clamp(zoom * factor, MIN_ZOOM, MAX_ZOOM);
    startX = worldCenterX - (screenW/2.f)/zoom;
    startY = worldCenterY - (screenH/2.f)/zoom;
    }

    //Movement
    void Movement(float directionX, float directionY){
    startX += directionX / zoom;
    startY += directionY / zoom;
    }

    SDL_FRect WorldToScreen(float worldX, float worldY, float width, float height ) const {
        return{
            (worldX - startX) * zoom, (worldY - startY) * zoom, width * zoom, height * zoom
        };
    }

};


#endif //TOTALWAR2D_CAMERA_H
