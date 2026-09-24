// P10: does an override participate in the new-segment group packing?
struct BA { virtual void o(int); };
void BA::o(int) {}
struct DA : BA { virtual void o(int); virtual void z(); virtual void o(char*); };
void DA::o(int) {} void DA::z() {} void DA::o(char*) {}

// P11: same-name group in new segment while another new name sits between (decl order ovr-free)
struct BB { virtual void w(); };
void BB::w() {}
struct DB : BB { virtual void z(); virtual void o(int); virtual void y(); virtual void o(char*); };
void DB::z() {} void DB::o(int) {} void DB::y() {} void DB::o(char*) {}
int main() { DA a; DB b; return 0; }
