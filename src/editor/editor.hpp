#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "../level/level.hpp"
#include "../widget/widgets/buttonwidget.hpp"
#include "../widget/widgets/enumwidget.hpp"
#include "../widget/widgets/booleanwidget.hpp"
#include "../widget/widgets/pathwidget.hpp"
#include "../widget/widgets/colorwidget.hpp"
#include "../widget/widgets/instructionwidget.hpp"
#include "../level/gameobject/gameobjects/wallblock.hpp"
#include "../level/gameobject/gameobjects/backgroundblock.hpp"
#include "../level/gameobject/gameobjects/enemy.hpp"
#include "../level/gameobject/gameobjects/coin.hpp"
#include "../level/gameobject/gameobjects/key.hpp"
#include "../level/gameobject/gameobjects/keyblock.hpp"
#include "../level/gameobject/gameobjects/conveyor.hpp"
#include "../level/gameobject/gameobjects/checkpoint.hpp"
#include "../level/gameobject/gameobjects/fog.hpp"
#include <functional>
#include <raylib.h>
#include <rlgl.h>

enum Mode { BUILD, EDIT };

class Editor {
public:

  Level* level;

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

  std::vector<Widget*> propertyWidgets;
  std::vector<Widget*> buildEditWidgets;

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
  ButtonWidget buildFogBlockButton = ButtonWidget("", 0, {170, 400, 60, 60}, std::bind(&Editor::selectFogButton, this));
  FogBlock fogBlock = FogBlock({180, 410}, level, 0);

  ButtonWidget buildPlayerButton = ButtonWidget("", 0, {10, 480, 60, 60}, std::bind(&Editor::selectPlayerButton, this));
  
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
  ButtonWidget editPathButton = ButtonWidget("PATH", 20, {90, 480, 60, 60}, std::bind(&Editor::pathButton, this));

  ButtonWidget configButton = ButtonWidget("configurationTexture", 0.24f, {10, SCREEN_HEIGHT - 75, 100, 60}, std::bind(&Editor::configurationButton, this));
  ButtonWidget playButton = ButtonWidget("playTexture", 0.24f, {130, SCREEN_HEIGHT - 75, 100, 60}, std::bind(&Editor::playTestButton, this));
 
  bool propertiesOpen = false;
  Rectangle propertiesRect = {SCREEN_WIDTH - 240, 80, 240, SCREEN_HEIGHT - 80 + 1000};
  bool instructions = false;
  int pathEditing = -1;
  bool instructionsInit = false;
  std::vector<InstructionWidget*> instructionWidgets;

  bool pathEditorOpen = false;
  bool pathEditorInit = false;
  float pathScroll = 0, instructionScroll = 0;
  std::vector<PathWidget*> pathWidgets;
  Rectangle pathEditorRect = {SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 4.0f, SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};

  ButtonWidget pathNewButton = ButtonWidget("NEW", 35, {pathEditorRect.x + 10 + 20, pathEditorRect.y + pathEditorRect.height - 10 - 20 - 40, (pathEditorRect.width / 2.0f - 40), 50}, std::bind(&Editor::newPath, this));
  ButtonWidget pathRemoveButton = ButtonWidget("CLEAR", 35, {pathEditorRect.x + 10 + 20 + (pathEditorRect.width / 2.0f - 40) + 20, pathEditorRect.y + pathEditorRect.height - 10 - 20 - 40, (pathEditorRect.width / 2.0f - 40), 50}, std::bind(&Editor::deletePath, this));

  ButtonWidget instructionNewButton = ButtonWidget("NEW", 35, {pathEditorRect.x + 10 + 20, pathEditorRect.y + pathEditorRect.height - 10 - 20 - 40, (pathEditorRect.width / 2.0f - 40) - 150, 50}, std::bind(&Editor::newInstruction, this));
  ButtonWidget instructionRemoveButton = ButtonWidget("CLEAR", 35, {pathEditorRect.x + 10 + 20 + (pathEditorRect.width / 2.0f - 40) + 20, pathEditorRect.y + pathEditorRect.height - 10 - 20 - 40, (pathEditorRect.width / 2.0f - 40), 50}, std::bind(&Editor::deleteInstruction, this));
  std::vector<std::string> optionsType = std::vector<std::string>{"Line", "Circle", "Wait"};
  EnumWidget instructionTypeWidget = EnumWidget("", {pathEditorRect.x + 20 + 20 + (pathEditorRect.width / 2.0f - 40) - 150, pathEditorRect.y + pathEditorRect.height - 10 - 20 - 40}, 150, 45, optionsType, "Line");

  float propertyScroll = 0.0f, maxScroll = 0.0f;
  bool scrollAllowed = false;

