#include <math.h>
#include <stdlib.h>

#define TILE_SIZE 64
#define MAP_WIDTH 24
#define MAP_HEIGHT 24

// Assuming a simple map representation where 0 is empty space and 1 is a wall
const int map[MAP_HEIGHT][MAP_WIDTH] = {
    // Map data...
};

typedef struct {
    double x, y; // Player position
    double dirX, dirY; // Direction vector of the ray
} Player;

double findHorizontalIntersection(Player player, double rayAngle) {
    double rayPosX = player.x;
    double rayPosY = player.y;
    double rayDirX = cos(rayAngle);
    double rayDirY = sin(rayAngle);

    // Calculate the ray's initial position on the nearest horizontal grid line
    double nextX = rayPosX;
    double nextY = floor(rayPosY / TILE_SIZE) * TILE_SIZE;

    // Determine the direction to step in x and y (either -1, 0, or 1)
    int stepX = (rayDirX < 0) ? -1 : 1;
    int stepY = (rayDirY < 0) ? -1 : 1;

    // Calculate step sizes
    double deltaX = TILE_SIZE / rayDirX;
    double deltaY = TILE_SIZE;

    // Adjust nextY and deltaX if rayDirY is negative
    if (rayDirY < 0) {
        nextY -= TILE_SIZE;
        deltaX = -deltaX;
    }

    // Raycasting loop
    while (nextX >= 0 && nextX < MAP_WIDTH * TILE_SIZE && nextY >= 0 && nextY < MAP_HEIGHT * TILE_SIZE) {
        int mapX = (int)floor(nextX / TILE_SIZE);
        int mapY = (int)floor(nextY / TILE_SIZE);

        // Check if the ray has hit a wall block
        if (map[mapY][mapX] == 1) {
            // Calculate and return the distance from the player to the point of intersection
            return hypot(nextX - player.x, nextY - player.y);
        }

        // Move to the next horizontal intersection
        nextX += deltaX;
        nextY += stepY * deltaY;
    }

    // Return a large number if no intersection is found
    return 1;
}

double findVerticalIntersection(Player player, double rayAngle) {
    double rayPosX = player.x;
    double rayPosY = player.y;
    double rayDirX = cos(rayAngle);
    double rayDirY = sin(rayAngle);

    // Calculate the ray's initial position on the nearest vertical grid line
    double nextX = floor(rayPosX / TILE_SIZE) * TILE_SIZE;
    double nextY = rayPosY;

    // Determine the direction to step in x and y (either -1, 0, or 1)
    int stepX = (rayDirX < 0) ? -1 : 1;
    int stepY = (rayDirY < 0) ? -1 : 1;

    // Calculate step sizes
    double deltaX = TILE_SIZE;
    double deltaY = TILE_SIZE / rayDirY;

    // Adjust nextX and deltaY if rayDirX is negative
    if (rayDirX < 0) {
        nextX -= TILE_SIZE;
        deltaY = -deltaY;
    }

    // Raycasting loop
    while (nextX >= 0 && nextX < MAP_WIDTH * TILE_SIZE && nextY >= 0 && nextY < MAP_HEIGHT * TILE_SIZE) {
        int mapX = (int)floor(nextX / TILE_SIZE);
        int mapY = (int)floor(nextY / TILE_SIZE);

        // Check if the ray has hit a wall block
        if (map[mapY][mapX] == 1) {
            // Calculate and return the distance from the player to the point of intersection
            return hypot(nextX - player.x, nextY - player.y);
        }

        // Move to the next vertical intersection
        nextX += stepX * deltaX;
        nextY += deltaY;
    }

    // Return a large number if no intersection is found
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

        // Increment the ray angle for the next pixel
        rayAngle += angleIncrement;
    }
}

void render(Player player, int x, double distance) {
    // This is a simple example of a render function
    // You would typically use a graphics library to render the pixel
    // For this example, we'll just print the distance to the console
    printf("Rendering pixel at x: %d, distance: %f\n", x, distance);
}