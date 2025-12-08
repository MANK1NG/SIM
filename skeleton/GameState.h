#pragma once
enum GameState {
	STATE_MENU,
	STATE_GAME,
	STATE_WIN,
	STATE_LOSE

};
extern GameState gameState;
extern double tiempoJuego;