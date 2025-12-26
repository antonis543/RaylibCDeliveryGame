#include"raylib.h"

#include"drawTextures.c"

const int INITIAL_WINDOW_WIDTH = 1000;
const int INITIAL_WINDOW_HEIGHT = 550;
const int DELIVERY_BIKE_RENDER_SIZE = 32;
const int DELIVERY_BIKE_SCALED_SIZE = 128;
const Color BACKGROUND_COLOR = DARKGRAY;
bool showOrders=false;
int count=0; //Number of order (Αριθμός παραγγελίας)

int main(void) {
  
  InitWindow(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, "RaylibProjectAuth");
  Texture2D Texture2DBackground = LoadTexture("map.jpg"); 
  SetTargetFPS(60);

  RenderTexture2D deliveryBikeRender = LoadRenderTexture(DELIVERY_BIKE_RENDER_SIZE, DELIVERY_BIKE_RENDER_SIZE);

  DrawDeliveryBike(deliveryBikeRender); 
  
  Rectangle bikeSource = {
    0, 0, deliveryBikeRender.texture.width, deliveryBikeRender.texture.height
  };
  
  Rectangle deliveryBike = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f, DELIVERY_BIKE_SCALED_SIZE, DELIVERY_BIKE_SCALED_SIZE};
  
  // initialize camera
  Camera2D cam = {0};
  cam.offset = (Vector2){GetScreenWidth() / 2.0f,GetScreenHeight() / 2.0f};
  cam.zoom = 1;
  cam.rotation = 0;

  while (!WindowShouldClose()) {
    BeginDrawing();

      ClearBackground(DARKGRAY);
    
      /*** MOVEMENT ***/ 
      // move forward
      if (IsKeyDown(KEY_W)) {
        deliveryBike.y -= 2;
      }
      // move backward (S)
      if (IsKeyDown(KEY_S)) {
        deliveryBike.y += 2;
      }
      // move left (A)
      if(IsKeyDown(KEY_A)) {
        deliveryBike.x -= 2;
      }
      // move right (D)
      if (IsKeyDown(KEY_D)) {
        deliveryBike.x += 2;
      }

      /*** CAMERA ***/
      // Set camera to follow the bike
      cam.target.x = deliveryBike.x;
      cam.target.y = deliveryBike.y;
      
      // Only if 0.8 <= cam.zoom <= 1.4 we want to change cam.zoom. Otherwise,
      // bike will become very small/big.
      if (cam.zoom >= 0.6 && GetMouseWheelMove() < 0) {
        cam.zoom -= 0.2;
      } else if (cam.zoom <= 1.6 && GetMouseWheelMove() > 0) {
        cam.zoom += 0.2;
      }
      
      BeginMode2D(cam);
        
        DrawTexture (Texture2DBackground, 0, 0, WHITE);
        Draw8BitRoad();
        DrawTexturePro(deliveryBikeRender.texture, bikeSource, deliveryBike, (Vector2) { DELIVERY_BIKE_SCALED_SIZE / 2, DELIVERY_BIKE_SCALED_SIZE / 2 }, 180, WHITE);
    
      EndMode2D();
      
      if (IsKeyPressed(KEY_K)) {
            showOrders = !showOrders;
      }
      
      if (showOrders)   {
          DrawRectangle (10, 10, 140, 170, WHITE);
          DrawText("Fuck PAOK", 15, 15 + count*25, 20, BLACK);
      }
    EndDrawing();
  }
  
  UnloadTexture (Texture2DBackground);
  UnloadRenderTexture(deliveryBikeRender);
  CloseWindow();

  return 0;
}
