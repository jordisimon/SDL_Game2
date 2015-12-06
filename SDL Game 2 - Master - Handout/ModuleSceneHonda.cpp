#include "Globals.h"
#include "Application.h"
#include "ModuleSceneHonda.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"

ModuleSceneHonda::ModuleSceneHonda(bool start_enabled): Module(start_enabled)
{
	// ground
	ground.x = 8;
	ground.y = 376;
	ground.w = 847;
	ground.h = 63;

	//background
	background.x = 120;
	background.y = 128;
	background.w = 670;
	background.h = 198;

	//ceiling
	ceiling.x = 91;
	ceiling.y = 8;
	ceiling.w = 764;
	ceiling.h = 47;

	//pool
	pool.x = 70;
	pool.y = 58;
	pool.w = 335;
	pool.h = 50;

	//lamp
	lamp.x = 813;
	lamp.y = 183;
	lamp.w = 55;
	lamp.h = 104;

	// water animation
	water.frames.push_back({ 0, 0, 0, 0 });
	water.frames.push_back({ 8, 448, 283, 17 });
	water.frames.push_back({ 296, 448, 283, 17 });
	water.frames.push_back({ 588, 448, 283, 17 });
	water.speed = 0.05f;
}


ModuleSceneHonda::~ModuleSceneHonda()
{
}

// Load assets
bool ModuleSceneHonda::Start()
{
	LOG("Loading honda scene");

	graphics = App->textures->Load("honda_stage.png");

	App->player->Enable();
	App->audio->PlayMusic("honda.ogg");

	return true;
}

// UnLoad assets
bool ModuleSceneHonda::CleanUp()
{
	LOG("Unloading honda scene");

	App->textures->Unload(graphics);
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneHonda::Update()
{
	// Draw everything --------------------------------------
	App->renderer->Blit(graphics, -9, 174, &ground); // floor
	App->renderer->Blit(graphics, 47, -1, &background, 0.75f); //background
	App->renderer->Blit(graphics, 0, 0, &ceiling, 0.75f); //ceiling
	App->renderer->Blit(graphics, 285, 143, &pool); //pool
	App->renderer->Blit(graphics, 310, 155, &(water.GetCurrentFrame())); // pool animation
	App->renderer->Blit(graphics, 155, 10, &lamp); //lamp1
	App->renderer->Blit(graphics, 675, 10, &lamp); //lamp2


	// TODO 11: Make that pressing space triggers a switch to ken logic module
	// using FadeToBlack module
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		App->fade->FadeToBlack(App->scene_ken, this);
		App->fade->Enable();
	}

	return UPDATE_CONTINUE;
}
