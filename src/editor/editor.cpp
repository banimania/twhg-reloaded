#include "editor.hpp"
#include <iostream>
#include <raylib.h>
#include <rlgl.h>
#include "../utils/fonts.hpp"
#include "../utils/textures.hpp"

void Editor::initWidgets() {
  init = true;
}

void Editor::tick() {
  if (!init) initWidgets();

  if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) || IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
    Vector2 mouseVec = {(float) GetMouseX(), (float) GetMouseY()};
    if (CheckCollisionPointRec(mouseVec, {120, 83, 32, 32})) {
      zLayer--;
    } else if (CheckCollisionPointRec(mouseVec, {185, 83, 32, 32})) {
      zLayer++;
    }
  }

  if (zLayer > 9) zLayer = 9;
  else if (zLayer < 0) zLayer = 0;

  if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
    camera.target = {camera.target.x - GetMouseDelta().x, camera.target.y - GetMouseDelta().y};
  }

  float wheel = GetMouseWheelMove();
  if (wheel != 0) {
    Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

    camera.offset = GetMousePosition();

    camera.target = mouseWorldPos;

    float scaleFactor = 1.0f + (0.25f * fabsf(wheel));
    if (wheel < 0) scaleFactor = 1.0f / scaleFactor;
    camera.zoom = std::clamp(camera.zoom * scaleFactor, 0.7f, 2.0f);
  }

  BeginMode2D(camera);
  
  level->background.tick(camera);

  tickConveyorManager();

  level->camera = camera;
  for (GameObject* gameObject : level->gameObjects) {
    gameObject->tick(&level->player);
  }

  drawGrid();

  DrawRectangle(level->startX, level->startY, 30, 30, playerColorOutline);
  DrawRectangle(level->startX + 5, level->startY + 5, 20, 20, playerColorFill);

  EndMode2D();
  
  level->hud.tickEditor();
  drawOutline();

  buildButton.tick();
  editButton.tick();

  //use rlScalef for scaling what the fuck am i doing lol

  if (mode == BUILD) {

    if (CheckCollisionPointRec(GetMousePosition(), {240, 80, SCREEN_WIDTH - 240, SCREEN_HEIGHT - 80})) {
      if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && selectedObject != -1) {
        Vector2 pos = GetScreenToWorld2D(GetMousePosition(), camera);
        GameObject* object;

        switch (selectedObject) {
          case 1:
            object = new WallBlock({(float) ((int) (pos.x / 40) * 40), (float) ((int) (pos.y / 40) * 40)}, level);
            break;
          case 2:
            object = new BackgroundBlock({(float) ((int) (pos.x / 40) * 40), (float) ((int) (pos.y / 40) * 40)}, level);
            break;
          case 3:
            object = new Enemy({(float) ((int) (pos.x / 40) * 40) + 20, (float) ((int) (pos.y / 40) * 40) + 20}, 10, level);
            break;
          case 4:
            object = new Coin({(float) ((int) (pos.x / 40) * 40) + 20, (float) ((int) (pos.y / 40) * 40) + 20}, 10, level);
            break;
          case 5:
            object = new Key({(float) ((int) (pos.x / 40) * 40) + 20, (float) ((int) (pos.y / 40) * 40) + 20}, 1, level);
            break;
          case 6:
            object = new KeyBlock({(float) ((int) (pos.x / 40) * 40), (float) ((int) (pos.y / 40) * 40)}, 1, level);
            break;
          case 7:
            object = new Conveyor({(float) ((int) (pos.x / 40) * 40), (float) ((int) (pos.y / 40) * 40)}, RIGHT, level);
            break;
          case 8:
            object = new Checkpoint({(float) ((int) (pos.x / 40) * 40), (float) ((int) (pos.y / 40) * 40)}, level);
            break;
          case 9:
            level->startX = (float) ((int) (pos.x / 40) * 40) + 5;
            level->startY = (float) ((int) (pos.y / 40) * 40) + 5;
            break;
        }

        if (object != nullptr) {
          level->gameObjects.push_back(object);
        }
      }
    }

    rlPushMatrix();
    buildWallblockButton.tick();
    float difHalf = (buildWallblockButton.rect.width * buildWallblockButton.scale - buildWallblockButton.rect.width) / 2.0f;
    rlTranslatef(wallBlock.rect.x - difHalf, wallBlock.rect.y - difHalf, 0.0f);
    rlScalef(buildWallblockButton.scale, buildWallblockButton.scale, 1.0f);
    rlTranslatef(-wallBlock.rect.x, -wallBlock.rect.y, 0.0f);
    wallBlock.tick(&level->player);
    rlPopMatrix();

    /*buildWallblockButton.tick();
    wallblock.rect = {20 - (buildwallblockbutton.rect.width * buildwallblockbutton.scale - buildwallblockbutton.rect.width) / 2.0f,
      250 - (buildwallblockbutton.rect.height * buildwallblockbutton.scale - buildwallblockbutton.rect.height) / 2.0f,
      40 * buildwallblockbutton.scale,
      40 * buildwallblockbutton.scale};
    wallBlock.tick(&level->player);*/

    rlPushMatrix();
    buildBackgroundBlockButton.tick();
    difHalf = (buildBackgroundBlockButton.rect.width * buildBackgroundBlockButton.scale - buildBackgroundBlockButton.rect.width) / 2.0f;
    rlTranslatef(backgroundBlock.rect.x - difHalf, backgroundBlock.rect.y - difHalf, 0.0f);
    rlScalef(buildBackgroundBlockButton.scale, buildBackgroundBlockButton.scale, 1.0f);
    rlTranslatef(-backgroundBlock.rect.x, -backgroundBlock.rect.y, 0.0f);
    backgroundBlock.tick(&level->player);
    rlPopMatrix();

    /*buildBackgroundBlockButton.tick();
    backgroundBlock.rect = {100 - (buildBackgroundBlockButton.rect.width * buildBackgroundBlockButton.scale - buildBackgroundBlockButton.rect.width) / 2.0f,
      250 - (buildBackgroundBlockButton.rect.height * buildBackgroundBlockButton.scale - buildBackgroundBlockButton.rect.height) / 2.0f,
      40 * buildBackgroundBlockButton.scale,
      40 * buildBackgroundBlockButton.scale};
    backgroundBlock.tick(&level->player);*/


    rlPushMatrix();
    buildEnemyButton.tick();
    difHalf = (buildEnemyButton.rect.width * buildEnemyButton.scale - buildEnemyButton.rect.width) / 2.0f;
    rlTranslatef(enemy.rect.x - difHalf * 0.7, enemy.rect.y - difHalf * 0.7, 0.0f);
    rlScalef(buildEnemyButton.scale, buildEnemyButton.scale, 1.0f);
    rlTranslatef(-enemy.rect.x, -enemy.rect.y, 0.0f);
    enemy.tick(&level->player);
    rlPopMatrix();

    /*buildEnemyButton.tick();
    enemy.rect = {190 - (buildEnemyButton.rect.width * buildEnemyButton.scale - buildEnemyButton.rect.width) / 2.0f,
      260 - (buildEnemyButton.rect.height * buildEnemyButton.scale - buildEnemyButton.rect.height) / 2.0f,
      20 * buildEnemyButton.scale,
      20 * buildEnemyButton.scale};
    enemy.radius = 10.0f * buildEnemyButton.scale;
    enemy.tick(&level->player);*/
    
    rlPushMatrix();
    buildCoinButton.tick();
    difHalf = (buildCoinButton.rect.width * buildCoinButton.scale - buildCoinButton.rect.width) / 2.0f;
    rlTranslatef(coin.rect.x - difHalf * 0.7, coin.rect.y - difHalf * 0.7, 0.0f);
    rlScalef(buildCoinButton.scale, buildCoinButton.scale, 1.0f);
    rlTranslatef(-coin.rect.x, -coin.rect.y, 0.0f);
    coin.tick(&level->player);
    rlPopMatrix();

    /*buildCoinButton.tick();
    coin.rect = {30 - (buildCoinButton.rect.width * buildCoinButton.scale - buildCoinButton.rect.width) / 2.0f,
      340 - (buildCoinButton.rect.height * buildCoinButton.scale - buildCoinButton.rect.height) / 2.0f,
      20 * buildCoinButton.scale,
      20 * buildCoinButton.scale};
    coin.radius = 10.0f * buildCoinButton.scale;
    coin.tick(&level->player);*/
    
    rlPushMatrix();
    buildKeyButton.tick();
    difHalf = (buildKeyButton.rect.width * buildKeyButton.scale - buildKeyButton.rect.width) / 2.0f;
    rlTranslatef(key.rect.x - difHalf * 0.7, key.rect.y - difHalf * 0.7, 0.0f);
    rlScalef(buildKeyButton.scale, buildKeyButton.scale, 1.0f);
    rlTranslatef(-key.rect.x, -key.rect.y, 0.0f);
    key.tick(&level->player);
    rlPopMatrix();

    rlPushMatrix();
    buildKeyBlockButton.tick();
    difHalf = (buildKeyBlockButton.rect.width * buildKeyBlockButton.scale - buildKeyBlockButton.rect.width) / 2.0f;
    rlTranslatef(keyBlock.rect.x - difHalf, keyBlock.rect.y - difHalf, 0.0f);
    rlScalef(buildKeyBlockButton.scale, buildKeyBlockButton.scale, 1.0f);
    rlTranslatef(-keyBlock.rect.x, -keyBlock.rect.y, 0.0f);
    keyBlock.tick(&level->player);
    rlPopMatrix();
   
    //In conveyor.cpp we use rlpushmatrix so we cant use this here TODO: fix brain issue
    /*rlPushMatrix();
    buildConveyorButton.tick();
    difHalf = (buildConveyorButton.rect.width * buildConveyorButton.scale - buildConveyorButton.rect.width) / 2.0f;
    rlTranslatef(conveyor.rect.x - difHalf, conveyor.rect.y - difHalf, 0.0f);
    rlScalef(buildConveyorButton.scale, buildConveyorButton.scale, 1.0f);
    rlTranslatef(-conveyor.rect.x, -conveyor.rect.y, 0.0f);
    conveyor.tick(&level->player);
    rlPopMatrix();*/
    buildConveyorButton.tick();
    conveyor.isEditorSample = true;
    conveyor.rect = {20 - (buildConveyorButton.rect.width * buildConveyorButton.scale - buildConveyorButton.rect.width) / 2.0f,
      410 - (buildConveyorButton.rect.height * buildConveyorButton.scale - buildConveyorButton.rect.height) / 2.0f,
      40 * buildConveyorButton.scale,
      40 * buildConveyorButton.scale};
    conveyor.tick(&level->player);  
    
    rlPushMatrix();
    buildCheckpointButton.tick();
    difHalf = (buildCheckpointButton.rect.width * buildCheckpointButton.scale - buildCheckpointButton.rect.width) / 2.0f;
    rlTranslatef(checkpoint.rect.x - difHalf, checkpoint.rect.y - difHalf, 0.0f);
    rlScalef(buildCheckpointButton.scale, buildCheckpointButton.scale, 1.0f);
    rlTranslatef(-checkpoint.rect.x, -checkpoint.rect.y, 0.0f);
    checkpoint.tick(&level->player);
    rlPopMatrix();

    rlPushMatrix();
    buildPlayerButton.tick();
    difHalf = (buildPlayerButton.rect.width * buildPlayerButton.scale - buildPlayerButton.rect.width) / 2.0f;
    Vector2 playerPos = {185, 415};
    rlTranslatef(playerPos.x - difHalf, playerPos.y - difHalf, 0.0f);
    rlScalef(buildPlayerButton.scale, buildPlayerButton.scale, 1.0f);
    rlTranslatef(-playerPos.x, -playerPos.y, 0.0f);
    DrawRectangle(playerPos.x, playerPos.y, 30, 30, playerColorOutline);
    DrawRectangle(playerPos.x + 5, playerPos.y + 5, 20, 20, playerColorFill);
    rlPopMatrix();
  }

  configButton.tick();
  playButton.tick();
}

