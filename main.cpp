#define MA_IMPLEMENTATION
#include "miniaudio.h"
#include <chrono>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>
#include <thread>
#include <vector>
#include <windows.h>
#include <mmsystem.h>
#include "libraries/colors.hpp"
#include "libraries/ansi_utils.hpp"

using namespace std;


#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77

// music
ma_engine engine;
ma_sound bgm_menu;
ma_sound bgm_classic_game;
ma_sound sfx_click;
ma_sound sfx_switch_piece;
ma_sound sfx_place_piece;
ma_sound sfx_line_clear;
ma_sound sfx_lose;

enum Page {
    MENU, CLASSIC, TEAM, LEADERBOARD, LOGIN, EXIT, LOGOUT, SHOP,
    LAST_PAGE // not an actual page; only for page count
};

enum PIECES {
        S1,       S2,      SM1,     SM2,
    // ##    |    ## ## |    ## | ## ##
    // ## ## | ## ##    | ## ## |    ## ##
    //    ## |          | ##    |

        T1,       T2,       T3,      T4,
    // ##    |          |    ## | ## ## ##
    // ## ## |    ##    | ## ## |    ##
    // ##    | ## ## ## |    ## | 

        L1,       L2,       L3,      L4, 
    // ##    |          | ## ## | ## ## ##
    // ##    |       ## |    ## | ##
    // ## ## | ## ## ## |    ## | 
        LM1,      LM2,     LM3,      LM4,
    //    ## | ## ## ## | ## ## | 
    //    ## |       ## | ##    | ##      
    // ## ## |          | ##    | ## ## ##

       I2,  I3,  I4,  I5,
    // ## | ## | ## | ##
    // ## | ## | ## | ##
    //    | ## | ## | ##
    //    |    | ## | ##
    //    |    |    | ##

        IH2,     IH3,         IH4,           IH5,
    // ## ## | ## ## ## | ## ## ## ## | ## ## ## ## ##

        O2,       O3,
    // ## ## | ## ## ##
    // ## ## | ## ## ##
    //       | ## ## ##

        R2x3,    R3x2,
    // ## ## | ## ## ##
    // ## ## | ## ## ##
    // ## ## | 

         LL1,       LL2,       LL3,       LL4,
    // ## ## ## | ##       |       ## | ## ## ##
    // ##       | ##       |       ## |       ##
    // ##       | ## ## ## | ## ## ## |       ##

    SPECIAL1, SPECIAL2,
    //    ## | ##
    // ##    |    ##

       SPECIAL3,  SPECIAL4,
    //       ## | ##
    //    ##    |    ##
    // ##       |       ##

    LAST_PIECE // not an actual piece
};


struct User {
    int uid = 0;
    string name = "Guest";
    long long int highest_score = 0;
    long long int current_score = 0;
};

struct Cell {
    bool active = false;
    string color = TXT_HIDDEN;

    Cell() = default;
    Cell(bool active, string color) : active(active), color(color) {}
};

struct ActivePiece {
    PIECES type;
    bool moveable;
    bool placed;

    ActivePiece(PIECES type) : type(type), moveable(false), placed(false) {}
};


