#include <iostream>
#include <windows.h>
#include <conio.h>
#include <limits>
#include <ctime>
#include <vector>
#include "Snake.h"


void hidecursor()
{
  HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO info;
  info.dwSize = 100;
  info.bVisible = FALSE;
  SetConsoleCursorInfo(consoleHandle, &info);
}

int main() {
  srand(time(nullptr));
  hidecursor();
  Snake a;
  a.console();
  return 0;
}
