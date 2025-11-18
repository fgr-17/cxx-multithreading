/**
 *    @file main.cpp
 *    @brief main file
 *    @author rouxfederico@gmail.com
 */

#include <common.h>
#include <iostream>
#include <thread>
#include <string>

void printMessage() {
  std::cout << "Hello from thread" << std::endl;
}

void countTo(const int n, const std::string& name) {
  for(auto i = 1; i <= n; i++) {
    std::cout << name << ": " << i << std::endl;
  }
}

/**
 *   @fn main
 *   @brief main program
 */

int main() {
  const int thread_1_max = 6;
  Common c;

  std::thread t(countTo, thread_1_max, "thread-1");
  t.join();

  std::cout << "Hello from main" << std::endl;


  return 0;
}