  BooleanWidget freeCameraWidget = BooleanWidget("Free Camera", false, {propertiesRect.x, propertiesRect.y + 40}, 240, 35);
  ButtonWidget checkerboardWidget = ButtonWidget("", 1, {propertiesRect.x + 10, propertiesRect.y + 90 + 40, 100, 100}, std::bind(&Editor::checkerboardButton, this));
  ButtonWidget plainWidget = ButtonWidget("", 1, {propertiesRect.x + propertiesRect.width - 110, propertiesRect.y + 90 + 40, 100, 100}, std::bind(&Editor::plainButton, this));
  ColorWidget backgroundPrimaryColorWidget = ColorWidget("Color 1", backgroundColorPrimary, {propertiesRect.x, propertiesRect.y + 200 + 40}, 240);
  ColorWidget backgroundSecondaryColorWidget = ColorWidget("Color 2", backgroundColorSecondary, {propertiesRect.x, propertiesRect.y + 200 + 270 + 40}, 240);

  ColorWidget outlineColorWidgetWallblock = ColorWidget("Outline", wallBlockColorOutline, {propertiesRect.x, propertiesRect.y + 40}, 240);
  ColorWidget fillColorWidgetWallblock = ColorWidget("Fill", wallBlockColorFill, {propertiesRect.x, propertiesRect.y + 270 + 40}, 240);
  
  ColorWidget fillColorWidgetBackgroundblock = ColorWidget("Fill", wallBlockColorFill, {propertiesRect.x, propertiesRect.y + 40}, 240);

  ColorWidget outlineColorWidgetEnemy = ColorWidget("Outline", enemyColorOutline, {propertiesRect.x, propertiesRect.y + 40}, 240);
  ColorWidget fillColorWidgetEnemy = ColorWidget("Fill", enemyColorFill, {propertiesRect.x, propertiesRect.y + 270 + 40}, 240);

  ColorWidget outlineColorWidgetCoin = ColorWidget("Outline", coinColorOutline, {propertiesRect.x, propertiesRect.y + 40}, 240);
  ColorWidget fillColorWidgetCoin = ColorWidget("Fill", coinColorFill, {propertiesRect.x, propertiesRect.y + 270 + 40}, 240);
 
  TextFieldWidget idWidgetKey = TextFieldWidget("Key ID", {propertiesRect.x + 10, propertiesRect.y + 70}, 220, 35, true, 4);
  ColorWidget outlineColorWidgetKey = ColorWidget("Outline", keyColorOutline, {propertiesRect.x, propertiesRect.y + 40 + 75}, 240);
  ColorWidget fillColorWidgetKey = ColorWidget("Fill", keyColorFill, {propertiesRect.x, propertiesRect.y + 270 + 40 + 75}, 240);
  
  TextFieldWidget idWidgetKeyBlock = TextFieldWidget("Key ID", {propertiesRect.x + 10, propertiesRect.y + 70}, 220, 35, true, 4);
  ColorWidget outlineColorWidgetKeyBlock = ColorWidget("Outline", keyColorOutline, {propertiesRect.x, propertiesRect.y + 40 + 75}, 240);
  ColorWidget fillColorWidgetKeyBlock = ColorWidget("Fill", keyColorFill, {propertiesRect.x, propertiesRect.y + 270 + 40 + 75}, 240);
 

  std::vector<std::string> options = std::vector<std::string>{"Up", "Down", "Right", "Left"};
  TextFieldWidget speedWidgetConveyor = TextFieldWidget("Speed", {propertiesRect.x + 10, propertiesRect.y + 70}, 220, 35, true, 3);
  EnumWidget directionWidgetConveyor = EnumWidget("Direction", {propertiesRect.x + 10, propertiesRect.y + 70 + 75}, 220, 35, options, "Right");
  ColorWidget arrowColorWidgetConveyor = ColorWidget("Arrow", conveyorColorArrow, {propertiesRect.x, propertiesRect.y + 40 + 75 + 75}, 240);
  ColorWidget fillColorWidgetConveyor = ColorWidget("Fill", conveyorColorFill, {propertiesRect.x, propertiesRect.y + 270 + 40 + 75 + 75}, 240);
 
  BooleanWidget goalWidgetCheckpoint = BooleanWidget("Is Goal", false, {propertiesRect.x, propertiesRect.y + 40}, 240, 35);
  BooleanWidget saveKeysWidgetCheckpoint = BooleanWidget("Save Keys", true, {propertiesRect.x, propertiesRect.y + 40 + 40}, 240, 35);
  BooleanWidget saveCoinsWidgetCheckpoint = BooleanWidget("Save Coins", true, {propertiesRect.x, propertiesRect.y + 40 + 40 + 40}, 240, 35);
  ColorWidget fillColorWidgetCheckpoint = ColorWidget("Fill", checkpointColorFill, {propertiesRect.x, propertiesRect.y + 40 + 40 + 40 + 40}, 240);
  
  BooleanWidget visibleWidgetFog = BooleanWidget("Visible", true, {propertiesRect.x, propertiesRect.y + 40}, 240, 35);
  TextFieldWidget radiusWidgetFog = TextFieldWidget("Radius", {propertiesRect.x + 10, propertiesRect.y + 40 + 70}, 220, 35, true, 3);
  
