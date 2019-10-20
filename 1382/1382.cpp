#include <iostream>
#include <vector>
#include <algorithm>

int OrderAndReturnChanges(std::vector<int> permutation)
{
    int changes = 0;

    for (int i = 0; i < permutation.size(); i++)
    {
        if (permutation[i] != i + 1)
        {
            int swap = permutation[i];

            auto it = std::find(permutation.begin(), permutation.end(), i + 1);
            int position = it - permutation.begin();

            permutation[i] = permutation[position];
            permutation[position] = swap;

            changes++;
        }
    }

    return changes;
}

int main()
{
    int T;
    std::cin >> T;

    for (int i = 0; i < T; i++)
    {
        int N;
        std::cin >> N;

        std::vector<int> permutation;

        for (int j = 0; j < N; j++)
        {
            int input;
            std::cin >> input;
            permutation.push_back(input);
        }

        std::cout << OrderAndReturnChanges(permutation) << std::endl;
    }
    return 0;
}
