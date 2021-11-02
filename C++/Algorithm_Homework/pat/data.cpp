#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
long long random(long long mod)
{
    long long n1, n2, n3, n4, ans;
    n1 = rand();
    n2 = rand();
    n3 = rand();
    n4 = rand();
    ans = n1 * n2 % mod;
    ans = ans * n3 % mod;
    ans = ans * n4 % mod;
    return ans;
}
int main()
{
    srand(time(0));
    // while (1)
    // {
    int n, m;
    // n = random(100000) + 1;
    n = 100000;
    m = 10;
    // n = 10;
    printf("%d\n", n);
    // m=random(6);
    printf("%d\n", m);
    for (int i = 0; i < n; i++)
    {
        int x = random(100000000);
        int y = random(100000000);
        printf("%d %d\n", x, y);
    }
    for (int i = 0; i < m; i++)
    {
        int x = random(10000000);
        int y = random(10000000);
        int k = random(n) + 1;
        printf("%d %d %d\n", x, y, k);
    }
    // }
    return 0;
}