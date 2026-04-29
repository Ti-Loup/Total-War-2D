//
// Created by Louis-Philippe on 4/14/2026.
//

#ifndef TOTALWAR2D_PLAYER_H
#define TOTALWAR2D_PLAYER_H

#include "Entity.h"
#include "State.h"

class Player : public Entity {
public :
    int currentGold = 2500;
    int nextTurnGold
    FactionZone faction = FactionZone::Knight;
    int GetUpgradeCost(int fromBuildingTier);
    void AddGold(int amount);
    bool SpendGold(int amount);//if enought money than buy -> 

    Player (SDL_Texture *texture = nullptr);
    ~Player();

    //texture du Player
       SDL_Texture  *texturePlayer = nullptr;

};



#endif //TOTALWAR2D_PLAYER_H
