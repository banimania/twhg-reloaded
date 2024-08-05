#include "io.hpp"
#include <cstring>
#include <utility>

#if defined(__EMSCRIPTEN__)
  #include <emscripten/emscripten.h>
  #include <emscripten/fetch.h>
#else
  #include <curl/curl.h>
  #include <curl/easy.h>
#endif
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include "needed.hpp"

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
  ((std::string*)userp)->append((char*)contents, size * nmemb);
  return size * nmemb;
}

#if defined(__EMSCRIPTEN__)
void top10loaded(emscripten_fetch_t* fetch) {
  std::string res = "";
  for (int i = 0; i < fetch->numBytes; i++) {
    res += fetch->data[i];
  }
  emscripten_fetch_close(fetch);
  TWHGReloaded::menu.top10Fetch = res;
  TWHGReloaded::menu.menuState = 5;
}

void whoamiloaded(emscripten_fetch_t* fetch) {
  std::string res = "";
  for (int i = 0; i < fetch->numBytes; i++) {
    res += fetch->data[i];
  }
  emscripten_fetch_close(fetch);
  TWHGReloaded::menu.whoamiFetch = res;
  account = whoamiAccount(res);
  if (TWHGReloaded::menu.menuState != 0) TWHGReloaded::menu.menuState = 4;
  TWHGReloaded::menu.getLevelStats();
}

void loginloaded(emscripten_fetch_t* fetch) {
  std::string res = "";
  for (int i = 0; i < fetch->numBytes; i++) {
    res += fetch->data[i];
  }
  emscripten_fetch_close(fetch);
  TWHGReloaded::menu.loginFetch = res;
  if (res == "Logged in successfully!\n") {
    whoami();
    TWHGReloaded::menu.loginWidget.text = "";
    TWHGReloaded::menu.passwordWidget.text = "";
    TWHGReloaded::menu.loginFetch = "";
    TWHGReloaded::menu.menuState = 4;
  }
}

void registerloaded(emscripten_fetch_t* fetch) {
  std::string res = "";
  for (int i = 0; i < fetch->numBytes; i++) {
    res += fetch->data[i];
  }
  emscripten_fetch_close(fetch);
  TWHGReloaded::menu.loginFetch = res;
  if (res == "Registered successfully!\n") {
    TWHGReloaded::menu.loginWidget.text = "";
    TWHGReloaded::menu.passwordWidget.text = "";
    TWHGReloaded::menu.loginFetch = "";
    TWHGReloaded::menu.menuState = 4;
  }
}

void logoutloaded(emscripten_fetch_t* fetch) {
  std::string res = "";
  for (int i = 0; i < fetch->numBytes; i++) {
    res += fetch->data[i];
  }
  emscripten_fetch_close(fetch);
  account = nullptr;
}

void submitloaded(emscripten_fetch_t* fetch) {
  std::string res = "";
  for (int i = 0; i < fetch->numBytes; i++) {
    res += fetch->data[i];
  }
  emscripten_fetch_close(fetch);
  TWHGReloaded::level.submitScoreFetch = res;
}

void wrloaded(emscripten_fetch_t* fetch) {
  std::string res = "";
  for (int i = 0; i < fetch->numBytes; i++) {
    res += fetch->data[i];
  }
  emscripten_fetch_close(fetch);
  TWHGReloaded::menu.wrMap.insert_or_assign(1, res);
}

void pbloaded(emscripten_fetch_t* fetch) {
  std::string res = "";
  for (int i = 0; i < fetch->numBytes; i++) {
    res += fetch->data[i];
  }
  emscripten_fetch_close(fetch);
  std::string time = "";
  std::string deaths = "";

  if (res == "Not logged in!") {
    time = "Not logged";
    deaths = "N/A";
  } else {
    std::stringstream ss(res);
    std::getline(ss, time, ' ');
    std::getline(ss, deaths, ' ');
  }

  TWHGReloaded::menu.pbMap.insert_or_assign(1, std::make_pair(time, deaths));
}

void difloaded(emscripten_fetch_t* fetch) {
  std::string res = "";
  for (int i = 0; i < fetch->numBytes; i++) {
    res += fetch->data[i];
  }
  emscripten_fetch_close(fetch);
  TWHGReloaded::menu.difMap.insert_or_assign(1, res);
}
#endif

bool status() {
  #if defined(__EMSCRIPTEN__)
  return "";  
  #else
  bool returnValue = false;
  curl = curl_easy_init();

  std::string response;

  curl_easy_setopt(curl, CURLOPT_URL, "https://twhgr.danimania.dev/server/status.php");
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

  curl_easy_perform(curl);
  if (response == "online") returnValue = true;
  curl_easy_cleanup(curl);

  return returnValue;
  #endif
}

