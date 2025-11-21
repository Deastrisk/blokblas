#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <windows.h>
#include <thread>
#include <chrono>
#include <ctime>
#include <conio.h>
#include "colors.h"

using namespace std;


typedef enum {
    MENU, CLASSIC, TEAM, LEADERBOARD, LOGIN, EXIT
} Page;

typedef enum {
        T0,       T1,       T2,      T3,
    // ##    |          |    ## | ## ## ##
    // ## ## |    ##    | ## ## |    ##
    // ##    | ## ## ## |    ## | 

        L1,       L2,       L3,      L4, 
    // ##    |          | ## ## | ## ## ##
    // ##    |       ## |    ## | ##
    // ## ## | ## ## ## |    ## | 
        LM1,      LM2,     LM3,      LM4,
    //    ## |          | ## ## | ## ## ##
    //    ## | ##       | ##    |       ##
    // ## ## | ## ## ## | ##    | 

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
    // ## ## ## | ## ## ## |       ## | ##
    // ##       |       ## |       ## | ##
    // ##       |       ## | ## ## ## | ## ## ##

      SPECIAL
    //    ##
    // ##
} PIECES;

typedef struct {
    int uid = 0;
    string name = "Guest";
    long long int highest_score = 0;
    long long int current_score = 0;
} User;

typedef struct {
    bool active = false;
    string color = TXT_RED;
} Cell;

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
    Page selected = LOGIN;
    while (true) {
        clearScreen();
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
                int count = 3;
                cout << "| | " 
                     << printPadding((len + buff + 1) / count - 6) << (selected == TEAM ? selected_color : "") << " TEAM " << (selected == TEAM ? string(TXT_RESET) : "")
                     << printPadding((len + buff + 1) / count - 6) << (selected == EXIT ? selected_color : "") << " EXIT " << (selected == EXIT ? string(TXT_RESET) : "")
                     << setw((len + buff + 1) / count) << "|\n";
            }
            else cout << "| | " << setw(len + buff + 1) << right << "|\n";
        }

        cout << "\\ \\                                                                                                                 /\n";
        cout << " \\_\\_______________________________________________________________________________________________________________/\n";

        // user input
        char inp = getch();

        // right arrow input
        if (inp == 77 || inp == 'd') {
            switch (selected) {
            case LOGIN:
                selected = CLASSIC;
                break;
            case CLASSIC:
                selected = LEADERBOARD;
                break;
            case LEADERBOARD:
                selected = TEAM;
                break;
            case TEAM:
                selected = EXIT;
                break;
            case EXIT:
                selected = LOGIN;
                break;
            }
        }

        // left arrow input
        if (inp == 75 || inp == 'a') {
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
            case TEAM:
                selected = LEADERBOARD;
                break;
            case EXIT:
                selected = TEAM;
                break;
            }
        }

        // down/up arrow
        if (inp == 80 || inp == 72 || inp == 'w' || inp == 's') {
            switch (selected) {
            case LOGIN:
                selected = TEAM;
                break;
            case CLASSIC:
                selected = TEAM;
                break;
            case LEADERBOARD:
                selected = EXIT;
                break;
            case TEAM:
                selected = CLASSIC;
                break;
            case EXIT:
                selected = LEADERBOARD;
                break;
            }
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
}


// ======== GAME KLASIK (GAME BIASA) Marcio ==========
int classic(int uid) {
    hideCursor();

    int rows = 8, cols = 8;
    vector<vector<Cell>> board(rows, vector<Cell>(cols));

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

        // print top border
        moveCursor(2, 0);
        cout << u8"╔";
        for (int i = 0; i < cols * 2 - 1; i++) {
            if (i % 2) cout << u8"╤";
            else cout << u8"════";
        }
        cout << u8"╗\n";

        for (int i = 0; i < rows * 2 - 1; i++) {
            if (i % 2) cout << u8"╟─";
            else cout << u8"║ ";

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

                cout << board[(i + 1) / 2][(j + 1) / 2].color << u8"██" << TXT_RESET;
                // cout << u8"██";
            }

            if (i % 2) cout << u8"─╢\n";
            else cout << u8" ║\n";
        }

        // print bottom border
        cout << u8"╚";
        for (int i = 0; i < cols * 2 - 1; i++) {
            if (i % 2) cout << u8"╧";
            else cout << u8"════";
        }
        cout << u8"╝\n";

        Sleep(800);
        if (getch()) break;
    }

    cout << string(TXT_RESET);

    page = MENU; // TEMP
    return 0;
}


void exit() {
    showCursor();
}


int main()
{
    hideCursor();

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
        else if (page == TEAM) break;
        else if (page == EXIT) break;
    }
    
    showCursor();
    return 0;
}
