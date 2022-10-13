#include <iostream>
#include <functional>
#include <csignal>
#include "Screen/Screen.h"
#include "Screen/ScreenFactory.h"
#include "Screen/ScreenManager.h"

using namespace std;

std::function<void(int)> windows_resize_handler;

void signal_handler(int signal) { windows_resize_handler(signal); }

ScreenManager::ScreenManager()
{
  windows_resize_handler = [&](int signal)
  {
    this->WindowsResizeHandler();
  };

  signal(SIGWINCH, signal_handler);

  this->current_screen_exists = false;
  this->ui_exit = false;
}

void ScreenManager::Set(string screen_name)
{
  if (!ScreenFactory::ExistsScreen(screen_name))
  {
    cout << "Error: screen " << screen_name << " cannot be setted because screen not exists.";
    return;
  }

  if (this->current_screen_exists)
    this->current_screen->Exit();
  this->current_screen = ScreenFactory::GetScreen(screen_name);
  this->current_screen_exists = true;
  this->current_screen->Initialize();
}

void ScreenManager::Run()
{
  // Hide teminal pointer
  printf("\33[?25l");

  while (!this->ui_exit)
    if (this->current_screen_exists)
    {
      system("clear");

      this->current_screen->Graphic();
      this->current_screen->Action();
    }

  // Show teminal pointer
  printf("\33[?25h");
}

void ScreenManager::Exit()
{
  if (this->current_screen_exists)
    this->current_screen->Exit();
  this->ui_exit = true;
}

bool ScreenManager::ExistsActiveScreen()
{
  return this->current_screen_exists;
}

void ScreenManager::WindowsResizeHandler()
{
  if (this->ExistsActiveScreen())
  {
    system("clear");
    if (this->current_screen_exists)
      this->current_screen->Graphic();
  }
}
