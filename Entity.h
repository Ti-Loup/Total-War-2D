//
// Created by Louis-Philippe on 4/14/2026.
//
#ifndef TOTALWAR2D_ENTITY_H
#define TOTALWAR2D_ENTITY_H

#include "components.h"
#include <SDL3/SDL_render.h>//Pour Uint64

//enum pour les differents types
enum class EntityType{
Player,
Enemy,
Building,
Particle,
Collectible
};
class Entity {
    // Le flag qui dit quels composants sont actifs
    Uint64 flag = 0u;

public:
    Entity() = default;
    virtual ~Entity() = default;//destruction
    //Pour la fonction update
    virtual void Update(float deltaTime) {}
    // Constructeur des EntityType
    //Collectible
    Entity(EntityType Collectible) : entityType(Collectible) {}
    // Les instances des componants
    //Les fonctions dans Components.h
    HealthComponents health;
    MovementComponents movement;
    RenderComponents render;
    TransformComponents transform;

    // Gestion des composants
    void AddComponent(Uint64 comps);
    bool HasComponent(Uint64 comps) const;
    void RemoveComponent(Uint64 comps);

    // Systèmes intégrés (Update et Render)
    virtual void MovementUpdate(float deltaTime);
    virtual void RenderUpdate(SDL_Renderer* renderer);
    virtual void HeightMovement(float deltaTime);

    //declaration des etiquettes de chacun pour intégrés les enums EntityType dans chaque entity
    EntityType entityType = EntityType::Enemy;

    //Bool pour savoir si un object est detruit ou non
    bool bIsDestroyed = false;
};

//La classe pour les 4 parties de la texture qui pars
class EnemyPart : public Entity{
public:
    SDL_Texture *texturePart = nullptr;
    float rotationAngle = 0.0f;
    float rotationSpeed = 200.0f;//rotation des textures cass/s
    float lifeTimer = 0.0f;
    float lifeDuration = 1.5f;//0.8 est nice et 4.0 aussi
//rect vide
SDL_FRect srcRect{};

    EnemyPart(SDL_FPoint pos, SDL_FRect src, SDL_FPoint velocity, SDL_Texture *texture, SDL_FPoint displaySize) : texturePart(texture), srcRect(src) {
        entityType = EntityType::Particle;
        transform.position = pos;
        transform.size = displaySize; // <- utilise la taille d'affichage
        movement.velocity = velocity;
    }
    void Update(float deltaTime) override {
        // Mouvement && rotation
        transform.position.x += movement.velocity.x * deltaTime;
        transform.position.y += movement.velocity.y * deltaTime;
        rotationAngle += rotationSpeed * deltaTime;
        // cmb de temps avant que les particles ce supp
        lifeTimer += deltaTime;
        if (lifeTimer >= lifeDuration) {
            bIsDestroyed = true;
        }
    }

};
#endif //TOTALWAR2D_ENTITY_H
