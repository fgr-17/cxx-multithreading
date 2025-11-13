/**
 *    @file main.cpp
 *    @brief main file
 *    @author rouxfederico@gmail.com
 */

#include <common.h>
#include <iostream>
#include <thread>

void printMessage() {
  std::cout << "Hello from thread" << std::endl;
}


/**
 *   @fn main
 *   @brief main program
 */

int main() {
  Common c;

  std::thread t(printMessage);
  t.join();

  std::cout << "Hello from main" << std::endl;


  return 0;
}
