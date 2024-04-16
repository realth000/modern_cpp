#include <concepts>
#include <format>
#include <string>

// Require has a variable called i.
template <typename T>
concept has_i = requires(T t) {
    { t.i };
};

// Require has a function called j, function signature void().
template <typename T>
concept has_j = requires(T t) {
    { t.j() };
};

// Require has k can convert to int type.
template <typename T>
concept has_k_implicit_int = requires(T t) {
    { t.k } -> std::convertible_to<int>;
};

// Require has a int type variable l.
template <typename T>
concept has_l = requires(T t) {
    { t.l } -> std::same_as<int &>;
};

struct Foo {
    int i;
    void j() {}
    int k;
    int l;
};

template <typename T>
    requires has_i<T>
void call_i(T t) {}

template <typename T>
    requires has_k_implicit_int<T>
void call_k(T t) {}

template <typename T>
    requires has_l<T>
void call_l(T t) {}

int main(int argc, char *argv[]) {
    Foo foo = {};
    call_i(foo);
    call_k(foo);
    call_l(foo);
}
