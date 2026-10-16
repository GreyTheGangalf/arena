// Arena — Stage 0: procedural game loop.
// Everything lives in main(): state is a few local variables, and each frame
// runs the same three steps in order: input -> update -> draw.
// Stage 1 adds enemies to this file; Stage 2 rewrites it with classes.

#include <algorithm>
#include <cmath>

#include "raylib.h"

int main() {
    constexpr int kScreenWidth = 1280;
    constexpr int kScreenHeight = 720;
    constexpr float kPlayerRadius = 16.0F;
    constexpr float kPlayerSpeed = 280.0F;  // pixels per second, not per frame

    InitWindow(kScreenWidth, kScreenHeight, "Arena");
    SetTargetFPS(60);

    // --- Game state ---
    Vector2 player{kScreenWidth / 2.0F, kScreenHeight / 2.0F};

    while (!WindowShouldClose()) {
        // dt makes movement frame-rate independent: at 30 FPS each step is twice as big.
        const float dt = GetFrameTime();

        // --- Input ---
        Vector2 dir{0.0F, 0.0F};
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) dir.x += 1.0F;
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  dir.x -= 1.0F;
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  dir.y += 1.0F;
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    dir.y -= 1.0F;

        // Without normalizing, diagonal movement would be ~1.41x faster.
        const float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (len > 0.0F) {
            dir.x /= len;
            dir.y /= len;
        }

        // --- Update ---
        player.x += dir.x * kPlayerSpeed * dt;
        player.y += dir.y * kPlayerSpeed * dt;
        player.x = std::clamp(player.x, kPlayerRadius, kScreenWidth - kPlayerRadius);
        player.y = std::clamp(player.y, kPlayerRadius, kScreenHeight - kPlayerRadius);

        // --- Draw ---
        BeginDrawing();
        ClearBackground(Color{18, 18, 24, 255});
        DrawCircleV(player, kPlayerRadius, Color{90, 200, 250, 255});

        // Frame time is the metric we will track through every stage.
        DrawFPS(10, 10);
        DrawText(TextFormat("frame: %.2f ms", static_cast<double>(dt) * 1000.0), 10, 34, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
