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

