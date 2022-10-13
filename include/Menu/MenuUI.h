#ifndef MENUUI_H
#define MENUUI_H

#include <iostream>
#include "Menu.h"

using namespace std;

class MenuUI
{
public:
  static void PrintMenu(Menu *menu);
  static void ActivateMenu(Menu *menu);
};

#endif
