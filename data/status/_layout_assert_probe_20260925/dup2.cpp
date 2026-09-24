typedef int  a1;
typedef char a1;
typedef char b1[1];
typedef char b1[2];
typedef int  c1;
typedef int *c1;
typedef char d1[(sizeof(int)==4)?1:-1];
typedef char d1[(sizeof(int)==4)?2:1];
int main() { return 0; }
