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

int PalydromeCost(std::string word, int K)
{
    int N = word.length();
    if (N == 1)
        return 0;

    int cost;

    if (K == 1)
    {
        cost = 0;
        for (int i = (N - 1) / 2, j = N - i - 1; i >= 0 && j < N; i--, j++)
        {
            if (word[i] != word[j])
                cost += GetChangeCost(word[i], word[j]);
        }
    }

    else
    {
        cost = INT_MAX;
        for (int i = 1; i < N; i++)
        {
            int actual_cost = PalydromeCost(word.substr(0, i), K - 1);
            actual_cost += PalydromeCost(word.substr(i, word.length() - i), K - 1);

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

    if (N == K)
        std::cout << 0 << std::endl;

    else
        std::cout << PalydromeCost(word, K) << std::endl;

    return 0;
}
