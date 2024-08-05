#ifndef MENU_HPP
#define MENU_HPP

#include "../level/level.hpp"
#include "../widget/widgets/textfieldwidget.hpp"

class Menu {
public:
  bool ticked = false;

  Level fakeLevel = Level(-1);

  bool right = true;

  int menuState = 0;

  TextFieldWidget loginWidget = TextFieldWidget("", {100, 200}, 220, 30, false, 12);
  TextFieldWidget passwordWidget = TextFieldWidget("", {100, 260}, 220, 30, false, 16);

  Menu() {};

  void tick();

  void singlePlayer();
  void multiPlayer();
  void levelEditor();
  void leaderboards();
  void accounts();
  void settings();
  void credits();
  void exit();

  void back();
  void backAc();

  void masterSlider();
  void musicSlider();
  void soundEffectsSlider();

  void loginB();
  void loginBB();
  void registerB();
  void registerBB();
  void saveB();
  void loadB();
  void logoutB();

  void getLevelStats();

  std::map<int, std::string> difMap;
  std::map<int, std::string> wrMap;
  std::map<int, std::pair<std::string, std::string>> pbMap;

  std::string loginFetch = "";
  std::string top10Fetch = "";
  std::string whoamiFetch = "";

  void button(std::string text, Rectangle rect, std::function<void()> func);
  void levelButton(std::string text, float time, std::string wrHolder, Rectangle rect, int levelId);
};

#endif
