#include "io.hpp"
#include <cstring>

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
  TWHGReloaded::menu.menuState = 4;
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
  account = whoamiAccount(response);
  if (account != nullptr) {
    TWHGReloaded::menu.menuState = 4;
    TWHGReloaded::menu.loginFetch = "";
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
  TWHGReloaded::menu.menuState = 4;
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

  return acc;
};
