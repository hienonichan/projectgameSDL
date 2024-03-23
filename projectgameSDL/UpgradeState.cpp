#include"UpgradeState.h"
#include"ObjectTextureManager.h"
#include"PlayState.h"

void UpgradeState::update() {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->update();
	}
}

void UpgradeState::render() {
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), background_texture, NULL, NULL);
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), textTexture, NULL, &textRect);
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->draw();
	}

	
}

bool UpgradeState::loadState() {
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/card1.png", "card1", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/card2.png", "card2", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/card3.png", "card3", GameControl::getInstance()->getRenderer());
	GameObject* button1 = new GameButton("card1", 350, 200, 173, 300, 2, upgrade_health);
	GameObject* button2 = new GameButton("card2", 550, 200, 173, 300, 2, upgrade_attack);
	GameObject* button3 = new GameButton("card3", 750, 200, 173, 300, 2, upgrade_ammo);

	gameObjects.push_back(button1);
	gameObjects.push_back(button2);
	gameObjects.push_back(button3);

	std::string background = "C:/projectgameSDL/projectgameSDL/anh ma mi.jpg";
	background_surface = IMG_Load(background.c_str());
	background_texture = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), background_surface);

	TTF_Font* font = TTF_OpenFont("C:/projectgameSDL/projectgameSDL/LibreBaskerville-Bold.ttf", 30);
	textSurface = TTF_RenderText_Blended(font, "YOU GOT NEW LEVEL! CHOOSE YOUR BOOST", colorText);
	textTexture = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface);
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);

	std::cout << "loading UpgradeState\n";
	return true;
}

bool UpgradeState::exitState() {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->clean();
	}
	gameObjects.clear();
	std::cout << "exiting UpgradeState\n";
	return true; 
}



void UpgradeState::upgrade_health() {
	PlayState* check = nullptr;
	std::vector<State*>loi = GameControl::getInstance()->getStateManager()->getVectorState();
	check = dynamic_cast<PlayState*>(loi[loi.size() - 2]);
	check->up_health();
	check->render_health();
	GameControl::getInstance()->getStateManager()->deleteState();
}

void UpgradeState::upgrade_attack() {
	PlayState* check = nullptr;
	std::vector<State*>loi = GameControl::getInstance()->getStateManager()->getVectorState();
	check = dynamic_cast<PlayState*>(loi[loi.size() - 2]);
	check->up_attack();
	GameControl::getInstance()->getStateManager()->deleteState();

}

void UpgradeState::upgrade_ammo() {
	PlayState* check = nullptr;
	std::vector<State*>loi = GameControl::getInstance()->getStateManager()->getVectorState();
	check = dynamic_cast<PlayState*>(loi[loi.size() - 2]);
	check->up_ammo();
	GameControl::getInstance()->getStateManager()->deleteState();
}