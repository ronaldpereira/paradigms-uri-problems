#include <iostream>
#include <string>
#include <array>
#include <algorithm>

bool IsPalindrome(std::string segment)
{
    if (segment.length() == 1)
        return true;

    else
    {
        for (int i = 0, j = segment.length() - 1; i < j; i++, j--)
        {
            if (segment[i] != segment[j])
                return false;
        }
        return true;
    }
}

int GetChangeCost(char letter_before, char letter_after)
{
    std::array<char, 26> alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                                     'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    auto iterator_letter_before = std::find(alphabet.begin(), alphabet.end(), letter_before);
    auto iterator_letter_after = std::find(alphabet.begin(), alphabet.end(), letter_after);

    int position_before = iterator_letter_before - alphabet.begin() + 1;
    int position_after = iterator_letter_after - alphabet.begin() + 1;

    if (iterator_letter_before <= iterator_letter_after)
    {
        if ((position_after - position_before) <= (position_before - position_after))
            return position_after - position_before;
        else
            return position_before - position_after;
    }

    // Done a loop over the end of alphabet
    else
    {
        if ((position_after - position_before) <= (position_before - position_after))
            return alphabet.size() - position_before + position_after;

        else
            return alphabet.size() - position_after + position_before;
    }
}

void GenerateSegments(int N, int K, std::string chain_chars)
{
    int actual_K = 0;

    if (N == K)
        std::cout << 0 << std::endl;

    else
    {
    }
}

int main()
{
    // Fast reading from input
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string chain_chars;
    int N, K;

    // std::cin >> N >> K;
    // std::cin >> chain_chars;

    // GenerateSegments(N, K, chain_chars);

    std::cout << GetChangeCost('a', 'c') << " " << GetChangeCost('a', 'z') << std::endl;

    return 0;
}
