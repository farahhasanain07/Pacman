#ifndef GHOSTS_H
#define GHOSTS_H

#include "config.h"
#include "map.h"
#include "raymath.h"

bool GhostCanMove(Vector2 pos, Vector2 dir) {

    int tileX = (int)((pos.x + dir.x * TILE_SIZE) / TILE_SIZE);
    int tileY = (int)((pos.y + dir.y * TILE_SIZE) / TILE_SIZE);
    if (tileX >= 0 && tileX < MAP_WIDTH && tileY >= 0 && tileY < MAP_HEIGHT) {
        return map[tileY][tileX] != 1;
    }
    return false;
}

void UpdateGhostAI(Entity *ghost, Entity pacman) {
  
    if ((int)ghost->position.x % TILE_SIZE == 0 && (int)ghost->position.y % TILE_SIZE == 0) {
        Vector2 target = pacman.position;
        
     
        switch(ghost->type) {
            case 0: 
                target = pacman.position; 
                break;
            case 1:
                target = Vector2Add(pacman.position, Vector2Scale(pacman.direction, TILE_SIZE * 4));
                break;
            default: 
                if (GetRandomValue(0, 10) > 6) target = (Vector2){ 0, 0 };
                break;
        }

        Vector2 directions[4] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
        Vector2 bestDir = ghost->direction;
        float minDistance = 999999.0f;

        for (int i = 0; i < 4; i++) {
  
            if (directions[i].x == -ghost->direction.x && directions[i].y == -ghost->direction.y) continue;

            if (GhostCanMove(ghost->position, directions[i])) {
                Vector2 nextTile = Vector2Add(ghost->position, Vector2Scale(directions[i], TILE_SIZE));
                float dist = Vector2Distance(nextTile, target);
                if (dist < minDistance) {
                    minDistance = dist;
                    bestDir = directions[i];
                }
            }
        }
        ghost->direction = bestDir;
    }

    ghost->position = Vector2Add(ghost->position, Vector2Scale(ghost->direction, ghost->speed));
}

#endif