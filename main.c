#include "config.h"
#include "map.h"
#include "ghosts.h"

void DrawHeart(float centerX, float centerY, float size, Color color) {
    DrawCircle(centerX - size/2, centerY - size/4, size/2, color);
    DrawCircle(centerX + size/2, centerY - size/4, size/2, color);
    DrawTriangle(
        (Vector2){ centerX - size, centerY },
        (Vector2){ centerX + size, centerY },
        (Vector2){ centerX, centerY + size * 1.1f },
        color
    );
}

bool IsPointInsideRect(Vector2 point, Rectangle rect) {
    return (point.x >= rect.x && point.x <= rect.x + rect.width &&
            point.y >= rect.y && point.y <= rect.y + rect.height);
}

bool IsValidPacmanMove(Vector2 pos, Vector2 dir) {
    int tileX = (int)((pos.x + dir.x * TILE_SIZE) / TILE_SIZE);
    int tileY = (int)((pos.y + dir.y * TILE_SIZE) / TILE_SIZE);
    if (tileX >= 0 && tileX < MAP_WIDTH && tileY >= 0 && tileY < MAP_HEIGHT) {
        return map[tileY][tileX] != 1;
    }
    return false;
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, " Farah's Pacman ");
    SetTargetFPS(60);

    int score = 0;
    int totalLives = 3;
    int livesLeft = 3;
    bool gameOver = false;

 
    Entity pacman = {{13 * TILE_SIZE, 23 * TILE_SIZE}, {0,0}, {0,0}, 4.0f, COLOR_PACMAN, -1};
    
    Entity ghosts[4] = {
        {{13 * TILE_SIZE, 11 * TILE_SIZE}, {1,0},  {0,0}, 2.5f, COLOR_BLINKY, 0},
        {{14 * TILE_SIZE, 11 * TILE_SIZE}, {-1,0}, {0,0}, 2.5f, COLOR_PINKY,  1},
        {{12 * TILE_SIZE, 12 * TILE_SIZE}, {0,-1}, {0,0}, 2.5f, COLOR_INKY,   2},
        {{15 * TILE_SIZE, 12 * TILE_SIZE}, {0,-1}, {0,0}, 2.5f, COLOR_CLYDE,  3}
    };

    Rectangle retryBtn = { SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 + 60, 180, 65 };
    Rectangle quitBtn  = { SCREEN_WIDTH / 2 + 20,  SCREEN_HEIGHT / 2 + 60, 180, 65 };

    while (!WindowShouldClose()) {
        Vector2 mousePos = GetMousePosition();

        if (!gameOver) {
       
            if (IsKeyDown(KEY_RIGHT)) pacman.nextDirection = (Vector2){ 1,  0 };
            if (IsKeyDown(KEY_LEFT))  pacman.nextDirection = (Vector2){-1,  0 };
            if (IsKeyDown(KEY_UP))    pacman.nextDirection = (Vector2){ 0, -1 };
            if (IsKeyDown(KEY_DOWN))  pacman.nextDirection = (Vector2){ 0,  1 };

     
            if ((int)pacman.position.x % TILE_SIZE == 0 && (int)pacman.position.y % TILE_SIZE == 0) {
                int tx = (int)(pacman.position.x / TILE_SIZE);
                int ty = (int)(pacman.position.y / TILE_SIZE);
                
                if (map[ty][tx] == 0 || map[ty][tx] == 3) {
                    score += (map[ty][tx] == 3) ? 50 : 10;
                    map[ty][tx] = 2; 
                }

                if (IsValidPacmanMove(pacman.position, pacman.nextDirection)) {
                    pacman.direction = pacman.nextDirection;
                } else if (!IsValidPacmanMove(pacman.position, pacman.direction)) {
                    pacman.direction = (Vector2){0,0}; 
                }
            }

            pacman.position.x += pacman.direction.x * pacman.speed;
            pacman.position.y += pacman.direction.y * pacman.speed;

       
            for (int i = 0; i < 4; i++) {
                UpdateGhostAI(&ghosts[i], pacman);
                
              
                if (CheckCollisionCircles(
                        (Vector2){pacman.position.x + TILE_SIZE/2, pacman.position.y + TILE_SIZE/2}, 12, 
                        (Vector2){ghosts[i].position.x + TILE_SIZE/2, ghosts[i].position.y + TILE_SIZE/2}, 12)) {
                    
                    livesLeft--;
                    if (livesLeft <= 0) {
                        gameOver = true;
                    } else {
                        
                        pacman.position = (Vector2){13 * TILE_SIZE, 23 * TILE_SIZE};
                        pacman.direction = (Vector2){0,0};
                        pacman.nextDirection = (Vector2){0,0};
                        ghosts[0].position = (Vector2){13 * TILE_SIZE, 11 * TILE_SIZE};
                        ghosts[1].position = (Vector2){14 * TILE_SIZE, 11 * TILE_SIZE};
                        ghosts[2].position = (Vector2){12 * TILE_SIZE, 12 * TILE_SIZE};
                        ghosts[3].position = (Vector2){15 * TILE_SIZE, 12 * TILE_SIZE};
                    }
                }
            }
        } else {
       
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (IsPointInsideRect(mousePos, retryBtn)) {
                    score = 0;
                    livesLeft = totalLives;
                    gameOver = false;
                    pacman.position = (Vector2){13 * TILE_SIZE, 23 * TILE_SIZE};
                    pacman.direction = (Vector2){0,0};
                    pacman.nextDirection = (Vector2){0,0};
                    ghosts[0].position = (Vector2){13 * TILE_SIZE, 11 * TILE_SIZE};
                    ghosts[1].position = (Vector2){14 * TILE_SIZE, 11 * TILE_SIZE};
                    ghosts[2].position = (Vector2){12 * TILE_SIZE, 12 * TILE_SIZE};
                    ghosts[3].position = (Vector2){15 * TILE_SIZE, 12 * TILE_SIZE};
                    
                    extern int map[31][28];
                    for(int y=1; y<30; y++) {
                        for(int x=1; x<27; x++) {
                            if(map[y][x] == 2) map[y][x] = 0; 
                        }
                    }
                }
                if (IsPointInsideRect(mousePos, quitBtn)) {
                    break; 
                }
            }
        }

        BeginDrawing();
        ClearBackground(COLOR_BG);

    
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                float cx = x * TILE_SIZE + TILE_SIZE / 2.0f;
                float cy = y * TILE_SIZE + TILE_SIZE / 2.0f;

                if (map[y][x] == 1) {
                    DrawRectangleRounded((Rectangle){x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE - 2, TILE_SIZE - 2}, 0.25f, 4, COLOR_WALL);
                } else if (map[y][x] == 0) {
                    DrawHeart(cx, cy, 7.0f, COLOR_HEART); 
                } else if (map[y][x] == 3) {
                    DrawHeart(cx, cy, 14.0f, COLOR_HEART); 
                }
            }
        }

   
        if (!gameOver) {
            DrawCircle(pacman.position.x + TILE_SIZE/2, pacman.position.y + TILE_SIZE/2, 18, pacman.color);
            for(int i = 0; i < 4; i++) {
                DrawCircle(ghosts[i].position.x + TILE_SIZE/2, ghosts[i].position.y + TILE_SIZE/2, 18, ghosts[i].color);
            }
        }

  
        DrawRectangle(0, SCREEN_HEIGHT - 80, SCREEN_WIDTH, 80, COLOR_WALL);
        DrawText(TextFormat("SCORE: %06d", score), 40, SCREEN_HEIGHT - 56, 32, COLOR_BG);
        
        DrawText(TextFormat("LIVES (%d/%d): ", livesLeft, totalLives), SCREEN_WIDTH - 440, SCREEN_HEIGHT - 56, 30, COLOR_BG);
        for (int i = 0; i < livesLeft; i++) {
            DrawHeart(SCREEN_WIDTH - 120 + (i * 40), SCREEN_HEIGHT - 40, 15.0f, COLOR_BG);
        }

  
        if (gameOver) {
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){ 255, 200, 215, 245 });
            
            DrawText("GAME OVER", SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT/2 - 80, 72, COLOR_HEART);
            DrawText(" Better luck next time! ", SCREEN_WIDTH/2 - 220, SCREEN_HEIGHT/2, 32, COLOR_PACMAN);

     
            Color rColor = IsPointInsideRect(mousePos, retryBtn) ? COLOR_BTN_HOVER : COLOR_BTN_BG;
            DrawRectangleRounded(retryBtn, 0.3f, 4, rColor);
            DrawText("Retry ", retryBtn.x + 38, retryBtn.y + 18, 28, COLOR_BG);

     
            Color qColor = IsPointInsideRect(mousePos, quitBtn) ? COLOR_BTN_HOVER : COLOR_BTN_BG;
            DrawRectangleRounded(quitBtn, 0.3f, 4, qColor);
            DrawText("Quit ", quitBtn.x + 46, quitBtn.y + 18, 28, COLOR_BG);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}