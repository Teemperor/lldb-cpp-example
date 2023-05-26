
struct Foo {
    int a;
    char b;
};

Foo foo_storage;

int main() {
    Foo &foo = foo_storage;
    foo.a = 4;
    foo.b = 2;

    foo.b += 1; // DEBUGGER_STOP_MARKER

    return foo.a + foo.b;
}
