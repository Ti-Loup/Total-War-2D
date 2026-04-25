//
// Created by Louis-Philippe on 4/22/2026.
//

#include "Settlements.h"

#include "Province.h"

Settlement::Settlement(SettlementType type, int provinceID, int col, int row, FactionZone faction) {
    tileCol = col;
    tileRow = row;
    settlementData.type = type;
    settlementData.provinceID = provinceID;

    //Base Income and Population per settlement type
    switch(type) {
        case SettlementType::Village:
            settlementData.baseIncome     = 25;
            settlementData.basePopulation = 250;
            settlementData.cityName = "Village";
            settlementData.buildings.resize(4, BuildingType::None);
            if (faction == FactionZone::Knight) {
                settlementData.buildings[0] = BuildingType::Settlement_Village_Knight;
            }
            else if (faction == FactionZone::Viking) {
                settlementData.buildings[0] = BuildingType::Settlement_Village_Viking;
            }
            else if (faction == FactionZone::Samurai) {
                settlementData.buildings[0] = BuildingType::Settlement_Village_Samurai;
            }
            break;
        case SettlementType::Castle:
            settlementData.baseIncome     = 100;
            settlementData.basePopulation = 1000;
            settlementData.cityName = "Castle";
            settlementData.buildings.resize(6, BuildingType::None);
            if (faction == FactionZone::Knight) {
                settlementData.buildings[0] = BuildingType::Settlement_Castle_Knight;
            }
            else if (faction == FactionZone::Viking) {
                settlementData.buildings[0] = BuildingType::Settlement_Castle_Viking;
            }
            else if (faction == FactionZone::Samurai) {
                settlementData.buildings[0] = BuildingType::Settlement_Castle_Samurai;
            }
            break;
        case SettlementType::Capital:
            settlementData.baseIncome     = 200;
            settlementData.basePopulation = 2500;
            settlementData.cityName = "Capital";
            settlementData.buildings.resize(8, BuildingType::None);
            if (faction == FactionZone::Knight) {
                settlementData.buildings[0] = BuildingType::Settlement_Capital_Knight;
            }
            else if (faction == FactionZone::Viking) {
                settlementData.buildings[0] = BuildingType::Settlement_Capital_Viking;
            }
            else if (faction == FactionZone::Samurai) {
                settlementData.buildings[0] = BuildingType::Settlement_Capital_Samurai;
            }
            break;
    }
}
