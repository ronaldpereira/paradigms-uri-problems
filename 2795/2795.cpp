#include <iostream>
#include <string>
#include <array>

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

void GenerateSegments(int N, int K, std::string chain_chars)
{
    std::array<char, 26> alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                                     'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    int actual_K = 0;

    if (N == K)
        std::cout << 0 << std::endl;

    else
    {
    }
}

int main()
{
    std::string chain_chars;
    int N, K;

    std::cin >> N >> K;
    std::cin >> chain_chars;

    GenerateSegments(N, K, chain_chars);

    return 0;
}