void Editor::drawGrid() {
  int areaWidth = 1280;
  int areaHeight = 640;

  int ni = camera.target.x / areaWidth;
  int nj = camera.target.y / areaHeight;

  for (int i = -2 - abs(ni); i <= 2 + abs(ni); i++) {
    for (int j = -2 - abs(nj); j <= 2 + abs(nj); j++) {
      DrawLineEx({(float) i * areaWidth, (float) j * areaHeight + 80}, {(float) (i + 1) * areaWidth, (float) j * areaHeight + 80}, 5.0f, RED);
      DrawLineEx({(float) i * areaWidth, (float) j * areaHeight + 80}, {(float) i * areaWidth, (float) (j + 1) * areaHeight + 80}, 5.0f, RED);
    }
  }
}

void Editor::drawOutline() {
  DrawRectangle(0, 80, 240, SCREEN_HEIGHT, editorUIColor);
  DrawRectangleGradientH(0, 80, 120, 40, editorGradient1Color, editorGradient2Color);
  DrawRectangleGradientH(120, 80, 120, 40, editorGradient2Color, editorGradient1Color);

  DrawOutlinedText(editorFontBold, "Layer", 30, 80, 35, WHITE, 2, BLACK);
  DrawOutlinedText(editorFontBold, zLayer == 0 ? "All" : std::to_string(zLayer).c_str(), zLayer == 0 ? 155 : 160, zLayer == 0 ? 86 : 80, zLayer == 0 ? 25 : 35, WHITE, 2, BLACK);

  DrawTextureEx(arrowLeftTexture, {120, 83}, 0.0f, 0.1f, RAYWHITE);
  DrawTextureEx(arrowRightTexture, {185, 83}, 0.0f, 0.1f, RAYWHITE);

  DrawRectangleGradientH(0, 190, 120, 40, editorGradient1Color, editorGradient2Color);
  DrawRectangleGradientH(120, 190, 120, 40, editorGradient2Color, editorGradient1Color);
  
  DrawOutlinedCenteredText(editorFontBold, mode == BUILD ? "OBJECTS" : "TOOLS", {0, 190, 240, 40}, 35, WHITE, 2, BLACK);

  DrawRectangleGradientH(0, SCREEN_HEIGHT - 100, 120, 10, editorGradient1Color, editorGradient2Color);
  DrawRectangleGradientH(120, SCREEN_HEIGHT - 100, 120, 10, editorGradient2Color, editorGradient1Color);
}

