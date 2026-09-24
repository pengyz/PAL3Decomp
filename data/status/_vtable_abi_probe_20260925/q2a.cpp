struct Q2 { Q2(); virtual int p() = 0; virtual int r(); int x; };
Q2::Q2() { x = 1; }
int Q2::r() { return x; }
