#include"UpgradeState.h"
#include"ObjectTextureManager.h"

void UpgradeState::update() {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->update();
	}
}

void UpgradeState::render() {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->draw();
	}
}

bool UpgradeState::loadState() {
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/card1.png", "card1", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/card2.png", "card2", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/card3.png", "card3", GameControl::getInstance()->getRenderer());
	GameObject* button1 = new GameButton("card1", 400, 200, 173, 300, 2, upgrade_health);
	GameObject* button2 = new GameButton("card2", 600, 200, 173, 300, 2, upgrade_attack);
	GameObject* button3 = new GameButton("card3", 800, 200, 173, 300, 2, upgrade_ammo);

	gameObjects.push_back(button1);
	gameObjects.push_back(button2);
	gameObjects.push_back(button3);


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

}

void UpgradeState::upgrade_attack() {

}

void UpgradeState::upgrade_ammo() {

}