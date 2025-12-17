#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "rlutil.h"

struct Point {
    int x, y;
};

int main() {
    srand(time(NULL));
    rlutil::cls();
    rlutil::hidecursor();
    rlutil::saveDefaultColor();
    
    const int width = 40;
    const int height = 20;
    
    // 蛇的初始位置
    std::vector<Point> snake;
    snake.push_back({width/2, height/2});
    
    // 食物位置
    Point food = {rand() % width + 1, rand() % height + 1};
    
    // 移動方向
    int dx = 1, dy = 0;
    
    // 遊戲狀態
    bool gameOver = false;
    int score = 0;
    
    // 繪製邊界
    rlutil::setColor(rlutil::WHITE);
    for (int x = 0; x <= width + 1; x++) {
        rlutil::locate(x, 0);
        std::cout << "#";
        rlutil::locate(x, height + 1);
        std::cout << "#";
    }
    for (int y = 0; y <= height + 1; y++) {
        rlutil::locate(0, y);
        std::cout << "#";
        rlutil::locate(width + 1, y);
        std::cout << "#";
    }
    
    while (!gameOver) {
        // 顯示分數
        rlutil::locate(width + 3, 1);
        std::cout << std::string(15, ' '); // 清除舊分數
        rlutil::locate(width + 3, 1);
        rlutil::setColor(rlutil::YELLOW);
        std::cout << "Score: " << score;
        
        // 繪製食物
        rlutil::locate(food.x, food.y);
        rlutil::setColor(rlutil::RED);
        std::cout << "O";
        
        // 繪製蛇
        for (size_t i = 0; i < snake.size(); i++) {
            rlutil::locate(snake[i].x, snake[i].y);
            rlutil::setColor(rlutil::LIGHTBLUE);
            if (i == 0) {
                std::cout << "O";  // 蛇頭
            } else {
                std::cout << "o";  // 蛇身
            }
        }
        
        rlutil::msleep(100);
        
        // 處理輸入(非阻塞)
        if (kbhit()) {
            int key = rlutil::getkey();
            if (key == rlutil::KEY_UP && dy == 0) {
                dx = 0; dy = -1;
            } else if (key == rlutil::KEY_DOWN && dy == 0) {
                dx = 0; dy = 1;
            } else if (key == rlutil::KEY_LEFT && dx == 0) {
                dx = -1; dy = 0;
            } else if (key == rlutil::KEY_RIGHT && dx == 0) {
                dx = 1; dy = 0;
            } else if (key == rlutil::KEY_ESCAPE) {
                break;
            }
        }
        
        // 計算新的蛇頭位置
        Point newHead = {snake[0].x + dx, snake[0].y + dy};
        
        // 檢查碰撞
        if (newHead.x < 1 || newHead.x > width ||
            newHead.y < 1 || newHead.y > height) {
            gameOver = true;
            break;
        }
        
        for (size_t i = 0; i < snake.size(); i++) {
            if (snake[i].x == newHead.x && snake[i].y == newHead.y) {
                gameOver = true;
                break;
            }
        }
        
        if (gameOver) break;
        
        // 移動蛇
        snake.insert(snake.begin(), newHead);
        
        // 檢查是否吃到食物
        if (newHead.x == food.x && newHead.y == food.y) {
            score++;
            food = {rand() % width + 1, rand() % height + 1};
        } else {
            // 清除蛇尾
            rlutil::locate(snake.back().x, snake.back().y);
            std::cout << " ";
            snake.pop_back();
        }
    }
    
    // 遊戲結束
    rlutil::cls();
    rlutil::locate(1, 10);
    rlutil::setColor(rlutil::RED);
    std::cout << "Game Over!" << std::endl;
    rlutil::locate(1, 11);
    rlutil::setColor(rlutil::YELLOW);
    std::cout << "Final Score: " << score << std::endl;
    
    rlutil::locate(1, 13);
    rlutil::resetColor();
    std::cout << "Press any key to exit...";
    rlutil::anykey();
    
    rlutil::showcursor();
    rlutil::cls();
    return 0;
}
