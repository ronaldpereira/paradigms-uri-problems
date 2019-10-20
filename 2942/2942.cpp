#include <iostream>
#include <vector>

struct VectorPermutation
{
    std::vector<int> permutation;
    int operations;
};

int GetMinXOROperations(std::vector<int> before, std::vector<int> after, int N)
{
    std::vector<VectorPermutation> permutations;
    permutations.push_back({before, 0});

    for (unsigned long long i = 0; i < N * 1e5; i++)
    {
        VectorPermutation p = permutations[i];

        if (p.permutation == after)
            return p.operations;

        for (int i = 1; i < p.permutation.size() - 1; i++)
        {
            std::vector<int> new_permutation;
            new_permutation = p.permutation;

            new_permutation[i] = new_permutation[i - 1] ^ new_permutation[i] ^ new_permutation[i + 1];

            permutations.push_back({new_permutation, p.operations + 1});
        }
    }

    return -1;
}

int main()
{
    int N;
    std::cin >> N;

    std::vector<int> vector_before, vector_after;

    for (int i = 0; i < N; i++)
    {
        int number;
        std::cin >> number;
        vector_before.push_back(number);
    }

    for (int i = 0; i < N; i++)
    {
        int number;
        std::cin >> number;
        vector_after.push_back(number);
    }

    int min_operations = GetMinXOROperations(vector_before, vector_after, N);

    if (min_operations >= 0)
        std::cout << min_operations << std::endl;

    else
        std::cout << "IMPOSSIBLE" << std::endl;

    return 0;
}