vector<vector<vector<Cell>>> pieces = {
    // S1
    {
        {Cell(true, TXT_PINK)},
        {Cell(true, TXT_PINK),    Cell(true, TXT_PINK)},
        {Cell(false, TXT_PINK),   Cell(true, TXT_PINK)},
    },
    // S2
    {
        {Cell(false, TXT_PINK),   Cell(true, TXT_PINK),  Cell(true, TXT_PINK)},
        {Cell(true, TXT_PINK),    Cell(true, TXT_PINK),  Cell(false, TXT_PINK)},
    },
    // SM1
    {
        {Cell(false, TXT_PINK),   Cell(true, TXT_PINK)},
        {Cell(true, TXT_PINK),    Cell(true, TXT_PINK)},
        {Cell(true, TXT_PINK)},
    },
    // SM2
    {
        {Cell(true, TXT_PINK),    Cell(true, TXT_PINK),  Cell(false, TXT_PINK)},
        {Cell(false, TXT_PINK),   Cell(true, TXT_PINK),  Cell(true, TXT_PINK)},
    },
    // T1
    {
        {Cell(true, TXT_GREEN)},
        {Cell(true, TXT_GREEN),   Cell(true, TXT_GREEN)},
        {Cell(true, TXT_GREEN)},
    },
    // T2
    {
        {Cell(false, TXT_GREEN),  Cell(true, TXT_GREEN)},
        {Cell(true, TXT_GREEN),   Cell(true, TXT_GREEN), Cell(true, TXT_GREEN)},
    },
    // T3
    {
        {Cell(false, TXT_GREEN),  Cell(true, TXT_GREEN)},
        {Cell(true, TXT_GREEN),   Cell(true, TXT_GREEN)},
        {Cell(false, TXT_GREEN),  Cell(true, TXT_GREEN)},
    },
    // T4
    {
        {Cell(true, TXT_GREEN),   Cell(true, TXT_GREEN),    Cell(true, TXT_GREEN)},
        {Cell(false, TXT_GREEN),  Cell(true, TXT_GREEN)},
    },

    // L1
    {
        {Cell(true, TXT_LIGHT_BLUE)},
        {Cell(true, TXT_LIGHT_BLUE)},
        {Cell(true, TXT_LIGHT_BLUE),  Cell(true, TXT_LIGHT_BLUE)},
    },
    // L2
    {
        {Cell(false, TXT_LIGHT_BLUE), Cell(false, TXT_LIGHT_BLUE),  Cell(true, TXT_LIGHT_BLUE)},
        {Cell(true, TXT_LIGHT_BLUE),  Cell(true, TXT_LIGHT_BLUE),   Cell(true, TXT_LIGHT_BLUE)},
    },
    // L3
    {
        {Cell(true, TXT_LIGHT_BLUE),  Cell(true, TXT_LIGHT_BLUE)},
        {Cell(false, TXT_LIGHT_BLUE), Cell(true, TXT_LIGHT_BLUE)},
        {Cell(false, TXT_LIGHT_BLUE), Cell(true, TXT_LIGHT_BLUE)},
    },
    // L4
    {
        {Cell(true, TXT_LIGHT_BLUE),  Cell(true, TXT_LIGHT_BLUE),   Cell(true, TXT_LIGHT_BLUE)},
        {Cell(true, TXT_LIGHT_BLUE)},
    },

    // LM1
    {
        {Cell(false, TXT_ORANGE), Cell(true, TXT_ORANGE)},
        {Cell(false, TXT_ORANGE), Cell(true, TXT_ORANGE)},
        {Cell(true, TXT_ORANGE),  Cell(true, TXT_ORANGE)},
    },
    // LM2
    {
        {Cell(true, TXT_ORANGE),  Cell(true, TXT_ORANGE),   Cell(true, TXT_ORANGE)},
        {Cell(false, TXT_ORANGE), Cell(false, TXT_ORANGE),  Cell(true, TXT_ORANGE)},
    },
    // LM3
    {
        {Cell(true, TXT_ORANGE),  Cell(true, TXT_ORANGE)},
        {Cell(true, TXT_ORANGE)},
        {Cell(true, TXT_ORANGE)},
    },
    // LM4
    {
        {Cell(true, TXT_ORANGE),  Cell(false, TXT_ORANGE),  Cell(false, TXT_ORANGE)},
        {Cell(true, TXT_ORANGE),  Cell(true, TXT_ORANGE),   Cell(true, TXT_ORANGE)},
    },

    // I2
    {
        {Cell(true, TXT_YELLOW)},
        {Cell(true, TXT_YELLOW)},
    },
    // I3
    {
        {Cell(true, TXT_YELLOW)},
        {Cell(true, TXT_YELLOW)},
        {Cell(true, TXT_YELLOW)},
    },
    // I4
    {
        {Cell(true, TXT_YELLOW)},
        {Cell(true, TXT_YELLOW)},
        {Cell(true, TXT_YELLOW)},
        {Cell(true, TXT_YELLOW)},
    },
    // I5
    {
        {Cell(true, TXT_YELLOW)},
        {Cell(true, TXT_YELLOW)},
        {Cell(true, TXT_YELLOW)},
        {Cell(true, TXT_YELLOW)},
        {Cell(true, TXT_YELLOW)},
    },

    // IH2
    {
        {Cell(true, TXT_YELLOW), Cell(true, TXT_YELLOW)},
    },
    // IH3
    {
        {Cell(true, TXT_YELLOW), Cell(true, TXT_YELLOW), Cell(true, TXT_YELLOW)},
    },
    // IH4
    {
        {Cell(true, TXT_YELLOW), Cell(true, TXT_YELLOW), Cell(true, TXT_YELLOW), Cell(true, TXT_YELLOW)},
    },
    // IH5
    {
        {Cell(true, TXT_YELLOW), Cell(true, TXT_YELLOW), Cell(true, TXT_YELLOW), Cell(true, TXT_YELLOW), Cell(true, TXT_YELLOW)},
    },

    // O2
    {
        {Cell(true, TXT_RED),   Cell(true, TXT_RED)},
        {Cell(true, TXT_RED),   Cell(true, TXT_RED)},
    },
    // O3
    {
        {Cell(true, TXT_RED),   Cell(true, TXT_RED),    Cell(true, TXT_RED)},
        {Cell(true, TXT_RED),   Cell(true, TXT_RED),    Cell(true, TXT_RED)},
        {Cell(true, TXT_RED),   Cell(true, TXT_RED),    Cell(true, TXT_RED)},
    },

    // R2x3
    {
        {Cell(true, TXT_BLUE),   Cell(true, TXT_BLUE)},
        {Cell(true, TXT_BLUE),   Cell(true, TXT_BLUE)},
        {Cell(true, TXT_BLUE),   Cell(true, TXT_BLUE)},
    },
    // R3x2
    {
        {Cell(true, TXT_BLUE),   Cell(true, TXT_BLUE),    Cell(true, TXT_BLUE)},
        {Cell(true, TXT_BLUE),   Cell(true, TXT_BLUE),    Cell(true, TXT_BLUE)},
    },

    // LL1
    {
        {Cell(true, TXT_MAGENTA),   Cell(true, TXT_MAGENTA),    Cell(true, TXT_MAGENTA)},
        {Cell(true, TXT_MAGENTA)},
        {Cell(true, TXT_MAGENTA)},
    },
    // LL2
    {
        {Cell(true, TXT_MAGENTA)},
        {Cell(true, TXT_MAGENTA)},
        {Cell(true, TXT_MAGENTA),   Cell(true, TXT_MAGENTA),    Cell(true, TXT_MAGENTA)},
    },
    // LL3
    {
        {Cell(false, TXT_MAGENTA),  Cell(false, TXT_MAGENTA),   Cell(true, TXT_MAGENTA)},
        {Cell(false, TXT_MAGENTA),  Cell(false, TXT_MAGENTA),   Cell(true, TXT_MAGENTA)},
        {Cell(true, TXT_MAGENTA),   Cell(true, TXT_MAGENTA),    Cell(true, TXT_MAGENTA)},
    },
    // LL4
    {
        {Cell(true, TXT_MAGENTA),   Cell(true, TXT_MAGENTA),    Cell(true, TXT_MAGENTA)},
        {Cell(false, TXT_MAGENTA),  Cell(false, TXT_MAGENTA),   Cell(true, TXT_MAGENTA)},
        {Cell(false, TXT_MAGENTA),  Cell(false, TXT_MAGENTA),   Cell(true, TXT_MAGENTA)},
    },

    // SPECIAL1
    {
        {Cell(false, TXT_CYAN), Cell(true, TXT_CYAN)},
        {Cell(true, TXT_CYAN)},
    },
    // SPECIAL2
    {
        {Cell(true, TXT_CYAN)},
        {Cell(false, TXT_CYAN), Cell(true, TXT_CYAN)},
    },
    // SPECIAL3
    {
        {Cell(false, TXT_LIME), Cell(false, TXT_LIME), Cell(true, TXT_LIME)},
        {Cell(false, TXT_LIME), Cell(true, TXT_LIME)},
        {Cell(true, TXT_LIME)},
    },
    // SPECIAL4
    {
        {Cell(true, TXT_LIME)},
        {Cell(false, TXT_LIME), Cell(true, TXT_LIME)},
        {Cell(false, TXT_LIME), Cell(false, TXT_LIME), Cell(true, TXT_LIME)},
    },
};

Page page = MENU;

// ========= FUNCTIONS ========
// dpt dari gugel jujur ae
// mslhe gk ada system("cls") tanpa windows.h T.T
string printPadding(int pad, char c = ' ') {
    string result = "";
    for (int i = 0; i < pad; i++) {
        result += c;
    }

    return result;
}

void arrowToWASD(unsigned char& key) {
    // detect arrow input
    int inp = key;
    if (inp == 0 || inp == 224) {
        int c = getch();
        if (c == RIGHT_ARROW) inp = 'd';
        else if (c == LEFT_ARROW) inp = 'a';
        else if (c == UP_ARROW) inp = 'w';
        else if (c == DOWN_ARROW) inp = 's';
    }
    key = inp;
    return;
}

long long int strlenIgnoreANSI(string text) {
    long long int len = 0;
    string sub;
    for (int i = 0; i < static_cast<int>(text.length());) {

        // remaining string is less than 2 chars; can't be a CSI ANSI prefix
        if (i + 1 >= static_cast<int>(text.length())) {
            len++;
            i++;
            continue;
        }

        sub = text.substr(i, text.length() - i);

        // doesn't begin with an ANSI CNI prefix
        if (!isCsiAnsi(sub)) {
            len++;
            i++;
            continue;
        }

        // skip ESC + [
        i += 2;

        // loop until reaches final byte
        while (i < static_cast<int>(text.length()) && !isAnsiFinalByte(text[i])) {
            i++;
        };

        // skips final byte
        if (i < static_cast<int>(text.length())) i++;
    }

    return len;
}

void boardCenteredText(const vector<string>& text, const vector<vector<Cell>> board) {
    int rows = board.size();
    int cols = board[0].size();
    for (int i = 0; i < static_cast<int>(text.size()); i++) {
        moveCursor(rows + i, (cols * 5 - strlenIgnoreANSI(text[i])) / 2);
        cout << text[i];
    }
}


