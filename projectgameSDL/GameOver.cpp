#include"GameOver.h"
#include"GameControl.h"
#include"GameButton.h"
#include"ObjectTextureManager.h"
#include"PlayState.h";
#include"HomeState.h"
void GameOver::update() {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->update();
	}
}


void GameOver::render() {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->draw();
	}

	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), textTexture, NULL, &textRect);
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), textTexture2, NULL, &textRect2);
}


bool GameOver::loadState() {
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/restart.png", "restart", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/menu.png", "menu", GameControl::getInstance()->getRenderer());

	GameObject* button1 = new GameButton("restart", 550, 200, 142, 60,1, restart);
	GameObject* button2 = new GameButton("menu", 560, 260, 135, 57,1, returnMenu);
	gameObjects.push_back(button1);
	gameObjects.push_back(button2);

	// hien chu mission failed
	TTF_Font* font = TTF_OpenFont("C:/projectgameSDL/projectgameSDL/GloriousChristmas-BLWWB.ttf", 45);
	textSurface = TTF_RenderText_Blended(font, "MISSION FAILED", colorText);
	textTexture = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface);
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
     
	// cap nhat score tu playState
	std::vector<State*>loi = GameControl::getInstance()->getStateManager()->getVectorState();
	State* play = loi[loi.size() - 2];
	max_score = play->getScore();
	TTF_Font*font2 = TTF_OpenFont("C:/projectgameSDL/projectgameSDL/LibreBaskerville-Bold.ttf", 30);
	textSurface2 = TTF_RenderText_Blended(font2, ("YOUR SCORE:" + std::to_string(max_score)).c_str(), colorText2);
	textTexture2 = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface2);
	SDL_QueryTexture(textTexture2, NULL, NULL, &textRect2.w, &textRect2.h);
   

	return true;
}

bool GameOver::exitState() {

	return true;
}

void GameOver::restart() {
	Mix_HaltChannel(-1);

	GameControl::getInstance()->getStateManager()->addState(new PlayState());

}

void GameOver::returnMenu() {
	GameControl::getInstance()->getStateManager()->addState(new HomeState());
}