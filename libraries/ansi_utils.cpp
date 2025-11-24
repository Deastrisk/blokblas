#include "ansi_utils.hpp"
#include <iostream>

using namespace std;

void clearScreen() {
    cout << "\033[2J\033[2;1H";
}

void hideCursor() {
    cout << "\033[?25l";
}

void showCursor() {
    cout << "\033[?25h";
}

void clear() {
    cout << "\033[2J";
}

void moveCursor(int row, int column) {
    cout << "\033[" << row << ";" << column << "H";
}

int isCsiAnsi(string text) {
    if (text.length() < 2) return false;
    if (text.substr(0, 2) == "\033[") {
        return true;
    }
    return false;
}

bool isAnsiFinalByte(char c) {
    return c >= '@' && c <= '~';
}