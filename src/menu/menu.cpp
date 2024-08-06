#include "menu.hpp"
#include <algorithm>
#include <functional>
#include <map>
#include <raylib.h>
#include <sstream>
#include <string>
#include <utility>
#include "../utils/needed.hpp"
#include "../utils/io.hpp"


//TODO: fix this nightmare
void Menu::getLevelStats() {
  getWorldRecord(1);
  getPersonalBest(1);
  getDifficulty(1);
}

void Menu::button(std::string text, Rectangle rect, std::function<void()> func) {
  bool hovered = CheckCollisionPointRec(TWHGReloaded::mouse, rect);
  if (text == "Multiplayer") {
    hovered = false;
  }
  DrawRectangleRec(rect, hovered ? Color{250, 200, 80, 255} : Color{33, 33, 33, 255});
  DrawText(text.c_str(), rect.x + 10, rect.y + 5, 30, WHITE);

  if (hovered && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) func();
}

void Menu::levelButton(std::string text, float time, std::string wrHolder, Rectangle rect, int levelId) {
  bool hovered = CheckCollisionPointRec(TWHGReloaded::mouse, rect);
  DrawRectangleRec(rect, hovered ? Color{250, 200, 80, 255} : Color{33, 33, 33, 255});

  std::string difficultyString = difMap.find(levelId)->second;
  std::string deathsString = pbMap.find(levelId)->second.second;
  //std::string pbString = pbMap.find(levelId)->second.first == "N/A" ? "N/A" : formatTime(std::stof(pbMap.find(levelId)->second.first));
  std::string pbString = pbMap.find(levelId)->second.first;
  if (pbString != "N/A" && pbString != "Not logged") {
    pbString = formatTime(std::stof(pbMap.find(levelId)->second.first));
  }
  std::string wrRes = wrMap.find(levelId)->second;
  std::string wrString = "N/A";
  if (wrRes != "N/A") {

    std::string wrTimeString = "";
    std::string wrHolderString = "";
    std::stringstream ss(wrRes);
    std::getline(ss, wrTimeString, ' ');
    std::getline(ss, wrHolderString, ' ');
    std::getline(ss, wrHolderString, ' ');
    wrTimeString = formatTime(std::stof(wrTimeString));
    wrString = std::string(wrHolderString + " by " + wrTimeString);
  }

  DrawText(std::string(text + "  Difficulty: " + difficultyString + "/10  Deaths: " + deathsString + "  PB: " + pbString).c_str(), rect.x + 10, rect.y + 5, 30, WHITE);
  DrawText(std::string("WR: " + wrString).c_str(), rect.x + 10, rect.y + 40, 35, WHITE);
  //DrawText(std::string("WR: " + formatTime(time) + " by " + wrHolder).c_str(), 750, rect.y + 5, 30, WHITE);
  if (hovered && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    menuState = 0;
    std::string levelPath = std::string("./res/levels/level" + std::to_string(levelId) + ".dat");
    TWHGReloaded::level.deserialize(levelPath);
    TWHGReloaded::level.reset();
    TWHGReloaded::state = PLAYING;
  }
}

void Menu::singlePlayer() {
  menuState = 3;
  getLevelStats();
}

void Menu::multiPlayer() {

}

void Menu::levelEditor() {
  TWHGReloaded::state = EDITOR;
}

void Menu::leaderboards() {
  top10();
}

void Menu::accounts() {
  if (account == nullptr) whoami();
  menuState = 4;

  getWorldRecord(1);
  getPersonalBest(1);
}

void Menu::settings() {
  menuState = 2;
}

void Menu::credits() {
  menuState = 1;
}

void Menu::exit() {
  std::exit(0);
}

void Menu::back() {
  menuState = 0;
}

void Menu::backAc() {
  menuState = 4;
}

void Menu::loginB() {
  menuState = 41;
}

void Menu::loginBB() {
  loginUser(loginWidget.text, passwordWidget.text);
}

void Menu::registerBB() {
  registerUser(loginWidget.text, passwordWidget.text);
}

void Menu::registerB() {
  menuState = 42;
}

void Menu::saveB() {
  saveUser();
}

void Menu::loadB() {
  loadUser();
}

void Menu::logoutB() {
  logoutUser();
}

