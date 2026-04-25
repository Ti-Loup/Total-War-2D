//
// Created by Louis-Philippe on 4/14/2026.
//
#include <vector>
#include <string>
#ifndef TOTALWAR2D_STATE_H
#define TOTALWAR2D_STATE_H

// different scenes
enum State {
Menu,
ChooseCharacter,
Game,
Tutorial,
Options,
Credits,
Quit,
};

//different type of Settlements
enum class SettlementType {
    Village, // 4 slots (village1 + 3 upgrades)
    Castle, // 6 slots (casstle 1  + 5 upgrades)
    Capital, // 8 slots for capital (capital 1 + 7 upgrades)
};

#endif //TOTALWAR2D_STATE_H
