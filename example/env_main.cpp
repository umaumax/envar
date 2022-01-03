#include <string.h>

#include <functional>
#include <iostream>

#include "envar.hpp"

int main(int argc, const char *argv[]) {
  int MEM_MAX_ENV     = 0;
  bool OVER_FORCE_ENV = false;
  printf("pre getInt\n");
  MEM_MAX_ENV = envar::GetInt("MEM_MAX", 512);
  printf("post getInt\n");
  std::cout << "MEM_MAX = " << MEM_MAX_ENV << std::endl;

  printf("pre getBool\n");
  OVER_FORCE_ENV = envar::GetBool("OVER_FORCE", false);
  printf("post getBool\n");
  std::cout << "OVER_FORCE = " << OVER_FORCE_ENV << std::endl;

  std::function<void(std::string)> printFunc = [](std::string str) {
    std::cout << str << std::endl;
  };
  printFunc("lambda print 1");

  void *ptr = (void *)&printFunc;
  bool ret  = envar::SetPtr<void *>("FUNC_PTR", ptr);
  std::cout << (ret ? "OK" : "ERROR") << std::endl;
  ptr = envar::GetPtr<void *>("FUNC_PTR");
  std::cout << "FUNC_PTR = " << (uintptr_t)ptr << std::endl;

  // passing function pointers via environment variables
  auto func = *envar::GetPtr<std::function<void(std::string)> *>("FUNC_PTR");
  func("lambda func calling via ptr");
  return 0;
}
