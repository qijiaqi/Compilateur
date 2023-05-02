int mul()
{
    int a = 36;
    int b =3;
    while (a > 8) {
        if (a <= b) {
            a = a - b;
        }
        a= a-1;

    }
    return a;
}
int main() {
    int e = mul();
    return e + 2;
}