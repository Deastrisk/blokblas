#ifndef ANSI_UTILS_HPP
#define ANSI_UTILS_HPP

#include <iostream>

void clearScreen();
void hideCursor();
void showCursor();
void clear();
void moveCursor(int row, int column);
int isCsiAnsi(std::string text);
bool isAnsiFinalByte(char c);

#endif