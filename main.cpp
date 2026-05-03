#include "snake.h"
#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
    SnakeGame snake_obj;
    char confirm;

    //  Ask the user if they actually want to start
    cout << "Welcome! Ready to play Snake? (y/n): ";
    cin >> confirm;

    if (confirm != 'y' && confirm != 'Y') {
        cout << "Maybe next time. Bye!" << endl;
        return 0;
    }

    //  Difficulty selection menu
    cout << "\nChoose your difficulty:" << endl;
    cout << "1. Easy Mode" << endl;
    cout << "2. Normal Mode" << endl;
    cout << "3. Hard Mode" << endl;
    cout << "Selection (1-3): ";
    
    int level;
    cin >> level;

    // Set the speed
    long wait_time;
    if (level == 1) {
        wait_time = 200000; // Slow speed
    } else if (level == 3) {
        wait_time = 50000;  // Very fast
    } else {
        wait_time = 120000; // Default medium speed
    }

    // Run the initialization (using the renamed function)
    snake_obj.init_game();

    // Main game loop
    while (!snake_obj.isGameOver()) {
        snake_obj.Draw();
        snake_obj.Input();
        snake_obj.Logic();
        
        // Control the frame rate
        usleep(wait_time); 
    }

    // Save best score and cleanup
    snake_obj.SaveHighScore();
    
    cout << "\n-----------------------" << endl;
    cout << "   GAME OVER!   " << endl;
    cout << "-----------------------" << endl;
    
    // Simple pause so the user can see their final score
    cout << "Press Enter to exit..." << endl;
    cin.ignore();
    cin.get();

    return 0;
}