// ======== MENU FUNCTIONS ========
void animateMenu() {
    hideCursor();

    const string BLOCK_BLAST[] = {
        "$$$$$$$\\  $$\\       $$$$$$\\   $$$$$$\\  $$\\   $$\\       $$$$$$$\\  $$\\        $$$$$$\\   $$$$$$\\ $$$$$$$$\\ ",
        "$$  __$$\\ $$ |     $$  __$$\\ $$  __$$\\ $$ | $$  |      $$  __$$\\ $$ |      $$  __$$\\ $$  __$$\\\\__$$  __|",
        "$$ |  $$ |$$ |     $$ /  $$ |$$ /  \\__|$$ |$$  /       $$ |  $$ |$$ |      $$ /  $$ |$$ /  \\__|  $$ |   ",
        "$$$$$$$\\ |$$ |     $$ |  $$ |$$ |      $$$$$  /        $$$$$$$\\ |$$ |      $$$$$$$$ |\\$$$$$$\\    $$ |   ",
        "$$  __$$\\ $$ |     $$ |  $$ |$$ |      $$  $$<         $$  __$$\\ $$ |      $$  __$$ | \\____$$\\   $$ |   ",
        "$$ |  $$ |$$ |     $$ |  $$ |$$ |  $$\\ $$ |\\$$\\        $$ |  $$ |$$ |      $$ |  $$ |$$\\   $$ |  $$ |   ",
        "$$$$$$$  |$$$$$$$$\\ $$$$$$  |\\$$$$$$  |$$ | \\$$\\       $$$$$$$  |$$$$$$$$\\ $$ |  $$ |\\$$$$$$  |  $$ |   ",
        "\\_______/ \\________|\\______/  \\______/ \\__|  \\__|      \\_______/ \\________|\\__|  \\__| \\______/   \\__|   ",
    };

    const string CBB[] = {
        string(TXT_YELLOW)  + "$$$$$$$\\  " +
        string(TXT_BLUE)    + "$$\\       " +
        string(TXT_RED)     + "$$$$$$\\   " +
        string(TXT_YELLOW)  + "$$$$$$\\  " +
        string(TXT_MAGENTA) + "$$\\   $$\\       " +
        string(TXT_CYAN)    + "$$$$$$$\\  $$\\        $$$$$$\\   $$$$$$\\ $$$$$$$$\\ " + TXT_RESET,

        string(TXT_YELLOW)  + "$$  __$$\\ " +
        string(TXT_BLUE)    + "$$ |     " +
        string(TXT_RED)     + "$$  __$$\\ " +
        string(TXT_YELLOW)  + "$$  __$$\\ " +
        string(TXT_MAGENTA) + "$$ | $$  |      " +
        string(TXT_CYAN)    + "$$  __$$\\ $$ |      $$  __$$\\ $$  __$$\\\\__$$  __|" + TXT_RESET,

        string(TXT_YELLOW)  + "$$ |  $$ |" +
        string(TXT_BLUE)    + "$$ |     " +
        string(TXT_RED)     + "$$ /  $$ |" +
        string(TXT_YELLOW)  + "$$ /  \\__|" +
        string(TXT_MAGENTA) + "$$ |$$  /       " +
        string(TXT_CYAN)    + "$$ |  $$ |$$ |      $$ /  $$ |$$ /  \\__|  $$ |   " + TXT_RESET,

        string(TXT_YELLOW)  + "$$$$$$$\\ |" +
        string(TXT_BLUE)    + "$$ |     " +
        string(TXT_RED)     + "$$ |  $$ |" +
        string(TXT_YELLOW)  + "$$ |      " +
        string(TXT_MAGENTA) + "$$$$$  /        " +
        string(TXT_CYAN)    + "$$$$$$$\\ |$$ |      $$$$$$$$ |\\$$$$$$\\    $$ |   " + TXT_RESET,

        string(TXT_YELLOW)  + "$$  __$$\\ " +
        string(TXT_BLUE)    + "$$ |     " +
        string(TXT_RED)     + "$$ |  $$ |" +
        string(TXT_YELLOW)  + "$$ |      " +
        string(TXT_MAGENTA) + "$$  $$<         " +
        string(TXT_CYAN)    + "$$  __$$\\ $$ |      $$  __$$ | \\____$$\\   $$ |   " + TXT_RESET,

        string(TXT_YELLOW)  + "$$ |  $$ |" +
        string(TXT_BLUE)    + "$$ |     " +
        string(TXT_RED)     + "$$ |  $$ |" +
        string(TXT_YELLOW)  + "$$ |  $$\\ " +
        string(TXT_MAGENTA) + "$$ |\\$$\\        " +
        string(TXT_CYAN)    + "$$ |  $$ |$$ |      $$ |  $$ |$$\\   $$ |  $$ |   " + TXT_RESET,

        string(TXT_YELLOW)  + "$$$$$$$  |" +
        string(TXT_BLUE)    + "$$$$$$$$\\ " +
        string(TXT_RED)     + "$$$$$$  |" +
        string(TXT_YELLOW)  + "\\$$$$$$  |" +
        string(TXT_MAGENTA) + "$$ | \\$$\\       " +
        string(TXT_CYAN)    + "$$$$$$$  |$$$$$$$$\\ $$ |  $$ |\\$$$$$$  |  $$ |   " + TXT_RESET,

        string(TXT_YELLOW)  + "\\_______/ " +
        string(TXT_BLUE)    + "\\________|" +
        string(TXT_RED)     + "\\______/  " +
        string(TXT_YELLOW)  + "\\______/ " +
        string(TXT_MAGENTA) + "\\__|  \\__|      " +
        string(TXT_CYAN)    + "\\_______/ \\________|\\__|  \\__| \\______/   \\__|   " + TXT_RESET,
    };

    const int ANIMATION_DELAY_MS = 60;
    int buff = 9;
    for (int i = BLOCK_BLAST[0].length(), len = i; i >= 0; i -= 5) {
        clearScreen();
        cout << "   _______________________________________________________________________________________________________________\n";
        cout << "  /\\_______________________________________________________________________________________________________________\\\n";
        cout << " /_/                                                                                                                \\\n";
        // print BLOCK BLAST dari array
        for (int j = 0, size = 8; j < size; j++) {
            cout << "| | " << setw(len) << left << BLOCK_BLAST[j].substr(i) << setw(buff) << right << "|" << "\n";
        }
        cout << "\\ \\                                                                                                                 /\n";
        cout << " \\_\\_______________________________________________________________________________________________________________/\n";
        this_thread::sleep_for(chrono::milliseconds(ANIMATION_DELAY_MS));
    }

    for (int i = 0, len = BLOCK_BLAST[0].length(); i <= 5; i += 5) {
        // cout << "test2";
        clearScreen();
        // cout << "test3";
        cout << "   _______________________________________________________________________________________________________________\n";
        cout << "  /\\_______________________________________________________________________________________________________________\\\n";
        cout << " /_/                                                                                                                \\\n";
        // print BLOCK BLAST dari array
        for (int j = 0, size = 8; j < size; j++) {
            cout << "| | " << setw(len + i) << right << BLOCK_BLAST[j] << setw(buff - i) << right << "|" << "\n";
        }
        cout << "\\ \\                                                                                                                 /\n";
        cout << " \\_\\_______________________________________________________________________________________________________________/\n";
        this_thread::sleep_for(chrono::milliseconds(ANIMATION_DELAY_MS));
    }
}

