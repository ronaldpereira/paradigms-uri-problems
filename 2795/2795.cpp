#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <limits.h>
#include <algorithm>

std::vector<std::vector<int>> dp;
std::string word;

int GetChangeCost(char letter_before, char letter_after)
{
    int l_b = letter_before - 'a';
    int l_a = letter_after - 'a';

    int diff = abs(l_b - l_a);

    return std::min(diff, 26 - diff);
}

int PalindromeCost(int K, int index_begin, int index_end)
{
    if (index_begin == index_end)
        return 0;

    if (index_begin == 6 && index_end == 8 && K == 1)
        std::cout << "aqui" << std::endl;

    if (K == 1)
    {
        if (dp[index_begin][index_end] == -1)
        {
            int cost = 0;
            for (int i = index_begin, j = index_end; i < j; i++, j--)
            {
                if (word[i] != word[j])
                    cost += GetChangeCost(word[i], word[j]);
            }
            dp[index_begin][index_end] = cost;
        }
        return dp[index_begin][index_end];
    }

    else
    {
        int cost = PalindromeCost(1, index_begin, index_end);
        for (int i = index_begin; i < index_end; i++)
        {
            int left = PalindromeCost(K - 1, index_begin, i);
            int right = PalindromeCost(K - 1, i + 1, index_end);

            cost = std::min(cost, left + right);
        }

        return cost;
    }
}

int main()
{
    // Fast reading from input
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N, K;

    std::cin >> N >> K;
    std::cin >> word;

    dp = std::vector<std::vector<int>>(N, std::vector<int>(N));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            (i == j) ? dp[i][j] = 0 : dp[i][j] = -1;

    if (N == K)
        std::cout << 0 << std::endl;

    else
        std::cout << PalindromeCost(K, 0, N - 1) << std::endl;

    return 0;
}
