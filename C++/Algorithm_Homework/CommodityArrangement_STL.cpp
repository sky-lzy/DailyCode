// #include <iostream>
#include <stdio.h>
#include <algorithm>
#include <list>

int main()
{
    // std::ios::sync_with_stdio(false);
    std::list<int> Goods;
    int N, M, K, L;
    // std::cin >> N >> M >> K >> L;
    scanf("%d%d%d%d", &N, &M, &K, &L);
    for (int i = 0; i < N + M + K + L; i++)
    {
        int temp, num, j, dir, num_a, num_b;
        std::list<int>::iterator temptr, temptr_a, temptr_b;
        // std::cin >> temp;
        scanf("%d", &temp);
        switch (temp)
        {
        case 1:
            // std::cin >> num >> j >> dir;
            scanf("%d%d%d", &num, &j, &dir);
            if (Goods.empty())
                Goods.emplace_back(num);
            else
            {
                temptr = std::find(Goods.begin(), Goods.end(), j);
                if (dir == 1)
                    temptr++;
                Goods.insert(temptr, num);
            }
            break;

        case 0:
            // std::cin >> num;
            scanf("%d", &num);
            temptr = std::find(Goods.begin(), Goods.end(), num);
            Goods.erase(temptr);
            break;

        case -1:
            // std::cin >> num_a >> num_b;
            scanf("%d%d", &num_a, &num_b);
            temptr_a = std::find(Goods.begin(), Goods.end(), num_a);
            temptr_b = std::find(Goods.begin(), Goods.end(), num_b);
            std::swap(*temptr_a, *temptr_b);
            break;

        case -2:
            Goods.reverse();
            break;
        default:
            break;
        }
    }

    std::for_each(Goods.begin(), Goods.end(), [](const int tempNum) { /* std::cout << tempNum << " ";  */ printf("%d ", tempNum); });
    // std::cout << -1 << std::endl;

    printf("-1\n");
    return 0;
}