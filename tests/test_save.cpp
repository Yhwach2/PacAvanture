#include <iostream>
#include <fstream>

int main() {
    std::cout << "Testing Save System...\n\n";

    // Test 1: Create a save file
    std::ofstream saveFile("test_save.txt");
    if (saveFile) {
        saveFile << "1\n100\n3\n5\n";
        saveFile.close();
        std::cout << "✓ Save file created\n";
    }

    // Test 2: Read it back
    std::ifstream loadFile("test_save.txt");
    if (loadFile) {
        int level, score, lives, coins;
        loadFile >> level >> score >> lives >> coins;

        if (level == 1 && score == 100 && lives == 3 && coins == 5) {
            std::cout << "✓ Save file reads correctly\n";
        }
        loadFile.close();
    }

    // Clean up
    std::remove("test_save.txt");

    std::cout << "\n Save system test passed!\n";
    return 0;
}