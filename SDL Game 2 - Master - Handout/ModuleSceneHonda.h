#pragma once
#include "ModuleScene.h"
#include "Animation.h"
#include "Point.h"

struct SDL_Texture;

class ModuleSceneHonda : public ModuleScene
{
public:
	ModuleSceneHonda(bool start_enabled = true);
	~ModuleSceneHonda();

	bool Init();
	update_status Update();

	SDL_Rect ground;
	iPoint groundPos;

	SDL_Rect background;
	iPoint backgroundPos;

	SDL_Rect pool;
	iPoint poolPos;

	SDL_Rect ceiling;
	iPoint ceilingPos;

	SDL_Rect lamp;
	iPoint lamp1Pos;
	iPoint lamp2Pos;

	Animation water;
	iPoint waterPos;
};


