#include "ModuleScene.h"
#include <cstdlib>

#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include "SDL/include/SDL_Rect.h"

ModuleScene::ModuleScene(bool active): Module(active)
{
}


ModuleScene::~ModuleScene()
{
}


bool ModuleScene::Start()
{
	LOG("Starting scene");

	graphics = App->textures->Load(spriteSheetName);

	App->player->Enable();
	App->audio->PlayMusic(musicName);

	return true;
}

bool ModuleScene::CleanUp()
{
	LOG("Unloading scene");

	App->textures->Unload(graphics);
	App->player->Disable();

	return true;
}

void ModuleScene::LoadSpriteSheetName(const char * sectionName)
{
	spriteSheetName = App->ini.GetValue(sectionName, "spriteSheetName", "");
}

void ModuleScene::LoadMusicName(const char * sectionName)
{
	musicName = App->ini.GetValue(sectionName, "music", "");
}

void ModuleScene::LoadSDLRect(SDL_Rect * rect, const char * sectionName, const char * keyName)
{
	char* keyComplete = new char[100];

	strcpy(keyComplete, keyName); strcat(keyComplete, "X");
	(*rect).x = atoi(App->ini.GetValue(sectionName, keyComplete, "0"));

	strcpy(keyComplete, keyName); strcat(keyComplete, "Y");
	(*rect).y = atoi(App->ini.GetValue(sectionName, keyComplete, "0"));

	strcpy(keyComplete, keyName); strcat(keyComplete, "W"); 
	(*rect).w = atoi(App->ini.GetValue(sectionName, keyComplete, "0"));

	strcpy(keyComplete, keyName); strcat(keyComplete, "H"); 
	(*rect).h = atoi(App->ini.GetValue(sectionName, keyComplete, "0"));

	RELEASE_ARRAY(keyComplete);
}

void ModuleScene::LoadPoint(iPoint * point, const char * sectionName, const char * keyName)
{
	char* keyComplete = new char[100];

	strcpy(keyComplete, keyName); strcat(keyComplete, "PosX");
	(*point).x = atoi(App->ini.GetValue(sectionName, keyComplete, "0"));

	strcpy(keyComplete, keyName); strcat(keyComplete, "PosY");
	(*point).y = atoi(App->ini.GetValue(sectionName, keyComplete, "0"));


	RELEASE_ARRAY(keyComplete);
}
