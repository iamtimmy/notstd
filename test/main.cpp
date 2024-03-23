#include <notstd>

int main() {
    int a {5};

    {
        defer {a = 10;};
    }

    return a;
}