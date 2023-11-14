#include <iostream>
#include "test.h"

Foo::Foo(int x) {
    Foo::x = x;
}

int main() {
    Foo foo = Foo();
    std::cout << foo.x << std::endl;
    return 0;
}