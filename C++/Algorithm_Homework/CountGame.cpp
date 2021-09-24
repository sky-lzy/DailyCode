#include <iostream>

long long CountGame(int inputNum)
{
    if (inputNum == 0)
        return 10;

    if (inputNum < 10)
        return inputNum;

    int Factor[10] = {0};
    for (int i = 9; i > 1 && inputNum > 1; i--)
        while (inputNum % i == 0)
        {
            inputNum /= i;
            Factor[i]++;
        }

    if (inputNum > 10)
        return -1;

    long long outputNum = 0;
    for (int i = 2; i < 10; i++)
    {
        while (Factor[i] > 0)
        {
            outputNum = outputNum * 10 + i;
            Factor[i]--;
        }
    }
    return outputNum;
}

int main()
{
    int inputNum;
    std::cin >> inputNum;
    std::cout << CountGame(inputNum) << std::endl;
    return 0;
}