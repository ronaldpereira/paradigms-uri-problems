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
    if (K == 1 || i == word.length() - 1)
    {
        dp[i][word.length() - 1] = GetChangeCost(i, word.length() - 1);
        dp[word.length() - 1][i] = dp[i][word.length() - 1];
        return dp[i][word.length() - 1];
    }

    else
    {
        int cost = PalindromeCost(1, 0);
        for (int j = i; j < word.length() - 1; j++)
        {
            int left = (dp[i][j] != -1) ? dp[i][j] : GetChangeCost(i, j);
            int right = PalindromeCost(K - 1, j + 1);

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

    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 26; j++)
            change_cost_dp[i][j] = std::min(std::abs(j - i), 26 - std::abs(j - i));

    dp = std::vector<std::vector<int>>(N, std::vector<int>(N));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            dp[i][j] = (i == j) ? 0 : -1;

    if (N == K)
        std::cout << 0 << std::endl;

    else
        std::cout << PalindromeCost(K, 0) << std::endl;

    return 0;
}
