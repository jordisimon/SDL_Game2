#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA
ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	position.x = 100;
	position.y = 216;

	// idle animation (arcade sprite sheet)
	idle.frames.push_back({7, 10, 60, 93});
	idle.frames.push_back({95, 10, 60, 93});
	idle.frames.push_back({184, 10, 60, 93});
	idle.frames.push_back({276, 10, 60, 93});
	idle.frames.push_back({366, 10, 60, 93});
	idle.speed = 0.2f;
	
	// walk backward animation (arcade sprite sheet)
	backward.frames.push_back({542, 131, 61, 87});
	backward.frames.push_back({628, 129, 59, 90});
	backward.frames.push_back({713, 128, 57, 90});
	backward.frames.push_back({797, 127, 57, 90});
	backward.frames.push_back({883, 128, 58, 91});
	backward.frames.push_back({974, 129, 57, 89});
	backward.speed = 0.1f;

	// TODO 8: setup the walk forward animation from ryu4.png
	forward.frames.push_back({ 0, 127, 68, 93 });
	forward.frames.push_back({ 78, 127, 68, 93 });
	forward.frames.push_back({ 161, 127, 68, 93 });
	forward.frames.push_back({ 251, 127, 73, 93 });
	forward.frames.push_back({ 341, 127, 68, 93 });
	forward.frames.push_back({ 419, 127, 68, 93 });
	forward.speed = 0.1f;

	currentAnimation = &forward;
}

ModulePlayer::~ModulePlayer()
{
	// Homework : check for memory leaks
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("ryu4.png"); // arcade version

	playerX = 80;

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update
update_status ModulePlayer::Update()
{
	// TODO 9: Draw the player with its animation
	// make sure to detect player movement and change its
	// position while cycling the animation(check Animation.h)
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
			backward.ResetAnimation();

		playerX -= (int)playerMovement;
		App->renderer->Blit(graphics, playerX, 104, &(backward.GetCurrentFrame()), 0.87f);
	}
	else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
	{
		idle.ResetAnimation();
		App->renderer->Blit(graphics, playerX, 104, &(idle.GetCurrentFrame()), 0.87f);
	}
	else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
			forward.ResetAnimation();

		playerX += (int)playerMovement;
		App->renderer->Blit(graphics, playerX, 104, &(forward.GetCurrentFrame()), 0.87f);
	}
	else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
	{
		idle.ResetAnimation();
		App->renderer->Blit(graphics, playerX, 104, &(idle.GetCurrentFrame()), 0.87f);
	}
	else
	{
		App->renderer->Blit(graphics, playerX, 104, &(idle.GetCurrentFrame()), 0.87f);
	}

	/*if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
	{
		currentAnimation = &forward;
	}

	if (App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN)
	{
		currentAnimation = &idle;
	}

	if (App->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN)
	{
		currentAnimation = &backward;
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN )
	{
		currentAnimation->PriorFrame();
	}
	else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
	{
		currentAnimation->NextFrame();
	}

	App->renderer->Blit(graphics, playerX, 104, &(currentAnimation->GetFrame()), 0.87f);*/

	return UPDATE_CONTINUE;
}