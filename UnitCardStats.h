//
// Created by lpgau on 2026-05-19.
//

#ifndef TOTALWAR2D_UNITCARDSTATS_H
#define TOTALWAR2D_UNITCARDSTATS_H

#include "Entity.h"
#include "Components.h"
class UnitCardStats {

};
/*
DLC Units Ideas Knight
- Assassins, Centurion, Prest warriors(different categories), Gladiators

*/

//KNIGHT LORDS :
//todo

//KNIGHT HEROS :
//todo


//Knight Units PEASANT(TIER 0 / ALREADY UNLOCKED)
class UnitCardKnight_Peasant : public Entity {
    public:
    int maxEntities = 60;
    int currentEntities = 60;

    UnitCardKnight_Peasant();

};

//PEASANT ARCHERS (TIER 0 / ALREADY UNLOCKED)
class UnitCardKnight_PeasantArchers : public Entity {
public:
    int maxEntities = 60;
    int currentEntities = 60;

    UnitCardKnight_PeasantArchers();

};

//BUILDING MILITARY
//Barracks_T1
class UnitCardKnight_Swordmen : public Entity {
public:
    int maxEntities = 40;
    int currentEntities = 40;

    UnitCardKnight_Swordmen();
};
//Barracks_T2
class UnitCardKnight_SwordAndShield : public Entity {
public:
    int maxEntities = 40;
    int currentEntities = 40;

    UnitCardKnight_SwordAndShield();
};
//Barracks_T3
class UnitCardKnight_MaceAndShield : public Entity {
public:
    int maxEntities = 40;
    int currentEntities = 40;

    UnitCardKnight_MaceAndShield();
};
//ArcheryRange_T1
class UnitCardKnight_Hunters : public Entity {
public:
    int maxEntities = 40;
    int currentEntities = 40;

    UnitCardKnight_Hunters();
};
//ArcheryRange_T2
class UnitCardKnight_Archers : public Entity {
public:
    int maxEntities = 40;
    int currentEntities = 40;

    UnitCardKnight_Archers();
};
//ArcheryRange_T3
class UnitCardKnight_LongBowmen : public Entity {
public:
    int maxEntities = 40;
    int currentEntities = 40;

    UnitCardKnight_LongBowmen();
};
//Stable_T1
class UnitCardKnight_PeasantHorsemen : public Entity {
public:
    int maxEntities = 30;
    int currentEntities = 30;

    UnitCardKnight_PeasantHorsemen();
};

//Stable_T2
class UnitCardKnight_LightCavalry : public Entity {
public:
    int maxEntities = 20;
    int currentEntities = 20;

    UnitCardKnight_LightCavalry();
};
//Stable_T3
class UnitCardKnight_HeavyCavalry : public Entity {
public:
    int maxEntities = 20;
    int currentEntities = 20;

    UnitCardKnight_HeavyCavalry();
};

//BUILDING ADV. MILITARY
//Artillery_T4
class UnitCardKnight_Catapult : public Entity {
public:
    int maxEntities = 4;
    int currentEntities = 4;

    UnitCardKnight_Catapult();
};
//Artillery_T5
class UnitCardKnight_Trebuchet : public Entity {
    int maxEntities = 4;
    int currentEntities = 4;

    UnitCardKnight_Trebuchet();
};

//Religion (future dlc for religious troops)
//////////////////////////////////////////

//VIKING UNITS

//Viking LORDS :
//todo

//Viking HEROS :
//todo Shaman


//SAMURAI Units

//Samurai LORDS

//Samurai Heros




#endif //TOTALWAR2D_UNITCARDSTATS_H