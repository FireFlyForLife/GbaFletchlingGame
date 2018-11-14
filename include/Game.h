#pragma once
#include <forward_list>

///The game concept
template<typename T>
class Game
{
	T implementation;
	friend T;

public:
	template<typename... TArgs>
	Game(TArgs&&... targs) : implementation{ *this, std::forward<TArgs&&>(targs)... }
	{}
	~Game() = default;

	Game(const Game& other) = delete;
	Game(Game&& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game& operator=(Game&& other) = delete;

	// Forwarding calls:
	void Init() { implementation.Init(); }
	void Update() { implementation.Update(); }
	void Render() { implementation.Render(); }
	void Shutdown() { implementation.Shutdown(); }

	// Game data
	bool quitGame = false;
	u32 frameCount = 0;
};

template<typename T>
void RunGameLoop(Game<T>& game)
{
	game.Init();

	while(!game.quitGame)
	{
		game.Update();
		game.Render();
		++game.frameCount;
	}

	game.Shutdown();
}
