#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

class SnakeGame {
private:
    bool gameOver;
    static int highScore;
    
    int x, y, foodX, foodY, score;
    int sizeOfBody; 
    std::vector<int> bodyX, bodyY;
    
    Direction dir;
    const int width;
    const int height;

public:
    SnakeGame();
    
    // File I/O for high score
    void LoadHighScore();   
    void SaveHighScore();   
    
    // Core game flow
    void init_game();       
    void Draw();            
    void Input();           
    void Logic();           
    
    bool isGameOver() { return gameOver; }
    void HideCursor();      
};

#endif
