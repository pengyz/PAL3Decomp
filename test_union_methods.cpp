// Test: Does MSVC 6.0 allow methods in unions?

union TestUnion {
    int x;
    float y;

    void setX(int val) { x = val; }
    int getX() { return x; }
};

int main() {
    TestUnion u;
    u.setX(42);
    return u.getX();
}
