#include <iostream>
#include <vector>
#include <algorithm>

int GetMinXOROperations(std::vector<int> before, std::vector<int> after, int N)
{
    int operations = 0;
    for (int i = 1, j = before.size() - 2; i <= j; i++, j--)
    {
        if (before[i] != after[i])
        {
            before[i] = before[i - 1] ^ before[i] ^ before[i + 1];
            operations++;
        }
        if (before[j] != after[j])
        {
            before[j] = before[j - 1] ^ before[j] ^ before[j + 1];
            operations++;
        }
    }

    if (before == after)
        return operations;
    else
        return -1;
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

    int min_operations = GetMinXOROperations(vector_before, vector_after, N);

    std::cout << (min_operations >= 0 ? std::to_string(min_operations) : "IMPOSSIBLE") << std::endl;

    return 0;
}
