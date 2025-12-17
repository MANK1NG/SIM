#include "GameEffectManager.h"

GameEffectManager::GameEffectManager(float tiempoCambio)
	:intervaloCambio(tiempoCambio), gen(std::random_device{}())
{
}

GameEffectManager::~GameEffectManager()
{
	if (efectoActual) {
		efectoActual->onExit();
	}
	for (auto e : effects) {
		delete e;
	}
}

void GameEffectManager::addEffect(GameEffect* efect)
{
	effects.push_back(efect);
}

void GameEffectManager::start()
{
	tiempo = 0.0f;
	efectoAleatorio();
}
void GameEffectManager::update(float t) {
	if (!efectoActual || effects.empty()) {
		return;
	}
	tiempo += t;
	efectoActual->update(t);
	if (tiempo >= intervaloCambio) {
		efectoAleatorio();
		tiempo = 0.0f;
	}
}

void GameEffectManager::estadoNormal()
{
	if (efectoActual) {
		efectoActual->onExit();

	}
	if (!effects.empty()) {
		efectoActual = effects[0];
		efectoActual->onEnter();
	}
}


void GameEffectManager::efectoAleatorio()
{
	if (effects.empty()) {
		return;
	}
	if (efectoActual) {
		efectoActual->onExit();
	}
	int index = getRandomRange(0, effects.size()-1);
	efectoActual = effects[index];
	efectoActual->onEnter();

}

int GameEffectManager::getRandomRange(int a, int b)
{
	std::uniform_int_distribution<int> dist(a, b);
	return dist(gen);
}
