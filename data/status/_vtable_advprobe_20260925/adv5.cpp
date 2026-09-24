// AD5: abstract class, one concrete virtual defined out-of-line + one pure
struct AB { virtual void concrete(); virtual void pure() = 0; int z; };
void AB::concrete() {}
void use_ab(AB* p) { p->concrete(); }
int main() { return 0; }
