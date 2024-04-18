#include <optional>
#include <format>
#include <iostream>

template <typename... _Args>
void print(std::format_string<_Args...> fmt, _Args&&... __args) {
    std::cout << std::format(fmt, __args...);
}

template <typename... _Args>
void println(std::format_string<_Args...> fmt, _Args&&... __args) {
    std::cout << std::format(fmt, __args...) << std::endl;
}

class Foo {
   public:
    void hello() const { println("hello: foo_={}, bar_={}", foo_, bar_); }

    double foo_;

    int bar_;

    static std::optional<Foo> New(double foo, int bar) {
        if (foo <= 0) {
            return std::nullopt;
        } else {
            return Foo(foo, bar);
        }
    }

    static Foo Default() { return Foo(0, 0); }

    void updateFoo(double foo) { foo_ = foo; }

    void updateBar(int bar) { bar_ = bar; }

   private:
    Foo(double foo, int bar) : foo_(foo), bar_(bar){};
};

std::optional<Foo> update(std::optional<Foo> foo) {
    foo->updateFoo(12.3);
    return std::optional(*foo);
}

Foo update_bar(std::optional<Foo> foo, int value) {
    foo->bar_ = value;
    return *foo;
}

int main() {
    auto foo = Foo::New(100, 200).and_then(update).transform([](foo x) { return update_bar(x, 345);}).or_else([] {
        return std::optional<Foo>(Foo::Default());
    });

    foo.hello();
    return 0;
}


