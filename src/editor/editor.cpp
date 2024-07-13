#include "editor.hpp"
#include "../utils/needed.hpp"

void Editor::initWidgets() {
  init = true;
}

void Editor::tick() {
  if (!init) initWidgets();

  if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) || IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
    Vector2 mouseVec = {(float) TWHGReloaded::mouse.x, (float) TWHGReloaded::mouse.y};
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

  if (wheel != 0 && CheckCollisionPointRec(TWHGReloaded::mouse, {240, 80, SCREEN_WIDTH - 240 * 2, SCREEN_HEIGHT - 80})) {
    Vector2 mouseWorldPos = GetScreenToWorld2D(TWHGReloaded::mouse, camera);

    camera.offset = TWHGReloaded::mouse;

    camera.target = mouseWorldPos;

    float scaleFactor = 1.0f + (0.25f * fabsf(wheel));
    if (wheel < 0) scaleFactor = 1.0f / scaleFactor;
    camera.zoom = std::clamp(camera.zoom * scaleFactor, 0.7f, 2.5f);
  }

  for (WallBlock* wallBlock : getAllGameObjectsInLayer<WallBlock>(zLayer)) {
    wallBlock->updateWallBlock(getAllGameObjectsInLayer<WallBlock>(zLayer));
  }
  
  for (KeyBlock* keyBlock : getAllGameObjectsInLayer<KeyBlock>(zLayer)) {
    keyBlock->updateKeyBlock(getAllGameObjectsInLayer<KeyBlock>(zLayer));
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
    } else {
      if (gameObject->zLayer != zLayer && zLayer != 0) {
        if (Key* key = dynamic_cast<Key*>(gameObject)) {
          DrawRectangleRec({gameObject->rect.x - 10, gameObject->rect.y - 10, gameObject->rect.width + 20, gameObject->rect.height + 20}, editorOtherLayerColor);
        } else DrawRectangleRec(gameObject->rect, editorOtherLayerColor);
      }
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

  drawOutline();

  buildButton.tick();
  editButton.tick();

  //use rlScalef for scaling what the fuck am i doing lol

  deleteTimer += GetFrameTime();

  propertiesOpen = ((mode == BUILD && ((selectedObject > 0 && selectedObject < 9) || configButton.selected)) || (mode == EDIT && isSingleType(selectedObjects)));

  if (propertiesOpen) {
    DrawRectangleRec(propertiesRect, editorUIColor);
    if (selectedObject == 1) tickSettings(&wallBlock);
    else if (selectedObject == 2) tickSettings(&backgroundBlock);
    else if (selectedObject == 3) tickSettings(&enemy);
    else if (selectedObject == 4) tickSettings(&coin);
    else if (selectedObject == 5) tickSettings(&key);
    else if (selectedObject == 6) tickSettings(&keyBlock);
    else if (selectedObject == 7) tickSettings(&conveyor);
    else if (selectedObject == 8) tickSettings(&checkpoint);
    else if (configButton.selected) tickSettings(nullptr);
    DrawRectangleGradientH(propertiesRect.x, propertiesRect.y, 120, 40, editorGradient1Color, editorGradient2Color);
    DrawRectangleGradientH(propertiesRect.x + 120, propertiesRect.y, 120, 40, editorGradient2Color, editorGradient1Color);
    DrawOutlinedCenteredText(editorFontBold, "PROPERTIES", {propertiesRect.x, propertiesRect.y, 240, 40}, 35, WHITE, 2, BLACK);
  }

  if (mode == BUILD) {

    selectedObjects = {};

    if (CheckCollisionPointRec(TWHGReloaded::mouse, {240, 80, propertiesOpen ? SCREEN_WIDTH - 240.0f * 2 : SCREEN_WIDTH - 240.0f, SCREEN_HEIGHT - 80})) {
      Vector2 pos = GetScreenToWorld2D(TWHGReloaded::mouse, camera);
      if (pos.x < 0) pos.x -= 40;
      if (pos.y < 0) pos.y -= 40;
      if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && selectedObject != -1) {
        GameObject* object;

        switch (selectedObject) {
          case 1: {
            WallBlock* wall = new WallBlock({(float) ((int) (pos.x / 40) * 40), (float) ((int) (pos.y / 40) * 40)}, level, zLayer);
            wall->outlineColor = outlineColorWidgetWallblock.color;
            wall->fillColor = fillColorWidgetWallblock.color;
            object = wall;
            break;
          }
          case 2: {
            BackgroundBlock* background = new BackgroundBlock({(float) ((int) (pos.x / 40) * 40), (float) ((int) (pos.y / 40) * 40)}, level, zLayer);
            background->fillColor = fillColorWidgetBackgroundblock.color;
            object = background;
            break;
          }
          case 3: {
            Enemy* enemy = new Enemy({(float) ((int) (pos.x / 40) * 40) + 20, (float) ((int) (pos.y / 40) * 40) + 20}, 10, level, zLayer);
            enemy->outlineColor = outlineColorWidgetEnemy.color;
            enemy->fillColor = fillColorWidgetEnemy.color;
            object = enemy;
            break;
          }
          case 4: {
            Coin* coin = new Coin({(float) ((int) (pos.x / 40) * 40) + 20, (float) ((int) (pos.y / 40) * 40) + 20}, 10, level, zLayer);
            coin->outlineColor = outlineColorWidgetCoin.color;
            coin->fillColor = fillColorWidgetCoin.color;
            object = coin;
            break;
          }
          case 5: {
            Key* key = new Key({(float) ((int) (pos.x / 40) * 40) + 20, (float) ((int) (pos.y / 40) * 40) + 20}, 1, level, zLayer);
            key->outlineColor = outlineColorWidgetKey.color;
            key->fillColor = fillColorWidgetKey.color;
            key->keyId = idWidgetKey.text.empty() ? 1 : std::stoi(idWidgetKey.text);
            object = key;
            break;
          }
          case 6: {
            KeyBlock* keyBlock = new KeyBlock({(float) ((int) (pos.x / 40) * 40), (float) ((int) (pos.y / 40) * 40)}, 1, level, zLayer);
            keyBlock->outlineColor = outlineColorWidgetKeyBlock.color;
            keyBlock->fillColor = fillColorWidgetKeyBlock.color;
            keyBlock->keyId = idWidgetKeyBlock.text.empty() ? 1 : std::stoi(idWidgetKeyBlock.text);
            object = keyBlock;
            break;
          }
          case 7: {
            Conveyor* conveyor = new Conveyor({(float) ((int) (pos.x / 40) * 40), (float) ((int) (pos.y / 40) * 40)}, RIGHT, level, zLayer);
            conveyor->arrowColor = arrowColorWidgetConveyor.color;
            conveyor->fillColor = fillColorWidgetConveyor.color;
            conveyor->speed = speedWidgetConveyor.text.empty() ? 80: std::stoi(speedWidgetConveyor.text);
            
            if (directionWidgetConveyor.selectedOption == "Right") conveyor->direction = RIGHT;
            else if (directionWidgetConveyor.selectedOption == "Left") conveyor->direction = LEFT;
            else if (directionWidgetConveyor.selectedOption == "Up") conveyor->direction = UP;
            else if (directionWidgetConveyor.selectedOption == "Down") conveyor->direction = DOWN;
            object = conveyor;
            break;
          }
          case 8: {
            Checkpoint* checkpoint = new Checkpoint({(float) ((int) (pos.x / 40) * 40), (float) ((int) (pos.y / 40) * 40)}, false, level, zLayer);
            checkpoint->fillColor = fillColorWidgetCheckpoint.color;
            checkpoint->goal = goalWidgetCheckpoint.value;
            checkpoint->saveKeys = saveKeysWidgetCheckpoint.value;
            checkpoint->saveCoins = saveCoinsWidgetCheckpoint.value;
            object = checkpoint;
            break;
          }
          case 9: {
            level->startX = (float) ((int) (pos.x / 40) * 40) + 5;
            level->startY = (float) ((int) (pos.y / 40) * 40) + 5;
            object = nullptr;
            break;
          }
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
    wallBlock.fillColor = fillColorWidgetWallblock.color;
    wallBlock.outlineColor = outlineColorWidgetWallblock.color;
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
    backgroundBlock.fillColor = fillColorWidgetBackgroundblock.color;
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
    enemy.outlineColor = outlineColorWidgetEnemy.color;
    enemy.fillColor = fillColorWidgetEnemy.color;
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
    coin.fillColor = fillColorWidgetCoin.color;
    coin.outlineColor = outlineColorWidgetCoin.color;
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
    key.fillColor = fillColorWidgetKey.color;
    key.outlineColor = outlineColorWidgetKey.color;
    key.tick(&level->player);
    rlPopMatrix();

    rlPushMatrix();
    buildKeyBlockButton.tick();
    difHalf = (buildKeyBlockButton.rect.width * buildKeyBlockButton.scale - buildKeyBlockButton.rect.width) / 2.0f;
    rlTranslatef(keyBlock.rect.x - difHalf, keyBlock.rect.y - difHalf, 0.0f);
    rlScalef(buildKeyBlockButton.scale, buildKeyBlockButton.scale, 1.0f);
    rlTranslatef(-keyBlock.rect.x, -keyBlock.rect.y, 0.0f);
    keyBlock.fillColor = fillColorWidgetKeyBlock.color;
    keyBlock.outlineColor = outlineColorWidgetKeyBlock.color;
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
    conveyor.fillColor = fillColorWidgetConveyor.color;
    conveyor.arrowColor = arrowColorWidgetConveyor.color;
    conveyor.speed = speedWidgetConveyor.text.empty() ? 80 : std::stoi(speedWidgetConveyor.text);
    if (directionWidgetConveyor.selectedOption == "Right") conveyor.direction = RIGHT;
    else if (directionWidgetConveyor.selectedOption == "Left") conveyor.direction = LEFT;
    else if (directionWidgetConveyor.selectedOption == "Up") conveyor.direction = UP;
    else if (directionWidgetConveyor.selectedOption == "Down") conveyor.direction = DOWN;
    conveyor.tick(&level->player); 
    
    rlPushMatrix();
    buildCheckpointButton.tick();
    difHalf = (buildCheckpointButton.rect.width * buildCheckpointButton.scale - buildCheckpointButton.rect.width) / 2.0f;
    rlTranslatef(checkpoint.rect.x - difHalf, checkpoint.rect.y - difHalf, 0.0f);
    rlScalef(buildCheckpointButton.scale, buildCheckpointButton.scale, 1.0f);
    rlTranslatef(-checkpoint.rect.x, -checkpoint.rect.y, 0.0f);
    checkpoint.fillColor = fillColorWidgetCheckpoint.color;
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

      if (IsKeyDown(KEY_DELETE)) {
        trashButton();
      }
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) || IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      if (CheckCollisionPointRec(TWHGReloaded::mouse, {240, 80, propertiesOpen ? SCREEN_WIDTH - 240.0f * 2 : SCREEN_WIDTH - 240.0f, SCREEN_HEIGHT - 80})) {
        if (!selecting) {
          selx1 = TWHGReloaded::mouse.x;
          sely1 = TWHGReloaded::mouse.y;
        }

        selecting = true;

        selx2 = TWHGReloaded::mouse.x;
        sely2 = TWHGReloaded::mouse.y;
      } else {
        if (selecting) {
          selx2 = std::max(240.0f, TWHGReloaded::mouse.x);
          sely2 = std::max(80.0f, TWHGReloaded::mouse.y);
        }
      }
    } else {
      if ((selection.width > 0 && selection.height > 0) || selecting) {
        Vector2 posToWorld = GetScreenToWorld2D({selection.x, selection.y}, camera);
        Vector2 pos2ToWorld = GetScreenToWorld2D({selection.x + selection.width, selection.y + selection.height}, camera);

        Rectangle selectionWorld = {posToWorld.x, posToWorld.y, pos2ToWorld.x - posToWorld.x, pos2ToWorld.y - posToWorld.y};
        
        if (!IsKeyDown(KEY_LEFT_SHIFT)) {
          selectedObjects.clear();
        }

        for (GameObject* gameObject : getAllGameObjectsInRect(selectionWorld, zLayer)) {
          selectedObjects.push_back(gameObject);
        }
      }
      selecting = false;
      selx1 = 0;
      selx2 = 0;
      sely1 = 0;
      sely2 = 0;
    }
  }

  if (isSingleType(selectedObjects)) {
    for (GameObject* gameObject : selectedObjects) {
      if (WallBlock* wallBlock = dynamic_cast<WallBlock*>(gameObject)) {
        wallBlock->fillColor = fillColorWidgetWallblock.color;
        wallBlock->outlineColor = outlineColorWidgetWallblock.color;
      } else if (BackgroundBlock* backgroundBlock = dynamic_cast<BackgroundBlock*>(gameObject)) {
        backgroundBlock->fillColor = fillColorWidgetBackgroundblock.color;
      } else if (Enemy* enemy = dynamic_cast<Enemy*>(gameObject)) {
        enemy->fillColor = fillColorWidgetEnemy.color;
        enemy->outlineColor = outlineColorWidgetEnemy.color;
      } else if (Coin* coin = dynamic_cast<Coin*>(gameObject)) {
        coin->fillColor = fillColorWidgetCoin.color;
        coin->outlineColor = outlineColorWidgetEnemy.color;
      } else if (Key* key = dynamic_cast<Key*>(gameObject)) {
        key->keyId = idWidgetKey.text.empty() ? 1 : std::stoi(idWidgetKey.text);
        key->fillColor = fillColorWidgetKey.color;
        key->outlineColor = outlineColorWidgetKey.color;
      } else if (KeyBlock* keyBlock = dynamic_cast<KeyBlock*>(gameObject)) {
        keyBlock->keyId = idWidgetKeyBlock.text.empty() ? 1 : std::stoi(idWidgetKeyBlock.text);
        keyBlock->fillColor = fillColorWidgetKeyBlock.color;
        keyBlock->outlineColor = outlineColorWidgetKeyBlock.color;
      } else if (Conveyor* conveyor = dynamic_cast<Conveyor*>(gameObject)) {
        conveyor->fillColor = fillColorWidgetConveyor.color;
        conveyor->arrowColor = arrowColorWidgetConveyor.color;
        
        if (directionWidgetConveyor.selectedOption == "Right") conveyor->direction = RIGHT;
        else if (directionWidgetConveyor.selectedOption == "Left") conveyor->direction = LEFT;
        else if (directionWidgetConveyor.selectedOption == "Up") conveyor->direction = UP;
        else if (directionWidgetConveyor.selectedOption == "Down") conveyor->direction = DOWN;
        
        conveyor->speed = speedWidgetConveyor.text.empty() ? 80 : std::stoi(speedWidgetConveyor.text);
      } else if (Checkpoint* checkpoint = dynamic_cast<Checkpoint*>(gameObject)) {
        checkpoint->goal = goalWidgetCheckpoint.value;
        checkpoint->saveKeys = saveKeysWidgetCheckpoint.value;
        checkpoint->saveCoins = saveCoinsWidgetCheckpoint.value;
        checkpoint->fillColor = fillColorWidgetCheckpoint.color;
      }
    }
  }

  configButton.tick();
  playButton.tick();


  level->hud.tickEditor();
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

  DrawOutlinedText(editorFontBold, "LAYER", 17, 80, 35, WHITE, 2, BLACK);
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
  bool wasSelected = buildWallblockButton.selected;
  selectedObject = 1;
  deselectAll();
  buildWallblockButton.setSelected(!wasSelected);
  if (!buildWallblockButton.selected) selectedObject = 0;
}

