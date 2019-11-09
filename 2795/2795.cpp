#include <iostream>
#include <vector>
#include <string>
#include <limits.h>

std::string word;
std::vector<std::vector<int>> dp;
std::vector<std::vector<int>> change_cost_dp(26, std::vector<int>(26));

int GetChangeCost(int index_begin, int index_end)
{
    int cost = 0;
    for (int i = index_begin, j = index_end; i < j; i++, j--)
        cost += change_cost_dp[(int)word[i] - 'a'][(int)word[j] - 'a'];

    return cost;
}

int PalindromeCost(int K, int i)
{
    if (K == 1)
    {
        if (dp[i][K] == -1)
            dp[i][K] = GetChangeCost(i, word.length() - 1);

        return dp[i][K];
    }

    else
    {
        int cost = PalindromeCost(1, i);
        for (int j = i; j < word.length() - 1; j++)
        {
            int left = GetChangeCost(i, j);
            int right = (dp[j + 1][K - 1] == -1) ? PalindromeCost(K - 1, j + 1) : dp[j + 1][K - 1];
            dp[j + 1][K - 1] = right;
            cost = std::min(cost, left + right);
        }
        dp[i][K] = cost;

        return dp[i][K];
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

    dp = std::vector<std::vector<int>>((N), std::vector<int>(K + 1));
    for (int i = 0; i < N; i++)
        for (int j = 0; j <= K; j++)
            dp[i][j] = -1;

    std::cout << PalindromeCost(K, 0) << std::endl;

    return 0;
}
