#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

long long ShellSortAndReturnMovements(std::vector<long long> permutation, int N)
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

long long GetMinXOROperations(std::vector<long long> before, std::vector<long long> after, int N)
{
    std::vector<long long> xor_before;
    std::vector<long long> xor_after;

    for (int i = 0; i < N - 1; i++)
        xor_before.push_back(before[i] ^ before[i + 1]);

    for (int i = 0; i < N - 1; i++)
        xor_after.push_back(after[i] ^ after[i + 1]);

    if (before[0] != after[0] || before[N - 1] != after[N - 1])
        return -1;

    else if (std::multiset<int>(xor_before.begin(), xor_before.end()) != std::multiset<int>(xor_after.begin(), xor_after.end()))
        return -1;

    else
    {
        std::vector<long long> xor_indexes(N - 1);
        for (int i = 0; i < N - 1; i++)
        {
            auto it = std::find(xor_before.begin(), xor_before.end(), xor_after[i]);
            int position = it - xor_before.begin();

            xor_indexes[position] = i;
            xor_after[i] = -1;
            xor_before[position] = -1;
        }
        return ShellSortAndReturnMovements(xor_indexes, N - 1);
    }
}

int main()
{
    // Fast reading from xor_indexes
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    std::cin >> N;

    std::vector<long long> vector_before(N), vector_after(N);

    for (int i = 0; i < N; i++)
        std::cin >> vector_before[i];

    for (int i = 0; i < N; i++)
        std::cin >> vector_after[i];

    long long min_operations = GetMinXOROperations(vector_before, vector_after, N);

    std::cout << (min_operations >= 0LL ? std::to_string(min_operations) : "IMPOSSIBLE") << std::endl;

    return 0;
}
