//
// Created by Louis-Philippe on 4/14/2026.
//

#include "Entity.h"
#include <random>

//Entity Conetient les components


void Entity::AddComponent(const Uint64 comps) {
    flag |= comps;
}

bool Entity::HasComponent(const Uint64 comps) const {
    return (flag & comps) == comps;
}

void Entity::RemoveComponent(const Uint64 comps) {
    flag &= ~comps;
}

void Entity::MovementUpdate(float deltaTime) {
    // Si l'entité a une position ET un mouvement, on bouge
    if (HasComponent(TRANSFORM | MOVEMENT)) {
        transform.position.x += movement.velocity.x * deltaTime;
        transform.position.y += movement.velocity.y * deltaTime;
    }
}
void Entity::HeightMovement(float deltaTime) {


}

void Entity::RenderUpdate(SDL_Renderer* renderer) {
    // Si l'entité a une position ET doit être rendue
    if (HasComponent(TRANSFORM | RENDER)) {
        SDL_FRect dst = {
            transform.position.x,
            transform.position.y,
            transform.size.x,
            transform.size.y
        };

        SDL_SetRenderDrawColor(renderer, render.color.r, render.color.g, render.color.b, render.color.a);
        SDL_RenderFillRect(renderer, &dst);
    }
}
