//
// Created by Louis-Philippe on 4/22/2026.
//

#include "Settlements.h"

Settlement::Settlement(SettlementType type, int provinceID, int col, int row) {
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
            break;
        case SettlementType::Castle:
            settlementData.baseIncome     = 100;
            settlementData.basePopulation = 1000;
            settlementData.cityName = "Castle";
            settlementData.buildings.resize(6, BuildingType::None);
            break;
        case SettlementType::Capital:
            settlementData.baseIncome     = 200;
            settlementData.basePopulation = 2500;
            settlementData.cityName = "Capital";
            settlementData.buildings.resize(8, BuildingType::None);
            break;
    }
}