void mainMenu() {
    ma_sound_start(&bgm_menu);

    const string BLOCK_BLAST = "$$$$$$$\\  $$\\       $$$$$$\\   $$$$$$\\  $$\\   $$\\       $$$$$$$\\  $$\\        $$$$$$\\   $$$$$$\\ $$$$$$$$\\ ";

    const string COLORED_BLOCK_BLAST[] = {
        string(TXT_YELLOW)  + "$$$$$$$\\  " +
        string(TXT_BLUE)    + "$$\\       " +
        string(TXT_RED)     + "$$$$$$\\   " +
        string(TXT_YELLOW)  + "$$$$$$\\  " +
        string(TXT_MAGENTA) + "$$\\   $$\\       " +
        string(TXT_CYAN)    + "$$$$$$$\\  $$\\        $$$$$$\\   $$$$$$\\ $$$$$$$$\\ " + TXT_RESET,

        string(TXT_YELLOW)  + "$$  __$$\\ " +
        string(TXT_BLUE)    + "$$ |     " +
        string(TXT_RED)     + "$$  __$$\\ " +
        string(TXT_YELLOW)  + "$$  __$$\\ " +
        string(TXT_MAGENTA) + "$$ | $$  |      " +
        string(TXT_CYAN)    + "$$  __$$\\ $$ |      $$  __$$\\ $$  __$$\\\\__$$  __|" + TXT_RESET,

        string(TXT_YELLOW)  + "$$ |  $$ |" +
        string(TXT_BLUE)    + "$$ |     " +
        string(TXT_RED)     + "$$ /  $$ |" +
        string(TXT_YELLOW)  + "$$ /  \\__|" +
        string(TXT_MAGENTA) + "$$ |$$  /       " +
        string(TXT_CYAN)    + "$$ |  $$ |$$ |      $$ /  $$ |$$ /  \\__|  $$ |   " + TXT_RESET,

        string(TXT_YELLOW)  + "$$$$$$$\\ |" +
        string(TXT_BLUE)    + "$$ |     " +
        string(TXT_RED)     + "$$ |  $$ |" +
        string(TXT_YELLOW)  + "$$ |      " +
        string(TXT_MAGENTA) + "$$$$$  /        " +
        string(TXT_CYAN)    + "$$$$$$$\\ |$$ |      $$$$$$$$ |\\$$$$$$\\    $$ |   " + TXT_RESET,

        string(TXT_YELLOW)  + "$$  __$$\\ " +
        string(TXT_BLUE)    + "$$ |     " +
        string(TXT_RED)     + "$$ |  $$ |" +
        string(TXT_YELLOW)  + "$$ |      " +
        string(TXT_MAGENTA) + "$$  $$<         " +
        string(TXT_CYAN)    + "$$  __$$\\ $$ |      $$  __$$ | \\____$$\\   $$ |   " + TXT_RESET,

        string(TXT_YELLOW)  + "$$ |  $$ |" +
        string(TXT_BLUE)    + "$$ |     " +
        string(TXT_RED)     + "$$ |  $$ |" +
        string(TXT_YELLOW)  + "$$ |  $$\\ " +
        string(TXT_MAGENTA) + "$$ |\\$$\\        " +
        string(TXT_CYAN)    + "$$ |  $$ |$$ |      $$ |  $$ |$$\\   $$ |  $$ |   " + TXT_RESET,

        string(TXT_YELLOW)  + "$$$$$$$  |" +
        string(TXT_BLUE)    + "$$$$$$$$\\ " +
        string(TXT_RED)     + "$$$$$$  |" +
        string(TXT_YELLOW)  + "\\$$$$$$  |" +
        string(TXT_MAGENTA) + "$$ | \\$$\\       " +
        string(TXT_CYAN)    + "$$$$$$$  |$$$$$$$$\\ $$ |  $$ |\\$$$$$$  |  $$ |   " + TXT_RESET,

        string(TXT_YELLOW)  + "\\_______/ " +
        string(TXT_BLUE)    + "\\________|" +
        string(TXT_RED)     + "\\______/  " +
        string(TXT_YELLOW)  + "\\______/ " +
        string(TXT_MAGENTA) + "\\__|  \\__|      " +
        string(TXT_CYAN)    + "\\_______/ \\________|\\__|  \\__| \\______/   \\__|   " + TXT_RESET,
    };

    // functional menu
    int len = BLOCK_BLAST.length();
    int buff = 9;
    Page selected = CLASSIC;
    while (true) {
        // clearScreen();
        moveCursor(2, 0);
        cout << "   _______________________________________________________________________________________________________________\n";
        cout << "  /\\_______________________________________________________________________________________________________________\\\n";
        cout << " /_/                                                                                                                \\\n";
        for (int j = 0, size = 8; j < size; j++) {
            cout << "| | " << printPadding(5) << COLORED_BLOCK_BLAST[j] << setw(buff - 5) << right << "|" << "\n";
        }

        string selected_color = string(TXT_BLACK) + "\033[48;5;252m";
        for (int i = 0; i < 5; i++) {
            if (i == 2) {
                int count = 4;
                cout << "| | " 
                     << printPadding((len + buff + 1) / count - 5) << (selected == LOGIN ? selected_color : "") << " LOGIN " << (selected == LOGIN ? string(TXT_RESET) : "")
                     << printPadding((len + buff + 1) / count - 9) << (selected == CLASSIC ? selected_color : "") << " CLASSIC " << (selected == CLASSIC ? string(TXT_RESET) : "")
                     << printPadding((len + buff + 1) / count - 13) << (selected == LEADERBOARD ? selected_color : "") << " LEADERBOARD " << (selected == LEADERBOARD? string(TXT_RESET) : "")
                     << setw((len + buff + 1) / count) << "|\n";
            }
            else if (i == 4) {
                int count = 4;
                cout << "| | " 
                     << printPadding((len + buff + 1) / count - 4) << (selected == SHOP ? selected_color : "") << " SHOP " << (selected == SHOP ? string(TXT_RESET) : "")
                     << printPadding((len + buff + 1) / count - 8) << (selected == TEAM ? selected_color : "") << " TEAM " << (selected == TEAM ? string(TXT_RESET) : "")
                     << printPadding((len + buff + 1) / count - 8) << (selected == EXIT ? selected_color : "") << " EXIT " << (selected == EXIT ? string(TXT_RESET) : "")
                     << setw((len + buff + 1) / count + 4) << "|\n";
            }
            else cout << "| | " << setw(len + buff + 1) << right << "|\n";
        }

        cout << "\\ \\                                                                                                                 /\n";
        cout << " \\_\\_______________________________________________________________________________________________________________/\n";

        // user input
        unsigned char inp;
        while (true) {
            // stop sound if it has ended
            if (ma_sound_at_end(&sfx_click)) {
                ma_sound_stop(&sfx_click);
            }

            inp = getch();

            // click sound
            ma_sound_start(&sfx_click);

            // detect arrow input
            arrowToWASD(inp);

            // right input
            if (inp == 'd') {
                // detect if its right arrow
                
                switch (selected) {
                case LOGIN:
                    selected = CLASSIC;
                    break;
                case CLASSIC:
                    selected = LEADERBOARD;
                    break;
                case LEADERBOARD:
                    selected = SHOP;
                    break;
                case SHOP:
                    selected = TEAM;
                    break;
                case TEAM:
                    selected = EXIT;
                    break;
                case EXIT:
                    selected = LOGIN;
                    break;
                }
                break;
            }

            // left input
            if (inp == 'a') {
                switch (selected) {
                case LOGIN:
                    selected = EXIT;
                    break;
                case CLASSIC:
                    selected = LOGIN;
                    break;
                case LEADERBOARD:
                    selected = CLASSIC;
                    break;
                case SHOP:
                    selected = LEADERBOARD;
                    break;
                case TEAM:
                    selected = SHOP;
                    break;
                case EXIT:
                    selected = TEAM;
                    break;
                }
                break;
            }

            // down/up arrow
            if (inp == 'w' || inp == 's') {
                switch (selected) {
                case LOGIN:
                    selected = SHOP;
                    break;
                case CLASSIC:
                    selected = TEAM;
                    break;
                case LEADERBOARD:
                    selected = EXIT;
                    break;
                case SHOP:
                    selected = LOGIN;
                    break;
                case TEAM:
                    selected = CLASSIC;
                    break;
                case EXIT:
                    selected = LEADERBOARD;
                    break;
                }
                break;
            }

            if (inp == '\r') {
                switch (selected) {
                case LOGIN:
                    page = LOGIN;
                    break;
                case CLASSIC:
                    page = CLASSIC;
                    break;
                case LEADERBOARD:
                    page = LEADERBOARD;
                    break;
                case SHOP:
                    page = SHOP;
                    break;
                case TEAM:
                    page = TEAM;
                    break;
                case EXIT:
                    page = EXIT;
                    break;
                }
                break;
            }
        }

        if (inp == '\r') break;
    }

    ma_sound_stop(&sfx_click);
    ma_sound_stop(&bgm_menu);
}


