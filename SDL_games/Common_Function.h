
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <Windows.h>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#undef main 

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 588;
const int SCREEN_BPP = 32;
const int SPEED_MAIN_OBJECT = 20;

const int NUM_THREATS = 13;//so luong threat
const int UNDER_LIMIT_THREAT = 200;
const int SPEED_BULLET_THREATS = 10;

static SDL_Surface* g_screen = NULL;
static SDL_Surface* g_background = NULL;
static SDL_Event g_even;
static SDL_Surface* g_img_menu = NULL;
static SDL_Surface* instruction = NULL;


static Mix_Chunk* g_sound_bullet[2];          // khai báo âm thanh của súng
static Mix_Chunk* g_sound_exp[2];
namespace SDLCommonFunc
{
	SDL_Surface* LoadImage(std::string file_path);
	SDL_Rect ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
	void ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y);
	void CleanUp();
	bool CheckCollision(const SDL_Rect& object, const SDL_Rect& object2);
	int ShowMenu(SDL_Surface* des, TTF_Font* font);
	int ShowInstruc(SDL_Surface* des, int x, int y);
	bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect);//hàm ktr tọa độ nằm trong vùng nào đó
}

#endif