void Menu::masterSlider() {
  bool hovered = CheckCollisionPointRec(TWHGReloaded::mouse, {static_cast<float>(100 + TWHGReloaded::master * 2 - 10), 250 - 8, 20, 20});

  DrawRectangle(100, 250, 200, 5, RAYWHITE);
  DrawRectangle(100 + TWHGReloaded::master * 2 - 10, 250 - 8, 20, 20, hovered ? GRAY : RAYWHITE);
  
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && hovered) {
    int nvalue = ((TWHGReloaded::mouse.x - 100) / 200.0f) * 100.0f;
    if (nvalue < 0) nvalue = 0;
    else if (nvalue > 100) nvalue = 100;
    TWHGReloaded::master = nvalue;
  }
}

void Menu::musicSlider() {
  bool hovered = CheckCollisionPointRec(TWHGReloaded::mouse, {static_cast<float>(100 + TWHGReloaded::music * 2 - 10), 320 - 8, 20, 20});

  DrawRectangle(100, 320, 200, 5, RAYWHITE);
  DrawRectangle(100 + TWHGReloaded::music * 2 - 10, 320 - 8, 20, 20, hovered ? GRAY : RAYWHITE);
  
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && hovered) {
    int nvalue = ((TWHGReloaded::mouse.x - 100) / 200.0f) * 100.0f;
    if (nvalue < 0) nvalue = 0;
    else if (nvalue > 100) nvalue = 100;
    TWHGReloaded::music = nvalue;
  }
}

void Menu::soundEffectsSlider() {
  bool hovered = CheckCollisionPointRec(TWHGReloaded::mouse, {static_cast<float>(100 + TWHGReloaded::effects * 2 - 10), 390 - 8, 20, 20});

  DrawRectangle(100, 390, 200, 5, RAYWHITE);
  DrawRectangle(100 + TWHGReloaded::effects * 2 - 10, 390 - 8, 20, 20, hovered ? GRAY : RAYWHITE);
  
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && hovered) {
    int nvalue = ((TWHGReloaded::mouse.x - 100) / 200.0f) * 100.0f;
    if (nvalue < 0) nvalue = 0;
    else if (nvalue > 100) nvalue = 100;
    TWHGReloaded::effects = nvalue;
  }
}

