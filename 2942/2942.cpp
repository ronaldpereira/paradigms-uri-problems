#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

long long ShellSortAndReturnMovements(std::vector<int> permutation, int N)
{
    long long movements = 0LL;

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

long long GetMinXOROperations(std::vector<int> before, std::vector<int> after, int N)
{
    std::vector<int> xor_before;
    std::vector<int> xor_after;

    for (int i = 0; i < N - 1; i++)
        xor_before.push_back(before[i] ^ before[i + 1]);

    for (int i = 0; i < N - 1; i++)
        xor_after.push_back(after[i] ^ after[i + 1]);

    if (std::multiset<int>(xor_before.begin(), xor_before.end()) != std::multiset<int>(xor_after.begin(), xor_after.end()))
        return -1;

    else
    {
        std::vector<int> xor_indexes(N - 1);
        for (int i = 0; i < N - 1; i++)
        {
            auto it = std::find(xor_after.begin(), xor_after.end(), xor_before[i]);
            int position = it - xor_after.begin();

            xor_indexes[i] = position;
            xor_before[i] = -1;
            xor_after[position] = -1;
        }
        return ShellSortAndReturnMovements(xor_indexes, N - 1);
    }
}

int main()
{
    // Fast reading from input
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    std::cin >> N;

    std::vector<int> vector_before, vector_after;

    for (int i = 0; i < N; i++)
    {
        int number;
        std::cin >> number;
        vector_before.push_back(number);
    }

    for (int i = 0; i < N; i++)
    {
        int number;
        std::cin >> number;
        vector_after.push_back(number);
    }

    long long min_operations = GetMinXOROperations(vector_before, vector_after, N);

    std::cout << (min_operations >= 0 ? std::to_string(min_operations) : "IMPOSSIBLE") << std::endl;

    return 0;
}
