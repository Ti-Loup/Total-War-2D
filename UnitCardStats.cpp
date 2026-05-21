//
// Created by lpgau on 2026-05-19.
//

#include "UnitCardStats.h"
#include "Components.h"
#include <SDL3_image/SDL_image.h>

//KNIGHT UNIT CARDS STATS
//(TIER 0)
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

UnitCardKnight_PeasantArchers::UnitCardKnight_PeasantArchers() {
    AddComponent(HEALTH);
    health.max_health = 6500;
    health.current_health = 6500;
    AddComponent(MOVEMENT);
    movement.velocity = {1.5f,1.5f};
    AddComponent(MELEE);
    meleeStats.max_meleeAttack = 5;
    meleeStats.current_meleeAttack = 5;
    meleeStats.max_meleeDefence = 7;
    meleeStats.current_meleeDefence = 7;
    meleeStats.max_weaponStrengh = 8;
    meleeStats.current_weaponStrengh = 8;
    meleeStats.max_chargeBonus = 3;
    meleeStats.current_chargeBonus = 3;
    AddComponent(RANGED);
    rangedStats.max_ammunition = 18;
    rangedStats.current_ammunition = 18;
    rangedStats.max_range = 120;
    rangedStats.current_range = 120;
    rangedStats.max_missileDamage = 24;
    rangedStats.current_missileDamage = 24;
    AddComponent(RENDER);
}

//TIER 1 MILITARY TROOPS
// VIKING UNIT CARDS STATS