std::string loginUser(std::string username, std::string password) {
  #if defined(__EMSCRIPTEN__)
  emscripten_fetch_attr_t attr;
  emscripten_fetch_attr_init(&attr);
  strcpy(attr.requestMethod, "POST");
  attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
  attr.onsuccess = loginloaded;

  const char* headers[] = {"Content-Type", "application/x-www-form-urlencoded", NULL};

  size_t body_size = strlen("username=") + strlen(username.c_str()) + strlen("&password=") + strlen(password.c_str()) + 1;
  char* body = new char[body_size];
  snprintf(body, body_size, "username=%s&password=%s", username.c_str(), password.c_str());
  
  attr.requestHeaders = headers;
  attr.requestData = body;
  attr.requestDataSize = body_size;

  emscripten_fetch(&attr, "https://twhgr.danimania.dev/server/login.php");
  return "";
  #else

  curl = curl_easy_init();

  std::string response;

  std::string postData = std::string("username=" + username + "&password=" + password);
  curl_easy_setopt(curl, CURLOPT_URL, "https://twhgr.danimania.dev/server/login.php");
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
  
  curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookies.txt");
  curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookies.txt");
  
  curl_easy_perform(curl);
  curl_easy_cleanup(curl);

  TWHGReloaded::menu.loginFetch = response;
  if (response == "Logged in successfully!\n") {
    whoami();
    TWHGReloaded::menu.loginWidget.text = "";
    TWHGReloaded::menu.passwordWidget.text = "";
    TWHGReloaded::menu.loginFetch = "";
    TWHGReloaded::menu.menuState = 4;
  }

  return "";
  #endif
};

std::string registerUser(std::string username, std::string password) {
  #if defined(__EMSCRIPTEN__)
  emscripten_fetch_attr_t attr;
  emscripten_fetch_attr_init(&attr);
  strcpy(attr.requestMethod, "POST");
  attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
  attr.onsuccess = registerloaded;

  const char* headers[] = {"Content-Type", "application/x-www-form-urlencoded", NULL};

  size_t body_size = strlen("username=") + strlen(username.c_str()) + strlen("&password=") + strlen(password.c_str()) + 1;
  char* body = new char[body_size];
  snprintf(body, body_size, "username=%s&password=%s", username.c_str(), password.c_str());
  
  attr.requestHeaders = headers;
  attr.requestData = body;
  attr.requestDataSize = body_size;

  emscripten_fetch(&attr, "https://twhgr.danimania.dev/server/register.php");
  return "";
  #else 
  curl = curl_easy_init();

  std::string response;

  std::string postData = std::string("username=" + username + "&password=" + password);
  curl_easy_setopt(curl, CURLOPT_URL, "https://twhgr.danimania.dev/server/register.php");
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
  
  curl_easy_perform(curl);
  curl_easy_cleanup(curl);

  TWHGReloaded::menu.menuState = 4;
  return response;

  #endif
};

std::string whoami() {

  #if defined(__EMSCRIPTEN__)
  emscripten_fetch_attr_t attr;
  emscripten_fetch_attr_init(&attr);
  strcpy(attr.requestMethod, "POST");
  attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
  attr.onsuccess = whoamiloaded;
  emscripten_fetch(&attr, "https://twhgr.danimania.dev/server/whoami.php");
  return "";
  #else
  curl = curl_easy_init();

  std::string response;

  curl_easy_setopt(curl, CURLOPT_URL, "https://twhgr.danimania.dev/server/whoami.php");
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
  
  curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookies.txt");
  curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookies.txt");
  
  curl_easy_perform(curl);
  curl_easy_cleanup(curl);

  TWHGReloaded::menu.whoamiFetch = response;
  if (TWHGReloaded::menu.menuState != 0) TWHGReloaded::menu.menuState = 4;
  account = whoamiAccount(response);

  return "";
  #endif
};

std::string top10() {
  #if defined(__EMSCRIPTEN__)
  emscripten_fetch_attr_t attr;
  emscripten_fetch_attr_init(&attr);
  strcpy(attr.requestMethod, "POST");
  attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
  attr.onsuccess = top10loaded;
  emscripten_fetch(&attr, "https://twhgr.danimania.dev/server/leaderboards.php");
  return "";
  #else
  curl = curl_easy_init();

  std::string response;

  curl_easy_setopt(curl, CURLOPT_URL, "https://twhgr.danimania.dev/server/leaderboards.php");
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
  
  curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookies.txt");
  curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookies.txt");
  
  curl_easy_perform(curl);
  curl_easy_cleanup(curl);

  TWHGReloaded::menu.top10Fetch = response;
  TWHGReloaded::menu.menuState = 5;
  return "";
  #endif
}

