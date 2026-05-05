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
            settlementData.baseIncome     = 0;
            settlementData.basePopulation = 250;
            settlementData.cityName = "Village";
            settlementData.buildings.resize(4, BuildingType::None);
            if (faction == FactionZone::Knight) {
                if (type == SettlementType::Village)  settlementData.buildings[0] = BuildingType::Settlement_Village_Knight_T1;
            }
            else if (faction == FactionZone::Viking) {
                if (type == SettlementType::Village)  settlementData.buildings[0] = BuildingType::Settlement_Village_Viking_T1;
            }
            else if (faction == FactionZone::Samurai) {
                if (type == SettlementType::Village)  settlementData.buildings[0] = BuildingType::Settlement_Village_Samurai_T1;
            }
            break;
        case SettlementType::Castle:
            settlementData.baseIncome     = 0;
            settlementData.basePopulation = 1000;
            settlementData.cityName = "Castle";
            settlementData.buildings.resize(6, BuildingType::None);
            if (faction == FactionZone::Knight) {
                if (type == SettlementType::Castle)   settlementData.buildings[0] = BuildingType::Settlement_Castle_Knight_T1;
            }
            else if (faction == FactionZone::Viking) {
                if (type == SettlementType::Castle)   settlementData.buildings[0] = BuildingType::Settlement_Castle_Viking_T1;
            }
            else if (faction == FactionZone::Samurai) {
                if (type == SettlementType::Castle)   settlementData.buildings[0] = BuildingType::Settlement_Castle_Samurai_T1;
            }
            break;
        case SettlementType::Capital:
            settlementData.baseIncome     = 0;
            settlementData.basePopulation = 2500;
            settlementData.cityName = "Capital";
            settlementData.buildings.resize(8, BuildingType::None);
            if (faction == FactionZone::Knight) {
                if (type == SettlementType::Capital)  settlementData.buildings[0] = BuildingType::Settlement_Capital_Knight_T1;
            }
            else if (faction == FactionZone::Viking) {
                if (type == SettlementType::Capital)  settlementData.buildings[0] = BuildingType::Settlement_Capital_Viking_T1;
            }
            else if (faction == FactionZone::Samurai) {
                if (type == SettlementType::Capital)  settlementData.buildings[0] = BuildingType::Settlement_Capital_Samurai_T1;
            }
            break;
    }
}
