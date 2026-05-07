//
// Created by Louis-Philippe on 4/14/2026.
//

#include "Player.h"
#include "State.h"
#include "SDL3/SDL.h"

Player::Player(SDL_Texture *texture) {
    //constructeur
    AddComponent(HEALTH);
    AddComponent(MOVEMENT);
    AddComponent(RENDER);
    AddComponent(TRANSFORM);

    //Le type d'entity
    entityType = EntityType::Player;

    //Texture Player
    texturePlayer = texture;

}
//destructeur
Player::~Player() {


}
// Returns 0=Capital, 1=Castle, 2=Village, -1=unknown
static int GetSettlementCategory(BuildingType type) {
    switch (type) {
        // ── Capitals ──
        case BuildingType::Settlement_Capital_Knight_T1:
        case BuildingType::Settlement_Capital_Knight_T2:
        case BuildingType::Settlement_Capital_Knight_T3:
        case BuildingType::Settlement_Capital_Knight_T4:
        case BuildingType::Settlement_Capital_Knight_T5:
        case BuildingType::Settlement_Capital_Viking_T1:
        case BuildingType::Settlement_Capital_Viking_T2:
        case BuildingType::Settlement_Capital_Viking_T3:
        case BuildingType::Settlement_Capital_Viking_T4:
        case BuildingType::Settlement_Capital_Viking_T5:
        case BuildingType::Settlement_Capital_Samurai_T1:
        case BuildingType::Settlement_Capital_Samurai_T2:
        case BuildingType::Settlement_Capital_Samurai_T3:
        case BuildingType::Settlement_Capital_Samurai_T4:
        case BuildingType::Settlement_Capital_Samurai_T5:
            return 0;

        // ── Castles ──
        case BuildingType::Settlement_Castle_Knight_T1:
        case BuildingType::Settlement_Castle_Knight_T2:
        case BuildingType::Settlement_Castle_Knight_T3:
        case BuildingType::Settlement_Castle_Knight_T4:
        case BuildingType::Settlement_Castle_Knight_T5:
        case BuildingType::Settlement_Castle_Viking_T1:
        case BuildingType::Settlement_Castle_Viking_T2:
        case BuildingType::Settlement_Castle_Viking_T3:
        case BuildingType::Settlement_Castle_Viking_T4:
        case BuildingType::Settlement_Castle_Viking_T5:
        case BuildingType::Settlement_Castle_Samurai_T1:
        case BuildingType::Settlement_Castle_Samurai_T2:
        case BuildingType::Settlement_Castle_Samurai_T3:
        case BuildingType::Settlement_Castle_Samurai_T4:
        case BuildingType::Settlement_Castle_Samurai_T5:
            return 1;

        // ── Villages ──
        case BuildingType::Settlement_Village_Knight_T1:
        case BuildingType::Settlement_Village_Knight_T2:
        case BuildingType::Settlement_Village_Knight_T3:
        case BuildingType::Settlement_Village_Viking_T1:
        case BuildingType::Settlement_Village_Viking_T2:
        case BuildingType::Settlement_Village_Viking_T3:
        case BuildingType::Settlement_Village_Samurai_T1:
        case BuildingType::Settlement_Village_Samurai_T2:
        case BuildingType::Settlement_Village_Samurai_T3:
            return 2;

        default:
            return -1;
    }
}

int Player::GetUpgradeCost(int fromBuildingTier, BuildingType type) {
    //hard coded

    // int category = GetSettlementCategory(type);
    //
    // // Capital
    // if (category == 0) {
    //     switch (fromBuildingTier) {
    //         case 1: return 1500;
    //         case 2: return 3000;
    //         case 3: return 6000;
    //         case 4: return 10000;
    //         default: return 123456;
    //     }
    // }
    // // Castle
    // if (category == 1) {
    //     switch (fromBuildingTier) {
    //         case 1: return 1000;
    //         case 2: return 2500;
    //         case 3: return 4000;
    //         case 4: return 6000;
    //         default: return 123456;
    //     }
    // }
    // // Village
    // if (category == 2) {
    //     switch (fromBuildingTier) {
    //         case 1: return 500;
    //         case 2: return 1500;
    //         default: return 123456;
    //     }
    // }
    //
    // return 123456;
//read the database to get the current cost + is next update
    const BuildingData* currentData = GetBuildingData(type);
    if (!currentData || currentData->upgradesTo == BuildingType::None)
        return 123456; // tier max ou type inconnu

    const BuildingData* nextData = GetBuildingData(currentData->upgradesTo);
    if (!nextData) return 123456;

    return nextData->cost;

}

void Player::AddGold(int amount) {
    currentGold += amount;
}

bool Player::SpendGold(int amount) {
    if (currentGold >= amount) {
        currentGold -= amount;
        return true;
    }
    return false;
}