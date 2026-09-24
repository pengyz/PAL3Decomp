// AD6: abstract class with virtual dtor defined out-of-line — emission anchor?
struct AB2 { virtual ~AB2(); virtual void pure() = 0; int z; };
AB2::~AB2() { z = 0; }
int main() { return 0; }
