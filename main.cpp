#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
// #include <windows.h> gabisa di codeshare makae diganti chrono + thread
#include <thread>
#include <chrono>
#include <ctime>
#include <conio.h>

using namespace std;

void clear_screen() {
    // dpt dari gugel jujur ae
    // mslhe gk ada system("cls") di codeshare T.T
    cout << "\033[2J\033[1;1H";
}

void animateMenu() {
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

    const int ANIMATION_DELAY_MS = 60;
    int buff = 11;
    for (int i = BLOCK_BLAST[0].length(), len = i; i >= 0; i -= 5) {
        clear_screen();
        cout << "   _______________________________________________________________________________________________________________\n";
        cout << "  /                                                                                                               \\\n";
        cout << " /                                                                                                                 \\\n";
        // print BLOCK BLAST dari array
        for (int j = 0, size = sizeof(BLOCK_BLAST) / sizeof(BLOCK_BLAST[0]); j < size; j++) {
            cout << "|" << setw(len) << left << BLOCK_BLAST[j].substr(i) << setw(buff) << right << "|" << "\n";
        }
        for (int i = 0; i < 5; i++) {
            cout << "|" << setw(len + buff + 1) << right << "|\n";
        }
        cout << "\\                                                                                                                  /\n";
        cout << " \\________________________________________________________________________________________________________________/\n";
        this_thread::sleep_for(chrono::milliseconds(ANIMATION_DELAY_MS));
    }

    for (int i = 0, len = BLOCK_BLAST[0].length(); i <= 5; i += 5) {
        clear_screen();
        cout << "   _______________________________________________________________________________________________________________\n";
        cout << "  /                                                                                                               \\\n";
        cout << " /                                                                                                                 \\\n";
        // print BLOCK BLAST dari array
        for (int j = 0, size = sizeof(BLOCK_BLAST) / sizeof(BLOCK_BLAST[0]); j < size; j++) {
            cout << "|" << setw(len + i) << right << BLOCK_BLAST[j] << setw(buff - i) << right << "|" << "\n";
        }
        for (int i = 0; i < 5; i++) {
            if (i == 3) cout << "|" << setw((len + buff + 1)/2) << "START" << setw((len + buff + 1)/2) << right << "|\n";
            else cout << "|" << setw(len + buff + 1) << right << "|\n";
        }
        cout << "\\                                                                                                                  /\n";
        cout << " \\________________________________________________________________________________________________________________/\n";
        this_thread::sleep_for(chrono::milliseconds(ANIMATION_DELAY_MS));
    }
    char key = ' ';
    key = getch();
    if (key == 13) {system("cls"); start = true;}
    while (start) {
        bool menu = true, play = false;
        while (menu) {
            cout << "1. Play\n"
                 << "2. Entah\n"
                 << "3. Entah\n"
                 << "4. Entah\n"
                 << "0. Exit\n";
            cin >> a;
            if (a == 0) return 0;
            else if (a == 1) play = true;
            else if (a == 2) entah = true;
            else if (a == 3) entah = true;
            else if (a == 4) entah = true;
        }
        while (play) {
            //kode nya
        }
    }
}

int main()
{
    animateMenu();
    return 0;
}
