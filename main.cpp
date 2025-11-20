#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
// #include <windows.h> gabisa di codeshare diganti chrono + thread
#include <thread>
#include <chrono>
#include <ctime>
#include <conio.h>
#include "colors.h"

using namespace std;


void clear_screen() {
    // dpt dari gugel jujur ae
    // mslhe gk ada system("cls") tanpa windows.h T.T
    cout << "\033[2J\033[1;1H";
}

string printPadding(int pad, char c = ' ') {
    string result = "";
    for (int i = 0; i < pad; i++) {
        result += pad;
    }

    return result;
}

// ==== MENU FUNCTIONS ====
void animateMenu(const string BLOCK_BLAST[8], const string CBB[8]) {
    const int ANIMATION_DELAY_MS = 60;
    int buff = 9;
    for (int i = BLOCK_BLAST[0].length(), len = i; i >= 0; i -= 5) {
        clear_screen();
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
        clear_screen();
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
    
    for (int i = 0, len = BLOCK_BLAST[0].length(); i <= 5; i += 5) {
        cout << "   _______________________________________________________________________________________________________________\n";
        cout << "  /\\_______________________________________________________________________________________________________________\\\n";
        cout << " /_/                                                                                                                \\\n";
        for (int j = 0, size = 8; j < size; j++) {
            cout << "| | " << printPadding(6) << BLOCK_BLAST[j] << setw(buff - 5) << right << "|" << "\n";
        }
        for (int i = 0; i < 5; i++) {
            if (i == 3) cout << "| | " << setw((len + buff + 1)/2) << "START" << setw((len + buff + 1)/2) << right << "|\n";
            else cout << "| | " << setw(len + buff + 1) << right << "|\n";
        }
        cout << "\\ \\                                                                                                                 /\n";
        cout << " \\_\\_______________________________________________________________________________________________________________/\n";
    }
}

void mainMenu() {
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

    animateMenu(BLOCK_BLAST, COLORED_BLOCK_BLAST);

    // functional menu
    int len = COLORED_BLOCK_BLAST[0].length();
    int buff = 9;
    cout << "   _______________________________________________________________________________________________________________\n";
    cout << "  /\\_______________________________________________________________________________________________________________\\\n";
    cout << " /_/                                                                                                                \\\n";
    for (int j = 0, size = 8; j < size; j++) {
        cout << "| | " << setw(len) << right << COLORED_BLOCK_BLAST[j] << setw(buff - 5) << right << "|" << "\n";
    }
    for (int i = 0; i < 5; i++) {
        if (i == 3) cout << "| | " << setw((len + buff + 1)/2) << "START" << setw((len + buff + 1)/2) << right << "|\n";
        else cout << "| | " << setw(len + buff + 1) << right << "|\n";
    }
    cout << "\\ \\                                                                                                                 /\n";
    cout << " \\_\\_______________________________________________________________________________________________________________/\n";
}

int main()
{
    mainMenu();
    
    return 0;
}
