#ifndef __MODULESCENEKEN_H__
#define __MODULESCENEKEN_H__

#include "ModuleScene.h"
#include "Animation.h"
#include "Point.h"

struct SDL_Texture;

class ModuleSceneKen : public ModuleScene
{

private:
	const float yShipOffsetDelta = 0.05f;
	float yShipOffset;
	bool yShipDirectionDown;

public:
	ModuleSceneKen( bool start_enabled = true);
	~ModuleSceneKen();

	bool Init();
	update_status Update();

public:
	SDL_Rect ground;
	iPoint groundPos;

	SDL_Rect background;
	iPoint backgroundPos;

	SDL_Rect ship;
	iPoint shipPos;

	Animation flag;
	iPoint flagPos;

	Animation shipGirl;
	iPoint shipGirlPos;
};

#endif // __MODULESCENEKEN_H__