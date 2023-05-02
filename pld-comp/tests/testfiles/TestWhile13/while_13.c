int func(){
    int a = 2;
    while (a < 8) {
        a=45;
        if (a <= 4) {
            a = 15;
        }
    }
    return a;
}
int main()
{
    int b = 2;
    b=func();
    return b;
}