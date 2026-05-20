//
// Created by lpgau on 2026-05-19.
//

#include "UnitCardStats.h"
#include "Components.h"
#include <SDL3_image/SDL_image.h>

//KNIGHT UNIT CARDS STATS
UnitCardKnight_Peasant::UnitCardKnight_Peasant() {
    AddComponent(HEALTH);
    health.max_health = 8400;
    health.current_health = 8400;
    AddComponent(MOVEMENT);
    movement.velocity = {1.5f,1.5f};
    AddComponent(MELEE);
    meleeStats.max_meleeAttack = 12;
    meleeStats.current_meleeAttack = 12;
    meleeStats.max_meleeDefence = 4;
    meleeStats.current_meleeDefence = 4;
    meleeStats.max_weaponStrengh = 14;
    meleeStats.current_weaponStrengh = 14;
    meleeStats.max_chargeBonus = 3;
    meleeStats.current_chargeBonus = 3;
    AddComponent(RENDER);

    // Amount of Entities in this UnitCard
    // int maxEntities = 60;
    // int currentEntities = 60;
}


// VIKING UNIT CARDS STATS