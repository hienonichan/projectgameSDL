#ifndef __State__
#define __State__

class State {
public:
	virtual void update() = 0;
	virtual void render() = 0;
	virtual bool loadState() = 0;
	virtual bool exitState() = 0;

	virtual int getStateCode() = 0;

	virtual int getScore() { return score; }
protected:
	int score = 0;
	int health = 5;
	
	 int max_ammo = 3;
	int ammo_count = max_ammo;
};

#endif