void logoutUser() {
  #if defined(__EMSCRIPTEN__)
  emscripten_fetch_attr_t attr;
  emscripten_fetch_attr_init(&attr);
  strcpy(attr.requestMethod, "POST");
  attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
  attr.onsuccess = logoutloaded;
  emscripten_fetch(&attr, "https://twhgr.danimania.dev/server/logout.php");
  #else
  curl = curl_easy_init();

  std::string response;

  curl_easy_setopt(curl, CURLOPT_URL, "https://twhgr.danimania.dev/server/logout.php");
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
  
  curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookies.txt");
  curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookies.txt");
  
  curl_easy_perform(curl);
  curl_easy_cleanup(curl);

  account = nullptr;

  #endif
}

void loadUser() {
  whoami();
}

void saveUser() {
  #if defined(__EMSCRIPTEN__)
  emscripten_fetch_attr_t attr;
  emscripten_fetch_attr_init(&attr);
  strcpy(attr.requestMethod, "POST");
  attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;

  const char* headers[] = {"Content-Type", "application/x-www-form-urlencoded", NULL};

  size_t body_size = strlen("deaths=") + strlen(std::to_string(account->deaths).c_str()) + strlen("&time=") + strlen(std::to_string(account->time).c_str()) + strlen("&score=") + strlen(std::to_string(account->score).c_str()) + 1;
  char* body = new char[body_size];
  snprintf(body, body_size, "deaths=%s&time=%s&score=%s", std::to_string(account->deaths).c_str(), std::to_string(account->time).c_str(), std::to_string(account->score).c_str());

  attr.requestHeaders = headers;
  attr.requestData = body;
  attr.requestDataSize = body_size;

  emscripten_fetch(&attr, "https://twhgr.danimania.dev/server/save.php");
  #else
  curl = curl_easy_init();

  std::string response;

  std::string postData = std::string("deaths=" + std::to_string(account->deaths) + "&time=" + std::to_string(account->time) + "&score=" + std::to_string(account->score));
  curl_easy_setopt(curl, CURLOPT_URL, "https://twhgr.danimania.dev/server/save.php");
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
  
  curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookies.txt");
  curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookies.txt");

  curl_easy_perform(curl);
  curl_easy_cleanup(curl);
  #endif
}

void submitScore(int levelId, float time, int deaths) {
  #if defined(__EMSCRIPTEN__)
  emscripten_fetch_attr_t attr;
  emscripten_fetch_attr_init(&attr);
  strcpy(attr.requestMethod, "POST");
  attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;

  const char* headers[] = {"Content-Type", "application/x-www-form-urlencoded", NULL};

  size_t body_size = strlen("levelid=") + strlen(std::to_string(levelId).c_str()) + strlen("&besttime=") + strlen(std::to_string(time).c_str()) + strlen("&deaths=") + strlen(std::to_string(deaths).c_str()) + 1;
  char* body = new char[body_size];
  snprintf(body, body_size, "levelid=%s&besttime=%s&deaths=%s", std::to_string(levelId).c_str(), std::to_string(time).c_str(), std::to_string(deaths).c_str());

  attr.requestHeaders = headers;
  attr.requestData = body;
  attr.requestDataSize = body_size;
  attr.onsuccess = submitloaded;

  emscripten_fetch(&attr, "https://twhgr.danimania.dev/server/submitscore.php");
  #else
  curl = curl_easy_init();

  std::string response;

  std::string postData = std::string("levelid=" + std::to_string(levelId) + "&besttime=" + std::to_string(time) + "&deaths=" + std::to_string(deaths));
  curl_easy_setopt(curl, CURLOPT_URL, "https://twhgr.danimania.dev/server/submitscore.php");
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
  
  curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookies.txt");
  curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookies.txt");

  curl_easy_perform(curl);
  curl_easy_cleanup(curl);
 
  TWHGReloaded::level.submitScoreFetch = response;

  TWHGReloaded::menu.getLevelStats();
  #endif
}

