	#include "Game.h"
using namespace std;
//declear the static member 
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::e;
int Game::Xbullet[20];
int Game::Ybullet[20];

//declear the map pointer 
Map* map = nullptr;
Player* man = nullptr;
enemy* monster[10];
Boss* test = nullptr;
Game::Game()
{

}
Game::~Game()
{

}
void Game::Initialize(const char* title, int x, int y, int width, int height, int screenOption)
{
	srand(time(0));
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "could't Initialize the SDL Library  " << SDL_GetError() << endl;
		gameEnd = true;
		return;
	}
	window = SDL_CreateWindow(title, x, y, width, height, screenOption);
	if (window == NULL)
	{
		cout << "could't create the window " << SDL_GetError() << endl;
		gameEnd = true;
		return;
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL)
	{
		cout << "could't create the renderer " << SDL_GetError() << endl;
		gameEnd = true;
		return;
	}
	
	return;
}
void Game::Draw()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	//Draw the game 
	map->Draw();
	man->Draw();
	for (int i = 0; i < 0; i++)
		if (monster[i] != nullptr)
			monster[i]->Draw();
	if (test != nullptr)
		test->Draw();
	///////////////////
	SDL_RenderPresent(renderer);
}
void Game::Update()
{
	man->Update();
	for (int i = 0; i < 0; i++){
		if (monster[i] != nullptr) {
			monster[i]->Update();
			for (int j = 0; j < 20; j++)
			{
				if (monster[i]->bulletHit(Xbullet[j], Ybullet[j])) {
					monster[i]->heart -= 1;
					Xbullet[j] = 0;
					Ybullet[j] = 0;
				}
			}
			if (monster[i]->heart <= 0)
				monster[i] = nullptr;
			
			
			}
		}
	//boss update
	if (test != nullptr) {
		test->Update();
		for (int j = 0; j < 20; j++)
		{
			if (test->bulletHit(Xbullet[j], Ybullet[j])) {
				test->heart -= 1;
				Xbullet[j] = 0;
				Ybullet[j] = 0;
			}
		}
		if (test->heart <= 0)
			test = nullptr;


	}
}
void Game::Close()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = NULL;
	renderer = NULL;
	SDL_Quit();
}
void Game::handleEvent()
{
	SDL_PollEvent(&e);
	man->handleEvent();
	switch (e.type)
	{
	case SDL_QUIT:
		gameEnd = true;
		break;
	case SDL_KEYUP:
		if (e.key.keysym.sym == SDLK_ESCAPE)
			gameEnd = true;
		break;
	default:
		break;
	}
}

void Game::setCharacter(int characterType)
{
	characterNum = characterType;
}
void Game:: setValue()
{
	for (int i = 0; i < 20; i++)
	{
		Xbullet[i] = 0;
		Ybullet[i] = 0;
	}
	//declear the pointer value 
	map = new Map(1);
	man = new Player(characterNum);
	for (int i = 0; i < 0; i++) {
		monster[i] = new enemy(50 + 200 * i, 50 + 200 * i);
	}
	test = new Boss(900, 250);

}