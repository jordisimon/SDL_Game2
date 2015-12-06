#pragma once
#include "Module.h"
#include "Point.h"

struct SDL_Texture;
struct SDL_Rect;


class ModuleScene :	public Module
{
public:
	ModuleScene(bool active = true);
	~ModuleScene();

	bool Start();
	bool CleanUp();

protected:
	const char* spriteSheetName;
	SDL_Texture* graphics = nullptr;

	const char* musicName;

	void LoadSpriteSheetName(const char* sectionName);
	void LoadMusicName(const char* sectionName);
	void LoadSDLRect(SDL_Rect* rect, const char* sectionName, const char* keyName);
	void LoadPoint(iPoint* point, const char* sectionName, const char* keyName);
};

