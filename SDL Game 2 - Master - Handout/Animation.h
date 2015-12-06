#pragma once
#include <cstdlib>
#include <vector>
#include "SimpleIni.h"

using namespace std;

class Animation
{
public:
	float speed;
	vector<SDL_Rect> frames;

private:
	float current_frame;

public:
	Animation() : frames(), speed(1.0f), current_frame(0.0f)
	{}

	void LoadAnimationFromConfig(CSimpleIniA* ini, const char* sectionName, const char* keyName)
	{
		char* keyComplete = new char[50];
		int frameNum = 0;
		char* frameNumChar = new char[3];
		int frameX, frameY, frameW, frameH;
		
		bool result;
		do
		{
			sprintf(frameNumChar, "%d", frameNum);

			strcpy(keyComplete, keyName); strcat(keyComplete, "FrameX"); strcat(keyComplete, frameNumChar);
			frameX = atoi(ini->GetValue(sectionName, keyComplete, "-1"));

			strcpy(keyComplete, keyName); strcat(keyComplete, "FrameY"); strcat(keyComplete, frameNumChar);
			frameY = atoi(ini->GetValue(sectionName, keyComplete, "-1"));

			strcpy(keyComplete, keyName); strcat(keyComplete, "FrameW"); strcat(keyComplete, frameNumChar);
			frameW = atoi(ini->GetValue(sectionName, keyComplete, "-1"));

			strcpy(keyComplete, keyName); strcat(keyComplete, "FrameH"); strcat(keyComplete, frameNumChar);
			frameH = atoi(ini->GetValue(sectionName, keyComplete, "-1"));

			result = (frameX != -1 && frameY != -1 && frameW != -1 && frameH != -1);

			if (result)
				frames.push_back({frameX, frameY, frameW, frameH});

			frameNum++;
		} while (result);


		strcpy(keyComplete, keyName); strcat(keyComplete, "Speed");

		speed = (float)atof(ini->GetValue(sectionName, keyComplete, "1.0f"));

		RELEASE_ARRAY(keyComplete);
		RELEASE_ARRAY(frameNumChar);
	}

	SDL_Rect& GetCurrentFrame()
	{
		current_frame += speed;
		if(current_frame >= frames.size())
			current_frame = 0.0f;
		return frames[(int)current_frame];
	}

	void ResetAnimation() { current_frame = 0.0f; }

	void NextFrame()
	{
		current_frame += 1.0f;
		if (current_frame >= frames.size())
			current_frame = 0.0f;
	}

	void PriorFrame()
	{
		current_frame -= 1.0f;
		if (current_frame < 0.0f)
			current_frame = frames.size() - 1.0f;
	}

	SDL_Rect& GetFrame()
	{
		return frames[(int)current_frame];
	}
};