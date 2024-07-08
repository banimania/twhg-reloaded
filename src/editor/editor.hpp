#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "../level/level.hpp"
#include "../widget/widgets/buttonwidget.hpp"
#include "../level/gameobject/gameobjects/wallblock.hpp"
#include "../level/gameobject/gameobjects/backgroundblock.hpp"
#include "../level/gameobject/gameobjects/enemy.hpp"
#include "../level/gameobject/gameobjects/coin.hpp"
#include "../level/gameobject/gameobjects/key.hpp"
#include "../level/gameobject/gameobjects/keyblock.hpp"
#include "../level/gameobject/gameobjects/conveyor.hpp"
#include "../level/gameobject/gameobjects/checkpoint.hpp"
#include <functional>
#include <raylib.h>

enum Mode { BUILD, EDIT };

class Editor {
public:
  Level* level = new Level();

  Camera2D camera;
  
  bool init = false;

  int zLayer = 1;

  Mode mode = BUILD;

  int selectedObject = -1;

  Vector2 lastDeleted = {0, 0};
  float deleteTimer = 0, deleteTime = 0.5f;

  float editKeyTimer = 0, editKeyTime = 0.07f;

  bool selecting = false;
  float selx1 = 0, selx2 = 0, sely1 = 0, sely2 = 0;
  std::vector<GameObject*> selectedObjects;

  ButtonWidget buildButton = ButtonWidget("BUILD", 35, {10, 130, 100, 50}, std::bind(&Editor::buildModeButton, this));
  ButtonWidget editButton = ButtonWidget("EDIT", 35, {130, 130, 100, 50}, std::bind(&Editor::buildEditButton, this));

  ButtonWidget buildWallblockButton = ButtonWidget("", 0, {10, 240, 60, 60}, std::bind(&Editor::selectWallblockButton, this));
  WallBlock wallBlock = WallBlock({20, 250}, level, 0);
  ButtonWidget buildBackgroundBlockButton = ButtonWidget("", 0, {90, 240, 60, 60}, std::bind(&Editor::selectBackgroundBlockButton, this));
  BackgroundBlock backgroundBlock = BackgroundBlock({100, 250}, level, 0);
  ButtonWidget buildEnemyButton = ButtonWidget("", 0, {170, 240, 60, 60}, std::bind(&Editor::selectEnemyButton, this));
  Enemy enemy = Enemy({200, 270}, 10.0f, level, 0);
  ButtonWidget buildCoinButton = ButtonWidget("", 0, {10, 320, 60, 60}, std::bind(&Editor::selectCoinButton, this));
  Coin coin = Coin({40, 350}, 10.0f, level, 0);
  ButtonWidget buildKeyButton = ButtonWidget("", 0, {90, 320, 60, 60}, std::bind(&Editor::selectKeyButton, this));
  Key key = Key({120, 350}, -69, level, 0);
  ButtonWidget buildKeyBlockButton = ButtonWidget("", 0, {170, 320, 60, 60}, std::bind(&Editor::selectKeyBlockButton, this));
  KeyBlock keyBlock = KeyBlock({180, 330}, -69, level, 0);
  ButtonWidget buildConveyorButton = ButtonWidget("", 0, {10, 400, 60, 60}, std::bind(&Editor::selectConveyorButton, this));
  Conveyor conveyor = Conveyor({20, 410}, RIGHT, level, 0);
  ButtonWidget buildCheckpointButton = ButtonWidget("", 0, {90, 400, 60, 60}, std::bind(&Editor::selectCheckpointButton, this));
  Checkpoint checkpoint = Checkpoint({100, 410}, false, level, 0);
  ButtonWidget buildPlayerButton = ButtonWidget("", 0, {170, 400, 60, 60}, std::bind(&Editor::selectPlayerButton, this));
 
  ButtonWidget editRightButton = ButtonWidget("rightArrowTexture", 0.04f, {10, 240, 60, 60}, std::bind(&Editor::rightButton, this));
  ButtonWidget editLeftButton = ButtonWidget("leftArrowTexture", 0.04f, {90, 240, 60, 60}, std::bind(&Editor::leftButton, this));
  ButtonWidget editUpButton = ButtonWidget("upArrowTexture", 0.04f, {170, 240, 60, 60}, std::bind(&Editor::upButton, this));
  ButtonWidget editDownButton = ButtonWidget("downArrowTexture", 0.04f, {10, 320, 60, 60}, std::bind(&Editor::downButton, this));
  ButtonWidget editSmallRightButton = ButtonWidget("rightArrowTexture", 0.02f, {90, 320, 60, 60}, std::bind(&Editor::smallRightButton, this));
  ButtonWidget editSmallLeftButton = ButtonWidget("leftArrowTexture", 0.02f, {170, 320, 60, 60}, std::bind(&Editor::smallLeftButton, this));
  ButtonWidget editSmallUpButton = ButtonWidget("upArrowTexture", 0.02f, {10, 400, 60, 60}, std::bind(&Editor::smallUpButton, this));
  ButtonWidget editSmallDownButton = ButtonWidget("downArrowTexture", 0.02f, {90, 400, 60, 60}, std::bind(&Editor::smallDownButton, this));
  ButtonWidget editTrashButton = ButtonWidget("trashTexture", 0.08f, {170, 400, 60, 60}, std::bind(&Editor::trashButton, this));
  ButtonWidget editDuplicateButton = ButtonWidget("duplicateTexture", 0.08f, {10, 480, 60, 60}, std::bind(&Editor::duplicateButton, this));

  ButtonWidget configButton = ButtonWidget("configurationTexture", 0.24f, {10, SCREEN_HEIGHT - 75, 100, 60}, std::bind(&Editor::buildModeButton, this));
  ButtonWidget playButton = ButtonWidget("playTexture", 0.24f, {130, SCREEN_HEIGHT - 75, 100, 60}, std::bind(&Editor::buildEditButton, this));
  
  Editor() {
    camera.zoom = 1;
    camera.rotation = 0.0f;
    camera.target = {-155, -80};

    buildButton.setSelected(true);
  }

  
  void tick();
  void initWidgets();
  
  void drawGrid();
  void drawOutline();
  
  void buildModeButton();
  void buildEditButton();

  void selectWallblockButton();
  void selectBackgroundBlockButton();
  void selectEnemyButton();
  void selectCoinButton();
  void selectKeyButton();
  void selectKeyBlockButton();
  void selectConveyorButton();
  void selectCheckpointButton();
  void selectPlayerButton();

  void rightButton();
  void leftButton();
  void upButton();
  void downButton();
  void smallRightButton();
  void smallLeftButton();
  void smallUpButton();
  void smallDownButton();

  void trashButton();

  void duplicateButton();

  std::vector<GameObject*> getAllGameObjectsInPos(Vector2 pos, int layer);

  std::vector<GameObject*> getAllGameObjectsInRect(Rectangle rect, int layer);

  template <typename T>
  std::vector<T*> getAllGameObjectsInLayer(int layer);

  template <typename T>
  std::vector<T*> getGameObjectsInPosAndLayer(Vector2 pos, int layer);

  void deselectAll();
};

#endif
