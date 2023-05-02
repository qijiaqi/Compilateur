int add(int a, int b,int c,int d)
{
    return a + b + d * c - 4 ;
}
int mul(int a, int b,int c,int d)
{
    return a * b * d * c - 4 ;
}
int main() {
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = mul(a, b,c,d) + add(a, b,c,d);
    return e;
}