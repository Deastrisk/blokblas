#include "colors.hpp"
#include <iostream>
#include <string>

using namespace std;

string txtToBg(const char* txt_color) {
    string ansi = txt_color;
    // format is: "\033[<id>m"
    if (ansi.length() == 5) {
        return (txt_color + 10);
    }
    // format is: "\033[38;5;<id>m"
    else {
        return ansi.replace(2, 2, "48");
    }
}