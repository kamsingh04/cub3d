void renderWall(int x, int y, int height, int color) {
    for (int i = 0; i < height; i++) {
        render(x, y + i, color);
    }
}

void renderWalls(Player player, int screenWidth) {
    for (int x = 0; x < screenWidth; x++) {
        double distance = raycast(player, x);
        int wallHeight = (int)(screenHeight / distance);
        int wallY = (screenHeight / 2) - (wallHeight / 2);
        if (map[x / TILE_SIZE][wallY / TILE_SIZE] == 1) {
            renderWall(x, wallY, wallHeight, 0xFF0000); // Red color
        }
    }
}


// In this example, the renderWall function draws a vertical line on the screen at
//  position (x, y) with a height of height pixels and a color of color. 
//  The renderWalls function iterates through the map array and finds the
//   positions of the walls, calculates their height, and calls renderWall
//    to draw them on the screen.

// Coloring the wall

// To color the wall, you can use a color value in the render function. In this example, we use the color 0xFF0000 (red) to draw the wall. 
// You can change this value to any other color you like.