#ifndef COLORS_HPP
#define COLORS_HPP

#include <iostream>

#define TXT_BLACK       "\033[30m"
#define TXT_RED         "\033[31m"
#define TXT_GREEN       "\033[32m"
#define TXT_YELLOW      "\033[33m"
#define TXT_BLUE        "\033[34m"
#define TXT_MAGENTA     "\033[35m"
#define TXT_CYAN        "\033[36m"
#define TXT_WHITE       "\033[37m"
#define TXT_RESET       "\033[0m"

#define TXT_BRIGHT_GREEN "\033[92m"

#define TXT_LIGHT_BLUE  "\033[38;5;123m"
#define TXT_ORANGE      "\033[38;5;208m"
#define TXT_LIME        "\033[38;5;155m"
#define TXT_PINK        "\033[38;5;212m"

#define BG_BLACK        "\033[40m"
#define BG_RED          "\033[41m"
#define BG_GREEN        "\033[42m"
#define BG_YELLOW       "\033[43m"
#define BG_BLUE         "\033[44m"
#define BG_MAGENTA      "\033[45m"
#define BG_CYAN         "\033[46m"
#define BG_WHITE        "\033[47m"


#define TXT_BOLD          "\033[1m"
#define TXT_DIM           "\033[2m"
#define TXT_ITALIC        "\033[3m"
#define TXT_UNDERLINE     "\033[4m"
#define TXT_BLINKING      "\033[5m"
#define TXT_INVERSE       "\033[7m"
#define TXT_HIDDEN        "\033[8m"
#define TXT_STRIKETHROUGH "\033[9m"

std::string txtToBg(const std::string& txt_color);

#endif