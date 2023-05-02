int func(){
    int a = 43;
    int b =12;
    while (a > 8) {
        if (a <= b) {
            a = a - b;
        }
        a= a-1;

    }
    return a;
}
int main()
{
    int b = 2;
    b=func();
    return b;
}