// ======== GAME KLASIK (GAME BIASA) Marcio ==========
void exitPage() {
    page = MENU;
    cout << TXT_RESET;
}

int outOfBound(
    const vector<vector<bool>>& board,
    const PIECES& piece, 
    int start_x, 
    int start_y
) {
    // out of bound (OOB)
    const int OOB_RIGHT = 2;
    const int OOB_LEFT = -2; // would never happen
    const int OOB_BOTTOM = 1;
    const int OOB_TOP = -1; // would never happen

    // piece is out of bound bottom
    if (start_y > static_cast<int>(board.size() - pieces[piece].size())) {
        return OOB_BOTTOM;
    }

    // piece is out of bound TOP
    if (start_y < 0) return OOB_TOP;

    // piece is out of bound left
    if (start_x < 0) return OOB_LEFT;

    // loops through the piece array
    for (int y = 0; y < static_cast<int>(pieces[piece].size()); y++) {
        // piece is out of bound right
        if (start_x > static_cast<int>(board[y].size() - pieces[piece][y].size())) {
            return OOB_RIGHT;
        }
    }

    // all checks passed
    return 0;
}

bool isPlaceable(
    const vector<vector<Cell>>& board,
    const PIECES& piece, 
    int start_x, 
    int start_y
) {
    int height = pieces[piece].size();
    int cols = board.size();
    int rows = board[0].size();
    
    // check if piece is out of bound (y)
    if (start_y > rows - height) return false;
    
    // loops through the piece array
    for (int y = 0; y < height; y++) {
        
        // check if piece is out of bound (x)
        int width = pieces[piece][y].size();
        if (start_x > cols - width) return false;
        
        for (int x = 0; x < width; x++) {
            // skip nonactive piece cell
            if (!pieces[piece][y][x].active) continue;

            // the selected board & piece cell are both active, therefore not placeable
            if (board[y + start_y][x + start_x].active) {
                return false;
            }
        }
    }

    // all checks passed
    return true;
}

bool placeablePieces(const vector<vector<Cell>>& board, vector<ActivePiece>& placeable_pieces) {
    // list of all potentially placeable pieces
    vector<PIECES> placeables = {
        S1, S2, SM1, SM2,
        T1, T2, T3, T4,
        L1, L2, L3, L4,
        LM1, LM2, LM3, LM4,
        I2, I3, I4, I5,
        IH2, IH3, IH4, IH5,
        O2, O3,
        R2x3, R3x2,
        LL1, LL2, LL3, LL4,
        SPECIAL1, SPECIAL2, SPECIAL3, SPECIAL4
    };
    
    // board sizes
    int rows = board.size();
    int cols = board[0].size();

    // initializes placeable_pieces
    placeable_pieces.clear();
    const int MAX = 3;

    // loops until enough placeable pieces are found
    while (placeable_pieces.size() < MAX) {

        // there aren't enough space for 3 unique pieces
        if (placeables.size() < 1) return false;

        // randomizes piece
        int selected_id = rand() % placeables.size();
        PIECES selected = placeables[selected_id];
        
        // initializes piece size
        int height = pieces[selected].size();
        int width = 0;

        // find piece max width
        for (int i = 0; i < height; i++) {
            if (width < static_cast<int>(pieces[selected][i].size())) {
                width = pieces[selected][i].size();
            }
        }

        // loops through every location (starting point for piece detection)
        bool found = false;
        for (int i = 0; i <= rows - height; i++) {

            for (int j = 0; j <= cols - width; j++) {
                // starting point not empty
                if (board[i][j].active) continue;

                // non placeable pieces
                if (!isPlaceable(board, selected, j, i)) continue;

                // save placeable pieces
                found = true;
                placeable_pieces.push_back(ActivePiece(selected));

                break;
            }

            if (found) break;
        }

        // erase placeable piece candidates if not found
        if (!found) {
            placeables.erase(placeables.begin() + selected_id);
        }
    }

    return true;
}

void movePiece(vector<vector<bool>>& moveable, const char& move) {
    // converts input to move by 1
    int modif_x = 0, modif_y = 0;
    switch (move) {
        case 'w': modif_y = -1; break;
        case 'a': modif_x = -1; break;
        case 's': modif_y = 1; break;
        case 'd': modif_x = 1; break;
        default: return;
    }

    // move piece sfx
    ma_sound_start(&sfx_click);

    // moves piece
    vector<vector<bool>> cpy(moveable.size(), vector<bool>(moveable[0].size()));
    for (int i = 0; i < static_cast<int>(moveable.size()); i++) {
        for (int j = 0; j < static_cast<int>(moveable[0].size()); j++) {
            if (!moveable[i][j]) continue;
            cpy[i + modif_y][j + modif_x] = moveable[i][j];
        }
    }
    moveable = cpy;
    return;
}

bool isMoveable(const vector<vector<bool>> moveable, char move) {
    // converts inp to move by 1 modifier
    int modif_x = 0, modif_y = 0;
    switch (move) {
        case 'w': modif_y = -1; break;
        case 'a': modif_x = -1; break;
        case 's': modif_y = 1; break;
        case 'd': modif_x = 1; break;
        default: return false;
    }

    // check if piece move is out of border
    vector<vector<bool>> cpy(moveable.size(), vector<bool>(moveable[0].size()));
    for (int i = 0; i < static_cast<int>(moveable.size()); i++) {
        for (int j = 0; j < static_cast<int>(moveable[0].size()); j++) {
            if (!moveable[i][j]) continue;
            if (i + modif_y < 0 || i + modif_y >= static_cast<int>(moveable.size())) return false;
            if (j + modif_x < 0 || j + modif_x >= static_cast<int>(moveable[0].size())) return false;
        }
    }
    return true;
}

bool isPlaceable(const vector<vector<bool>>& moveable, const vector<vector<Cell>>& board) {
    for (int i = 0; i < static_cast<int>(moveable.size()); i++) {
        for (int j = 0; j < static_cast<int>(moveable[0].size()); j++) {
            if (!moveable[i][j]) continue;

            // active moveable cell is occupied
            if (board[i][j].active) return false;
        }
    }

    return true;
}