void Editor::selectBackgroundBlockButton() {
  bool wasSelected = buildBackgroundBlockButton.selected;
  selectedObject = 2;
  deselectAll();
  buildBackgroundBlockButton.setSelected(!wasSelected);
  if (!buildBackgroundBlockButton.selected) selectedObject = 0;
}

void Editor::selectEnemyButton() {
  bool wasSelected = buildEnemyButton.selected;
  selectedObject = 3;
  deselectAll();
  buildEnemyButton.setSelected(!wasSelected);
  if (!buildEnemyButton.selected) selectedObject = 0;
}

void Editor::selectCoinButton() {
  bool wasSelected = buildCoinButton.selected;
  selectedObject = 4;
  deselectAll();
  buildCoinButton.setSelected(!wasSelected);
  if (!buildCoinButton.selected) selectedObject = 0;
}

void Editor::selectKeyButton() {
  bool wasSelected = buildKeyButton.selected;
  selectedObject = 5;
  deselectAll();
  buildKeyButton.setSelected(!wasSelected);
  if (!buildKeyButton.selected) selectedObject = 0;
}

void Editor::selectKeyBlockButton() {
  bool wasSelected = buildKeyBlockButton.selected;
  selectedObject = 6;
  deselectAll();
  buildKeyBlockButton.setSelected(!wasSelected);
  if (!buildKeyBlockButton.selected) selectedObject = 0;
}

