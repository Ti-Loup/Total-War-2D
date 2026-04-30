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

int Player::GetUpgradeCost(int fromBuildingTier, BuildingType type) {
    //KNIGHT UPGRADE PRICES
    //capital
    if (type == BuildingType::Settlement_Capital_Knight) {
        switch (fromBuildingTier) {
            case 1: //tier 1 to 2
                return 1500;
            case 2: //tier 2 to 3
                return 3000;
            case 3: //tier 3 to 4
                return 6000;
            case 4: //tier 4 to 5
                return 10000;
            default: return 123456;
        }
    }
    //castle
    else if (type == BuildingType::Settlement_Castle_Knight) {
        switch (fromBuildingTier) {
            case 1:
                return 1000;
            case 2:
                return 2500;
            case 3:
                return 4000;
            case 4:
                return 6000;
            default: return 123456;
        }
    }
    //village
    else if (type == BuildingType::Settlement_Village_Knight) {
        switch (fromBuildingTier) {
            case 1:
                return 500;
            case 2:
                return 1500;
            default: return 123456;
        }
    }
    //VIKING UPGRADE PRICES
    //capital
    if (type == BuildingType::Settlement_Capital_Viking) {
        switch (fromBuildingTier) {
            case 1: //tier 1 to 2
                return 1500;
            case 2: //tier 2 to 3
                return 3000;
            case 3: //tier 3 to 4
                return 6000;
            case 4: //tier 4 to 5
                return 10000;
            default: return 123456;
        }
    }
    //castle
    else if (type == BuildingType::Settlement_Castle_Viking) {
        switch (fromBuildingTier) {
            case 1:
                return 1000;
            case 2:
                return 2500;
            case 3:
                return 4000;
            case 4:
                return 6000;
            default: return 123456;
        }
    }
    //village
    else if (type == BuildingType::Settlement_Village_Viking) {
        switch (fromBuildingTier) {
            case 1:
                return 500;
            case 2:
                return 1500;
            default: return 123456;
        }
    }
    //SAMURAI UPGRADE PRICES
    //capital
    if (type == BuildingType::Settlement_Capital_Samurai) {
        switch (fromBuildingTier) {
            case 1: //tier 1 to 2
                return 1500;
            case 2: //tier 2 to 3
                return 3000;
            case 3: //tier 3 to 4
                return 6000;
            case 4: //tier 4 to 5
                return 10000;
            default: return 123456;
        }
    }
    //castle
    else if (type == BuildingType::Settlement_Castle_Samurai) {
        switch (fromBuildingTier) {
            case 1:
                return 1000;
            case 2:
                return 2500;
            case 3:
                return 4000;
            case 4:
                return 6000;
            default: return 123456;
        }
    }
    //village
    else if (type == BuildingType::Settlement_Village_Samurai) {
        switch (fromBuildingTier) {
            case 1:
                return 500;
            case 2:
                return 1500;
            default: return 123456;
        }
    }
    return 123456;
}

void Player::AddGold(int amount) {
    currentGold += amount;
}
//can buy if enought current Gold
bool Player::SpendGold(int amount) {
    if (currentGold >= amount) {
        currentGold -= amount;
        return true;
    }
    return false;
}