void removeMoveablePiece(vector<vector<bool>>& board) {
    for (int i = 0; i < static_cast<int>(board.size()); i++) {
        for (int j = 0; j < static_cast<int>(board[i].size()); j++) {
            if (board[i][j]) board[i][j] = false;
        }
    }
}

void placePiece(
    vector<vector<bool>>& moveable, 
    vector<vector<Cell>>& board, 
    string color, 
    vector<ActivePiece>& piece_list
) {
    // place piece sfx
    ma_sound_start(&sfx_place_piece);

    // "copies" moveable to board
    for (int i = 0; i < static_cast<int>(moveable.size()); i++) {
        for (int j = 0; j < static_cast<int>(moveable[0].size()); j++) {
            if (!moveable[i][j]) continue;

            // pieces cells
            moveable[i][j] = false;
            board[i][j].active = true;
            board[i][j].color = color;
        }
    }

    for (int i = 0; i < static_cast<int>(piece_list.size()); i++) {
        if (!piece_list[i].moveable) continue;

        // moveable piece -> placed piece
        piece_list[i].moveable = false;
        piece_list[i].placed = true;
    }
}

void printPiecesList(const vector<ActivePiece>& piece_list) {
    // top border
    cout << u8"╔";
    for (int i = 0, len = 5; i < len; i++) {
        if (i % 2) cout << u8"╤";
        else cout << u8"════════════";

        if (i == len / 2) cout << u8"═";
    }
    cout << u8"╗\n";

    const int MAX_PIECE_HEIGHT = 5;
    const int MAX_PIECE_WIDTH = 5;
    for (int i = 0; i < MAX_PIECE_HEIGHT; i++) {
        cout << u8"║ ";
        for (int x = 0, type = 0; x < 5; x++) {
            if (x % 2) {
                cout << " │ ";
                if (x == 1) cout << " ";
                continue;
            }

            for (int j = 0; j < MAX_PIECE_WIDTH; j++) {
                // more than piece height
                if (i >= static_cast<int>(pieces[piece_list[type].type].size())) {
                    cout << "  ";
                    continue;
                }

                // more than piece width
                if (j >= static_cast<int>(pieces[piece_list[type].type][i].size())) {
                    cout << "  ";
                    continue;
                }

                // skip if piece cell nonactive
                if (!pieces[piece_list[type].type][i][j].active) {
                    cout << "  ";
                    continue;
                }

                // skip if piece is currently used
                if (piece_list[type].moveable && !piece_list[type].placed) {
                    cout << "  ";
                    continue;
                }

                // skip if piece is placed
                if (!piece_list[type].moveable && piece_list[type].placed) {
                    cout << "  ";
                    continue;
                }

                // print colored cell
                cout << pieces[piece_list[type].type][i][j].color << u8"██" << TXT_RESET;
            }
            type++;
        }
        cout << u8" ║\n";
    }

    // bottom border
    cout << u8"╚";
    for (int i = 0, len = 5; i < len; i++) {
        if (i % 2) cout << u8"╧";
        else cout << u8"════════════";

        if (i == len / 2) cout << u8"═";
    }
    cout << u8"╝\n";
}

void centerPiece(
    const vector<vector<bool>>& moveable,
    const PIECES& type,
    int& x,
    int& y
) {
    y = (moveable.size() - pieces[type].size()) / 2;
    int max_width = 0;
    for (int i = 0; i < static_cast<int>(pieces[type].size()); i++) {
        if (static_cast<int>(pieces[type][i].size()) > max_width) max_width = pieces[type][i].size();
    }
    x = (moveable[0].size() - max_width) / 2;
}

bool alignPiece(
    vector<vector<bool>>& moveable,
    const PIECES& type,
    int& x,
    int& y
) {
    // out of bound (OOB) past the board border
    const int OOB_RIGHT = 2;
    const int OOB_BOTTOM = 1;
    const int OOB_TOP = -1;
    const int OOB_LEFT = -2;

    // move piece if isn't addable
    while (true) {
        int isaddable = outOfBound(moveable, type, x, y);
        if (!isaddable) break;
        if (isaddable == OOB_RIGHT) x--;
        if (isaddable == OOB_BOTTOM) y--;

        // piece is too large
        if (isaddable == OOB_LEFT) {
            return false;
        }
        if (isaddable == OOB_TOP) {
            return false;
        }
    }

    return true;
}

bool addPiece(
    vector<vector<bool>>& moveable,
    const PIECES& type,
    int x,
    int y
) {
    if (!alignPiece(moveable, type, x, y)) return false;

    // adds piece to moveable
    for (int i = 0; i < static_cast<int>(pieces[type].size()); i++) {
        for (int j = 0; j < static_cast<int>(pieces[type][i].size()); j++) {
            if (!pieces[type][i][j].active) continue;
            
            // adds active piece cells to moveable
            moveable[i + y][j + x] = pieces[type][i][j].active;
        }
    }

    return true;
}

bool addPiece(vector<vector<bool>>& moveable, const PIECES& type) {
    int centery, centerx;
    centerPiece(moveable, type, centerx, centery);
    if (!addPiece(moveable, type, centerx, centery)) return false;
    return true;
}

void getTopLeft(const vector<vector<bool>>& moveable, int& x, int& y) {
    int miny = moveable.size();
    int minx = moveable[0].size();
    // uppermost y
    for (int i = 0; i < static_cast<int>(moveable.size()); i++) {
        for (int j = 0; j < static_cast<int>(moveable[0].size()); j++) {
            // cell isn't active
            if (!moveable[i][j]) continue;

            // gets miny and minx
            if (i >= miny && j >= minx) continue;
            if (i < miny) miny = i;
            if (j < minx) minx = j;
        }
    }

    x = minx;
    y = miny;
}

void switchPiece(
    vector<vector<bool>>& moveable, 
    const unsigned char& inp, 
    vector<ActivePiece>& piece_list, 
    string& color
) {
    // switch piece sfx
    ma_sound_start(&sfx_switch_piece);

    int next_piece_id = inp - '1';
    PIECES next_piece = piece_list[next_piece_id].type;
    const int NO_ACTIVE_PIECE = -1;
    int current_piece_id = NO_ACTIVE_PIECE;

    // gets currently used piece
    for (int i = 0; i < static_cast<int>(piece_list.size()); i++) {
        if (piece_list[i].moveable) {
            current_piece_id = i;
        }
    }
    
    // current piece is the same as next piece
    if (current_piece_id == next_piece_id) return;
    
    // there are no active pieces in moveable board
    if (current_piece_id == NO_ACTIVE_PIECE) {
        removeMoveablePiece(moveable);
        addPiece(moveable, next_piece);
        color = pieces[next_piece][0][0].color;
        piece_list[next_piece_id].moveable = true;
        return;
    }

    // get the top-leftmost of the movable piece
    int minx = 0, miny = 0;
    getTopLeft(moveable, minx, miny);
 
    // current piece unused (nonactive), next piece in use (active)
    piece_list[current_piece_id].moveable = false;
    piece_list[next_piece_id].moveable = true;

    // switch piece in moveable board V
    removeMoveablePiece(moveable);
    addPiece(moveable, next_piece, minx, miny);

    return;
}

bool isSwitchable(const vector<ActivePiece>& piece_list, int inp) {
    inp = inp - '1';
    if (inp < 0 || inp > static_cast<int>(piece_list.size())) return false;
    if (piece_list[inp].moveable || piece_list[inp].placed) return false;
    return true;
}

