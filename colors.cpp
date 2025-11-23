#include "colors.hpp"
#include <iostream>
#include <string>
#include <regex>

using namespace std;

string txtToBg(const string& txt_color) {
    // format 1 : "\033[<30-37>m"
    regex format1(R"(^\033\[3[0-7]m$)");
    if (regex_match(txt_color, format1)) {
        return "\033[4" + txt_color.substr(3, 1) + "m";
    }
    // format 2 : "\033[<90-97>m"
    regex format2(R"(\033\[9[0-7]m)");
    if (regex_match(txt_color, format2)) {
        return "\033[10" + txt_color.substr(3, 1) + "m";
    }
    // format 3 : "\033[38;5;<0-255>m"
    // int len;
    // "\033[48;5;0m"
    // len = 9
    // "\033[48;5;255m"
    // len = 11
    regex format3(R"(^\033\[38;5;((1?[0-9]{1,2})|(2(([0-4][0-9])|(5[0-5]))))$)");
    if (regex_match(txt_color, format3)) {
        return "\033[48;5;" + txt_color.substr(7, txt_color.length() - 9);
    }

    return txt_color;
}