#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <vector>

#define LEN 10

/****** constexpr ******/

constexpr int len_foo_constexpr() { return 5; }

constexpr int fibonacci(const int n) {
  // From C++11
  // return n == 1 || n == 2 ? 1 : fibonacci(n-1) + fibonacci(n-2);

  // From C++14, can use `if` in `constexpr` functions
  if (n == 1 || n == 2) {
    return 2;
  }
  return fibonacci(n - 1) + fibonacci(n - 2);
}

constexpr void run_constepr() { std::cout << fibonacci(10) << std::endl; }

/****** Variable definition in `if` ******/

void run_variable_definition_in_if() {
  std::vector<int> vec = {1, 2, 3, 4};

  // From C++17, initialize variables in `if`
  if (const std::vector<int>::iterator it =
          std::find(vec.begin(), vec.end(), 3);
      it != vec.end()) {
    *it = 100;
  }

  for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
    std::cout << *it << std::endl;
  }
}

/****** Initialize list ******/

class Foo1 {
 public:
  Foo1(std::initializer_list<int> list) {
    for (std::initializer_list<int>::iterator it = list.begin();
         it != list.end(); it++) {
      vec_.push_back(*it);
    }
  }

 private:
  std::vector<int> vec_;
};

void run_initialize_list() {
	Foo1 foo1 = Foo1({1, 2, 3, 4});
}

int main() {
  run_constepr();
  run_variable_definition_in_if();
  run_initialize_list();
}
