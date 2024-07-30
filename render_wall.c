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

