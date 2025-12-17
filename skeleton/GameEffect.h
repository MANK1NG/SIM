#pragma once
class GameEffect {
public:
	virtual ~GameEffect() {};
	virtual void onEnter() {};
	virtual void onExit() {};
	virtual void update(float t) {};
};