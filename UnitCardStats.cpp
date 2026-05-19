//
// Created by lpgau on 2026-05-19.
//

#include "UnitCardStats.h"
#include "Components.h"
#include <SDL3_image/SDL_image.h>

//Knight Unit cards Stats
UnitCardKnight_Peasant::unitCardKnight_Peasant() {
    AddComponent(HEALTH);
    health.max_health = 8400;
    health.current_health = 8400;
    AddComponent(MOVEMENT);
    AddComponent(MELEE);

    AddComponent(RENDER);

}