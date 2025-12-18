#pragma once
#include <vector>
#include <random>
#include "GameEffect.h"
class GameEffectManager
{
public:
	GameEffectManager(float tiempoCambio = 20.0f);
	~GameEffectManager();

	void addEffect(GameEffect* efect);
	void start();
	void update(float t);
	void estadoNormal();
	GameEffect* getActiveEffect() const { return efectoActual; }

private:
	std::vector<GameEffect*> effects;
	GameEffect* efectoActual = nullptr;
	float tiempo = 0.0f;
	float intervaloCambio;
	void efectoAleatorio();
	std::mt19937 gen;
	int getRandomRange(int a, int b);

};

