#include"SetupState.h"
#include"GameButton.h"
#include"ObjectTextureManager.h"
#include"MapObject.h"
#include"PlayState.h"

void SetupState::update() {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->update();
	}
}

void SetupState::render() {
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), texture_background, NULL, NULL);
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), texture_home, NULL, &rect_home);

	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), textTexture, NULL, &textRect);
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), textTexture1, NULL, &textRect1);
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), textTexture2, NULL, &textRect2);
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->draw();
	}
}


bool SetupState::loadState() {
	TTF_Font* font = TTF_OpenFont("C:/projectgameSDL/projectgameSDL/phong chu2.ttf", 40);

	textSurface = TTF_RenderText_Blended(font, "CHOOSE MAP", colorText);
	textTexture = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface);
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);

	TTF_Font* font2 = TTF_OpenFont("C:/projectgameSDL/projectgameSDL/phong chu2.ttf", 30);
	textSurface1 = TTF_RenderText_Blended(font2, "first Map", colorText1);
	textTexture1 = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface1);
	SDL_QueryTexture(textTexture1, NULL, NULL, &textRect1.w, &textRect1.h);

	textSurface2 = TTF_RenderText_Blended(font2, "second Map", colorText2);
	textTexture2 = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface2);
	SDL_QueryTexture(textTexture2, NULL, NULL, &textRect2.w, &textRect2.h);

	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/anh map.jpg", "map1", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/anh map2.jpg", "map2", GameControl::getInstance()->getRenderer());

	GameObject* button1 = new GameButton("map1",400, 300, 160, 160, 1, map1ToPlay);
	GameObject* button2 = new GameButton("map2", 700, 300, 160, 160, 1, map2ToPlay);
	gameObjects.push_back(button1);
	gameObjects.push_back(button2);

	std::string background = "C:/projectgameSDL/projectgameSDL/background1.jpg";
	surface_background = IMG_Load(background.c_str());
	texture_background = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), surface_background);

	surface_home = IMG_Load("C:/projectgameSDL/projectgameSDL/homepic.png");
	texture_home = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), surface_home);

	std::cout << "loading SetupState\n";
	return true;
}


bool SetupState::exitState() {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->clean();
	}
	gameObjects.clear();
	SDL_FreeSurface(textSurface);
	SDL_FreeSurface(textSurface1);
	SDL_FreeSurface(textSurface2);
	SDL_FreeSurface(surface_background);
	SDL_FreeSurface(surface_home);

	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(textTexture1);
	SDL_DestroyTexture(textTexture2);
	SDL_DestroyTexture(texture_background);
	SDL_DestroyTexture(texture_home);

	ObjectTextureManager::getInstance()->eraseTexture("map1");
	ObjectTextureManager::getInstance()->eraseTexture("map2");

	std::cout << "exiting SetupState\n";
	return true;
}


void SetupState::map1ToPlay() {
	Map::getInstance()->changeMap(1);
	GameControl::getInstance()->getStateManager()->addState(new PlayState());
}


void SetupState::map2ToPlay() {
	Map::getInstance()->changeMap(2);
	GameControl::getInstance()->getStateManager()->addState(new PlayState());
}