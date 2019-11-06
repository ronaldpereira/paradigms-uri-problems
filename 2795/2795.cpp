#include <iostream>

int dp[400][400];
char word[400];
int change_cost_dp[26][26];

int PalindromeCost(int K, int index_begin, int index_end)
{
    if (index_begin == index_end)
        return 0;

    if (K == 1)
    {
        if (dp[index_begin][index_end] == -1)
        {
            int cost = 0;
            for (int i = index_begin, j = index_end; i < j; i++, j--)
            {
                if (word[i] != word[j])
                    cost += change_cost_dp[(int)word[i] - 'a'][(int)word[j] - 'a'];
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
            int left = PalindromeCost(1, index_begin, i);
            int right = PalindromeCost(K - 1, i + 1, index_end);

            cost = std::min(cost, left + right);
        }
        dp[index_begin][index_end] = cost;

        return dp[index_begin][index_end];
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

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            (i == j) ? dp[i][j] = 0 : dp[i][j] = -1;

    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 26; j++)
            change_cost_dp[i][j] = std::min(std::abs(j - i), 26 - std::abs(j - i));

    if (N == K)
        std::cout << 0 << std::endl;

    else
        std::cout << PalindromeCost(K, 0, N - 1) << std::endl;

    return 0;
}
