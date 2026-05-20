//
// Created by lpgau on 2026-05-19.
//

#ifndef TOTALWAR2D_UNITCARDSTATS_H
#define TOTALWAR2D_UNITCARDSTATS_H

#include "Entity.h"
#include "Components.h"
class UnitCardStats {

};

//Knight Units (TIER 0 / ALREADY UNLOCKED)
class UnitCardKnight_Peasant : public Entity {
    public:
    int maxEntities = 60;
    int currentEntities = 60;

    UnitCardKnight_Peasant();

};

//Viking Units

//Samurai Units


#endif //TOTALWAR2D_UNITCARDSTATS_H