#ifndef CONFIG_H
#define CONFIG_H
#include "raylib.h"


#define SCREEN_WIDTH 1120   
#define SCREEN_HEIGHT 1252  
#define MAP_WIDTH 28
#define MAP_HEIGHT 31
#define TILE_SIZE 40       


#define COLOR_BG          (Color){ 255, 230, 235, 255 }  
#define COLOR_WALL        (Color){ 255, 143, 177, 255 }  
#define COLOR_PACMAN      (Color){ 255, 105, 180, 255 }  
#define COLOR_HEART       (Color){ 255, 64, 129, 255 }   


#define COLOR_BLINKY      (Color){ 255, 160, 160, 255 }  
#define COLOR_PINKY       (Color){ 255, 185, 212, 255 }  
#define COLOR_INKY        (Color){ 175, 225, 245, 255 }  
#define COLOR_CLYDE       (Color){ 255, 235, 175, 255 }  


#define COLOR_BTN_BG      (Color){ 255, 182, 193, 255 }  
#define COLOR_BTN_HOVER   (Color){ 255, 143, 177, 255 }  

typedef struct Entity {
    Vector2 position;      
    Vector2 direction;     
    Vector2 nextDirection; 
    float speed;           
    Color color;
    int type; 
} Entity;

#endif