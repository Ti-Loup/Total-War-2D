//
// Created by lpgau on 2026-05-19.
//

#include "UnitCardStats.h"
#include "Components.h"
#include <SDL3_image/SDL_image.h>

//Knight Unit cards Stats
UnitCardStats::unitCardKnight_Peasant() {
    AddComponent(HEALTH);
    health.maxHealth = 8400;
    health.currentHealth = 8400;
    AddComponent(MELEE);


}