int checkLines(const vector<vector<Cell>>& board, vector<int>& clear_col, vector<int>& clear_row) {
    int lines_cleared = 16;

    // clear_col and clear_row isn't the same size as board
    if (clear_row.size() != board.size() || clear_col.size() != board[0].size()) {
        return 0;
    }
    
    // check lines (vertical & horizontal)
    for (int i = 0; i < static_cast<int>(board.size()); i++) {
        for (int j = 0; j < static_cast<int>(board[i].size()); j++) {
            if (board[i][j].active) continue;

            // cell isn't active but row is still considered cleared
            if (clear_row[i]) {
                clear_row[i] = false;
                lines_cleared--;
            }

            // cell isn't active but cols is still considered cleared
            if (clear_col[j]) {
                clear_col[j] = false;
                lines_cleared--;
            }
        }
    }
    
    return lines_cleared;
}

void clearLines(vector<vector<Cell>>& board, const vector<int>& clear_col, const vector<int>& clear_row) {
    // clear line sfx
    ma_sound_start(&sfx_line_clear);

    // clears line
    for (int i = 0; i < static_cast<int>(board.size()); i++) {
        for (int j = 0; j < static_cast<int>(board[0].size()); j++) {
            if (!clear_col[j] && !clear_row[i]) continue;

            board[i][j].active = false;
            board[i][j].color = TXT_HIDDEN;
        }
    }

    return;
}

bool piecesArePlaceable(vector<vector<Cell>> board, vector<ActivePiece> piece_list) {
    const int piece_count = static_cast<int>(piece_list.size());
    // the amount of pieces able to be placed (removed for efficiency)
    // int placeable_count = 0;
    bool placeable = false;

    const int rows = static_cast<int>(board.size());
    const int cols = static_cast<int>(board[0].size());

    // skip if all pieces are placed
    bool areplaced = true;
    for (int i = 0; i < piece_count; i++) {
        if (piece_list[i].placed) continue;
        areplaced = false;
    }

    if (areplaced) {
        return true;
    }

    // query nonplaced pieces
    for (int type = 0; type < piece_count && !placeable; type++) {
        ActivePiece current = piece_list[type];
        if (current.placed) continue;

        placeable = false;

        // piece height
        int height = static_cast<int>(pieces[current.type].size());
        int width = 0;

        // find max width
        for (int i = 0; i < height; i++) {
            int current_width = pieces[current.type][i].size();
            if (current_width <= width) continue;
            width = current_width;
        }

        // query for unplaceable piece
        for (int i = 0; i <= rows - height && !placeable; i++) {
            for (int j = 0; j <= cols - width; j++) {
                if (!isPlaceable(board, current.type, j, i)) continue;

                // piece is placeable
                return true;
            }
        }
    }

    return false;
}

void classicDisplay(
    const vector<vector<Cell>>& board, 
    const vector<vector<bool>>& moveable, 
    const int score, 
    vector<ActivePiece> pieces_list
) {
    int rows = board.size();
    int cols = board[0].size();

    // carves topmost edge into space
    moveCursor(1, 0);
    cout << setw(41) << "\n";
    cout << u8"╔";
    for (int i = 0; i < cols * 2 - 1; i++) {
        if (i % 2) cout << u8"╤";
        else cout << u8"════";
    }
    // when the terminal window isn't maximized, there will be a visual glitch without this
    cout << u8"╗                                     \n";

    for (int i = 0; i < rows * 2 - 1; i++) {
        // left border
        if (i % 2) cout << u8"╟─";
        else cout << u8"║ ";

        // isinya
        for (int j = 0; j < cols * 2 - 1; j++) {
            if (i % 2 && j % 2) {
                cout << "─┼─";
                continue;
            }

            if (i % 2) {
                cout << "──";
                continue;
            }

            if (j % 2) {
                cout << " │ ";
                continue;
            }

            // prints game/colors
            int piecey = (i + 1) / 2;
            int piecex = (j + 1) / 2;
            if (moveable[piecey][piecex] && board[piecey][piecex].active) {
                cout << txtToBg(board[piecey][piecex].color) << u8"░░" << TXT_RESET;
            } else if (moveable[piecey][piecex]) {
                cout << string(TXT_WHITE) << u8"██" << TXT_RESET;
            } else {
                cout << board[piecey][piecex].color << u8"██" << TXT_RESET;
            }
        }

        // right border
        if (i % 2) cout << u8"─╢";
        else cout << u8" ║";

        // instructions
        const int INS_START = 5;
        if (i == INS_START - 3)      cout << "  " << TXT_BOLD << TXT_BRIGHT_GREEN << "Guest" << TXT_RESET;
        else if (i == INS_START - 2) cout << "  Score : " << score;
        else if (i == INS_START)     cout << "  W / ↑ : move piece up";
        else if (i == INS_START + 1) cout << "  A / ← : move piece left";
        else if (i == INS_START + 2) cout << "  S / ↓ : move piece down";
        else if (i == INS_START + 3) cout << "  D / → : move piece right";
        else if (i == INS_START + 4) cout << "  1-3   : select piece";
        else if (i == INS_START + 5) cout << "  space : place piece";
        else if (i == INS_START + 6) cout << "  enter : use item";
        else if (i == INS_START + 7) cout << "  ESC   : exit game";
        // when the terminal window isn't maximized, there will be a visual glitch without this -- 2
        else cout << "                               ";
        
        cout << "\n";
    }

    // print bottom border
    cout << u8"╚";
    for (int i = 0; i < cols * 2 - 1; i++) {
        if (i % 2) cout << u8"╧";
        else cout << u8"════";
    }
    cout << u8"╝\n";

    printPiecesList(pieces_list);
}

void loseGame(const vector<vector<Cell>> board, int score) {
    // lost sound sfx
    ma_sound_start(&sfx_lose);
    
    vector<string> text = {
        string(TXT_RED) + TXT_BOLD + " You Lost D: " + TXT_RESET,
        " Your final score is: " + string(TXT_BOLD) + TXT_LIGHT_BLUE + to_string(score) + TXT_RESET + " ",
        "",
        string(TXT_LIGHT_BLUE) + " space" + TXT_RESET + " to go to menu ",
    };
    
    boardCenteredText(text, board);
    if (getch()) {};
    exitPage();
}

