#pragma once
#ifndef TOTALWAR2D_PROVINCE_H
#define TOTALWAR2D_PROVINCE_H

#include <string>
#include <vector>
#include <SDL3/SDL.h>

enum class FactionZone : uint8_t {
    Knight,
    Viking,
    Samurai,
    Ocean
};

//get the SettlementComponent
struct SettlementComponent;

struct Province {
    int id;
    std::string name;
    FactionZone owner;
    bool isCapital = false;

    int GetTotalIncome(const std::vector<SettlementComponent>& settlements) const;
    int GetTotalPopulation(const std::vector<SettlementComponent>& settlements) const;
};


#endif //TOTALWAR2D_PROVINCE_H
