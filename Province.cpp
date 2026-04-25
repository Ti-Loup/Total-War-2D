
#include "Province.h"

#include "Components.h"

int Province::GetTotalIncome(const std::vector<SettlementComponent>& settlements) const {
    int total = 0;
    for (const auto& s : settlements)
        if (s.provinceID == id) total += s.GetTotalIncome(); // ← was s.baseIncome
    return total;
}

int Province::GetTotalPopulation(const std::vector<SettlementComponent> &settlements) const {
    int populationTotal = 0;
    for (const auto &s : settlements) if (s.provinceID == id)populationTotal += s.basePopulation;
    return populationTotal;
}
