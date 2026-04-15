//
// Created by Louis-Philippe on 4/14/2026.
//

#ifndef TOTALWAR2D_COMPONENTS_H
#define TOTALWAR2D_COMPONENTS_H

#include "State.h"
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>



 //Creation du enum des components
 typedef enum
 {
 HEALTH = 1ULL << 0,
 MOVEMENT = 1ULL << 1,
 RENDER = 1ULL << 2,
 TRANSFORM = 1ULL << 3,
 } ComponentType;

//class de base
class Components {
public:
	virtual ~Components () = default;//destructions des components
};
//
class HealthComponents : public Components
{
  public:
	Sint32 current_health = 0;
	Sint32 max_health = 0;

	HealthComponents () = default;
};

class MovementComponents : public Components
{

  public:
	SDL_FPoint velocity = { 0.f, 0.f };


	//Ajout timer pour les cerfs
	float Timer = 0.0f;

	MovementComponents () = default;
};

class RenderComponents : public Components
{
  public:
	SDL_Color color = { 0, 0, 0, 0 };

	RenderComponents () = default;
};

class TransformComponents : public Components
{

  public:
	SDL_FPoint position = { 0.f, 0.f };
	SDL_FPoint size = { 0.f, 0.f };

	TransformComponents () = default;
};


#endif //TOTALWAR2D_COMPONENTS_H
