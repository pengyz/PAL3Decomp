// AD2: derived class adds NEW overload of same name as base overload group
struct B2 { virtual void o(int); virtual void o(double); virtual void p(); int b; };
struct D2 : B2 { virtual void o(char); int d; };   // new overload appended?
void B2::o(int) {} void B2::o(double) {} void B2::p() {}
void D2::o(char) {}
int main() { D2 d; return 0; }
