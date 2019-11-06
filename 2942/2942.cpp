#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

long long GetMinMovements(std::vector<int> origin, std::vector<int> target, int N)
{
    long long movements = 0;

    for (int i = 0; i < N; i++)
    {
        if (origin[i] != target[i])
        {
            auto it = std::find(origin.begin() + i, origin.end(), target[i]);
            int position = it - origin.begin();

            for (int j = position; j > i; j--)
            {
                int tmp = origin[j - 1];
                origin[j - 1] = origin[j];
                origin[j] = tmp;
                movements++;
            }
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
        return GetMinMovements(xor_after, xor_before, N - 1);
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
