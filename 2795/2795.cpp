#include <iostream>
#include <vector>
#include <string>
#include <limits.h>

std::string word;
std::vector<std::vector<int>> dp;
std::vector<std::vector<int>> change_cost_dp(26, std::vector<int>(26));
std::vector<std::vector<int>> palindrome_cost_dp;

int GetChangeCost(int index_begin, int index_end)
{
    if (palindrome_cost_dp[index_begin][index_end] == -1)
    {
        int cost = 0;
        for (int i = index_begin, j = index_end; i < j; i++, j--)
            cost += change_cost_dp[(int)word[i] - 'a'][(int)word[j] - 'a'];

        palindrome_cost_dp[index_begin][index_end] = cost;
    }

    return palindrome_cost_dp[index_begin][index_end];
}

int PalindromeCost(int K, int i)
{
    if (K == 1)
    {
        if (dp[1][i] == -1)
        {
            dp[1][i] = GetChangeCost(i, word.length() - 1);
        }
        return dp[1][i];
    }

    else
    {
        if (dp[K][i] == -1)
        {
            int cost = PalindromeCost(1, i);
            for (int j = i; j < word.length() - 1; j++)
            {
                int actual_cost = GetChangeCost(i, j);
                actual_cost += PalindromeCost(K - 1, j + 1);
                cost = std::min(cost, actual_cost);
            }
            dp[K][i] = cost;
        }
        return dp[K][i];
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

    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 26; j++)
            change_cost_dp[i][j] = std::min(std::abs(j - i), 26 - std::abs(j - i));

    palindrome_cost_dp = std::vector<std::vector<int>>((N), std::vector<int>(N));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            palindrome_cost_dp[i][j] = (i == j) ? 0 : -1;

    dp = std::vector<std::vector<int>>((K + 1), std::vector<int>(N));
    for (int i = 0; i <= K; i++)
        for (int j = 0; j < N; j++)
            dp[i][j] = -1;

    std::cout << PalindromeCost(K, 0) << std::endl;

    return 0;
}
