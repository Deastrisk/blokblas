#include <array>
#include <chrono>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>
#include <thread>
#include <vector>
#include <windows.h>
#include "colors.hpp"

using namespace std;

#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77

enum Page {
    MENU, CLASSIC, TEAM, LEADERBOARD, LOGIN, EXIT, LOGOUT, SHOP,
    LAST_PAGE // not an actual page; only for page count
};

enum PIECES {
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

    LAST_PIECE // not an actual piece; only for piece count
};


struct User {
    int uid = 0;
    string name = "Guest";
    long long int highest_score = 0;
    long long int current_score = 0;
};

struct Cell {
    bool active = false;
    const char* color = TXT_HIDDEN;

    Cell() = default;
    Cell(bool active, const char* color) : active(active), color(color) {}
};


vector<vector<vector<Cell>>> pieces = {
    // T1
    {
        {Cell(true, TXT_GREEN)},
        {Cell(true, TXT_GREEN),   Cell(true, TXT_GREEN)},
        {Cell(true, TXT_GREEN)}
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
        {Cell(false, TXT_ORANGE),  Cell(false, TXT_ORANGE),  Cell(true, TXT_ORANGE)},
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
        // cout << "test";
    }
}

void mainMenu() {
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
            inp = getch();

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
}


// ======== GAME KLASIK (GAME BIASA) Marcio ==========
bool isPlaceable(
    const vector<vector<Cell>>& board,
    const PIECES& piece, 
    int start_x, 
    int start_y
) {
    // check if piece is out of range (y)
    if (start_y >= board.size() - pieces[piece].size()) {
        return false;
    }

    // loops through the piece array
    for (int y = 0; y < pieces[piece].size(); y++) {
        // check if piece is out of range (x)
        if (start_x >= board[y].size() - pieces[piece][y].size()) {
            return false;
        }
        
        for (int x = 0; x < pieces[piece][y].size(); x++) {
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

void placeablePieces(const vector<vector<Cell>>& board, vector<PIECES>& placeable_pieces) {
    // list of all potentially placeable pieces
    vector<PIECES> placeables = {
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

    // loops until enough placeable pieces are found
    const int MAX = 3;
    while (placeable_pieces.size() < MAX) {
        // randomizes piece
        PIECES selected = PIECES(rand() % placeables.size());
        
        // loops through every location (starting point for piece detection)
        for (int i = 0; i < board.size(); i++) {
            bool checked = false;
            for (int j = 0; j < board[i].size(); j++) {
                // invalid staring point if not empty
                if (board[i][j].active) continue;

                // save placeable pieces
                if (isPlaceable(board, selected, j, i)) {
                    placeable_pieces.push_back(selected);
                }

                // erase placeable piece candidates after check
                placeables.erase(placeables.begin() + selected);
                checked = true;
                break;
            }

            if (checked) break;
        }
    }

    return;
}

void removeMoveablePiece(vector<vector<bool>>& board) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j]) board[i][j] = false;
        }
    }
}