void Editor::buildModeButton() {
  mode = BUILD;
  buildButton.setSelected(true);
  editButton.setSelected(false);
}

void Editor::buildEditButton() {
  mode = EDIT;
  buildButton.setSelected(false);
  editButton.setSelected(true);
}

void Editor::selectWallblockButton() {
  selectedObject = 1;
  deselectAll();
  buildWallblockButton.setSelected(true);
}

void Editor::selectBackgroundBlockButton() {
  selectedObject = 2;
  deselectAll();
  buildBackgroundBlockButton.setSelected(true);
}

void Editor::selectEnemyButton() {
  selectedObject = 3;
  deselectAll();
  buildEnemyButton.setSelected(true);
}

void Editor::selectCoinButton() {
  selectedObject = 4;
  deselectAll();
  buildCoinButton.setSelected(true);
}

void Editor::selectKeyButton() {
  selectedObject = 5;
  deselectAll();
  buildKeyButton.setSelected(true);
}

void Editor::selectKeyBlockButton() {
  selectedObject = 6;
  deselectAll();
  buildKeyBlockButton.setSelected(true);
}

void Editor::selectConveyorButton() {
  selectedObject = 7;
  deselectAll();
  buildConveyorButton.setSelected(true);
}

void Editor::selectCheckpointButton() {
  selectedObject = 8;
  deselectAll();
  buildCheckpointButton.setSelected(true);
}

void Editor::selectPlayerButton() {
  selectedObject = 9;
  deselectAll();
  buildPlayerButton.setSelected(true);
}

void Editor::deselectAll() {
  buildWallblockButton.setSelected(false);
  buildBackgroundBlockButton.setSelected(false);
  buildEnemyButton.setSelected(false);
  buildCoinButton.setSelected(false);
  buildKeyButton.setSelected(false);
  buildKeyBlockButton.setSelected(false);
  buildConveyorButton.setSelected(false);
  buildCheckpointButton.setSelected(false);
  buildPlayerButton.setSelected(false);
}
