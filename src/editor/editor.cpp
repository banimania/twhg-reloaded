#include "editor.hpp"
#include <algorithm>
#include <raylib.h>
#include <rlgl.h>
#include "../utils/fonts.hpp"
#include "../utils/textures.hpp"
#include <iostream>

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
    camera.target = {camera.target.x - GetMouseDelta().x / camera.zoom, camera.target.y - GetMouseDelta().y / camera.zoom};
  }

  float wheel = GetMouseWheelMove();
  if (wheel != 0) {
    Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

    camera.offset = GetMousePosition();

    camera.target = mouseWorldPos;

    float scaleFactor = 1.0f + (0.25f * fabsf(wheel));
    if (wheel < 0) scaleFactor = 1.0f / scaleFactor;
    camera.zoom = std::clamp(camera.zoom * scaleFactor, 0.7f, 2.5f);
  }

  for (WallBlock* wallBlock : getAllGameObjectsInLayer<WallBlock>(zLayer)) {
    wallBlock->updateWallBlock(getAllGameObjectsInLayer<WallBlock>(zLayer));
  }

  BeginMode2D(camera);
  
  level->background.tick(camera);

  tickConveyorManager();

  level->camera = camera;
  for (GameObject* gameObject : level->gameObjects) {
    gameObject->tick(&level->player);
    if (std::find(selectedObjects.begin(), selectedObjects.end(), gameObject) != selectedObjects.end()) {
      if (Key* key = dynamic_cast<Key*>(gameObject)) {
        DrawTextureEx(keyTexture, {gameObject->rect.x - 5, gameObject->rect.y - 5}, 0.0f, 0.06f, editorSelectColor);
      } else if (Enemy* enemy = dynamic_cast<Enemy*>(gameObject)) {
        DrawCircle(enemy->rect.x + 10, enemy->rect.y + 10, 10.0f, editorSelectColor);
      } else if (Coin* coin = dynamic_cast<Coin*>(gameObject)) {
        DrawCircle(coin->rect.x + 10, coin->rect.y + 10, 10.0f, editorSelectColor);
      } else DrawRectangleRec(gameObject->rect, editorSelectColor);
    }
  }

  drawGrid();

  DrawRectangle(level->startX, level->startY, 30, 30, playerColorOutline);
  DrawRectangle(level->startX + 5, level->startY + 5, 20, 20, playerColorFill);

  EndMode2D();
  

  Rectangle selection = {std::min(selx1, selx2), std::min(sely1, sely2), std::max(selx1, selx2) - std::min(selx1, selx2), std::max(sely1, sely2) - std::min(sely1, sely2)};

  DrawRectangleRec(selection, editorSelectColor);
  DrawRectangleRec({selection.x, selection.y, selection.width, 5}, editorSelectColor);
  DrawRectangleRec({selection.x, selection.y + selection.height - 5, selection.width, 5}, editorSelectColor);
  DrawRectangleRec({selection.x, selection.y + 5, 5, selection.height - 10}, editorSelectColor);
  DrawRectangleRec({selection.x + selection.width - 5, selection.y + 5, 5, selection.height - 10}, editorSelectColor);

  level->hud.tickEditor();
  drawOutline();

  buildButton.tick();
  editButton.tick();

  //use rlScalef for scaling what the fuck am i doing lol

  deleteTimer += GetFrameTime();

  if (mode == BUILD) {

    selectedObjects = {};

    if (CheckCollisionPointRec(GetMousePosition(), {240, 80, SCREEN_WIDTH - 240, SCREEN_HEIGHT - 80})) {
      Vector2 pos = GetScreenToWorld2D(GetMousePosition(), camera);
      if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && selectedObject != -1) {
        GameObject* object;

        switch (selectedObject) {
          case 1:
            object = new WallBlock({(float) ((int) (pos.x / 40) * 40), (float) ((int) (pos.y / 40) * 40)}, level, zLayer);
            break;
          case 2:
            object = new BackgroundBlock({(float) ((int) (pos.x / 40) * 40), (float) ((int) (pos.y / 40) * 40)}, level, zLayer);
            break;
          case 3:
            object = new Enemy({(float) ((int) (pos.x / 40) * 40) + 20, (float) ((int) (pos.y / 40) * 40) + 20}, 10, level, zLayer);
            break;
          case 4:
            object = new Coin({(float) ((int) (pos.x / 40) * 40) + 20, (float) ((int) (pos.y / 40) * 40) + 20}, 10, level, zLayer);
            break;
          case 5:
            object = new Key({(float) ((int) (pos.x / 40) * 40) + 20, (float) ((int) (pos.y / 40) * 40) + 20}, 1, level, zLayer);
            break;
          case 6:
            object = new KeyBlock({(float) ((int) (pos.x / 40) * 40), (float) ((int) (pos.y / 40) * 40)}, 1, level, zLayer);
            break;
          case 7:
            object = new Conveyor({(float) ((int) (pos.x / 40) * 40), (float) ((int) (pos.y / 40) * 40)}, RIGHT, level, zLayer);
            break;
          case 8:
            object = new Checkpoint({(float) ((int) (pos.x / 40) * 40), (float) ((int) (pos.y / 40) * 40)}, false, level, zLayer);
            break;
          case 9:
            level->startX = (float) ((int) (pos.x / 40) * 40) + 5;
            level->startY = (float) ((int) (pos.y / 40) * 40) + 5;
            object = nullptr;
            break;
        }

        //if (selectedObject == 1 && !getGameObjectsInPos({object->rect.x, object->rect.y}, zLayer).empty()) object = nullptr;
        if (selectedObject == 1 && !getGameObjectsInPosAndLayer<WallBlock>({object->rect.x, object->rect.y}, zLayer).empty()) object = nullptr;
        else if (selectedObject == 2 && !getGameObjectsInPosAndLayer<BackgroundBlock>({object->rect.x, object->rect.y}, zLayer).empty()) object = nullptr;
        else if (selectedObject == 3 && !getGameObjectsInPosAndLayer<Enemy>({object->rect.x, object->rect.y}, zLayer).empty()) object = nullptr;
        else if (selectedObject == 4 && !getGameObjectsInPosAndLayer<Coin>({object->rect.x, object->rect.y}, zLayer).empty()) object = nullptr;
        else if (selectedObject == 5 && !getGameObjectsInPosAndLayer<Key>({object->rect.x, object->rect.y}, zLayer).empty()) object = nullptr;
        else if (selectedObject == 6 && !getGameObjectsInPosAndLayer<KeyBlock>({object->rect.x, object->rect.y}, zLayer).empty()) object = nullptr;
        else if (selectedObject == 7 && !getGameObjectsInPosAndLayer<Conveyor>({object->rect.x, object->rect.y}, zLayer).empty()) object = nullptr;
        else if (selectedObject == 8 && !getGameObjectsInPosAndLayer<Checkpoint>({object->rect.x, object->rect.y}, zLayer).empty()) object = nullptr;

        if (object != nullptr) {
          level->gameObjects.push_back(object);
        }
      } else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        Vector2 deletionPos = {(float) ((int) (pos.x / 40) * 40), (float) ((int) (pos.y / 40) * 40)};
        if ((lastDeleted.x != deletionPos.x || lastDeleted.y != deletionPos.y) || (lastDeleted.x == deletionPos.x && lastDeleted.y == deletionPos.y && deleteTimer > deleteTime)) {
          deleteTimer = 0.0f;
          lastDeleted = deletionPos; 
          std::vector<GameObject*> gameObjects = getAllGameObjectsInPos(deletionPos, zLayer);

          if (gameObjects.empty()) {
            gameObjects = getAllGameObjectsInPos({deletionPos.x + 10, deletionPos.y + 10}, zLayer);
          }

          if (!gameObjects.empty()) {
            level->gameObjects.erase(std::remove(level->gameObjects.begin(), level->gameObjects.end(), gameObjects.at(gameObjects.size() - 1)));
          }
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
  } else if (mode == EDIT) {
    editRightButton.tick();
    editLeftButton.tick();
    editUpButton.tick();
    editDownButton.tick();
    
    editSmallRightButton.tick();
    editSmallUpButton.tick();
    editSmallLeftButton.tick();
    editSmallDownButton.tick();

    editTrashButton.tick();

    editDuplicateButton.tick();

    editKeyTimer += GetFrameTime();
    
    if (editKeyTimer > editKeyTime) {
      editKeyTimer = 0.0f;
      if (IsKeyDown(KEY_W)) {
        IsKeyDown(KEY_LEFT_SHIFT) ? smallUpButton() : upButton();
      }

      if (IsKeyDown(KEY_S)) {
        IsKeyDown(KEY_LEFT_SHIFT) ? smallDownButton() : downButton();
      }
      
      if (IsKeyDown(KEY_A)) {
        IsKeyDown(KEY_LEFT_SHIFT) ? smallLeftButton() : leftButton();
      }

      if (IsKeyDown(KEY_D)) {
        IsKeyDown(KEY_LEFT_SHIFT) ? smallRightButton() : rightButton();
      }

      if (IsKeyDown(KEY_BACKSPACE) || IsKeyDown(KEY_DELETE)) {
        trashButton();
      }
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) || IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      if (CheckCollisionPointRec(GetMousePosition(), {240, 80, SCREEN_WIDTH - 240, SCREEN_HEIGHT - 80})) {
        if (!selecting) {
          selx1 = GetMousePosition().x;
          sely1 = GetMousePosition().y;
        }

        selecting = true;

        selx2 = GetMousePosition().x;
        sely2 = GetMousePosition().y;
      } else {
        if (selecting) {
          selx2 = std::max(240.0f, GetMousePosition().x);
          sely2 = std::max(80.0f, GetMousePosition().y);
        }
      }
    } else {
      if ((selection.width > 0 && selection.height > 0) || selecting) {
        Vector2 posToWorld = GetScreenToWorld2D({selection.x, selection.y}, camera);
        Vector2 pos2ToWorld = GetScreenToWorld2D({selection.x + selection.width, selection.y + selection.height}, camera);

        Rectangle selectionWorld = {posToWorld.x, posToWorld.y, pos2ToWorld.x - posToWorld.x, pos2ToWorld.y - posToWorld.y};
        selectedObjects = getAllGameObjectsInRect(selectionWorld, zLayer);
      }
      selecting = false;
      selx1 = 0;
      selx2 = 0;
      sely1 = 0;
      sely2 = 0;
    }
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

void Editor::rightButton() {
  for (GameObject* gameObject : selectedObjects) {
    gameObject->rect.x += 40;
  }
}

void Editor::leftButton() {
  for (GameObject* gameObject : selectedObjects) {
    gameObject->rect.x -= 40;
  }
}

void Editor::upButton() {
  for (GameObject* gameObject : selectedObjects) {
    gameObject->rect.y -= 40;
  }
}

void Editor::downButton() {
  for (GameObject* gameObject : selectedObjects) {
    gameObject->rect.y += 40;
  }
}

void Editor::smallRightButton() {
  for (GameObject* gameObject : selectedObjects) {
    gameObject->rect.x += 1;
  }
}

void Editor::smallLeftButton() {
  for (GameObject* gameObject : selectedObjects) {
    gameObject->rect.x -= 1;
  }
}

void Editor::smallUpButton() {
  for (GameObject* gameObject : selectedObjects) {
    gameObject->rect.y -= 1;
  }
}

void Editor::smallDownButton() {
  for (GameObject* gameObject : selectedObjects) {
    gameObject->rect.y += 1;
  }
}

void Editor::trashButton() {
  for (GameObject* gameObject : selectedObjects) {
    level->gameObjects.erase(std::remove(level->gameObjects.begin(), level->gameObjects.end(), gameObject));
  }
  selectedObjects.clear();
}

void Editor::duplicateButton() {
  for (GameObject* gameObject : selectedObjects) {
    level->gameObjects.push_back(gameObject->clone());
  }
}

std::vector<GameObject*> Editor::getAllGameObjectsInRect(Rectangle rect, int layer) {
  std::vector<GameObject*> result;

  for (GameObject* gameObject : level->gameObjects) {
    if (CheckCollisionRecs(rect, gameObject->rect) && (layer == gameObject->zLayer || layer == 0)) result.push_back(gameObject);
  }
  return result;
}

std::vector<GameObject*> Editor::getAllGameObjectsInPos(Vector2 pos, int layer) {
  std::vector<GameObject*> result;

  for (GameObject* gameObject : level->gameObjects) {
    if (gameObject->rect.x == pos.x && gameObject->rect.y == pos.y && (layer == gameObject->zLayer || layer == 0)) result.push_back(gameObject);
  }
  return result;
}

template <typename T>
std::vector<T*> Editor::getAllGameObjectsInLayer(int layer) {
  std::vector<T*> result;

  for (GameObject* gameObject : level->gameObjects) {
    if (gameObject->zLayer == layer) {
      if (T* t = dynamic_cast<T*>(gameObject)) {
        result.push_back(t);
      }
    }
  }

  return result;
}


template <typename T>
std::vector<T*> Editor::getGameObjectsInPosAndLayer(Vector2 pos, int layer) {
  std::vector<T*> result;

  for (GameObject* gameObject : level->gameObjects) {
    if (T* t = dynamic_cast<T*>(gameObject)) {
      if (gameObject->rect.x == pos.x && gameObject->rect.y == pos.y && (layer == gameObject->zLayer || layer == 0)) result.push_back(t);
    }
  }
  return result;
}