void switchPiece(vector<vector<bool>> board, const unsigned char& inp, vector<PIECES> type) {
    
    return;
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

    // moves piece
    vector<vector<bool>> cpy(moveable.size(), vector<bool>(moveable[0].size()));
    for (int i = 0; i < moveable.size(); i++) {
        for (int j = 0; j < moveable[0].size(); j++) {
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
    for (int i = 0; i < moveable.size(); i++) {
        for (int j = 0; j < moveable[0].size(); j++) {
            if (!moveable[i][j]) continue;
            if (i + modif_y < 0 || i + modif_y >= moveable.size()) return false;
            if (j + modif_x < 0 || j + modif_x >= moveable[0].size()) return false;
        }
    }
    return true;
}

bool isPlaceable(const vector<vector<bool>>& moveable, const vector<vector<Cell>>& board) {
    for (int i = 0; i < moveable.size(); i++) {
        for (int j = 0; j < moveable[0].size(); j++) {
            if (!moveable[i][j]) continue;

            // active moveable cell is occupied
            if (board[i][j].active) return false;
        }
    }

    return true;
}

void placePiece(vector<vector<bool>>& moveable, vector<vector<Cell>>& board, const char* color) {
    for (int i = 0; i < moveable.size(); i++) {
        for (int j = 0; j < moveable[0].size(); j++) {
            if (!moveable[i][j]) continue;
            moveable[i][j] = false;
            board[i][j].active = true;
            board[i][j].color = color;
        }
    }
}

void printPiecesList(vector<PIECES> types) {
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
                if (i >= pieces[types[type]].size()) {
                    cout << "  ";
                    continue;
                }

                if (j >= pieces[types[type]][i].size()) {
                    cout << "  ";
                    continue;
                }

                // skip if piece cell nonactive
                if (!pieces[types[type]][i][j].active) {
                    cout << "  ";
                    continue;
                }

                // print colored cell
                cout << pieces[types[type]][i][j].color << u8"██" << TXT_RESET;
                // cout << u8"██";
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

void selectPiece();

void exitGame(bool& quit) {
    page = MENU;
    quit = true;
}

int classic(int uid) {
    hideCursor();

    int rows = 8, cols = 8;
    // array[row][column]
    vector<vector<Cell>> board(rows, vector<Cell>(cols));
    vector<vector<bool>> moveable(rows, vector<bool>(cols, false));
    char* current_color = TXT_BLUE;

    // testing
    moveable[2][5] = true;
    moveable[3][5] = true;
    moveable[3][6] = true;

    vector<PIECES> pieces_list;
    placeablePieces(board, pieces_list);

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

        // pieces list is empty
        bool pieces_list_empty = true;
        for (int i = 0; i < pieces_list.size(); i++) {
            if (pieces_list[i] != LAST_PIECE) {
                pieces_list_empty = false;
                break;
            }
        }

        // summoning pieces from the kingdom of imagination
        if (pieces_list_empty) {
            placeablePieces(board, pieces_list);
        }

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
                if (moveable[(i + 1) / 2][(j + 1) / 2]) {
                    cout << string(TXT_WHITE) << u8"██" << TXT_RESET;
                } else {
                    cout << board[(i + 1) / 2][(j + 1) / 2].color << u8"██" << TXT_RESET;
                }
            }

            // right border
            if (i % 2) cout << u8"─╢";
            else cout << u8" ║";

            // instructions
            const int INS_START = 3;
            if (i == INS_START)     cout << "  W / ↑ : move piece up";
            else if (i == INS_START + 1) cout << "  A / ← : move piece left";
            else if (i == INS_START + 2) cout << "  S / ↓ : move piece down";
            else if (i == INS_START + 3) cout << "  D / → : move piece right";
            else if (i == INS_START + 4) cout << "  1-3   : select piece";
            else if (i == INS_START + 5) cout << "  space : place piece";
            else if (i == INS_START + 6) cout << "  enter : use item";
            else if (i == INS_START + 7) cout << "  ESC   : exit game";
            // when the terminal window isn't maximized, there will be a visual glitch without this 2
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

        // will the player quit the game?? D:
        bool isquit = false; // they couldn't possibly... right?

        // ask for input
        while (true) {
            unsigned char inp = getch();

            // moves piece
            arrowToWASD(inp);
            if (isMoveable(moveable, inp)) {
                movePiece(moveable, inp);
            }

            // places piece
            if (inp == ' ' && isPlaceable(moveable, board)) {
                placePiece(moveable, board, current_color);
            }

            // switch piece
            if (inp >= '1' && inp <= '3') {
                switchPiece(moveable, inp, pieces_list);
            }

            // exit game
            if (inp == '\e') exitGame(isquit);
            break;
        }
        
        // player quits game
        if (isquit) break;
    }

    cout << string(TXT_RESET);

    page = MENU; // TEMP
    return 0;
}


// ======== TEAM GAME (Alan) ========
void team(int uid) {
    return 0;
}





void exit() {
    showCursor();
}


int main()
{
    hideCursor();
    srand(time(0));

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
        else if (page == LEADERBOARD) break;
        else if (page == SHOP) break;
        else if (page == TEAM) team(uid);
        else if (page == EXIT) break;
    }
    
    showCursor();
    return 0;
}
