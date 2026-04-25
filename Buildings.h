//
// Created by Louis-Philippe on 4/24/2026.
//
#pragma once
#ifndef TOTALWAR2D_BUILDINGS_H
#define TOTALWAR2D_BUILDINGS_H
#include <string>
#include <vector>
#include "Province.h"
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
ReinforceWalls_T3,
ReinforceWalls_T4,
ReinforceWalls_T5,
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
//Military (Red)
//melee
WarLodge_T1,
WarLodge_T2,
WarLodge_T3,
//ranged
ShootingGround_T1,
ShootingGround_T2,
ShootingGround_T3,
//Cavalry
HorseTraining_T1,
HorseTraining_T2,
HorseTraining_T3,
//AdvancedMilitary
//Better melee Units 3+
ChosensOfOdin_T3,
ChosensOfOdin_T4,
ChosensOfOdin_T5,
//Defence
ReinforcedDrakkar_T3,
ReinforcedDrakkar_T4,
ReinforcedDrakkar_T5,
//Growth/Economy
SlaveMarket_T1,
SlaveMarket_T2,
SlaveMarket_T3,
//Church
Shrine_T1,
Shrine_T2,
Shrine_T3,
SacrificeRitual_T1,
SacrificeRitual_T2,
SacrificeRitual_T3,
//  -> SAMURAI BUILDINGS <-
Settlement_Village_Samurai,
Settlement_Castle_Samurai,
Settlement_Capital_Samurai,
//Military(Red)
SwordSchool_T1,
SwordSchool_T2,
SwordSchool_T3,
//Archery
ArcheryDojo_T1,
ArcheryDojo_T2,
ArcheryDojo_T3,
//Stable
WarhorseStable_T1,
WarhorseStable_T2,
WarhorseStable_T3,
//AdvancedMilitary(purple)
SiegeEngineerWorkshop_T4,
SiegeEngineerWorkshop_T5,
GunSmith_T4,
GunSmith_T5,
//Defence (Yellow)
FortifiedCastle_T3,
FortifiedCastle_T4,
FortifiedCastle_T5,
//growth/economy
Market_T1,
Market_T2,
Market_T3,

//church
Hospital_T1,
Hospital_T2,
Hospital_T3,
Chapel_T1,
Chapel_T2,
Chapel_T3,

//UNIQUE Building
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

