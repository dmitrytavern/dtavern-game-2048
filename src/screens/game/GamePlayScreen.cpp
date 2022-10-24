#include <string>
#include "global.h"
#include "core/Core.h"
#include "core/CoreMatrix.h"
#include "core/CoreScore.h"
#include "interface/Interface.h"
#include "interface/BannerInterface.h"
#include "interface/WindowInterface.h"
#include "interface/MatrixInterface.h"
#include "interface/DialogInterface.h"
#include "screens/game/GamePlayScreen.h"

enum Triggers
{
  GAME_MENU_SWIPE_UP_KEY = 119,
  GAME_MENU_SWIPE_LEFT_KEY = 97,
  GAME_MENU_SWIPE_DOWN_KEY = 115,
  GAME_MENU_SWIPE_RIGHT_KEY = 100,
  GAME_MENU_EXIT_KEY = 101,
};

void GamePlayScreen::Initialize()
{
  Core::ToStartGame();
}

void GamePlayScreen::Render()
{
  unsigned int matrix_size = Core::Matrix::GetSize();
  unsigned int matrix_cell_height = Interface::Matrix::CELL_HEIGHT;
  unsigned int matrix_borders = Interface::Matrix::BORDER_SIZE * 2;
  unsigned int menu_borders = Interface::Banner::BORDER_SIZE * 2;
  unsigned int matrix_print_rows = matrix_size * matrix_cell_height + matrix_borders;
  unsigned int menu_print_rows = menu_borders + 5;
  unsigned int other_print_rows = 2; // Score, Title

  Interface::Window::PrintVerticalAlign(matrix_print_rows + menu_print_rows + other_print_rows);

#ifdef __linux__
  Interface::Window::PrintCenter("━━━━ 2048 Game Session ━━━━", 28);
#else
  Interface::Window::PrintCenter("---- 2048 Game Session ----");
#endif

  Interface::Window::PrintCenter("Your score: " + std::to_string(Core::Score::Get()));

  Interface::Matrix::Print(Core::Matrix::Get(), Core::Matrix::GetSize());

  Interface::Banner::Print("Control", {"w - swipe to up",
                                       "a - swipe to left",
                                       "s - swipe to down",
                                       "d - swipe to right",
                                       "e - exit"});
}

void GamePlayScreen::Run()
{
  bool dialog = true;

  while (dialog)
  {
    const int code = Interface::Dialog::GetCharCode();

    switch (code)
    {
    case GAME_MENU_SWIPE_UP_KEY:
      Core::ToMove(Core::Matrix::SWIPE_DIRECTION_UP);
      dialog = false;
      break;

    case GAME_MENU_SWIPE_LEFT_KEY:
      Core::ToMove(Core::Matrix::SWIPE_DIRECTION_LEFT);
      dialog = false;
      break;

    case GAME_MENU_SWIPE_DOWN_KEY:
      Core::ToMove(Core::Matrix::SWIPE_DIRECTION_DOWN);
      dialog = false;
      break;

    case GAME_MENU_SWIPE_RIGHT_KEY:
      Core::ToMove(Core::Matrix::SWIPE_DIRECTION_RIGHT);
      dialog = false;
      break;

    case GAME_MENU_EXIT_KEY:
      this->SetSignal(SCREEN_SIGNAL_EXIT);
      dialog = false;
      break;
    }
  }

  if (!Core::ExistsMove())
    this->SetSignal(SCREEN_SIGNAL_SET, SCREEN_GAME_OVER_NAME);
}