void getWorldRecord(int levelId) {
  #if defined(__EMSCRIPTEN__)
  emscripten_fetch_attr_t attr;
  emscripten_fetch_attr_init(&attr);
  strcpy(attr.requestMethod, "POST");
  attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;

  const char* headers[] = {"Content-Type", "application/x-www-form-urlencoded", NULL};

  size_t body_size = strlen("levelid=") + strlen(std::to_string(levelId).c_str()) + 1;
  char* body = new char[body_size];
  snprintf(body, body_size, "levelid=%s", std::to_string(levelId).c_str());

  attr.requestHeaders = headers;
  attr.requestData = body;
  attr.requestDataSize = body_size;
  attr.onsuccess = wrloaded;
  attr.userData = &levelId;

  emscripten_fetch(&attr, "https://twhgr.danimania.dev/server/getworldrecord.php");
  #else
  curl = curl_easy_init();

  std::string response;

  std::string postData = std::string("levelid=" + std::to_string(levelId));
  curl_easy_setopt(curl, CURLOPT_URL, "https://twhgr.danimania.dev/server/getworldrecord.php");
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
  
  curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookies.txt");
  curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookies.txt");

  curl_easy_perform(curl);
  curl_easy_cleanup(curl);

  TWHGReloaded::menu.wrMap.insert_or_assign(levelId, response);

  #endif
}

void getPersonalBest(int levelId) {
  #if defined(__EMSCRIPTEN__)
  emscripten_fetch_attr_t attr;
  emscripten_fetch_attr_init(&attr);
  strcpy(attr.requestMethod, "POST");
  attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;

  const char* headers[] = {"Content-Type", "application/x-www-form-urlencoded", NULL};

  size_t body_size = strlen("levelid=") + strlen(std::to_string(levelId).c_str()) + 1;
  char* body = new char[body_size];
  snprintf(body, body_size, "levelid=%s", std::to_string(levelId).c_str());

  attr.requestHeaders = headers;
  attr.requestData = body;
  attr.requestDataSize = body_size;
  attr.onsuccess = pbloaded;
  attr.userData = &levelId;

  emscripten_fetch(&attr, "https://twhgr.danimania.dev/server/getpersonalbest.php");
  #else
  curl = curl_easy_init();

  std::string response;

  std::string postData = std::string("levelid=" + std::to_string(levelId));
  curl_easy_setopt(curl, CURLOPT_URL, "https://twhgr.danimania.dev/server/getpersonalbest.php");
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
  
  curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookies.txt");
  curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookies.txt");

  curl_easy_perform(curl);
  curl_easy_cleanup(curl);
  
  std::string time = "";
  std::string deaths = "";

  if (response == "Not logged in!") {
    time = "Not logged";
    deaths = "N/A";
  } else {
    std::stringstream ss(response);
    std::getline(ss, time, ' ');
    std::getline(ss, deaths, ' ');
  }

  TWHGReloaded::menu.wrMap.insert_or_assign(levelId, std::make_pair(time, deaths));

  #endif
}

void getDifficulty(int levelId) {
  #if defined(__EMSCRIPTEN__)
  emscripten_fetch_attr_t attr;
  emscripten_fetch_attr_init(&attr);
  strcpy(attr.requestMethod, "POST");
  attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;

  const char* headers[] = {"Content-Type", "application/x-www-form-urlencoded", NULL};

  size_t body_size = strlen("levelid=") + strlen(std::to_string(levelId).c_str()) + 1;
  char* body = new char[body_size];
  snprintf(body, body_size, "levelid=%s", std::to_string(levelId).c_str());

  attr.requestHeaders = headers;
  attr.requestData = body;
  attr.requestDataSize = body_size;
  attr.onsuccess = difloaded;
  attr.userData = &levelId;

  emscripten_fetch(&attr, "https://twhgr.danimania.dev/server/getdifficulty.php");
  #else
  curl = curl_easy_init();

  std::string response;

  std::string postData = std::string("levelid=" + std::to_string(levelId));
  curl_easy_setopt(curl, CURLOPT_URL, "https://twhgr.danimania.dev/server/getdifficulty.php");
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
  
  curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookies.txt");
  curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookies.txt");

  curl_easy_perform(curl);
  curl_easy_cleanup(curl);
  
  TWHGReloaded::menu.difMap.insert_or_assign(levelId, response);

  #endif
}

Account* whoamiAccount(std::string whoami) {
  if (whoami.empty() || whoami == "Not logged in!") return nullptr;

  Account* acc = new Account();
  
  std::string id = "";
  std::string username = "";
  std::string access = "";
  std::string deaths = "";
  std::string time = "";
  std::string score = "";

  std::stringstream ss(whoami);
  std::getline(ss, id, '\n');
  std::getline(ss, username, '\n');
  std::getline(ss, access, '\n');
  std::getline(ss, deaths, '\n');
  std::getline(ss, time, '\n');
  std::getline(ss, score, '\n');

  acc->id = std::stoi(id);
  acc->username = username;
  acc->access = std::stoi(access);
  acc->deaths = std::stoi(deaths);
  acc->time = std::stof(time);
  acc->score = std::stoi(score);

  TWHGReloaded::menu.getLevelStats();

  return acc;
};
