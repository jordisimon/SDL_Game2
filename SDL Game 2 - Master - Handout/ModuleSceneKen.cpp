#include "Globals.h"
#include "Application.h"
#include "ModuleSceneKen.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"

#define CONFIG_SECTION "Scene_Ken"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneKen::ModuleSceneKen(bool start_enabled) : ModuleScene(start_enabled)
{
}

ModuleSceneKen::~ModuleSceneKen()
{}

// Load assets
bool ModuleSceneKen::Init()
{
	LoadSpriteSheetName(CONFIG_SECTION);
	LoadMusicName(CONFIG_SECTION);

	// ground
	LoadSDLRect(&ground, CONFIG_SECTION, "ground");
	LoadPoint(&groundPos, CONFIG_SECTION, "ground");

	// Background / sky
	LoadSDLRect(&background, CONFIG_SECTION, "background");
	LoadPoint(&backgroundPos, CONFIG_SECTION, "background");

	// TODO 2 : setup the foreground (red ship) with
	// coordinates x,y,w,h from ken_stage.png
	LoadSDLRect(&ship, CONFIG_SECTION, "ship");
	LoadPoint(&shipPos, CONFIG_SECTION, "ship");

	yShipOffset = 0.0f;
	yShipDirectionDown = true;

	// flag animation
	flag.LoadAnimationFromConfig(&(App->ini), CONFIG_SECTION, "flag");
	LoadPoint(&flagPos, CONFIG_SECTION, "flag");

	// TODO 4: Setup Girl Animation from coordinates from ken_stage.png
	shipGirl.LoadAnimationFromConfig(&(App->ini), CONFIG_SECTION, "shipGirl");
	LoadPoint(&shipGirlPos, CONFIG_SECTION, "shipGirl");

	return true;
}


// Update: draw background
update_status ModuleSceneKen::Update()
{
	// TODO 5: make sure the ship goes up and down
	if (yShipDirectionDown)
	{
		yShipOffset += yShipOffsetDelta;
		if (yShipOffset >= 5.0f)
		{
			yShipDirectionDown = false;
			yShipOffset = 5.0f;
		}
	} 
	else
	{
		yShipOffset -= yShipOffsetDelta;
		if (yShipOffset <= 0.0f)
		{
			yShipDirectionDown = true;
			yShipOffset = 0.0f;
		}
	}

	// Draw everything --------------------------------------
	// TODO 1: Tweak the movement speed of the sea&sky + flag to your taste
	App->renderer->Blit(graphics, backgroundPos.x, backgroundPos.y, &background, 0.75f); // sea and sky
	App->renderer->Blit(graphics, flagPos.x, flagPos.y, &(flag.GetCurrentFrame()), 0.75f); // flag animation

	// TODO 3: Draw the ship. Be sure to tweak the speed.
	
	App->renderer->Blit(graphics, shipPos.x, shipPos.y + (int)yShipOffset, &ship, 0.87f); // sea and sky

	// TODO 6: Draw the girl. Make sure it follows the ship movement!
	App->renderer->Blit(graphics, shipGirlPos.x, shipGirlPos.y + (int)yShipOffset, &(shipGirl.GetCurrentFrame()), 0.87f); // flag animation

	App->renderer->Blit(graphics, groundPos.x, groundPos.y, &ground);

	// TODO 10: Build an entire new scene "honda", you can find its
	// and music in the Game/ folder

	// TODO 11: Make that pressing space triggers a switch to honda logic module
	// using FadeToBlack module
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		App->fade->FadeToBlack(App->scene_honda, this);
		App->fade->Enable();
	}
		

	return UPDATE_CONTINUE;
}