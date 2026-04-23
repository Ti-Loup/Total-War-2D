//
// Created by Louis-Philippe on 4/22/2026.
//

#ifndef TOTALWAR2D_SETTLEMENTS_H
#define TOTALWAR2D_SETTLEMENTS_H
#include "Entity.h"
#include "State.h"
class Settlement : public Entity {
    public:
    SettlementComponent settlementData;
    int tileCol = 0;
    int tileRow = 0;

    Settlement(SettlementType type, int provinceID, int col, int row);
};

#endif //TOTALWAR2D_SETTLEMENTS_H
