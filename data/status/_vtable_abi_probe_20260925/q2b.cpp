struct Q2 { Q2(); virtual int p() = 0; virtual int r(); int x; };
struct DQ2 : Q2 { virtual int p(); };
int DQ2::p() { return 2; }
struct O { virtual void o(int); virtual void o(double); virtual int o(char *, int); int z; };
void O::o(int) {} void O::o(double) {} int O::o(char *, int) { return 0; }
int main() { DQ2 d; O o; return d.p() + (int)o.z; }
