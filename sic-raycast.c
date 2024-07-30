#include <math.h>
#include <stdlib.h>

#define TILE_SIZE 64
#define MAP_WIDTH 24
#define MAP_HEIGHT 24

typedef struct {
    double x, y; 
    double dirX, dirY;
} Player;

double findHorizontalIntersection(Player player, double rayAngle) 
{
    double rayPosX = player.x;
    double rayPosY = player.y;
    double rayDirX = cos(rayAngle);
    double rayDirY = sin(rayAngle);

    double nextX = rayPosX;
    double nextY = floor(rayPosY / TILE_SIZE) * TILE_SIZE;

    int stepX = (rayDirX < 0) ? -1 : 1;
    int stepY = (rayDirY < 0) ? -1 : 1;
    double deltaX = TILE_SIZE / rayDirX;
    double deltaY = TILE_SIZE;
    if (rayDirY < 0) {
        nextY -= TILE_SIZE;
        deltaX = -deltaX;
    }
    while (nextX >= 0 && nextX < MAP_WIDTH * TILE_SIZE && nextY >= 0 && nextY < MAP_HEIGHT * TILE_SIZE) {
        int mapX = (int)floor(nextX / TILE_SIZE);
        int mapY = (int)floor(nextY / TILE_SIZE);
        if (map[mapY][mapX] == 1)
            return hypot(nextX - player.x, nextY - player.y);
        nextX += deltaX;
        nextY += stepY * deltaY;
    }
    return 1;
}

double findVerticalIntersection(Player player, double rayAngle) {
    double rayPosX = player.x;
    double rayPosY = player.y;
    double rayDirX = cos(rayAngle);
    double rayDirY = sin(rayAngle);

    double nextX = floor(rayPosX / TILE_SIZE) * TILE_SIZE;
    double nextY = rayPosY;
    int stepX = (rayDirX < 0) ? -1 : 1;
    int stepY = (rayDirY < 0) ? -1 : 1;
    double deltaX = TILE_SIZE;
    double deltaY = TILE_SIZE / rayDirY;
    if (rayDirX < 0) {
        nextX -= TILE_SIZE;
        deltaY = -deltaY;
    }
    while (nextX >= 0 && nextX < MAP_WIDTH * TILE_SIZE && nextY >= 0 && nextY < MAP_HEIGHT * TILE_SIZE) {
        int mapX = (int)floor(nextX / TILE_SIZE);
        int mapY = (int)floor(nextY / TILE_SIZE);
        if (map[mapY][mapX] == 1)
            return hypot(nextX - player.x, nextY - player.y);
        nextX += stepX * deltaX;
        nextY += deltaY;
    }
    return 1;
}

void raycast(Player player, int screenWidth) {
    double rayAngle = player.angle - (player.fov / 2);
    double angleIncrement = player.fov / screenWidth;

    for (int i = 0; i < screenWidth; i++) {
        double horizontalDistance = findHorizontalIntersection(player, rayAngle);
        double verticalDistance = findVerticalIntersection(player, rayAngle);

        double distance = (horizontalDistance < verticalDistance) ? horizontalDistance : verticalDistance;
        render(player, i, distance);
        rayAngle += angleIncrement;
    }
}

void render(Player player, int x, double distance) {
    printf("Rendering pixel at x: %d, distance: %f\n", x, distance);
}