void Editor::selectConveyorButton() {
  bool wasSelected = buildConveyorButton.selected;
  selectedObject = 7;
  deselectAll();
  buildConveyorButton.setSelected(!wasSelected);
  if (!buildConveyorButton.selected) selectedObject = 0;
}

void Editor::selectCheckpointButton() {
  bool wasSelected = buildCheckpointButton.selected;
  selectedObject = 8;
  deselectAll();
  buildCheckpointButton.setSelected(!wasSelected);
  if (!buildCheckpointButton.selected) selectedObject = 0;
}

void Editor::selectPlayerButton() {
  bool wasSelected = buildPlayerButton.selected;
  selectedObject = 9;
  deselectAll();
  buildPlayerButton.setSelected(!wasSelected);
  if (!buildPlayerButton.selected) selectedObject = 0;
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
  configButton.setSelected(false);
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

void Editor::configurationButton() {
  bool wasSelected = configButton.selected;
  deselectAll();
  configButton.setSelected(!wasSelected);
  selectedObject = -1;
}

void Editor::playTestButton() {
  level->reset();
  TWHGReloaded::state = PLAYTEST;
}

void Editor::checkerboardButton() {
  level->background.backgroundType = CHECKERBOARD;
  checkerboardWidget.setSelected(true);
  plainWidget.setSelected(false);
}

void Editor::plainButton() {
  level->background.backgroundType = PLAIN;
  checkerboardWidget.setSelected(false);
  plainWidget.setSelected(true);
}

void Editor::tickSettings(GameObject* object) {

  if (scrollAllowed) {
    float propertyScrollDelta = -GetMouseWheelMove() * GetFrameTime() * 2000;

    if (CheckCollisionPointRec(TWHGReloaded::mouse, {240, 80, SCREEN_WIDTH - 240 * 2, SCREEN_HEIGHT - 80})) propertyScrollDelta = 0;

    if (propertyScroll + propertyScrollDelta < 0) {
      propertyScrollDelta = -propertyScroll;
    } else if (propertyScroll + propertyScrollDelta > maxScroll) propertyScrollDelta = 0;
    propertyScroll += propertyScrollDelta;
    

    propertiesRect.y -= propertyScrollDelta;
    for (Widget* widget : propertyWidgets) {
      widget->rect.y -= propertyScrollDelta;
      if (ColorWidget* colorWidget = dynamic_cast<ColorWidget*>(widget)) {
        colorWidget->redWidget.rect.y -= propertyScrollDelta;
        colorWidget->greenWidget.rect.y -= propertyScrollDelta;
        colorWidget->blueWidget.rect.y -= propertyScrollDelta;
      }
    }

  } else {
    propertiesRect.y += propertyScroll;
    for (Widget* widget : propertyWidgets) {
      widget->rect.y += propertyScroll;
      if (ColorWidget* colorWidget = dynamic_cast<ColorWidget*>(widget)) {
        colorWidget->redWidget.rect.y += propertyScroll;
        colorWidget->greenWidget.rect.y += propertyScroll;
        colorWidget->blueWidget.rect.y += propertyScroll;
      }
    }
    propertyScroll = 0;
  }

  //propertiesRect.y = 80 - propertyScroll;

  scrollAllowed = false;

  if (WallBlock* wallBlock = dynamic_cast<WallBlock*>(object)) {
    outlineColorWidgetWallblock.tick();
    fillColorWidgetWallblock.tick();
  } else if (BackgroundBlock* backgroundBlock = dynamic_cast<BackgroundBlock*>(object)) {
    fillColorWidgetBackgroundblock.tick();
  } else if (Enemy* enemy = dynamic_cast<Enemy*>(object)) {
    outlineColorWidgetEnemy.tick();
    fillColorWidgetEnemy.tick();
  } else if (Coin* coin = dynamic_cast<Coin*>(object)) {
    outlineColorWidgetCoin.tick();
    fillColorWidgetCoin.tick();
  } else if (Key* key = dynamic_cast<Key*>(object)) {
    scrollAllowed = true;
    maxScroll = 100;

    outlineColorWidgetKey.tick();
    fillColorWidgetKey.tick();
    if (idWidgetKey.text.empty() && !idWidgetKey.active) idWidgetKey.text = std::to_string(1);
    idWidgetKey.tick();
  } else if (KeyBlock* keyBlock = dynamic_cast<KeyBlock*>(object)) {
    scrollAllowed = true;
    maxScroll = 100;
    
    outlineColorWidgetKeyBlock.tick();
    fillColorWidgetKeyBlock.tick();
    if (idWidgetKeyBlock.text.empty() && !idWidgetKeyBlock.active) idWidgetKeyBlock.text = std::to_string(1);
    idWidgetKeyBlock.tick();
  } else if (Conveyor* conveyor = dynamic_cast<Conveyor*>(object)) {
    scrollAllowed = true;
    maxScroll = 100;

    arrowColorWidgetConveyor.tick();
    fillColorWidgetConveyor.tick();
    if (speedWidgetConveyor.text.empty() && !speedWidgetConveyor.active) speedWidgetConveyor.text = std::to_string(80);
    speedWidgetConveyor.tick();
    directionWidgetConveyor.tick();
  } else if (Checkpoint* checkpoint = dynamic_cast<Checkpoint*>(object)) {
    fillColorWidgetCheckpoint.tick();
    goalWidgetCheckpoint.tick();
    saveCoinsWidgetCheckpoint.tick();
    saveKeysWidgetCheckpoint.tick();
  } else if (object == nullptr) {
    freeCameraWidget.tick();

    scrollAllowed = true;
    maxScroll = 170;

    DrawRectangleRec({propertiesRect.x, propertiesRect.y + 40 + 40, propertiesRect.width, 40}, {174, 174, 174, 255});
    DrawTextEx(hudFontBold, "Background", {propertiesRect.x + 10, propertiesRect.y + 40 + 40 + 2}, 35, 0, RAYWHITE);

    checkerboardWidget.tick();
    plainWidget.tick();

    rlPushMatrix();
    float difHalf = (checkerboardWidget.rect.width * checkerboardWidget.scale - checkerboardWidget.rect.width) / 2.0f;
    rlTranslatef(checkerboardWidget.rect.x + checkerboardWidget.rect.width / 2.0f + difHalf, checkerboardWidget.rect.y + checkerboardWidget.rect.height / 2.0f + difHalf, 0.0f);
    rlScalef(checkerboardWidget.scale, checkerboardWidget.scale, 1.0f);
    rlTranslatef(-checkerboardWidget.rect.x - checkerboardWidget.rect.width / 2.0f - difHalf, -checkerboardWidget.rect.y - checkerboardWidget.rect.height / 2.0f - difHalf, 0.0f);
    DrawRectangleRec({checkerboardWidget.rect.x + checkerboardWidget.borderThickness, checkerboardWidget.rect.y + checkerboardWidget.borderThickness, checkerboardWidget.rect.width - 2 * checkerboardWidget.borderThickness, checkerboardWidget.rect.height - 2 * checkerboardWidget.borderThickness}, level->background.colorPrimary);
    DrawRectangleRec({checkerboardWidget.rect.x + checkerboardWidget.borderThickness, checkerboardWidget.rect.y + checkerboardWidget.borderThickness, checkerboardWidget.rect.width / 2.0f - checkerboardWidget.borderThickness, checkerboardWidget.rect.height / 2.0f - checkerboardWidget.borderThickness}, level->background.colorSecondary);
    DrawRectangleRec({checkerboardWidget.rect.x + checkerboardWidget.rect.width / 2.0f, checkerboardWidget.rect.y + checkerboardWidget.rect.height / 2.0f, checkerboardWidget.rect.width / 2.0f - checkerboardWidget.borderThickness, checkerboardWidget.rect.height / 2.0f - checkerboardWidget.borderThickness}, level->background.colorSecondary);
    rlPopMatrix();

    rlPushMatrix();
    difHalf = (plainWidget.rect.width * plainWidget.scale - plainWidget.rect.width) / 2.0f;
    rlTranslatef(plainWidget.rect.x + plainWidget.rect.width / 2.0f + difHalf, plainWidget.rect.y + plainWidget.rect.height / 2.0f + difHalf, 0.0f);
    rlScalef(plainWidget.scale, plainWidget.scale, 1.0f);
    rlTranslatef(-plainWidget.rect.x - plainWidget.rect.width / 2.0f - difHalf, -plainWidget.rect.y - plainWidget.rect.height / 2.0f - difHalf, 0.0f);
    DrawRectangleRec({plainWidget.rect.x + plainWidget.borderThickness, plainWidget.rect.y + plainWidget.borderThickness, plainWidget.rect.width - 2 * plainWidget.borderThickness, plainWidget.rect.height - 2 * plainWidget.borderThickness}, level->background.colorPrimary);
    rlPopMatrix();

    backgroundPrimaryColorWidget.tick();
    backgroundSecondaryColorWidget.tick();

    level->background.colorPrimary = backgroundPrimaryColorWidget.color;
    level->background.colorSecondary = backgroundSecondaryColorWidget.color;

    level->freeCameraMode = freeCameraWidget.value;
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

bool Editor::isSingleType(std::vector<GameObject*>& gameObjects) {
  if (gameObjects.empty()) return false;

  const std::type_info& type = typeid(*gameObjects.at(0));

  for (GameObject* gameObject : gameObjects) {
    if (typeid(*gameObject) != type) return false;
  }

  if (type == typeid(wallBlock)) selectedObject = 1;
  else if (type == typeid(backgroundBlock)) selectedObject = 2;
  else if (type == typeid(enemy)) selectedObject = 3;
  else if (type == typeid(coin)) selectedObject = 4;
  else if (type == typeid(key)) selectedObject = 5;
  else if (type == typeid(keyBlock)) selectedObject = 6;
  else if (type == typeid(conveyor)) selectedObject = 7;
  else if (type == typeid(checkpoint)) selectedObject = 8;

  return true;
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
