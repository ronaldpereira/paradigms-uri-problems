#include <iostream>
#include <vector>

int ShellSortAndReturnMovements(std::vector<int> permutation, int N)
{
    int movements = 0;

    for (int gap = N / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < N; i++)
        {
            int temp = permutation[i];

            int j;
            for (j = i; j >= gap && permutation[j - gap] > temp; j -= gap)
            {
                permutation[j] = permutation[j - gap];
                movements += gap + gap - 1;
            }
            permutation[j] = temp;
        }
    }
    return movements;
}

int main()
{
    // Fast reading from input
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    while (1)
    {
        int N;
        std::cin >> N;

        if (N == 0)
            break;

        std::vector<int> permutation;
        for (int i = 0; i < N; i++)
        {
            int number;
            std::cin >> number;
            permutation.push_back(number);
        }

        std::cout << (ShellSortAndReturnMovements(permutation, N) % 2 == 0 ? "Carlos" : "Marcelo") << std::endl;
    }
    return 0;
}
