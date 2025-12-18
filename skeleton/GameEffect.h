#pragma once
#include <string>

class GameEffect {
public:
	virtual ~GameEffect() {};
	virtual void onEnter() {};
	virtual void onExit() {};
	virtual void update(float t) {};
	virtual std::string getName() { return ""; };

};