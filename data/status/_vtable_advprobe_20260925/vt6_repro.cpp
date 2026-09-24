struct O { virtual void o(int); virtual void o(double); virtual int o(char *, int); virtual void o(); int z; };
void O::o(int) {} void O::o(double) {} int O::o(char *, int) { return 0; } void O::o() {}
struct DO : O { virtual void o(double); int dz; };   // override only ONE overload
void DO::o(double) {}
int main() { DO d; return 0; }
