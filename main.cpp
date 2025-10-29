#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
// #include <windows.h> gabisa di codeshare makae diganti chrono + thread
#include <thread>
#include <chrono>
#include <ctime>

using namespace std;

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
        cout << "\033[2J\033[1;1H";  std::cout << "\033[2J\033[1;1H"; 
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
        cout << "\033[2J\033[1;1H";  std::cout << "\033[2J\033[1;1H"; 
        cout << "   _______________________________________________________________________________________________________________\n";
        cout << "  /                                                                                                               \\\n";
        cout << " /                                                                                                                 \\\n";
        // print BLOCK BLAST dari array
        for (int j = 0, size = sizeof(BLOCK_BLAST) / sizeof(BLOCK_BLAST[0]); j < size; j++) {
            cout << "|" << setw(len + i) << right << BLOCK_BLAST[j] << setw(buff - i) << right << "|" << "\n";
        }
        for (int i = 0; i < 5; i++) {
            cout << "|" << setw(len + buff + 1) << right << "|\n";
        }
        cout << "\\                                                                                                                  /\n";
        cout << " \\________________________________________________________________________________________________________________/\n";
        this_thread::sleep_for(chrono::milliseconds(ANIMATION_DELAY_MS));
    }    
}

int main()
{
    animateMenu();
    return 0;
}
