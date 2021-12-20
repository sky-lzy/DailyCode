#include <iostream>
#include <vector>
#include <string>

void PreWork(const std::string &str, std::vector<int> &Pre)
{
    int size = str.size();
    // Pre.swap(std::vector<int>(size, 0));
    Pre.resize(size);
    Pre[0] = 0;
    int i = 1, j = 0; //i为Pre[i]，j为待比较的str[j]
    while (i < size)
    {
        //匹配
        if (str[i] == str[j])
        {
            Pre[i] = j + 1;
            i++;
            j++;
        }
        //若不匹配，则回退至已经比较过的
        else if (j > 0)
            j = Pre[j - 1];
        //若始终不匹配，则无匹配串
        else
        {
            Pre[i] = 0;
            i++;
        }
    }
}

int KMP(std::string &str1, std::string &str2)
{
    std::vector<int> Pre;
    PreWork(str2, Pre);
    int size1 = str1.size(), size2 = str2.size();

    int i = 0, j = 0;
    while (i < size1)
    {
        if (str1[i] == str2[j])
        {
            //是否已经比较完子串
            if (j == size2 - 1)
                return i - size2 + 1;
            else
            {
                i++;
                j++;
            }
        }
        else
        {
            if (j > 0)
                j = Pre[j - 1];
            else
                i++;
        }
    }
    return -1;
}

int main()
{
    std::string str1, str2;
    std::cout << "input str1:\n";
    std::cin >> str1;
    std::cout << "input str2:\n";
    std::cin >> str2;
    int match = KMP(str1, str2);
    if (match == -1)
        std::cout << "No Matching!\n";
    else
        std::cout << match << '\n';

    return 0;
}