enum class BuildingCategory {
    Military,
    AdvancedMilitary,
    Defence,
    Economy,
    Religion
};
//To Show whats Military, Whats AdvancedMilitary ... etc etc
inline BuildingCategory GetBuildingCategory(BuildingType buildingType){
    switch (buildingType){
    //  ~~ Knight ~~
    case BuildingType::Barracks_T1:
    case BuildingType::Barracks_T2:
    case BuildingType::Barracks_T3:
    case BuildingType::ArcheryRange_T1:
    case BuildingType::ArcheryRange_T2:
    case BuildingType::ArcheryRange_T3:
    case BuildingType::Stable_T1:
    case BuildingType::Stable_T2:
    case BuildingType::Stable_T3:
    //  ~~ Vikings ~~
    case BuildingType::WarLodge_T1:
    case BuildingType::WarLodge_T2:
    case BuildingType::WarLodge_T3:
    case BuildingType::ShootingGround_T1:
    case BuildingType::ShootingGround_T2:
    case BuildingType::ShootingGround_T3:
    case BuildingType::HorseTraining_T1:
    case BuildingType::HorseTraining_T2:
    case BuildingType::HorseTraining_T3:
    //  ~~ Samurai ~~
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

        //  ~~ Knight ~~
        case BuildingType::Artillery_T4:
        case BuildingType::Artillery_T5:
        //  ~~ Vikings ~~
        case BuildingType::ChosensOfOdin_T3:
        case BuildingType::ChosensOfOdin_T4:
        case BuildingType::ChosensOfOdin_T5:
        //  ~~ Samurai ~~
        case BuildingType::SiegeEngineerWorkshop_T4:
        case BuildingType::SiegeEngineerWorkshop_T5:
        case BuildingType::GunSmith_T4:
        case BuildingType::GunSmith_T5:
            return BuildingCategory::AdvancedMilitary;

            //  ~~ Knight ~~
            case BuildingType::ReinforceWalls_T3:
            case BuildingType::ReinforceWalls_T4:
            case BuildingType::ReinforceWalls_T5:
            //  ~~ Vikings ~~
            case BuildingType::ReinforcedDrakkar_T3:
            case BuildingType::ReinforcedDrakkar_T4:
            case BuildingType::ReinforcedDrakkar_T5:
            //  ~~ Samurai ~~
            case BuildingType::FortifiedCastle_T3:
            case BuildingType::FortifiedCastle_T4:
            case BuildingType::FortifiedCastle_T5:
                return BuildingCategory::Defence;

                //  ~~ Knight ~~
                case BuildingType::Economy_T1:
                case BuildingType::Economy_T2:
                case BuildingType::Economy_T3:
                case BuildingType::Growth_T1:
                case BuildingType::Growth_T2:
                case BuildingType::Growth_T3:
                //  ~~ Vikings ~~
                case BuildingType::SlaveMarket_T1:
                case BuildingType::SlaveMarket_T2:
                case BuildingType::SlaveMarket_T3:
                //  ~~ Samurai ~~
                case BuildingType::Market_T1:
                case BuildingType::Market_T2:
                case BuildingType::Market_T3:
                    return BuildingCategory::Economy;

                    //  ~~ Knight ~~
                    case BuildingType::Church_T1:
                    case BuildingType::Church_T2:
                    case BuildingType::Church_T3:
                    //  ~~ Vikings ~~
                    case BuildingType::Shrine_T1:
                    case BuildingType::Shrine_T2:
                    case BuildingType::Shrine_T3:
                    case BuildingType::SacrificeRitual_T1:
                    case BuildingType::SacrificeRitual_T2:
                    case BuildingType::SacrificeRitual_T3:
                    //  ~~ Samurai ~~
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
inline std::vector<BuildingType> GetBuildingsForCategory(BuildingCategory cat, FactionZone faction) {
    switch (cat) {

        case BuildingCategory::Military:
            if (faction == FactionZone::Knight)
                return {BuildingType::Barracks_T1, BuildingType::ArcheryRange_T1, BuildingType::Stable_T1};
            if (faction == FactionZone::Viking)
                return {BuildingType::WarLodge_T1, BuildingType::ShootingGround_T1, BuildingType::HorseTraining_T1};
            if (faction == FactionZone::Samurai)
                return {BuildingType::SwordSchool_T1, BuildingType::ArcheryDojo_T1, BuildingType::WarhorseStable_T1};
            break;

        case BuildingCategory::AdvancedMilitary:
            if (faction == FactionZone::Knight)
                return {BuildingType::Artillery_T4};
            if (faction == FactionZone::Viking)
                return {BuildingType::ChosensOfOdin_T3};
            if (faction == FactionZone::Samurai)
                return {BuildingType::SiegeEngineerWorkshop_T4, BuildingType::GunSmith_T4};
            break;

        case BuildingCategory::Defence:
            if (faction == FactionZone::Knight)
                return {BuildingType::ReinforceWalls_T3};
            if (faction == FactionZone::Viking)
                return {BuildingType::ReinforcedDrakkar_T3};
            if (faction == FactionZone::Samurai)
                return {BuildingType::FortifiedCastle_T3};
            break;

        case BuildingCategory::Economy:
            if (faction == FactionZone::Knight)
                return {BuildingType::Economy_T1, BuildingType::Growth_T1};
            if (faction == FactionZone::Viking)
                return {BuildingType::SlaveMarket_T1, BuildingType::Growth_T1};
            if (faction == FactionZone::Samurai)
                return {BuildingType::Market_T1, BuildingType::Growth_T1};
            break;

        case BuildingCategory::Religion:
            if (faction == FactionZone::Knight)
                return {BuildingType::Church_T1};
            if (faction == FactionZone::Viking)
                return {BuildingType::Shrine_T1, BuildingType::SacrificeRitual_T1};
            if (faction == FactionZone::Samurai)
                return {BuildingType::Hospital_T1, BuildingType::Chapel_T1};
            break;
    }
    return {};
}



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
// ── KNIGHT ECONOMY ──
        {BuildingType::Economy_T1, {"Peasant Fields",    "Basic farmland.",          100,  0,  25,  0, BuildingType::Economy_T2}},
        {BuildingType::Economy_T2, {"Manor Fields",      "Established farmland.",    250,  5,  60,  0, BuildingType::Economy_T3}},
        {BuildingType::Economy_T3, {"Prosperous Estate", "Rich agricultural land.",  500, 10, 120,  0, BuildingType::None}},
        {BuildingType::Growth_T1,  {"Village Market",    "Grows population.",         80,  0,  10,  2, BuildingType::Growth_T2}},
        {BuildingType::Growth_T2,  {"Town Market",       "Grows population faster.", 200,  5,  20,  4, BuildingType::Growth_T3}},
        {BuildingType::Growth_T3,  {"Grand Market",      "Major growth bonus.",      400, 10,  40,  6, BuildingType::None}},

        // ── KNIGHT MILITARY ──
        {BuildingType::Barracks_T1,     {"Militia Grounds",  "Trains basic infantry.",   150, 10,  0, 0, BuildingType::Barracks_T2}},
        {BuildingType::Barracks_T2,     {"Training Grounds", "Trains medium infantry.",  300, 20,  0, 0, BuildingType::Barracks_T3}},
        {BuildingType::Barracks_T3,     {"War Academy",      "Trains elite infantry.",   600, 35,  0, 0, BuildingType::None}},
        {BuildingType::ArcheryRange_T1, {"Archery Range",    "Trains archers.",          150, 10,  0, 0, BuildingType::ArcheryRange_T2}},
        {BuildingType::ArcheryRange_T2, {"Fletchers Guild",  "Trains longbowmen.",       300, 20,  0, 0, BuildingType::ArcheryRange_T3}},
        {BuildingType::ArcheryRange_T3, {"Royal Archery",    "Trains elite archers.",    600, 35,  0, 0, BuildingType::None}},
        {BuildingType::Stable_T1,       {"Stable",           "Trains light cavalry.",    150, 10,  0, 0, BuildingType::Stable_T2}},
        {BuildingType::Stable_T2,       {"Knight Stable",    "Trains heavy cavalry.",    300, 20,  0, 0, BuildingType::Stable_T3}},
        {BuildingType::Stable_T3,       {"Royal Stable",     "Trains elite cavalry.",    600, 35,  0, 0, BuildingType::None}},

        // ── KNIGHT ADVANCED MILITARY ──
        {BuildingType::Artillery_T4, {"Siege Workshop",  "Builds catapults.",  800, 40, 0, 0, BuildingType::Artillery_T5}},
        {BuildingType::Artillery_T5, {"Royal Artillery", "Builds trebuchets.", 1200, 60, 0, 0, BuildingType::None}},

        // ── KNIGHT DEFENCE ──
        {BuildingType::ReinforceWalls_T3, {"Stone Walls",    "Reinforces defences.",     600, 20, 0, 5, BuildingType::ReinforceWalls_T4}},
        {BuildingType::ReinforceWalls_T4, {"Fortified Walls","Strong stone walls.",      900, 30, 0, 8, BuildingType::ReinforceWalls_T5}},
        {BuildingType::ReinforceWalls_T5, {"Castle Walls",   "Impregnable defences.",   1400, 45, 0,12, BuildingType::None}},

        // ── KNIGHT RELIGION ──
        {BuildingType::Church_T1, {"Chapel",    "Improves public order.",  100,  5, 0,  5, BuildingType::Church_T2}},
        {BuildingType::Church_T2, {"Church",    "Strong public order.",    250, 10, 0, 10, BuildingType::Church_T3}},
        {BuildingType::Church_T3, {"Cathedral", "Major public order.",     500, 15, 0, 20, BuildingType::None}},

        // ── VIKING MILITARY ──
        {BuildingType::WarLodge_T1,       {"War Lodge",         "Trains raiders.",         150, 10, 0, 0, BuildingType::WarLodge_T2}},
        {BuildingType::WarLodge_T2,       {"Warrior Hall",      "Trains berserkers.",      300, 20, 0, 0, BuildingType::WarLodge_T3}},
        {BuildingType::WarLodge_T3,       {"Jarl's War Hall",   "Trains elite warriors.",  600, 35, 0, 0, BuildingType::None}},
        {BuildingType::ShootingGround_T1, {"Shooting Ground",   "Trains skirmishers.",     150, 10, 0, 0, BuildingType::ShootingGround_T2}},
        {BuildingType::ShootingGround_T2, {"Hunting Lodge",     "Trains hunters.",         300, 20, 0, 0, BuildingType::ShootingGround_T3}},
        {BuildingType::ShootingGround_T3, {"Elite Marksmen",    "Trains elite archers.",   600, 35, 0, 0, BuildingType::None}},
        {BuildingType::HorseTraining_T1,  {"Horse Training",    "Trains light cavalry.",   150, 10, 0, 0, BuildingType::HorseTraining_T2}},
        {BuildingType::HorseTraining_T2,  {"Cavalry Grounds",   "Trains heavy cavalry.",   300, 20, 0, 0, BuildingType::HorseTraining_T3}},
        {BuildingType::HorseTraining_T3,  {"Elite Horsemen",    "Trains elite cavalry.",   600, 35, 0, 0, BuildingType::None}},

        // ── VIKING ADVANCED MILITARY ──
        {BuildingType::ChosensOfOdin_T3, {"Chosen of Odin",  "Elite berserker unit.",  800, 40, 0, 0, BuildingType::ChosensOfOdin_T4}},
        {BuildingType::ChosensOfOdin_T4, {"Odin's Warriors", "Legendary berserkers.", 1200, 60, 0, 0, BuildingType::ChosensOfOdin_T5}},
        {BuildingType::ChosensOfOdin_T5, {"Einherjar",       "Mythical warriors.",    1800, 80, 0, 0, BuildingType::None}},

        // ── VIKING DEFENCE ──
        {BuildingType::ReinforcedDrakkar_T3, {"Drakkar Docks",    "Reinforced ships.",    600, 20, 0, 5, BuildingType::ReinforcedDrakkar_T4}},
        {BuildingType::ReinforcedDrakkar_T4, {"War Drakkar",      "Heavy warships.",      900, 30, 0, 8, BuildingType::ReinforcedDrakkar_T5}},
        {BuildingType::ReinforcedDrakkar_T5, {"Legendary Drakkar","Unstoppable fleet.",  1400, 45, 0,12, BuildingType::None}},

        // ── VIKING ECONOMY ──
        {BuildingType::SlaveMarket_T1, {"Slave Market",  "Income from raids.",   100,  0, 30, -2, BuildingType::SlaveMarket_T2}},
        {BuildingType::SlaveMarket_T2, {"Slave Port",    "More raid income.",    250,  5, 65, -3, BuildingType::SlaveMarket_T3}},
        {BuildingType::SlaveMarket_T3, {"Grand Slave Market","Major raid income.",500, 10,130, -5, BuildingType::None}},

        // ── VIKING RELIGION ──
        {BuildingType::Shrine_T1,          {"Shrine",          "Pleases the gods.",      100,  5, 0,  5, BuildingType::Shrine_T2}},
        {BuildingType::Shrine_T2,          {"Temple",          "Greater divine favor.",  250, 10, 0, 10, BuildingType::Shrine_T3}},
        {BuildingType::Shrine_T3,          {"Great Temple",    "Odin smiles upon you.",  500, 15, 0, 20, BuildingType::None}},
        {BuildingType::SacrificeRitual_T1, {"Ritual Ground",   "Blood for Odin.",        150,  5, 0,  8, BuildingType::SacrificeRitual_T2}},
        {BuildingType::SacrificeRitual_T2, {"Sacrifice Altar", "Greater blood offering.",300, 10, 0, 15, BuildingType::SacrificeRitual_T3}},
        {BuildingType::SacrificeRitual_T3, {"Grand Sacrifice", "Odin's full blessing.",  600, 15, 0, 25, BuildingType::None}},

        // ── SAMURAI MILITARY ──
        {BuildingType::SwordSchool_T1,   {"Sword School",    "Trains katana units.",    150, 10, 0, 0, BuildingType::SwordSchool_T2}},
        {BuildingType::SwordSchool_T2,   {"Kenjutsu Dojo",   "Trains elite swordsmen.", 300, 20, 0, 0, BuildingType::SwordSchool_T3}},
        {BuildingType::SwordSchool_T3,   {"Bushido Academy", "Trains master swordsmen.",600, 35, 0, 0, BuildingType::None}},
        {BuildingType::ArcheryDojo_T1,   {"Archery Dojo",    "Trains bowmen.",          150, 10, 0, 0, BuildingType::ArcheryDojo_T2}},
        {BuildingType::ArcheryDojo_T2,   {"Kyudo School",    "Trains expert archers.",  300, 20, 0, 0, BuildingType::ArcheryDojo_T3}},
        {BuildingType::ArcheryDojo_T3,   {"Master Kyudo",    "Trains elite archers.",   600, 35, 0, 0, BuildingType::None}},
        {BuildingType::WarhorseStable_T1,{"Warhorse Stable", "Trains light cavalry.",   150, 10, 0, 0, BuildingType::WarhorseStable_T2}},
        {BuildingType::WarhorseStable_T2,{"Samurai Stable",  "Trains heavy cavalry.",   300, 20, 0, 0, BuildingType::WarhorseStable_T3}},
        {BuildingType::WarhorseStable_T3,{"Elite Warhorse",  "Trains elite cavalry.",   600, 35, 0, 0, BuildingType::None}},

        // ── SAMURAI ADVANCED MILITARY ──
        {BuildingType::SiegeEngineerWorkshop_T4, {"Siege Workshop",  "Builds siege engines.", 800, 40, 0, 0, BuildingType::SiegeEngineerWorkshop_T5}},
        {BuildingType::SiegeEngineerWorkshop_T5, {"Master Siege",    "Elite siege engines.",  1200, 60, 0, 0, BuildingType::None}},
        {BuildingType::GunSmith_T4,              {"Gunsmith",         "Builds firearms.",       800, 40, 0, 0, BuildingType::GunSmith_T5}},
        {BuildingType::GunSmith_T5,              {"Master Gunsmith",  "Elite firearms.",        1200, 60, 0, 0, BuildingType::None}},

        // ── SAMURAI DEFENCE ──
        {BuildingType::FortifiedCastle_T3, {"Stone Castle",     "Reinforced castle.",   600, 20, 0,  5, BuildingType::FortifiedCastle_T4}},
        {BuildingType::FortifiedCastle_T4, {"Fortified Castle", "Strong defences.",     900, 30, 0,  8, BuildingType::FortifiedCastle_T5}},
        {BuildingType::FortifiedCastle_T5, {"Impregnable Keep", "Unbreachable walls.", 1400, 45, 0, 12, BuildingType::None}},

        // ── SAMURAI ECONOMY ──
        {BuildingType::Market_T1, {"Village Market", "Basic trade.",        100,  0, 25,  0, BuildingType::Market_T2}},
        {BuildingType::Market_T2, {"Town Market",    "Established trade.",  250,  5, 60,  0, BuildingType::Market_T3}},
        {BuildingType::Market_T3, {"Grand Market",   "Rich trade routes.",  500, 10,120,  0, BuildingType::None}},

        // ── SAMURAI RELIGION ──
        {BuildingType::Hospital_T1, {"Field Hospital", "Heals troops.",        100,  5, 0,  5, BuildingType::Hospital_T2}},
        {BuildingType::Hospital_T2, {"Hospital",       "Better healing.",      250, 10, 0, 10, BuildingType::Hospital_T3}},
        {BuildingType::Hospital_T3, {"Grand Hospital", "Full medical care.",   500, 15, 0, 15, BuildingType::None}},
        {BuildingType::Chapel_T1,   {"Shinto Shrine",  "Basic worship.",       100,  5, 0,  5, BuildingType::Chapel_T2}},
        {BuildingType::Chapel_T2,   {"Shinto Temple",  "Greater worship.",     250, 10, 0, 10, BuildingType::Chapel_T3}},
        {BuildingType::Chapel_T3,   {"Grand Shrine",   "Divine blessing.",     500, 15, 0, 20, BuildingType::None}},
    };
    return db;
}
inline const BuildingData* GetBuildingData(BuildingType type) {
    const auto& db = GetBuildingDatabase();
    auto it = db.find(type);
    return (it != db.end()) ? &it->second : nullptr;
}
#endif //TOTALWAR2D_BUILDINGS_H
