/**
 *    @file main.cpp
 *    @brief main file
 *    @author rouxfederico@gmail.com
 */

#include <common.h>
#include <iostream>
#include <thread>
#include <string>

void print_message() {
  std::cout << "Hello from thread" << std::endl;
}

void count_to(const int n, const std::string& name) {
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
  const int thread_2_max = 3;
  Common c;

  std::thread t1(count_to, thread_1_max, "thread-1");
  std::thread t2(count_to, thread_2_max, "thread-2");
  t1.join();
  t2.join();

  std::cout << "Hello from main" << std::endl;


  return 0;
}
