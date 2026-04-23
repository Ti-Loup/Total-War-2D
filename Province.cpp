
#include "Province.h"
#include "State.h"

int Province::GetTotalIncome(const std::vector<SettlementComponent> &settlements) const {
    int incomeTotal = 0;
    for (const auto &s : settlements) if (s.provinceID == id) incomeTotal += s.baseIncome;
    return incomeTotal;
}

int Province::GetTotalPopulation(const std::vector<SettlementComponent> &settlements) const {
    int populationTotal = 0;
    for (const auto &s : settlements) if (s.provinceID == id)populationTotal += s.basePopulation;
    return populationTotal;
}
