//
// Created by Louis-Philippe on 4/24/2026.
//
#pragma once
#ifndef TOTALWAR2D_BUILDINGS_H
#define TOTALWAR2D_BUILDINGS_H
#include <string>
#include <unordered_map> //an associative container that stores key-value pairs with unique keys

//the different buildings
enum class BuildingType{
None,
//  -> KNIGHT BUILDINGS <-
Settlement_Village_Knight,
Settlement_Castle_Knight,
Settlement_Capital_Knight,
//Military (Red)
//sword, axe, Halberd
Barracks_T1,
Barracks_T2,
Barracks_T3,
//arc, albale
ArcheryRange_T1,
ArcheryRange_T2,
ArcheryRange_T3,
//Cavalry
Stable_T1,
Stable_T2,
Stable_T3,
//Special Military (Purple) Tier 3+
Artillery_T4,
Artillery_T5,//catapults

//Defence (Yellow)
StoneWall_T4,
StoneWall_T5,
//Economy(Green)
Economy_T1,
Economy_T2,
Economy_T3,
//Growth(Green)
Growth_T1,
Growth_T2,
Growth_T3,
//Religion (Public Order)
Church_T1,
Church_T2,
Church_T3,
//  -> ViKINGS BUILDINGS <-
Settlement_Village_Viking,
Settlement_Castle_Viking,
Settlement_Capital_Viking,

//  -> SAMURAI BUILDINGS <-
Settlement_Village_Samurai,
Settlement_Castle_Samurai,
Settlement_Capital_Samurai,

//UNIQUE Building based on position
//unique town
Quarry_T1,
Quarry_T2,
Quarry_T3,
LumberCamp_T1,
LumberCamp_T2,
LumberCamp_T3,
IronMine_T1,
IronMine_T2,
IronMine_T3,
GoldMine_T1,
GoldMine_T2,
GoldMine_T3,
};

struct BuildingData {
std::string name;
std::string descrpiton;
int cost;
int upkeep;//barracks & defence buildings
int incomeBonus;
int publicOrderBonus;
BuildingType upgradesTo; // if doesnt upgrade more its max tier
};


inline const std::unordered_map<BuildingType, BuildingData>& GetBuildingDatabase() {
    static std::unordered_map<BuildingType, BuildingData>db= {
        {BuildingType::Economy_T1, {"Peasant Fields", "Basic farmland.", 100, 0,   25,  0, BuildingType::Economy_T2}},//if 1 go towards 2
        {BuildingType::Economy_T2, {"Manor Fields", "Established farmland.",  250, 5,   60,  0, BuildingType::Economy_T3}},
        {BuildingType::Economy_T3, {"Prosperous Estate", "Rich agricultural land.", 500, 10,  120, 0, BuildingType::None}},

    };
    return db;
}
inline const BuildingData* GetBuildingData(BuildingType type) {
    const auto& db = GetBuildingDatabase();
    auto it = db.find(type);
    return (it != db.end()) ? &it->second : nullptr;
}
#endif //TOTALWAR2D_BUILDINGS_H
