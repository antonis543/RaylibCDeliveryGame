#include"raylib.h"

#include"drawTextures.c"

int main(void) {
  
  InitWindow(1000, 550, "RaylibProjectAuth");
  SetTargetFPS(60);

  RenderTexture2D deliveryBike = LoadRenderTexture(32, 32);

  DrawDeliveryBike(deliveryBike);    

  int keyPressed = 0;

  Rectangle bikeSource = {
    0, 0, deliveryBike.texture.width, deliveryBike.texture.height
  };

  Rectangle bikePos = {GetScreenWidth() / 2, GetScreenHeight() / 2, 128, 128};

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(BLACK);

    // move forward
    if (IsKeyDown(KEY_W)) {
      bikePos.y -= 2;
    }
    // move backward (S)
    if (IsKeyDown(KEY_S)) {
      bikePos.y += 2;
    }
    // move left (A)
    if(IsKeyDown(KEY_A)) {
      bikePos.x -= 2;
    }
    // move right (D)
    if (IsKeyDown(KEY_D)) {
      bikePos.x += 2;
    }

    DrawTexturePro(deliveryBike.texture, bikeSource, bikePos, (Vector2) { 64, 64 }, 180, WHITE);

    EndDrawing();
  }

  UnloadRenderTexture(deliveryBike);
  CloseWindow();

  return 0;
}