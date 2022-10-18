#pragma once
#include "libraries/Game/GameController.h"
#include "libraries/Screen/Screen.h"
#include "libraries/Menu/Menu.h"

class GamePlayScreen : public Screen
{
private:
  Menu *screen_menu;
  GameController **game;
  function<void()> fn_exit;
  function<void()> fn_call_game_over;

public:
  GamePlayScreen(GameController **game);
  void Initialize();
  void Terminate();
  void Render();
  void Run();
};
