//
// Created by Louis-Philippe on 4/14/2026.
//

#ifndef TOTALWAR2D_COMPONENTS_H
#define TOTALWAR2D_COMPONENTS_H
#include "Buildings.h"
#include "State.h"
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>



 //Creation du enum des components
 typedef enum
 {
 HEALTH = 1ULL << 0, //Heal, Armour, Leadership
 MOVEMENT = 1ULL << 1, //Speed
 MELEE = 1ULL << 2, // Melee Attack, Melee Defence, Weapon Strengh, Charge Bonus
 RANGED = 1ULL << 3, // Munition, Portée, Puissance des tirs
 RENDER = 1ULL << 4,
 TRANSFORM = 1ULL << 5,
 } ComponentType;

//class de base
class Components {
public:
	virtual ~Components () = default;//destructions des components
};
//
class HealthComponents : public Components
{
  public:
	Sint32 current_health = 0;
	Sint32 max_health = 0;

	HealthComponents () = default;
};

class MovementComponents : public Components
{

  public:
	SDL_FPoint velocity = { 0.f, 0.f }; //Must be int not float


	//Ajout timer pour les cerfs
	float Timer = 0.0f;

	MovementComponents () = default;
};

// Melee Attack, Melee Defence, Weapon Strengh, Charge Bonus
class MeleeComponent : public Components {
public:
	//melee
	Sint32 current_meleeAttack = 0;
	Sint32 max_meleeAttack = 0;
	//Defence
	Sint32 current_meleeDefence = 0;
	Sint32 max_meleeDefence = 0;
	//Weapon Strengh
	Sint32 current_weaponStrengh = 0;
	Sint32 max_weaponStrengh = 0;
	//Charge bonus
	Sint32 current_chargeBonus = 0;
	Sint32 max_chargeBonus = 0;

	MeleeComponent () = default;
};
// Munition, Portée, Puissance des tirs
class RangedComponents : public Components {
public:
	//Munitions
	Sint32 current_ammunition = 0;
	Sint32 max_ammunition = 0;
	//Range
	Sint32 current_range = 0;
	Sint32 max_range = 0;
	//Missile Damage
	Sint32 current_missileDamage = 0;
	Sint32 max_missileDamage = 0;

	RangedComponents () = default;
};

class RenderComponents : public Components
{
  public:
	SDL_Color color = { 0, 0, 0, 0 };

	RenderComponents () = default;
};

class TransformComponents : public Components
{

  public:
	SDL_FPoint position = { 0.f, 0.f };
	SDL_FPoint size = { 0.f, 0.f };

	TransformComponents () = default;
};

struct SettlementComponent {
    std::string cityName = "Settlement";
    SettlementType type = SettlementType::Village;
    int provinceID = -1;
    int baseIncome = 0;
    int basePopulation = 0;
    int publicOrder  = 0;
    int settlementTier = 1;

    //Construction (turnTime)
    bool bBuidingUnderConstruction = false;
    int constructionTime = 0;
    int pendingTier = 0;

    std::vector<BuildingType> buildings;
    std::vector<BuildingType> pendingBuildings;
    std::vector<int> slotConstructionTimes;

    // Totals base + all built bonuses
    int GetTotalIncome() const {
        int total = baseIncome;
        for (auto bt : buildings) {
            const BuildingData* data = GetBuildingData(bt);
            if (data) total += data->incomeBonus;
        }
        return total;
    }

    int GetTotalPublicOrder() const {
        int total = publicOrder;
        for (auto bt : buildings) {
            const BuildingData* data = GetBuildingData(bt);
            if (data) total += data->publicOrderBonus;
        }
        return total;
    }
};

#endif //TOTALWAR2D_COMPONENTS_H
