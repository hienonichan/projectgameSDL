#include"GameOver.h"
#include"GameControl.h"
#include"GameButton.h"
#include"ObjectTextureManager.h"
#include"PlayState.h";
#include"HomeState.h"

int hightscore = 0;

void GameOver::update() {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->update();
	}
}


void GameOver::render() {
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), texture_background, NULL, NULL);
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), texture_home, NULL, &rect_home);
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->draw();
	}
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), textTexture, NULL, &textRect);
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), textTexture2, NULL, &textRect2);
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), textTexture3, NULL, &textRect3);
}


bool GameOver::loadState() {
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source_picture/restart.png", "restart", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source_picture/menu.png", "menu", GameControl::getInstance()->getRenderer());

	GameObject* button1 = new GameButton("restart", 480, 230, 287, 120,1, restart);
	GameObject* button2 = new GameButton("menu", 480, 350, 287, 122,1, returnMenu);
	gameObjects.push_back(button1);
	gameObjects.push_back(button2);

	// hien chu mission failed
	TTF_Font* font = TTF_OpenFont("C:/projectgameSDL/projectgameSDL/source_ttf/PixeloidSans-Bold.ttf", 30);
	textSurface = TTF_RenderText_Blended(font, "MISSION FAILED", colorText);
	textTexture = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface);
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
     

	// cap nhat score tu playState
	std::vector<State*>loi = GameControl::getInstance()->getStateManager()->getVectorState();
	State* play = loi[loi.size() - 2];
	score = play->getScore();
	if (score > hightscore) { hightscore = score; }
	TTF_Font*font2 = TTF_OpenFont("C:/projectgameSDL/projectgameSDL/source_ttf/LibreBaskerville-Bold.ttf", 20);
	textSurface2 = TTF_RenderText_Blended(font2, ("Your score:" + std::to_string(score)).c_str(), colorText2);
	textTexture2 = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface2);
	SDL_QueryTexture(textTexture2, NULL, NULL, &textRect2.w, &textRect2.h);
   
	textSurface3 = TTF_RenderText_Blended(font2, ("Your highscore:" + std::to_string(hightscore)).c_str(), colorText3);
	textTexture3 = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface3);
	SDL_QueryTexture(textTexture3, NULL, NULL, &textRect3.w, &textRect3.h);


	std::string background = "C:/projectgameSDL/projectgameSDL/source_picture/background1.jpg";
	surface_background = IMG_Load(background.c_str());
	texture_background = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), surface_background);
	surface_home = IMG_Load("C:/projectgameSDL/projectgameSDL/source_picture/homepic.png");
	texture_home = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), surface_home);
	return true;
}


bool GameOver::exitState() {
	SDL_FreeSurface(textSurface);
	SDL_FreeSurface(textSurface2);
	SDL_FreeSurface(surface_background);
	SDL_FreeSurface(surface_home);
	SDL_FreeSurface(textSurface3);

	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(textTexture2);
	SDL_DestroyTexture(texture_background);
	SDL_DestroyTexture(texture_home);
	SDL_DestroyTexture(textTexture3);

	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->clean();
	}
	gameObjects.clear();


	return true;
}

void GameOver::restart() {
	Mix_HaltChannel(-1);
   std::vector<State*> loi=	GameControl::getInstance()->getStateManager()->getVectorState();
   loi[loi.size() - 2]->exitState();
   loi.erase(loi.begin() + loi.size() - 2);
	GameControl::getInstance()->getStateManager()->addState(new PlayState());
}



void GameOver::returnMenu() {
	std::vector<State*> loi = GameControl::getInstance()->getStateManager()->getVectorState();
	loi[loi.size() - 2]->exitState();
	GameControl::getInstance()->getStateManager()->addState(new HomeState());
}