#ifndef SCREENFACTORY_H
#define SCREENFACTORY_H

#include "Screen.h"
#include "vector"

using namespace std;

class ScreenFactory
{
private:
  static vector<Screen *> screens;

public:
  static void AddScreen(Screen *screen);
  static Screen *GetScreen(string screen_name);
  static bool ExistsScreen(string screen_name);
};

#endif