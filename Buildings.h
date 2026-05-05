//
// Created by Louis-Philippe on 4/24/2026.
//
#pragma once
#ifndef TOTALWAR2D_BUILDINGS_H
#define TOTALWAR2D_BUILDINGS_H
#include <string>
#include <vector>
#include "Province.h"
#include "State.h"
#include <unordered_map>

enum class BuildingType{
None,
//  -> KNIGHT BUILDINGS <-
Settlement_Village_Knight_T1,
Settlement_Village_Knight_T2,
Settlement_Village_Knight_T3,
Settlement_Castle_Knight_T1,
Settlement_Castle_Knight_T2,
Settlement_Castle_Knight_T3,
Settlement_Castle_Knight_T4,
Settlement_Castle_Knight_T5,
Settlement_Capital_Knight_T1,
Settlement_Capital_Knight_T2,
Settlement_Capital_Knight_T3,
Settlement_Capital_Knight_T4,
Settlement_Capital_Knight_T5,
Barracks_T1,
Barracks_T2,
Barracks_T3,
ArcheryRange_T1,
ArcheryRange_T2,
ArcheryRange_T3,
Stable_T1,
Stable_T2,
Stable_T3,
Artillery_T4,
Artillery_T5,
ReinforceWalls_T3,
ReinforceWalls_T4,
ReinforceWalls_T5,
Economy_T1,
Economy_T2,
Economy_T3,
Growth_T1,
Growth_T2,
Growth_T3,
Church_T1,
Church_T2,
Church_T3,

//  -> VIKINGS BUILDINGS <-
Settlement_Village_Viking_T1,
Settlement_Village_Viking_T2,
Settlement_Village_Viking_T3,
Settlement_Castle_Viking_T1,
Settlement_Castle_Viking_T2,
Settlement_Castle_Viking_T3,
Settlement_Castle_Viking_T4,
Settlement_Castle_Viking_T5,
Settlement_Capital_Viking_T1,
Settlement_Capital_Viking_T2,
Settlement_Capital_Viking_T3,
Settlement_Capital_Viking_T4,
Settlement_Capital_Viking_T5,
WarLodge_T1,
WarLodge_T2,
WarLodge_T3,
ShootingGround_T1,
ShootingGround_T2,
ShootingGround_T3,
HorseTraining_T1,
HorseTraining_T2,
HorseTraining_T3,
ChosensOfOdin_T3,
ChosensOfOdin_T4,
ChosensOfOdin_T5,
ReinforcedDrakkar_T3,
ReinforcedDrakkar_T4,
ReinforcedDrakkar_T5,
SlaveMarket_T1,
SlaveMarket_T2,
SlaveMarket_T3,
Shrine_T1,
Shrine_T2,
Shrine_T3,
SacrificeRitual_T1,
SacrificeRitual_T2,
SacrificeRitual_T3,

//  -> SAMURAI BUILDINGS <-
Settlement_Village_Samurai_T1,
Settlement_Village_Samurai_T2,
Settlement_Village_Samurai_T3,
Settlement_Castle_Samurai_T1,
Settlement_Castle_Samurai_T2,
Settlement_Castle_Samurai_T3,
Settlement_Castle_Samurai_T4,
Settlement_Castle_Samurai_T5,
Settlement_Capital_Samurai_T1,
Settlement_Capital_Samurai_T2,
Settlement_Capital_Samurai_T3,
Settlement_Capital_Samurai_T4,
Settlement_Capital_Samurai_T5,
SwordSchool_T1,
SwordSchool_T2,
SwordSchool_T3,
ArcheryDojo_T1,
ArcheryDojo_T2,
ArcheryDojo_T3,
WarhorseStable_T1,
WarhorseStable_T2,
WarhorseStable_T3,
SiegeEngineerWorkshop_T4,
SiegeEngineerWorkshop_T5,
GunSmith_T4,
GunSmith_T5,
FortifiedCastle_T3,
FortifiedCastle_T4,
FortifiedCastle_T5,
Market_T1,
Market_T2,
Market_T3,
Hospital_T1,
Hospital_T2,
Hospital_T3,
Chapel_T1,
Chapel_T2,
Chapel_T3,

//UNIQUE Buildings
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

enum class BuildingCategory {
    Military,
    AdvancedMilitary,
    Defence,
    Economy,
    Religion
};

inline BuildingCategory GetBuildingCategory(BuildingType buildingType){
    switch (buildingType){
    case BuildingType::Barracks_T1:
    case BuildingType::Barracks_T2:
    case BuildingType::Barracks_T3:
    case BuildingType::ArcheryRange_T1:
    case BuildingType::ArcheryRange_T2:
    case BuildingType::ArcheryRange_T3:
    case BuildingType::Stable_T1:
    case BuildingType::Stable_T2:
    case BuildingType::Stable_T3:
    case BuildingType::WarLodge_T1:
    case BuildingType::WarLodge_T2:
    case BuildingType::WarLodge_T3:
    case BuildingType::ShootingGround_T1:
    case BuildingType::ShootingGround_T2:
    case BuildingType::ShootingGround_T3:
    case BuildingType::HorseTraining_T1:
    case BuildingType::HorseTraining_T2:
    case BuildingType::HorseTraining_T3:
    case BuildingType::SwordSchool_T1:
    case BuildingType::SwordSchool_T2:
    case BuildingType::SwordSchool_T3:
    case BuildingType::ArcheryDojo_T1:
    case BuildingType::ArcheryDojo_T2:
    case BuildingType::ArcheryDojo_T3:
    case BuildingType::WarhorseStable_T1:
    case BuildingType::WarhorseStable_T2:
    case BuildingType::WarhorseStable_T3:
        return BuildingCategory::Military;

    case BuildingType::Artillery_T4:
    case BuildingType::Artillery_T5:
    case BuildingType::ChosensOfOdin_T3:
    case BuildingType::ChosensOfOdin_T4:
    case BuildingType::ChosensOfOdin_T5:
    case BuildingType::SiegeEngineerWorkshop_T4:
    case BuildingType::SiegeEngineerWorkshop_T5:
    case BuildingType::GunSmith_T4:
    case BuildingType::GunSmith_T5:
        return BuildingCategory::AdvancedMilitary;

    case BuildingType::ReinforceWalls_T3:
    case BuildingType::ReinforceWalls_T4:
    case BuildingType::ReinforceWalls_T5:
    case BuildingType::ReinforcedDrakkar_T3:
    case BuildingType::ReinforcedDrakkar_T4:
    case BuildingType::ReinforcedDrakkar_T5:
    case BuildingType::FortifiedCastle_T3:
    case BuildingType::FortifiedCastle_T4:
    case BuildingType::FortifiedCastle_T5:
        return BuildingCategory::Defence;

    case BuildingType::Economy_T1:
    case BuildingType::Economy_T2:
    case BuildingType::Economy_T3:
    case BuildingType::Growth_T1:
    case BuildingType::Growth_T2:
    case BuildingType::Growth_T3:
    case BuildingType::SlaveMarket_T1:
    case BuildingType::SlaveMarket_T2:
    case BuildingType::SlaveMarket_T3:
    case BuildingType::Market_T1:
    case BuildingType::Market_T2:
    case BuildingType::Market_T3:
        return BuildingCategory::Economy;

    case BuildingType::Church_T1:
    case BuildingType::Church_T2:
    case BuildingType::Church_T3:
    case BuildingType::Shrine_T1:
    case BuildingType::Shrine_T2:
    case BuildingType::Shrine_T3:
    case BuildingType::SacrificeRitual_T1:
    case BuildingType::SacrificeRitual_T2:
    case BuildingType::SacrificeRitual_T3:
    case BuildingType::Hospital_T1:
    case BuildingType::Hospital_T2:
    case BuildingType::Hospital_T3:
    case BuildingType::Chapel_T1:
    case BuildingType::Chapel_T2:
    case BuildingType::Chapel_T3:
        return BuildingCategory::Religion;

    default:
        return BuildingCategory::Economy;
    }
}

struct BuildingData {
    std::string name;
    std::string descrpiton;
    int cost;
    int upkeep;
    int incomeBonus;
    int publicOrderBonus;
    int Tier;
    int constructionTurns;
    BuildingType upgradesTo;

};

inline const std::unordered_map<BuildingType, BuildingData>& GetBuildingDatabase() {
    static std::unordered_map<BuildingType, BuildingData> db;
    if (!db.empty()) return db;

    // Helper lambda to insert cleanly
    auto add = [&](BuildingType key, BuildingData data) { db[key] = data; };

    // ── KNIGHT SETTLEMENTS ──
    //Village
    add(BuildingType::Settlement_Village_Knight_T1, {"Hamlet",        "VillageTier1", 0, 0, 25,  0, 1, 1, BuildingType::None});
    add(BuildingType::Settlement_Village_Knight_T2, {"Village",       "VillageTier2", 0, 0, 50,  0, 2, 1, BuildingType::None});
    add(BuildingType::Settlement_Village_Knight_T3, {"Large Village", "VillageTier3", 0, 0, 100, 0, 3, 1, BuildingType::None});
    add(BuildingType::Settlement_Castle_Knight_T1,  {"Small Fort",    "", 0, 0, 100, 0, 1, 1, BuildingType::None});
    add(BuildingType::Settlement_Castle_Knight_T2,  {"Fort",          "", 0, 0, 175, 0, 2, 1, BuildingType::None});
    add(BuildingType::Settlement_Castle_Knight_T3,  {"Castle",        "", 0, 0, 275, 0, 3, 1, BuildingType::None});
    add(BuildingType::Settlement_Castle_Knight_T4,  {"Large Castle",  "", 0, 0, 400, 0, 4, 1, BuildingType::None});
    add(BuildingType::Settlement_Castle_Knight_T5,  {"Citadel",       "", 0, 0, 550, 0, 5, 1, BuildingType::None});
    add(BuildingType::Settlement_Capital_Knight_T1, {"Small Town",    "", 0, 0, 200,  0, 1, 1, BuildingType::None});
    add(BuildingType::Settlement_Capital_Knight_T2, {"Town",          "", 0, 0, 350,  0, 2, 1, BuildingType::None});
    add(BuildingType::Settlement_Capital_Knight_T3, {"City",          "", 0, 0, 550,  0, 3, 1, BuildingType::None});
    add(BuildingType::Settlement_Capital_Knight_T4, {"Large City",    "", 0, 0, 800,  0, 4, 1, BuildingType::None});
    add(BuildingType::Settlement_Capital_Knight_T5, {"Royal Capital", "", 0, 0, 1100, 0, 5, 1, BuildingType::None});

    // ── VIKING SETTLEMENTS ──
    add(BuildingType::Settlement_Village_Viking_T1, {"Small Settlement", "", 0, 0, 25,  0, 1, 1, BuildingType::None});
    add(BuildingType::Settlement_Village_Viking_T2, {"Settlement",       "", 0, 0, 50,  0, 2, 1, BuildingType::None});
    add(BuildingType::Settlement_Village_Viking_T3, {"Large Settlement", "", 0, 0, 100, 0, 3, 1, BuildingType::None});
    add(BuildingType::Settlement_Castle_Viking_T1,  {"Small Longfort",   "", 0, 0, 100, 0, 1, 1, BuildingType::None});
    add(BuildingType::Settlement_Castle_Viking_T2,  {"Longfort",         "", 0, 0, 175, 0, 2, 1, BuildingType::None});
    add(BuildingType::Settlement_Castle_Viking_T3,  {"Great Longfort",   "", 0, 0, 275, 0, 3, 1, BuildingType::None});
    add(BuildingType::Settlement_Castle_Viking_T4,  {"Viking Fortress",  "", 0, 0, 400, 0, 4, 1, BuildingType::None});
    add(BuildingType::Settlement_Castle_Viking_T5,  {"Jarl's Keep",      "", 0, 0, 550, 0, 5, 1, BuildingType::None});
    add(BuildingType::Settlement_Capital_Viking_T1, {"Small Longhouse",  "", 0, 0, 200,  0, 1, 1, BuildingType::None});
    add(BuildingType::Settlement_Capital_Viking_T2, {"Longhouse",        "", 0, 0, 350,  0, 2, 1, BuildingType::None});
    add(BuildingType::Settlement_Capital_Viking_T3, {"Great Longhouse",  "", 0, 0, 550,  0, 3, 1, BuildingType::None});
    add(BuildingType::Settlement_Capital_Viking_T4, {"Viking City",      "", 0, 0, 800,  0, 4, 1, BuildingType::None});
    add(BuildingType::Settlement_Capital_Viking_T5, {"Jarl's Capital",   "", 0, 0, 1100, 0, 5, 1, BuildingType::None});

    // ── SAMURAI SETTLEMENTS ──
    add(BuildingType::Settlement_Village_Samurai_T1, {"Small Village", "", 0, 0, 25,  0, 1, 1, BuildingType::None});
    add(BuildingType::Settlement_Village_Samurai_T2, {"Village",       "", 0, 0, 50,  0, 2, 1, BuildingType::None});
    add(BuildingType::Settlement_Village_Samurai_T3, {"Large Village", "", 0, 0, 100, 0, 3, 1, BuildingType::None});
    add(BuildingType::Settlement_Castle_Samurai_T1,  {"Small Yashiro", "", 0, 0, 100, 0, 1, 1, BuildingType::None});
    add(BuildingType::Settlement_Castle_Samurai_T2,  {"Yashiro",       "", 0, 0, 175, 0, 2, 1, BuildingType::None});
    add(BuildingType::Settlement_Castle_Samurai_T3,  {"Castle",        "", 0, 0, 275, 0, 3, 1, BuildingType::None});
    add(BuildingType::Settlement_Castle_Samurai_T4,  {"Large Castle",  "", 0, 0, 400, 0, 4, 1, BuildingType::None});
    add(BuildingType::Settlement_Castle_Samurai_T5,  {"Fortress",      "", 0, 0, 550, 0, 5, 1, BuildingType::None});
    add(BuildingType::Settlement_Capital_Samurai_T1, {"Small Town",       "", 0, 0, 200,  0, 1, 1, BuildingType::None});
    add(BuildingType::Settlement_Capital_Samurai_T2, {"Town",             "", 0, 0, 350,  0, 2, 1, BuildingType::None});
    add(BuildingType::Settlement_Capital_Samurai_T3, {"City",             "", 0, 0, 550,  0, 3, 1, BuildingType::None});
    add(BuildingType::Settlement_Capital_Samurai_T4, {"Large City",       "", 0, 0, 800,  0, 4, 1, BuildingType::None});
    add(BuildingType::Settlement_Capital_Samurai_T5, {"Shogun's Capital", "", 0, 0, 1100, 0, 5, 1, BuildingType::None});

    // ── KNIGHT ECONOMY ──
    add(BuildingType::Economy_T1, {"Peasant Fields",    "Basic farmland.",         100,  0,  25,  0, 1, 2, BuildingType::Economy_T2});
    add(BuildingType::Economy_T2, {"Manor Fields",      "Established farmland.",   250,  5,  60,  0, 2, 3, BuildingType::Economy_T3});
    add(BuildingType::Economy_T3, {"Prosperous Estate", "Rich agricultural land.", 500, 10, 120,  0, 3, 4, BuildingType::None});
    add(BuildingType::Growth_T1,  {"Village Market",    "Grows population.",        80,  0,  10,  2, 1, 2, BuildingType::Growth_T2});
    add(BuildingType::Growth_T2,  {"Town Market",       "Grows population faster.", 200, 5,  20,  4, 2, 3, BuildingType::Growth_T3});
    add(BuildingType::Growth_T3,  {"Grand Market",      "Major growth bonus.",      400, 10, 40,  6, 3, 4, BuildingType::None});

    // ── KNIGHT MILITARY ──
    add(BuildingType::Barracks_T1,     {"Militia Grounds",  "Trains basic infantry.",   150, 10, 0, 0, 1, 2, BuildingType::Barracks_T2});
    add(BuildingType::Barracks_T2,     {"Training Grounds", "Trains medium infantry.",  300, 20, 0, 0, 2, 3, BuildingType::Barracks_T3});
    add(BuildingType::Barracks_T3,     {"War Academy",      "Trains elite infantry.",   600, 35, 0, 0, 3, 4, BuildingType::None});
    add(BuildingType::ArcheryRange_T1, {"Archery Range",    "Trains archers.",          150, 10, 0, 0, 1, 2, BuildingType::ArcheryRange_T2});
    add(BuildingType::ArcheryRange_T2, {"Fletchers Guild",  "Trains longbowmen.",       300, 20, 0, 0, 2, 3, BuildingType::ArcheryRange_T3});
    add(BuildingType::ArcheryRange_T3, {"Royal Archery",    "Trains elite archers.",    600, 35, 0, 0, 3, 4, BuildingType::None});
    add(BuildingType::Stable_T1,       {"Stable",           "Trains light cavalry.",    150, 10, 0, 0, 1, 2, BuildingType::Stable_T2});
    add(BuildingType::Stable_T2,       {"Knight Stable",    "Trains heavy cavalry.",    300, 20, 0, 0, 2, 3, BuildingType::Stable_T3});
    add(BuildingType::Stable_T3,       {"Royal Stable",     "Trains elite cavalry.",    600, 35, 0, 0, 3, 4, BuildingType::None});

    // ── KNIGHT ADVANCED MILITARY ──
    add(BuildingType::Artillery_T4, {"Siege Workshop",  "Builds catapults.",   800,  40, 0, 0, 4, 5, BuildingType::Artillery_T5});
    add(BuildingType::Artillery_T5, {"Royal Artillery", "Builds trebuchets.", 1200,  60, 0, 0, 5, 6, BuildingType::None});

    // ── KNIGHT DEFENCE ──
    add(BuildingType::ReinforceWalls_T3, {"Stone Walls",     "Reinforces defences.",    600, 20, 0,  5, 3, 4, BuildingType::ReinforceWalls_T4});
    add(BuildingType::ReinforceWalls_T4, {"Fortified Walls", "Strong stone walls.",     900, 30, 0,  8, 4, 5, BuildingType::ReinforceWalls_T5});
    add(BuildingType::ReinforceWalls_T5, {"Castle Walls",    "Impregnable defences.",  1400, 45, 0, 12, 5, 6, BuildingType::None});

    // ── KNIGHT RELIGION ──
    add(BuildingType::Church_T1, {"Chapel",    "Improves public order.",  100,  5, 0,  5, 1, 2, BuildingType::Church_T2});
    add(BuildingType::Church_T2, {"Church",    "Strong public order.",    250, 10, 0, 10, 2, 3, BuildingType::Church_T3});
    add(BuildingType::Church_T3, {"Cathedral", "Major public order.",     500, 15, 0, 20, 3, 4, BuildingType::None});

    // ── VIKING MILITARY ──
    add(BuildingType::WarLodge_T1,       {"War Lodge",       "Trains raiders.",         150, 10, 0, 0, 1, 2, BuildingType::WarLodge_T2});
    add(BuildingType::WarLodge_T2,       {"Warrior Hall",    "Trains berserkers.",      300, 20, 0, 0, 2, 3, BuildingType::WarLodge_T3});
    add(BuildingType::WarLodge_T3,       {"Jarl's War Hall", "Trains elite warriors.",  600, 35, 0, 0, 3, 4, BuildingType::None});
    add(BuildingType::ShootingGround_T1, {"Shooting Ground", "Trains skirmishers.",     150, 10, 0, 0, 1, 2, BuildingType::ShootingGround_T2});
    add(BuildingType::ShootingGround_T2, {"Hunting Lodge",   "Trains hunters.",         300, 20, 0, 0, 2, 3, BuildingType::ShootingGround_T3});
    add(BuildingType::ShootingGround_T3, {"Elite Marksmen",  "Trains elite archers.",   600, 35, 0, 0, 3, 4, BuildingType::None});
    add(BuildingType::HorseTraining_T1,  {"Horse Training",  "Trains light cavalry.",   150, 10, 0, 0, 1, 2, BuildingType::HorseTraining_T2});
    add(BuildingType::HorseTraining_T2,  {"Cavalry Grounds", "Trains heavy cavalry.",   300, 20, 0, 0, 2, 3, BuildingType::HorseTraining_T3});
    add(BuildingType::HorseTraining_T3,  {"Elite Horsemen",  "Trains elite cavalry.",   600, 35, 0, 0, 3, 4, BuildingType::None});

    // ── VIKING ADVANCED MILITARY ──
    add(BuildingType::ChosensOfOdin_T3, {"Chosen of Odin",  "Elite berserker unit.",   800,  40, 0, 0, 3, 4, BuildingType::ChosensOfOdin_T4});
    add(BuildingType::ChosensOfOdin_T4, {"Odin's Warriors", "Legendary berserkers.",  1200,  60, 0, 0, 4, 5, BuildingType::ChosensOfOdin_T5});
    add(BuildingType::ChosensOfOdin_T5, {"Einherjar",       "Mythical warriors.",     1800,  80, 0, 0, 5, 6, BuildingType::None});

    // ── VIKING DEFENCE ──
    add(BuildingType::ReinforcedDrakkar_T3, {"Drakkar Docks",     "Reinforced ships.",    600, 20, 0,  5, 3, 4, BuildingType::ReinforcedDrakkar_T4});
    add(BuildingType::ReinforcedDrakkar_T4, {"War Drakkar",       "Heavy warships.",      900, 30, 0,  8, 4, 5, BuildingType::ReinforcedDrakkar_T5});
    add(BuildingType::ReinforcedDrakkar_T5, {"Legendary Drakkar", "Unstoppable fleet.",  1400, 45, 0, 12, 5, 6, BuildingType::None});

    // ── VIKING ECONOMY ──
    add(BuildingType::SlaveMarket_T1, {"Slave Market",       "Income from raids.",    100,  0,  30, -2, 1, 2, BuildingType::SlaveMarket_T2});
    add(BuildingType::SlaveMarket_T2, {"Slave Port",         "More raid income.",     250,  5,  65, -3, 2, 3, BuildingType::SlaveMarket_T3});
    add(BuildingType::SlaveMarket_T3, {"Grand Slave Market", "Major raid income.",    500, 10, 130, -5, 3, 4, BuildingType::None});

    // ── VIKING RELIGION ──
    add(BuildingType::Shrine_T1,          {"Shrine",          "Pleases the gods.",        100,  5, 0,  5, 1, 2, BuildingType::Shrine_T2});
    add(BuildingType::Shrine_T2,          {"Temple",          "Greater divine favor.",    250, 10, 0, 10, 2, 3, BuildingType::Shrine_T3});
    add(BuildingType::Shrine_T3,          {"Great Temple",    "Odin smiles upon you.",    500, 15, 0, 20, 3, 4, BuildingType::None});
    add(BuildingType::SacrificeRitual_T1, {"Ritual Ground",   "Blood for Odin.",          150,  5, 0,  8, 1, 2, BuildingType::SacrificeRitual_T2});
    add(BuildingType::SacrificeRitual_T2, {"Sacrifice Altar", "Greater blood offering.",  300, 10, 0, 15, 2, 3, BuildingType::SacrificeRitual_T3});
    add(BuildingType::SacrificeRitual_T3, {"Grand Sacrifice", "Odin's full blessing.",    600, 15, 0, 25, 3, 4, BuildingType::None});

    // ── SAMURAI MILITARY ──
    add(BuildingType::SwordSchool_T1,    {"Sword School",    "Trains katana units.",     150, 10, 0, 0, 1, 2, BuildingType::SwordSchool_T2});
    add(BuildingType::SwordSchool_T2,    {"Kenjutsu Dojo",   "Trains elite swordsmen.",  300, 20, 0, 0, 2, 3, BuildingType::SwordSchool_T3});
    add(BuildingType::SwordSchool_T3,    {"Bushido Academy", "Trains master swordsmen.", 600, 35, 0, 0, 3, 4, BuildingType::None});
    add(BuildingType::ArcheryDojo_T1,    {"Archery Dojo",    "Trains bowmen.",           150, 10, 0, 0, 1, 2, BuildingType::ArcheryDojo_T2});
    add(BuildingType::ArcheryDojo_T2,    {"Kyudo School",    "Trains expert archers.",   300, 20, 0, 0, 2, 3, BuildingType::ArcheryDojo_T3});
    add(BuildingType::ArcheryDojo_T3,    {"Master Kyudo",    "Trains elite archers.",    600, 35, 0, 0, 3, 4, BuildingType::None});
    add(BuildingType::WarhorseStable_T1, {"Warhorse Stable", "Trains light cavalry.",    150, 10, 0, 0, 1, 2, BuildingType::WarhorseStable_T2});
    add(BuildingType::WarhorseStable_T2, {"Samurai Stable",  "Trains heavy cavalry.",    300, 20, 0, 0, 2, 3, BuildingType::WarhorseStable_T3});
    add(BuildingType::WarhorseStable_T3, {"Elite Warhorse",  "Trains elite cavalry.",    600, 35, 0, 0, 3, 4, BuildingType::None});

    // ── SAMURAI ADVANCED MILITARY ──
    add(BuildingType::SiegeEngineerWorkshop_T4, {"Siege Workshop", "Builds siege engines.",  800,  40, 0, 0, 4, 5, BuildingType::SiegeEngineerWorkshop_T5});
    add(BuildingType::SiegeEngineerWorkshop_T5, {"Master Siege",   "Elite siege engines.",  1200,  60, 0, 0, 5, 6, BuildingType::None});
    add(BuildingType::GunSmith_T4,              {"Gunsmith",        "Builds firearms.",       800,  40, 0, 0, 4, 5, BuildingType::GunSmith_T5});
    add(BuildingType::GunSmith_T5,              {"Master Gunsmith", "Elite firearms.",        1200, 60, 0, 0, 5, 6, BuildingType::None});

    // ── SAMURAI DEFENCE ──
    add(BuildingType::FortifiedCastle_T3, {"Stone Castle",     "Reinforced castle.",    600, 20, 0,  5, 3, 4, BuildingType::FortifiedCastle_T4});
    add(BuildingType::FortifiedCastle_T4, {"Fortified Castle", "Strong defences.",      900, 30, 0,  8, 4, 5, BuildingType::FortifiedCastle_T5});
    add(BuildingType::FortifiedCastle_T5, {"Impregnable Keep", "Unbreachable walls.",  1400, 45, 0, 12, 5, 6, BuildingType::None});

    // ── SAMURAI ECONOMY ──
    add(BuildingType::Market_T1, {"Village Market", "Basic trade.",        100,  0,  25, 0, 1, 2, BuildingType::Market_T2});
    add(BuildingType::Market_T2, {"Town Market",    "Established trade.",  250,  5,  60, 0, 2, 3, BuildingType::Market_T3});
    add(BuildingType::Market_T3, {"Grand Market",   "Rich trade routes.",  500, 10, 120, 0, 3, 4, BuildingType::None});

    // ── SAMURAI RELIGION ──
    add(BuildingType::Hospital_T1, {"Field Hospital", "Heals troops.",       100,  5, 0,  5, 1, 2, BuildingType::Hospital_T2});
    add(BuildingType::Hospital_T2, {"Hospital",       "Better healing.",     250, 10, 0, 10, 2, 3, BuildingType::Hospital_T3});
    add(BuildingType::Hospital_T3, {"Grand Hospital", "Full medical care.",  500, 15, 0, 15, 3, 4, BuildingType::None});
    add(BuildingType::Chapel_T1,   {"Shinto Shrine",  "Basic worship.",      100,  5, 0,  5, 1, 2, BuildingType::Chapel_T2});
    add(BuildingType::Chapel_T2,   {"Shinto Temple",  "Greater worship.",    250, 10, 0, 10, 2, 3, BuildingType::Chapel_T3});
    add(BuildingType::Chapel_T3,   {"Grand Shrine",   "Divine blessing.",    500, 15, 0, 20, 3, 4, BuildingType::None});

    return db;
}

inline const BuildingData* GetBuildingData(BuildingType type) {
    const auto& buildingDataBase = GetBuildingDatabase();
    auto it = buildingDataBase.find(type);
    return (it != buildingDataBase.end()) ? &it->second : nullptr;
}

inline std::vector<BuildingType> GetBuildingsForCategory(BuildingCategory categoryType, FactionZone faction, int settlementTier) {
    int maxTier = settlementTier;

    std::vector<BuildingType> results;

    switch (categoryType) {
        case BuildingCategory::Military:
            if (faction == FactionZone::Knight)
                results = {BuildingType::Barracks_T1, BuildingType::ArcheryRange_T1, BuildingType::Stable_T1};
            else if (faction == FactionZone::Viking)
                results = {BuildingType::WarLodge_T1, BuildingType::ShootingGround_T1, BuildingType::HorseTraining_T1};
            else if (faction == FactionZone::Samurai)
                results = {BuildingType::SwordSchool_T1, BuildingType::ArcheryDojo_T1, BuildingType::WarhorseStable_T1};
            break;

        case BuildingCategory::AdvancedMilitary:
            if (faction == FactionZone::Knight)
                results = {BuildingType::Artillery_T4};
            else if (faction == FactionZone::Viking)
                results = {BuildingType::ChosensOfOdin_T3};
            else if (faction == FactionZone::Samurai)
                results = {BuildingType::SiegeEngineerWorkshop_T4, BuildingType::GunSmith_T4};
            break;

        case BuildingCategory::Defence:
            if (faction == FactionZone::Knight)
                results = {BuildingType::ReinforceWalls_T3};
            else if (faction == FactionZone::Viking)
                results = {BuildingType::ReinforcedDrakkar_T3};
            else if (faction == FactionZone::Samurai)
                results = {BuildingType::FortifiedCastle_T3};
            break;

        case BuildingCategory::Economy:
            if (faction == FactionZone::Knight)
                results = {BuildingType::Economy_T1, BuildingType::Growth_T1};
            else if (faction == FactionZone::Viking)
                results = {BuildingType::SlaveMarket_T1, BuildingType::Growth_T1};
            else if (faction == FactionZone::Samurai)
                results = {BuildingType::Market_T1, BuildingType::Growth_T1};
            break;

        case BuildingCategory::Religion:
            if (faction == FactionZone::Knight)
                results = {BuildingType::Church_T1};
            else if (faction == FactionZone::Viking)
                results = {BuildingType::Shrine_T1, BuildingType::SacrificeRitual_T1};
            else if (faction == FactionZone::Samurai)
                results = {BuildingType::Hospital_T1, BuildingType::Chapel_T1};
            break;
    }

    std::vector<BuildingType> filtered;
    for (BuildingType bt : results) {
        const BuildingData* data = GetBuildingData(bt);
        if (data && data->Tier <= maxTier)
            filtered.push_back(bt);
    }
    return filtered;
}

#endif //TOTALWAR2D_BUILDINGS_H