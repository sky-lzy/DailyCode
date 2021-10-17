/********************
 * KMP算法  字符串匹配
 * 复杂度: Θ(m + n)
 * ****************** */
//未完成

#include <iostream>
#include <vector>

std::vector<int> Pretreatment(std::string &test)
{
    int m = test.size();
    std::vector<int> Next({0});
    for (int i = 1; i < m; i++)
    {
        int k = m - 1;
        for (; k > 0; k--)
        {
            int j = 0;
            for (; j <= k; j++)
            {
                if (test[j] != test[m - k + j])
                    break;
            }
            if (j == k + 1)
                break;
        }
        Next.emplace_back(k);
    }
}

int KMP(std::string &String, std::string &test)
{
    int n = String.size(), m = test.size();
}