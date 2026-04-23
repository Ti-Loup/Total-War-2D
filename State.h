//
// Created by Louis-Philippe on 4/14/2026.
//
#include <vector>
#ifndef TOTALWAR2D_STATE_H
#define TOTALWAR2D_STATE_H

// different scenes
enum State {
Menu,
ChooseCharacter,
Game,
Tutorial,
Options,
Credits,
Quit,
};

//different type of Settlements
enum class SettlementType {
    Village, // 4 slots (village1 + 3 upgrades)
    Castle, // 6 slots (casstle 1  + 5 upgrades)
    Capital, // 8 slots for capital (capital 1 + 7 upgrades)
};

//different building inside a settlements
enum class BuildingType {
    None, // no Building constructed
    Special,//one or 2 per capital (tier 5 building) Strong bonuses or special unit
    Military, // military building type ex: infantry upgrade
    AdvancedMilitary, // AdvancedMilitary type ex: Trebuchet or powder
    Economy, // farm, income, bonus in raiding
    Religion,//public order and faith Good againts revolte
    Defence //Better wall from wood to stone / better garrison
};

//What a settlement has
struct SettlementComponent {
    SettlementType type = SettlementType::Village;
    int provinceID = -1;
    //base stats of a settlement
    int baseIncome = 25; // village 25, castle 100, capital 200
    int basePopulation = 250; //village 250, castle 1000, capital 2500
    int baseGrowthRate = 50;// base population that increase per turn

    std::vector<BuildingType> buildings; //amount of building available base of SettleentType
};

#endif //TOTALWAR2D_STATE_H
