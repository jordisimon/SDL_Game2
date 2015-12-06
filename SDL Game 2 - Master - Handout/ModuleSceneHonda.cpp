#include "Application.h"
#include "ModuleSceneHonda.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"

#define CONFIG_SECTION "Scene_Honda"

ModuleSceneHonda::ModuleSceneHonda(bool start_enabled) : ModuleScene(start_enabled)
{
}

ModuleSceneHonda::~ModuleSceneHonda()
{
}

bool ModuleSceneHonda::Init()
{
	LoadSpriteSheetName(CONFIG_SECTION);
	LoadMusicName(CONFIG_SECTION);

	// ground
	LoadSDLRect(&ground, CONFIG_SECTION, "ground");
	LoadPoint(&groundPos, CONFIG_SECTION, "ground");

	//background
	LoadSDLRect(&background, CONFIG_SECTION, "background");
	LoadPoint(&backgroundPos, CONFIG_SECTION, "background");

	//ceiling
	LoadSDLRect(&ceiling, CONFIG_SECTION, "ceiling");
	LoadPoint(&ceilingPos, CONFIG_SECTION, "ceiling");

	//pool
	LoadSDLRect(&pool, CONFIG_SECTION, "pool");
	LoadPoint(&poolPos, CONFIG_SECTION, "pool");

	//lamp
	LoadSDLRect(&lamp, CONFIG_SECTION, "lamp");
	LoadPoint(&lamp1Pos, CONFIG_SECTION, "lamp1");
	LoadPoint(&lamp2Pos, CONFIG_SECTION, "lamp2");

	// water animation
	water.LoadAnimationFromConfig(&(App->ini), CONFIG_SECTION, "water");
	LoadPoint(&waterPos, CONFIG_SECTION, "water");

	return true;
}


// Update: draw background
update_status ModuleSceneHonda::Update()
{
	// Draw everything --------------------------------------
	App->renderer->Blit(graphics, groundPos.x, groundPos.y, &ground); // floor
	App->renderer->Blit(graphics, backgroundPos.x, backgroundPos.y, &background, 0.75f); //background
	App->renderer->Blit(graphics, ceilingPos.x, ceilingPos.y, &ceiling, 0.75f); //ceiling
	App->renderer->Blit(graphics, poolPos.x, poolPos.y, &pool); //pool
	App->renderer->Blit(graphics, waterPos.x, waterPos.y, &(water.GetCurrentFrame())); // pool animation
	App->renderer->Blit(graphics, lamp1Pos.x, lamp1Pos.y, &lamp); //lamp1
	App->renderer->Blit(graphics, lamp2Pos.x, lamp2Pos.y, &lamp); //lamp2


	// TODO 11: Make that pressing space triggers a switch to ken logic module
	// using FadeToBlack module
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		App->fade->FadeToBlack(App->scene_ken, this);
		App->fade->Enable();
	}

	return UPDATE_CONTINUE;
}
