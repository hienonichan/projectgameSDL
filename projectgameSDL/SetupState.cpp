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
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), textTexture, NULL, &textRect);
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->draw();
	}
}


bool SetupState::loadState() {
	TTF_Font* font = TTF_OpenFont("C:/projectgameSDL/projectgameSDL/phong chu2.ttf", 45);
	textSurface = TTF_RenderText_Blended(font, "Choose place to start mission", colorText);
	textTexture = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface);
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);

	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/anh map.jpg", "map1", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/anh map2.jpg", "map2", GameControl::getInstance()->getRenderer());

	GameObject* button1 = new GameButton("map1",300, 300, 249, 249, 1, map1ToPlay);
	GameObject* button2 = new GameButton("map2", 800, 300, 249, 249, 1, map2ToPlay);
	gameObjects.push_back(button1);
	gameObjects.push_back(button2);

	std::cout << "loading SetupState\n";
	return true;
}


bool SetupState::exitState() {

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