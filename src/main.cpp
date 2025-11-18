/**
 *    @file main.cpp
 *    @brief main file
 *    @author rouxfederico@gmail.com
 */

#include <atomic>
#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <functional>
#include <vector>
#include <chrono>

void print_message() {
  std::cout << "Hello from thread" << std::endl;
}

void count_to(std::mutex& mtx, const int n, const std::string& name) {
  for(auto i = 1; i <= n; i++) {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << name << ": " << i << std::endl;
  }
}

int counter = 0;

void increment(std::mutex& mtx, const int times) {
  for (int i = 0; i < times; ++i) {
      std::unique_lock<std::mutex> lock(mtx);
      ++counter;
      std::cout << "Counter: " << counter << std::endl;
      lock.unlock();  // ✓ Unlock early!

      // Do expensive work WITHOUT holding the lock
      std::this_thread::sleep_for(std::chrono::milliseconds(10));

      // Can lock again if needed
      lock.lock();
      std::cout << "Thread still working..." << std::endl;
  }
}

std::atomic<int> atomic_counter{0};

void atomic_increment(const int times) {
  for(auto i = 0; i < times; i++) {
    atomic_counter++;
    std::cout << "Counter: " << atomic_counter << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

void spawn_single_threads() {
  std::mutex mtx;

  const int thread_1_max = 6;
  const int thread_2_max = 3;

  std::cout << "Spawning single threads" << std::endl;

  std::thread t1(count_to, std::ref(mtx), thread_1_max, "thread-1");
  std::thread t2(count_to, std::ref(mtx), thread_2_max, "thread-2");
  t1.join();
  t2.join();
}

void spawn_vectorized_threads(const int max) {
  std::vector<std::thread> threads;

  std::cout << "Spawning vectorized threads| max : " << max << std::endl;
  for(auto i = 0; i < max; i++) {
    threads.emplace_back([i](){std::cout << "thread-" << i << "running" << std::endl;});
  }

  for (auto& t : threads) {
    t.join();
  }
}

void threads_sync_unique_lock(const int max) {
  std::vector<std::thread> threads;
  std::mutex mtx;

  std::cout << "Spawning threads - unique lock | max : " << max << std::endl;
  for(auto i = 0; i < max; i++) {
    threads.emplace_back(increment, std::ref(mtx), i);
  }

  for (auto& t : threads) {
    t.join();
  }
}

void threads_atomic_counter(const int max) {
  std::vector<std::thread> threads;

  std::cout << "Spawning threads - atomic lock | max : " << max << std::endl;
  for(auto i = 0; i < max; i++) {
    threads.emplace_back(atomic_increment, i);
  }

  for (auto& t : threads) {
    t.join();
  }
}
/**
 *   @fn main
 *   @brief main program
 */

int main() {

  spawn_single_threads();
  spawn_vectorized_threads(4);
  threads_sync_unique_lock(3);
  threads_atomic_counter(4);
  std::cout << "Hello from main" << std::endl;


  return 0;
}
