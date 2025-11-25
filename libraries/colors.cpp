#include "colors.hpp"
#include <iostream>
#include <string>

using namespace std;

string txtToBg(const string& txt_color) {
    // format 1 : "\033[<30-37>m"
    if (
        (txt_color.substr(0, 3) == "\033[3") &&
        (txt_color[3] >= '0' && txt_color[3] <= 7) &&
        (txt_color[4] == 'm')
    ) {
        return "\033[4" + txt_color.substr(3, 1) + "m";
    }

    // format 2 : "\033[<90-97>m"
    if (
        (txt_color.substr(0, 3) == "\033[9") &&
        (txt_color[3] >= '0' && txt_color[3] <= 7) &&
        (txt_color[4] == 'm')
    ) {
        return "\033[10" + txt_color.substr(3, 1) + "m";
    }

    // format 3 : "\033[38;5;<0-255>m"
    // used regex before tp katae regex di c++ lambat dan mending pake if...
    if (
        (txt_color.substr(0, 7) == "\033[38;5;") &&
        (((txt_color.length() == 9) && (
            (txt_color[7] >= '0' && txt_color[7] <= '9') &&
            (txt_color[8] == 'm')
        )) ||
        ((txt_color.length() == 10) && (
            (txt_color[7] >= '1' && txt_color[7] <= '9') &&
            (txt_color[8] >= '0' && txt_color[8] <= '9') &&
            (txt_color[9] == 'm')
        )) ||
        ((txt_color.length() == 11 && txt_color[7] == '1') && (
            (txt_color[8] >= '0' && txt_color[8] <= '9') &&
            (txt_color[9] >= '0' && txt_color[8] <= '9') &&
            (txt_color[10] == 'm')
        )) ||
        ((txt_color.length() == 11 && txt_color[7] == '2') && (
            (txt_color[8] >= '0' && txt_color[8] <= '4') &&
            (txt_color[9] >= '0' && txt_color[9] <= '9') &&
            (txt_color[10] == 'm')
        )) ||
        ((txt_color.length() == 11 && txt_color.substr(7, 2) == "25") && (
            (txt_color[9] >= '0' && txt_color[9] <= '5') &&
            (txt_color[10] == 'm')
        )))
    ) {
        return "\033[48;5;" + txt_color.substr(7, txt_color.length() - 9) + 'm';
    }

    // txt_color follows none of the format
    return txt_color;
}