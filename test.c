#include "raylib.h"   // Raylib header
int main() {
   Font font = GetFontDefault();
   Vector2 pos = {0, 0};
   Vector2 origin = {0, 0};

   InitWindow(800, 600, "test");
   Color nice_color = {0,0,0,255};

   while (!WindowShouldClose()) {
      BeginDrawing();
      DrawTextPro(font, "Hello World!", pos, origin, 0.0f, 0.0f, 0.0f, nice_color);
      EndDrawing();
   }
   return 0;
}
