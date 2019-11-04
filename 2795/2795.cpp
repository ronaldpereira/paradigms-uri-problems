#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <limits.h>
#include <algorithm>

int GetChangeCost(char letter_before, char letter_after)
{
    std::array<char, 26> alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                                     'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    auto iterator_letter_before = std::find(alphabet.begin(), alphabet.end(), letter_before);
    auto iterator_letter_after = std::find(alphabet.begin(), alphabet.end(), letter_after);

    int position_before = iterator_letter_before - alphabet.begin() + 1;
    int position_after = iterator_letter_after - alphabet.begin() + 1;

    int diff = abs(position_after - position_before);

    return std::min(diff, 26 - diff);
}

int PalydromeCost(std::string word, int K, std::vector<std::vector<int>> *dp, int index_begin, int index_end)
{
    int N = word.length();
    if (N == 1)
        return 0;

    int cost;

    if (K == 1)
    {
        if ((*dp)[index_begin][index_end] >= 0)
            return (*dp)[index_begin][index_end];
        else
        {
            cost = 0;
            for (int i = (N - 1) / 2, j = N - i - 1; i >= 0 && j < N; i--, j++)
            {
                if (word[i] != word[j])
                    cost += GetChangeCost(word[i], word[j]);
            }
            (*dp)[index_begin][index_end] = cost;
            return (*dp)[index_begin][index_end];
        }
    }

    else
    {
        cost = PalydromeCost(word, 1, dp, 0, N - 1);
        for (int i = 1; i < N; i++)
        {
            int actual_cost = PalydromeCost(word.substr(0, i), K - 1, dp, 0, i - 1);
            actual_cost += PalydromeCost(word.substr(i, N - i), K - 1, dp, i, N - 1);

            cost = std::min(cost, actual_cost);
        }
    }
    return cost;
}

int main()
{
    // Fast reading from input
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string word;
    int N, K;

    std::cin >> N >> K;
    std::cin >> word;

    std::vector<std::vector<int>> dp(N, std::vector<int>(N));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            (i == j) ? dp[i][j] = 0 : dp[i][j] = -1;

    if (N == K)
        std::cout << 0 << std::endl;

    else
        std::cout << PalydromeCost(word, K, &dp, 0, N - 1) << std::endl;

    return 0;
}