int classic(int uid = 0) {
    hideCursor();

    ma_sound_start(&bgm_classic_game);

    int rows = 8, cols = 8;
    // array[row][column]
    vector<vector<Cell>> board(rows, vector<Cell>(cols));
    vector<vector<bool>> moveable(rows, vector<bool>(cols, false));
    string current_color = TXT_BLUE;

    // creates a list of switchable pieces
    vector<ActivePiece> pieces_list;
    placeablePieces(board, pieces_list);

    int prev_score = 0;
    int score = prev_score;
    int combo = 0;

    bool update_display = true;
    // bool update_score = true;

    // game
    while (true) {
        // cout << u8"╔════╤════╤════╤════╤════╤════╤════╤════╗\n";
        // cout << u8"║ ██ │ ██ │ ██ │ ██ │ ██ │ ██ │ ██ │ ██ ║\n";
        // cout << u8"╟────┼────┼────┼────┼────┼────┼────┼────╢\n";
        // cout << u8"║ ██ │ ██ │ ██ │ ██ │ ██ │ ██ │ ██ │ ██ ║\n";
        // cout << u8"╟────┼────┼────┼────┼────┼────┼────┼────╢\n";
        // cout << u8"║ ██ │ ██ │ ██ │ ██ │ ██ │ ██ │ ██ │ ██ ║\n";
        // cout << u8"╟────┼────┼────┼────┼────┼────┼────┼────╢\n";
        // cout << u8"║ ██ │ ██ │ ██ │ ██ │ ██ │ ██ │ ██ │ ██ ║\n";
        // cout << u8"╟────┼────┼────┼────┼────┼────┼────┼────╢\n";
        // cout << u8"║ ██ │ ██ │ ██ │ ██ │ ██ │ ██ │ ██ │ ██ ║\n";
        // cout << u8"╟────┼────┼────┼────┼────┼────┼────┼────╢\n";
        // cout << u8"║ ██ │ ██ │ ██ │ ██ │ ██ │ ██ │ ██ │ ██ ║\n";
        // cout << u8"╟────┼────┼────┼────┼────┼────┼────┼────╢\n";
        // cout << u8"║ ██ │ ██ │ ██ │ ██ │ ██ │ ██ │ ██ │ ██ ║\n";
        // cout << u8"╟────┼────┼────┼────┼────┼────┼────┼────╢\n";
        // cout << u8"║ ██ │ ██ │ ██ │ ██ │ ██ │ ██ │ ██ │ ██ ║\n";
        // cout << u8"╚════╧════╧════╧════╧════╧════╧════╧════╝\n";

        // score animation
        if (prev_score < score) {
            // increment the score
            int difference = score - prev_score;
            if (difference > 100) {
                prev_score += (score - prev_score) / 7;
            } else {
                prev_score += 7;
            }

            if (prev_score > score) {
                prev_score = score;
            }

            moveCursor(6, cols * 5 + 12);
            cout << prev_score;
            this_thread::sleep_for(chrono::milliseconds(60));
        }

        // display
        if (update_display) {
            classicDisplay(board, moveable, score, pieces_list);
            update_display = false;
        }

        bool piece_placed = false;

        // ask for input
        if (kbhit()) {
            unsigned char inp = getch();
            
            // moves piece
            arrowToWASD(inp);
            if (isMoveable(moveable, inp)) {
                movePiece(moveable, inp);
            }

            // places piece
            if (inp == ' ' && isPlaceable(moveable, board)) {
                const char* c_color = current_color.c_str();
                placePiece(moveable, board, c_color, pieces_list);
                piece_placed = true;
            }

            // clear lines
            vector<int> clear_col(board.size(), true);
            vector<int> clear_row(board[0].size(), true);
            int line_count = checkLines(board, clear_col, clear_row);    
            score += line_count * 50;
            if (piece_placed && line_count > 0) {
                clearLines(board, clear_col, clear_row);
                moveCursor(6, cols * 5 + 12);
                cout << printPadding(static_cast<int>(log10(score) + 2), ' ');
            }

            // switch piece
            if (isSwitchable(pieces_list, inp)) {
                switchPiece(moveable, inp, pieces_list, current_color);
            }

            // player exit game
            if (inp == '\33') {
                exitPage();
                return 0;
            }

            update_display = true;
        }
        
        // piece placed
        if (piece_placed) {
            // pieces list is empty
            bool pieces_list_empty = true;
            for (int i = 0; i < static_cast<int>(pieces_list.size()); i++) {
                if (!pieces_list[i].placed) {
                    pieces_list_empty = false;
                    break;
                }
            }
            
            // player loses
            int isplaceable = piecesArePlaceable(board, pieces_list);
            if (!isplaceable) {
                loseGame(board, score);
                ma_sound_stop(&bgm_classic_game);
                exitPage();
                return 0;
            }

            // summoning random pieces from Ankewelts kingdom
            if (pieces_list_empty) {
                placeablePieces(board, pieces_list);
            }
        }
    }

    cout << string(TXT_RESET);
    exitPage();
    return 0;
}


// ======== TEAM GAME (Alan) ========
void team(int uid) {
    return;
}





void exit() {
    showCursor();
}


int main()
{
    hideCursor();
    srand(time(0));

    ma_result result;
    
    // sound engine initialization
    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        cout << "Failed to initialize sound engine\n";
        return result;
    }

    // ma_sound sfx_click;
    // ma_sound sfx_switch_piece;
    // ma_sound sfx_place_piece;
    // ma_sound sfx_line_clear;
    // ma_sound sfx_lose;

    // bgm menu initialization
    result = ma_sound_init_from_file(&engine, "bgm/menu.wav", 0, NULL, NULL, &bgm_menu);
    if (result != MA_SUCCESS) {
        cout << "Failed to initialize menu bgm\n";
        return result;
    }
    // sets bgm to loop
    ma_sound_set_looping(&bgm_menu, true);

    // bgm classic game initialization
    result = ma_sound_init_from_file(&engine, "bgm/sink_into_oblivion.mp3", 0, NULL, NULL, &bgm_classic_game);
    if (result != MA_SUCCESS) {
        cout << "Failed to initialize classic game bgm\n";
        return result;
    }
    ma_sound_set_looping(&bgm_classic_game, true);

    // sfx click initalization
    result = ma_sound_init_from_file(&engine, "sfx/single_click.wav", 0, NULL, NULL, &sfx_click);
    if (result != MA_SUCCESS) {
        cout << "Failed to initialize click sfx\n";
        return result;
    }

    // sfx switch piece initialization
    result = ma_sound_init_from_file(&engine, "sfx/switch_piece.mp3", 0, NULL, NULL, &sfx_switch_piece);
    if (result != MA_SUCCESS) {
        cout << "Failed to initialize switch piece sfx\n";
        return result;
    }

    // sfx lose initialization
    result = ma_sound_init_from_file(&engine, "sfx/lose_sound.wav", 0, NULL, NULL, &sfx_lose);
    if (result != MA_SUCCESS) {
        cout << "Failed to initialize lose sound sfx\n";
        return result;
    }

    // sfx place piece initialization
    result = ma_sound_init_from_file(&engine, "sfx/place_piece.wav", 0, NULL, NULL, &sfx_place_piece);
    if (result != MA_SUCCESS) {
        cout << "Failed to initialize place piece sfx\n";
        return result;
    }

    // sfx line clear initialization
    result = ma_sound_init_from_file(&engine, "sfx/line_clear.wav", 0, NULL, NULL, &sfx_line_clear);
    if (result != MA_SUCCESS) {
        cout << "Failed to initialize line clear sfx\n";
        return result;
    }

    // spy karakter unicode kyk ╝ bisa ngeprint di terminal
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    animateMenu();

    // delay for colored title
    this_thread::sleep_for(chrono::milliseconds(500));

    int uid = 0;
    while (true) {
        clearScreen();
        if (page == MENU) mainMenu();
        else if (page == CLASSIC) classic(uid);
        else if (page == LOGIN) break;
        else if (page == LOGOUT) break;
        else if (page == LEADERBOARD) break;
        else if (page == SHOP) break;
        else if (page == TEAM) team(uid);
        else if (page == EXIT) break;
    }
    
    // frees sounds from memory
    ma_sound_uninit(&bgm_menu);
    ma_sound_uninit(&bgm_classic_game);
    ma_sound_uninit(&sfx_click);
    ma_sound_uninit(&sfx_line_clear);
    ma_sound_uninit(&sfx_lose);
    ma_sound_uninit(&sfx_place_piece);
    ma_sound_uninit(&sfx_switch_piece);

    // frees the sound engine
    ma_engine_uninit(&engine);

    showCursor();
    return 0;
}