  Editor(Level* level) {
    this->level = level;
    camera.zoom = 0.8f;
    camera.rotation = 0.0f;
    camera.target = {-155, -80};
    
    conveyor = Conveyor({20, 410}, RIGHT, level, 0);

    buildButton.setSelected(true);

    speedWidgetConveyor.maxNumber = 300;
    idWidgetKey.maxNumber = 999;
    idWidgetKeyBlock.maxNumber = 999;
    radiusWidgetFog.maxNumber = 999;

    if (level->background.backgroundType == PLAIN) plainWidget.setSelected(true);
    else checkerboardWidget.setSelected(true);

    backgroundPrimaryColorWidget.color = level->background.colorPrimary;
    backgroundSecondaryColorWidget.color = level->background.colorSecondary;

    buildEditWidgets.push_back(&buildWallblockButton);
    buildEditWidgets.push_back(&buildBackgroundBlockButton);
    buildEditWidgets.push_back(&buildEnemyButton);
    buildEditWidgets.push_back(&buildCoinButton);
    buildEditWidgets.push_back(&buildKeyButton);
    buildEditWidgets.push_back(&buildKeyBlockButton);
    buildEditWidgets.push_back(&buildConveyorButton);
    buildEditWidgets.push_back(&buildCheckpointButton);
    buildEditWidgets.push_back(&buildFogBlockButton);
    buildEditWidgets.push_back(&buildPlayerButton);
    buildEditWidgets.push_back(&editUpButton);
    buildEditWidgets.push_back(&editSmallUpButton);
    buildEditWidgets.push_back(&editDownButton);
    buildEditWidgets.push_back(&editSmallDownButton);
    buildEditWidgets.push_back(&editRightButton);
    buildEditWidgets.push_back(&editSmallRightButton);
    buildEditWidgets.push_back(&editLeftButton);
    buildEditWidgets.push_back(&editSmallLeftButton);
    buildEditWidgets.push_back(&editDuplicateButton);
    buildEditWidgets.push_back(&editTrashButton);
    buildEditWidgets.push_back(&editPathButton);
    buildEditWidgets.push_back(&configButton);
    buildEditWidgets.push_back(&playButton);
    buildEditWidgets.push_back(&editButton);
    buildEditWidgets.push_back(&buildButton);

    propertyWidgets.push_back(&outlineColorWidgetWallblock);
    propertyWidgets.push_back(&fillColorWidgetWallblock);
    propertyWidgets.push_back(&fillColorWidgetBackgroundblock);
    propertyWidgets.push_back(&outlineColorWidgetEnemy);
    propertyWidgets.push_back(&fillColorWidgetEnemy);
    propertyWidgets.push_back(&outlineColorWidgetCoin);
    propertyWidgets.push_back(&fillColorWidgetCoin);
    propertyWidgets.push_back(&outlineColorWidgetKey);
    propertyWidgets.push_back(&fillColorWidgetKey);
    propertyWidgets.push_back(&idWidgetKey);
    propertyWidgets.push_back(&fillColorWidgetKeyBlock);
    propertyWidgets.push_back(&outlineColorWidgetKeyBlock);
    propertyWidgets.push_back(&idWidgetKeyBlock);
    propertyWidgets.push_back(&speedWidgetConveyor);
    propertyWidgets.push_back(&directionWidgetConveyor);
    propertyWidgets.push_back(&fillColorWidgetConveyor);
    propertyWidgets.push_back(&arrowColorWidgetConveyor);
    propertyWidgets.push_back(&goalWidgetCheckpoint);
    propertyWidgets.push_back(&saveCoinsWidgetCheckpoint);
    propertyWidgets.push_back(&saveKeysWidgetCheckpoint);
    propertyWidgets.push_back(&fillColorWidgetCheckpoint);
    propertyWidgets.push_back(&freeCameraWidget);
    propertyWidgets.push_back(&plainWidget);
    propertyWidgets.push_back(&checkerboardWidget);
    propertyWidgets.push_back(&backgroundPrimaryColorWidget);
    propertyWidgets.push_back(&backgroundSecondaryColorWidget);
    propertyWidgets.push_back(&visibleWidgetFog);
    propertyWidgets.push_back(&radiusWidgetFog);
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
  void selectFogButton();
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
  
  void pathButton();

  void newPath();
  void deletePath();

  void newInstruction();
  void deleteInstruction();

  void configurationButton();
  void playTestButton();

  void checkerboardButton();
  void plainButton();

  void tickSettings(GameObject* object);

  std::vector<GameObject*> getAllGameObjectsInPos(Vector2 pos, int layer);

  std::vector<GameObject*> getAllGameObjectsInRect(Rectangle rect, int layer);

  template <typename T>
  std::vector<T*> getAllGameObjectsInLayer(int layer);

  template <typename T>
  std::vector<T*> getGameObjectsInPosAndLayer(Vector2 pos, int layer);

  bool isSingleType(std::vector<GameObject*>& gameObjects);
 
  bool areSamePath(std::vector<GameObject*>& gameObjects);

  void deselectAll();
};

#endif
