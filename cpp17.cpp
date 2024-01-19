#include <algorithm>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <tuple>
#include <vector>

struct Employee {
  unsigned id;
  std::string name;
  // Static fields will be ignored in initializing list or structured binding.
  // No matter which position the static field is.
  static const int somethingStatic = 2;
  std::string role;
  unsigned salary;
};

void learn_structured_binding() {
  // Match data from tuple
  // Use `std::make_tuple` to make a tuple from raw data.
  const auto t = std::make_tuple(1, 2, "100");
  const auto [first, second, third] = t;
  std::cout << "[structured binding]"
            << " first:" << first << " second:" << second << " third:" << third
            << std::endl;

  // Match data from struct;
  const auto employee = Employee{1, "Alice", "Bob", 1000};
  const auto [id, name, role, salary] = employee;
  std::cout << "[structured binding]"
            << " id:" << id << " name:" << name << " role:" << role
            << " salary:" << salary << std::endl;
}

void learn_initialize_variable_in_if() {
  // Initialize variable `i` in `if` condition.
  // In the `()`.
  //
  // `i` only lives inside the `if` statement (and `else`).
  if (auto i(2); i == 2) {
    std::cout << "[initialize in if]"
              << " i:" << i << std::endl;
  } else {
    // Here we can also use `i`.
    std::cout << "[initialize in if]"
              << " i(else):" << i << std::endl;
  }
  // ERROR: undeclared variable `i`.
  // std::cout << "can not find i" << i << std::endl;
}

void learn_initialize_with_brackets() {
  int x1 = 1;
  int x2{1};
  int x3(1);

  std::vector<int> v1{1, 2, 3};     // [1, 2, 3]
  std::vector<int> v2 = {1, 2, 3};  // [1, 2, 3]
  // Using contructor, (size, value).
  std::vector<int> v3(5, 20);  // [20, 20, 20, 20, 20]

  auto v4{1};  // int v4 = 1;
  // ERROR: Initializer with type auto contains multiple expressions.
  // auto v5{1, 2};
  // std::initializer_list<int>
  auto v6 = {1};
  // std::initializer_list<int>
  auto v7 = {1, 2};
  // ERROR: Conflict element type.
  // auto v8 = {1, 2, 3.0};

  // `()` has implicit conversion while `{}` not.
  // This means:
  // implicitly casting from double to int.
  int x4(1.2);
  // ERROR: double can not be owned by initializer_list of `int`.
  // int x5 = {1.2};
}

void learn_constexpr_if() {
  if constexpr (true) {
    //
  } else if constexpr (false) {
    //
  }
}

// static inline class member in header file does not encounter multiple
// definition compile error.
class SomeClass {
  static const inline std::string someValue = "foo";
};

template <typename... Ts>
auto sum(Ts... ts) {
  // Give a default value 0 to fit zero-args `ts`.
  return (ts + ... + 0);
}

template <typename R, typename... Ts>
auto sum_at_least_one(const R& first, Ts... other) {
  return (first + ... + other);
}

template <typename T, typename... Ts>
bool within(T min, T max, Ts... ts) {
  //
  return ((min <= ts && ts <= max) && ...);
}

void learn_fold_expression_args() {
  // Fold args.
  const auto theSum = sum(1, 2, 3, 4, 5);
  std::cout << "[fold args]"
            << " theSum:" << theSum << std::endl;
  const auto theSum2 = sum_at_least_one(1, 2, 3, 4, 5);
  std::cout << "[fold args]"
            << " theSum2:" << theSum2 << std::endl;
  // Allowed
  const auto theSum3 = sum();
  std::cout << "[fold args]"
            << " theSum3:" << theSum3 << std::endl;
  // ERROR: No matching function to call `sum_at_least_one`.
  // const auto theSum4 = sum_at_least_one();
}

template <typename T>
void print_vector(const std::vector<T>& vector) {
  auto count = 0;
  for (const auto& v : vector) {
    std::cout << "[containers]"
              << " vector: " << v << " at index:" << count << std::endl;
    count++;
  }
  count = 0;
}

constexpr auto odd = [](auto i) { return i % 2 != 0; };

void learn_containers() {
  // Vector
  auto vector = std::vector<int>{1, 2, 2, 3, 4, 5, 7, 2};

  std::cout << "[containers] vector find the first element of 5" << std::endl;
  const auto pos = std::find(vector.begin(), vector.end(), 5);
  if (pos != vector.cend()) {
    std::cout << "[containers] vector position of element 5: " << *pos
              << std::endl;
  } else {
    std::cout << "[containers] vector does not contain element 5" << std::endl;
  }

  std::cout << "[containers] vector insert element on the tail:" << std::endl;
  vector.emplace_back(100);
  print_vector(vector);

  std::cout << "[containers] vector insert element before the head:"
            << std::endl;
  vector.emplace(vector.begin(), 200);
  print_vector(vector);

  if (!vector.empty()) {
    std::cout << "[containers] vector remove the last element:" << std::endl;
    // pop_back on an empty vector is UB!
    vector.pop_back();
    print_vector(vector);
  }

  std::cout << "[containers] vector remove element equals to 2" << std::endl;
  const auto vector_new_end(std::remove(vector.begin(), vector.end(), 2));
  vector.erase(vector_new_end, std::end(vector));
  print_vector(vector);

  std::cout << "[containers] vector remove element that % 2 != 0" << std::endl;
  vector.erase(std::remove_if(vector.begin(), vector.end(), odd),
               std::end(vector));
  // Shrink the capacity of `vector`.
  // CAUTION: This will reallocate all elements in the container.
  vector.shrink_to_fit();
  print_vector(vector);
}

int main() {
  learn_structured_binding();
  learn_initialize_variable_in_if();
  learn_initialize_with_brackets();
  learn_constexpr_if();
  learn_fold_expression_args();
  learn_containers();

  std::cout << "--------------------------------------------" << std::endl;
}
