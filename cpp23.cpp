#include <format>
#include <iostream>
#include <optional>

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

enum class BuildError {
    invalid_args,
    internl_error,
};

class MyExpect {
   public:
    double foo_;
    int bar_;

    static std::expected<MyExpect, BuildError> New(double foo, int bar) {
        if (bar < 0) {
            return std::unexpected(BuildError::invalid_args);
        } else {
            return MyExpect{foo, bar};
        }
    }

    static MyExpect Default() { return MyExpect{0, 0}; }

    void print_data() const { println("hello: foo_={}, bar_={}", foo_, bar_); }

    void updateFoo(double foo) { foo_ = foo; }

    void updateBar(double bar) { bar_ = bar; }

   private:
    MyExpect(double foo, int bar) : foo_(foo), bar_(bar) {}
};

std::optional<Foo> update(std::optional<Foo> foo) {
    foo->updateFoo(12.3);
    return std::optional(*foo);
}

Foo update_bar(std::optional<Foo> foo, int value) {
    foo->bar_ = value;
    return *foo;
}

std::expected<MyExpect, BuildError> update2(std::expected<MyExpect, BuildError> myExpect) {
    myExpect->updateFoo(12.3);
    return {*myExpect};
}

MyExpect update_bar2(std::expected<MyExpect, BuildError> myExpect, int bar) {
    myExpect->updateBar(bar);
    return *myExpect;
}

int main() {
    auto foo = Foo::New(100, 200).and_then(update).transform([](foo x) { return update_bar(x, 345); }).or_else([] {
        return std::optional<Foo>(Foo::Default());
    });

    auto myExpect =
        MyExpect::New(100, 200)
            .and_then(update2)
            .transform([](MyExpect x) { return update_bar2(x, 345); })
            .or_else([](BuildError buildError) { return std::expected<MyExpect, BuildError>(MyExpect::Default()); });

    myExpect->print_data();

    foo.hello();
    return 0;
}
