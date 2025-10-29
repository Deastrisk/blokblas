#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <windows.h>
#include <ctime>

using namespace std;

void menuAnimation() {
    const string BLOCK_BLAST[] = {
        "$$$$$$$\\  $$\\       $$$$$$\\   $$$$$$\\  $$\\   $$\\       $$$$$$$\\  $$\\        $$$$$$\\   $$$$$$\\ $$$$$$$$\\",
        "$$  __$$\\ $$ |     $$  __$$\\ $$  __$$\\ $$ | $$  |      $$  __$$\\ $$ |      $$  __$$\\ $$  __$$\\__$$  __|",
        "$$ |  $$ |$$ |     $$ /  $$ |$$ /  \\__|$$ |$$  /       $$ |  $$ |$$ |      $$ /  $$ |$$ /  \\__|  $$ |   ",
        "$$$$$$$\\ |$$ |     $$ |  $$ |$$ |      $$$$$  /        $$$$$$$\\ |$$ |      $$$$$$$$ |\\$$$$$$\\    $$ |   ",
        "$$  __$$\\ $$ |     $$ |  $$ |$$ |      $$  $$<         $$  __$$\\ $$ |      $$  __$$ | \\____$$\\   $$ |   ",
        "$$ |  $$ |$$ |     $$ |  $$ |$$ |  $$\\ $$ |\\$$\\        $$ |  $$ |$$ |      $$ |  $$ |$$\\   $$ |  $$ |   ",
        "$$$$$$$  |$$$$$$$$\\ $$$$$$  |\\$$$$$$  |$$ | \\$$\\       $$$$$$$  |$$$$$$$$\\ $$ |  $$ |\\$$$$$$  |  $$ |   ",
        "\\_______/ \\________|\\______/  \\______/ \\__|  \\__|      \\_______/ \\________|\\__|  \\__| \\______/   \\__|   ",
    };

    for (int i = BLOCK_BLAST[0].length(); i >= 0; i -= 3) {
        cout << "   _______________________________________________________________________________________________________________\n";
        cout << "  /                                                                                                               \\\n";
        cout << " /                                                                                                                 \\\n";
        cout << "|" << BLOCK_BLAST[0].substr(i) << "\n";
        cout << "|" << BLOCK_BLAST[1].substr(i)  << "\n";
        cout << "|" << BLOCK_BLAST[2].substr(i)  << "\n";
        cout << "|" << BLOCK_BLAST[3].substr(i)  << "\n";
        cout << "|" << BLOCK_BLAST[4].substr(i)  << "\n";
        cout << "|" << BLOCK_BLAST[5].substr(i)  << "\n";
        cout << "|" << BLOCK_BLAST[6].substr(i)  << "\n";
        cout << "|" << BLOCK_BLAST[7].substr(i)  << "\n";
        Sleep(200);
        system("cls");
    }
}

int tambah(int a, int b) {
    int hasil = a + b;
    return hasil;
}

int main()
{
    menuAnimation();
    return 0;
}
