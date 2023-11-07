#include "Game.h"
#include "Windows.h"

enum AnimState
{
	Idle,
	WalkForward,
	WalkBackward,
	WalkLeft,
	WalkRight,
	AttackForward,
	AttackBackward,
	AttackLeft,
	AttackRight
};

AnimState animState = WalkForward;

bool attackLeft = true;

SDL_Texture* playerSprite;
int spriteWidth = 32;
int spriteHeight = 32;
int currentFrame = 0;
int maxFrames = 4;


int frameCount = 0;
SDL_Rect* srcRect = new SDL_Rect();
SDL_Rect* destRect = new SDL_Rect();

int playerPositionX = 0;
int playerPositionY = 0;



Game::Game() {

}

Game::~Game() {


}

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullScreen) {

	int flags = 0;

	if (fullScreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialised!..." << std::endl;

		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);

		if (window) {
			std::cout << "Window Created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, flags);

		if (renderer) {
			SDL_SetRenderDrawColor(renderer,255, 255, 255, 255);
			std::cout << "Renderer Created!" << std::endl;
		}

		isRunning = true;
	}else{
		isRunning = false;
	}


	SDL_Surface* tempSurface = IMG_Load("assets/knight.png");
	playerSprite = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
}

bool Game::running() {
	return isRunning;
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;

		default:
			break;
	}
}

void Game::update() {
	frameCount++;
	if (frameCount > 1000) {
		//std::cout << "next frame"<<std::endl;
		frameCount = 0;
		currentFrame++;


		if (GetKeyState('A') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			std::cout << "Move Left" << std::endl;
			if (animState != WalkLeft) {
				currentFrame = 0;
			}
			animState = WalkLeft;
			

		}else if (GetKeyState('D') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			std::cout << "Move Right" << std::endl;
			if (animState != WalkRight) {
				currentFrame = 0;
			}
			animState = WalkRight;
		}else if (GetKeyState('K') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			std::cout << "Attack Right" << std::endl;
			if (animState != AttackRight) {
				currentFrame = 0;
			}
			animState = AttackRight;

			
		}
		else {
			std::cout << "Idle" << std::endl;
			if (animState != Idle) {
				currentFrame = 0;
			}
			animState = Idle;
		}



		switch (animState) {
		case WalkForward:
			playerPositionY += 2;
			break;
		case WalkBackward:
			playerPositionY -= 2;
			break;
		case WalkLeft:
			playerPositionX -= 2;
			break;
		case WalkRight:
			playerPositionX += 2;
			break;
		}
		
		

		if (currentFrame > maxFrames) {
			currentFrame = 0;
			/*
			if (animState == WalkForward) {
				if (attackLeft) {
					attackLeft = false;
					animState = AttackLeft;
				}
				else {
					attackLeft = true;
					animState = AttackRight;
				}
				
			}
			else {
				animState = WalkForward;
			}*/
			
		}
	}
}




void Game::render() {
	SDL_RenderClear(renderer);

	

	//walking forwards will be 0 
	//walking backwards 1
	//left is 2
	//right is 3

	//4 attack forward
	//5 attack backward
	//6 attack left
	//7 attack right
	//


	switch (animState)
	{
	case Idle:
		srcRect->y = 0*spriteHeight;
		currentFrame = 0;
		break;
	case WalkForward:
		srcRect->y = 0*spriteHeight;
		break;
	case WalkBackward:
		srcRect->y = 1*spriteHeight;
		break;
	case WalkLeft:
		srcRect->y = 2 * spriteHeight;
		break;
	case WalkRight:
		srcRect->y = 3 * spriteHeight;
		break;
	case AttackForward:
		srcRect->y = 4 * spriteHeight;
		break;
	case AttackBackward:
		srcRect->y = 5 * spriteHeight;
		break;
	case AttackLeft:
		srcRect->y = 6 * spriteHeight;
		break; 
	case AttackRight:
		srcRect->y = 7 * spriteHeight;
		break;
	}
	
	
	srcRect->x = 0 + currentFrame * spriteWidth;

	

	srcRect->w = 32;
	srcRect->h = 32;
	
	destRect->x = (800 / 2) + playerPositionX;
	destRect->y = (600 / 2) + playerPositionY;
	destRect->w = 32;
	destRect->h = 32;

	SDL_RenderCopy(renderer, playerSprite, srcRect,destRect);

	SDL_RenderPresent(renderer);
}
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}