void Menu::tick() {
  if (!ticked) {
    difMap.emplace(std::make_pair(1, "N/A"));
    wrMap.emplace(std::make_pair(1, "N/A"));
    pbMap.emplace(std::make_pair(1, std::make_pair("N/A", "N/A")));

    getLevelStats();
    whoami();
    ticked = true;
    fakeLevel.deserialize("./res/levels/level1.dat");
    fakeLevel.camera.target.y += 40;

    loginWidget.menu = true;
    passwordWidget.menu = true;
    passwordWidget.password = true;
  }

  fakeLevel.camera.target.x += GetFrameTime() * 10 * (right ? 1 : -1);
  if (fakeLevel.camera.target.x > 1200) {
    right = false;
    fakeLevel.camera.target.x = 1199;
  } else if (fakeLevel.camera.target.x < 0){
    right = true;
    fakeLevel.camera.target.x = 1;
  }

  BeginMode2D(fakeLevel.camera);
  fakeLevel.background.tick(fakeLevel.camera);

  tickConveyorManager();

  std::vector<Path*> pathsTicked;
  for (int i = 0; i < fakeLevel.gameObjects.size(); i++) {
    //for (GameObject* gameObject : gameObjects) {
    GameObject* gameObject = fakeLevel.gameObjects[i];
    for (int pathId : gameObject->pathIds) {
      Path* path = fakeLevel.findPath(pathId);
      if (std::find(pathsTicked.begin(), pathsTicked.end(), path) == pathsTicked.end()) {
        path->tick();
        pathsTicked.push_back(path);
      }
    }

    gameObject->tick(&fakeLevel.player);
   
    //last vector reset in order to fix inaccuracies (circle movement moment)
    for (Path* path : pathsTicked) {
      if (!path->instructions.empty()) {
        if (i == fakeLevel.gameObjects.size() - 1) path->getCurrentInstruction()->last = {0.0f, 0.0f};
      }
    }
  }
  EndMode2D();
 
  DrawRectangleRec({0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}, {0, 0, 0, 100});
 
  if (IsKeyReleased(KEY_ESCAPE) && (menuState != 41 && menuState != 42)) back();
  if (menuState == 0) {
    button("Singleplayer", {80, 250, 250, 40}, std::bind(&Menu::singlePlayer, this));
    button("Multiplayer", {80, 250 + 50 * 1, 250, 40}, std::bind(&Menu::multiPlayer, this));
    button("Level Editor", {80, 250 + 50 * 2, 250, 40}, std::bind(&Menu::levelEditor, this));
    button("Leaderboards", {80, 250 + 50 * 3, 250, 40}, std::bind(&Menu::leaderboards, this));
    button("Accounts", {80, 250 + 50 * 4, 250, 40}, std::bind(&Menu::accounts, this));
    button("Settings", {80, 250 + 50 * 5, 250, 40}, std::bind(&Menu::settings, this));
    button("Credits", {80, 250 + 50 * 6, 250, 40}, std::bind(&Menu::credits, this));
    button("Exit", {80, 250 + 50 * 7, 250, 40}, std::bind(&Menu::exit, this));

    DrawTextureEx(twhgTexture, {80, 50}, 0.0f, 0.26f, WHITE);
  } else if (menuState == 1) {
    button("<- Back", {80, 50, 130, 40}, std::bind(&Menu::back, this));

    DrawText("Credits", 80, 110, 50, WHITE);
    DrawRectangleRec({80, 160, 1100, 500}, {0, 0, 0, 100});
    DrawText("Developer", 100, 170, 30, WHITE);
    DrawText("danimania", 100, 200, 30, WHITE);
    DrawText("Art Director", 100, 250, 30, WHITE);
    DrawText("sergiolan55", 100, 280, 30, WHITE);
    DrawText("- \"I would rather eat broken glass than play this game\"", 100, 310, 30, WHITE);
    DrawText("Feel free to send suggestions or bug reports in the Discord server", 100, 350, 30, WHITE);
    DrawText("(twhgr.danimania.dev/discord) and feel free to support the game:", 100, 380, 30, WHITE);
    DrawText("ko-fi.com/danimania", 100, 410, 30, WHITE);
    
    if (IsKeyDown(KEY_ESCAPE)) menuState = 0;
  } else if (menuState == 2) {
    button("<- Back", {80, 50, 130, 40}, std::bind(&Menu::back, this));
    
    DrawText("Settings", 80, 110, 50, WHITE);
    DrawRectangleRec({80, 160, 1100, 500}, {0, 0, 0, 100});
    DrawText("Volume", 100, 170, 40, WHITE);
    DrawText(std::string("Master: " + std::to_string((int) TWHGReloaded::master) + "%").c_str(), 100, 210, 30, WHITE);
    masterSlider();
    DrawText(std::string("Music: " + std::to_string((int) TWHGReloaded::music) + "%").c_str(), 100, 280, 30, WHITE);
    musicSlider();
    DrawText(std::string("Sound Effects: " + std::to_string((int) TWHGReloaded::effects) + "%").c_str(), 100, 350, 30, WHITE);
    soundEffectsSlider();

    updateVolumes();
    
    if (IsKeyDown(KEY_ESCAPE)) menuState = 0;
  } else if (menuState == 3) {
    button("<- Back", {80, 50, 130, 40}, std::bind(&Menu::back, this));
    
    DrawText("Singleplayer", 80, 110, 50, WHITE);
    DrawRectangleRec({80, 160, 1100, 500}, {0, 0, 0, 100});
    
    levelButton("1 - Unnamed Level", 574, "danimania", {100, 180, 1050, 80}, 1);
    
    if (IsKeyDown(KEY_ESCAPE)) menuState = 0;
  } else if (menuState == 4) {
    button("<- Back", {80, 50, 130, 40}, std::bind(&Menu::back, this));
    
    DrawText("Accounts", 80, 110, 50, WHITE);
    DrawRectangleRec({80, 160, 1100, 500}, {0, 0, 0, 100});
    DrawText(std::string("You are currently " + std::string(account == nullptr ? "not logged in!" : "logged in!")).c_str(), 100, 170, 30, WHITE);
    if (account != nullptr) {
      std::string accountType = "User";
      if (account->access == 2) accountType = "Moderator";
      else if (account->access == 3) accountType = "Administrator";

      DrawText(std::string("Username: " + account->username).c_str(), 100, 210, 30, WHITE);
      DrawText(std::string("Account type: " + accountType).c_str(), 100, 250, 30, WHITE);
      DrawText(std::string("Deaths: " + std::to_string(account->deaths)).c_str(), 100, 290, 30, WHITE);
      DrawText(std::string("Time played: " + formatTime(account->time)).c_str(), 100, 330, 30, WHITE);
      DrawText(std::string("Score: " + std::to_string(account->score)).c_str(), 100, 370, 30, WHITE);

      button("Save", {110, 410, 130, 40}, std::bind(&Menu::saveB, this));
      button("Load", {110, 460, 130, 40}, std::bind(&Menu::loadB, this));
      button("Logout", {110, 510, 130, 40}, std::bind(&Menu::logoutB, this));
    } else {
      button("Login", {100, 200, 150, 40}, std::bind(&Menu::loginB, this));
      button("Register", {100, 250, 150, 40}, std::bind(&Menu::registerB, this));
    }
  } else if (menuState == 41) {

    if (IsKeyReleased(KEY_ESCAPE)) backAc();

    button("<- Back", {80, 50, 130, 40}, std::bind(&Menu::backAc, this));
  
    DrawText("Accounts", 80, 110, 50, WHITE);
    DrawRectangleRec({80, 160, 1100, 500}, {0, 0, 0, 100});

    DrawText("Username", 100, 180, 20, RAYWHITE);
    loginWidget.tick();

    DrawText("Password", 100, 240, 20, RAYWHITE);
    passwordWidget.tick();

    button("Login", {100, 300, 150, 40}, std::bind(&Menu::loginBB, this));

    DrawText(loginFetch.c_str(), 100, 350, 20, RED);
  } else if (menuState == 42) {
    
    if (IsKeyReleased(KEY_ESCAPE)) backAc();
    
    button("<- Back", {80, 50, 130, 40}, std::bind(&Menu::backAc, this));
    
    DrawText("Accounts", 80, 110, 50, WHITE);
    DrawRectangleRec({80, 160, 1100, 500}, {0, 0, 0, 100});

    DrawText("Username", 100, 180, 20, RAYWHITE);
    loginWidget.tick();

    DrawText("Password", 100, 240, 20, RAYWHITE);
    passwordWidget.tick();

    button("Register", {100, 300, 150, 40}, std::bind(&Menu::registerBB, this));

    DrawText(loginFetch.c_str(), 100, 350, 20, RED);
  } else if (menuState == 5) {

    if (IsKeyReleased(KEY_ESCAPE)) backAc();
    
    button("<- Back", {80, 50, 130, 40}, std::bind(&Menu::back, this));
    
    DrawText("Leaderboards", 80, 110, 50, WHITE);
    DrawRectangleRec({80, 160, 1100, 500}, {0, 0, 0, 100});

    DrawText("Username", 100, 180, 20, WHITE);
    DrawText("Deaths", 400, 180, 20, WHITE);
    DrawText("Time played", 650, 180, 20, WHITE);
    DrawText("Score", 1000, 180, 20, WHITE);
    for (int i = 0; i < 10; i++) {
      DrawRectangleRec({100, 200 + i * 40.0f, 1060, 40}, (i % 2 == 0 ? Color{0, 0, 0, 100} : Color{0, 0, 0, 200}));
      /*DrawText("danimania", 110, 200 + i * 40.0f + 5, 30, WHITE);
      DrawText("0", 400, 200 + i * 40.0f + 5, 30, WHITE);
      DrawText("00:00.00", 650, 200 + i * 40.0f + 5, 30, WHITE);
      DrawText("999", 1000, 200 + i * 40.0f + 5, 30, WHITE);*/
    }

    std::string playerline = "";
    std::stringstream ss(top10Fetch);
    int count = 0;
    while(std::getline(ss, playerline, '\n')) {
      std::string name = "";
      std::string deaths = "";
      std::string time = "";
      std::string score = "";
      std::stringstream ss2(playerline);

      std::getline(ss2, name, ' ');
      std::getline(ss2, deaths, ' ');
      std::getline(ss2, time, ' ');
      std::getline(ss2, score, ' ');

      time = formatTime(std::stof(time));

      DrawText(name.c_str(), 110, 200 + count * 40.0f + 5, 30, WHITE);
      DrawText(deaths.c_str(), 400, 200 + count * 40.0f + 5, 30, WHITE);
      DrawText(time.c_str(), 650, 200 + count * 40.0f + 5, 30, WHITE);
      DrawText(score.c_str(), 1000, 200 + count * 40.0f + 5, 30, WHITE);
      
      count++;
    }
  }
}
