#ifndef IO_HPP
#define IO_HPP

#include <functional>
#if defined(__EMSCRIPTEN__)
  #include <emscripten/emscripten.h>
  #include <emscripten/fetch.h>
#else
  #include <curl/curl.h>
#endif
#include <string>

struct Account {
  int id;
  std::string username;
  int access;
  int deaths;
  float time;
  int score;
};

inline Account* account;
#if defined(__EMSCRIPTEN__)
#else
inline CURL* curl;
#endif
bool status();
std::string loginUser(std::string username, std::string password);
std::string registerUser(std::string username, std::string password);
std::string whoami();
void logoutUser();
void loadUser();
void saveUser();
std::string top10();

Account* whoamiAccount(std::string whoami);

#endif
