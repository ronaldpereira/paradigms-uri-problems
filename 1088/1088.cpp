#include <iostream>
#include <vector>

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

int Merge(std::vector<int> &xor_indexes, std::vector<int> &tmp, int left, int mid, int right)
{
    int inversions = 0;

    int i = left;
    int j = mid;
    int k = left;

    while (i <= mid - 1 && j <= right)
    {
        if (xor_indexes[i] <= xor_indexes[j])
            tmp[k++] = xor_indexes[i++];

        else
        {
            tmp[k++] = xor_indexes[j++];
            inversions += 1 * (mid - i);
        }
    }

    while (i <= mid - 1)
        tmp[k++] = xor_indexes[i++];

    while (j <= right)
        tmp[k++] = xor_indexes[j++];

    for (i = left; i <= right; i++)
        xor_indexes[i] = tmp[i];

    return inversions;
}

int MergeSort(std::vector<int> &xor_indexes, std::vector<int> &tmp, int left, int right)
{
    int inversions = 0;
    if (right > left)
    {
        int mid = (left + right) / 2;

        inversions = MergeSort(xor_indexes, tmp, left, mid);
        inversions += MergeSort(xor_indexes, tmp, mid + 1, right);

        inversions += Merge(xor_indexes, tmp, left, mid + 1, right);
    }

    return inversions;
}

int GetMinInversions(std::vector<int> &xor_indexes, int N)
{
    std::vector<int> tmp(N);
    return MergeSort(xor_indexes, tmp, 0, N - 1);
}

int main()
{
    // Fast reading from input
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    while (1)
    {
        int N;
        std::cin >> N;

        if (N == 0)
            break;

        std::vector<int> permutation;
        for (int i = 0; i < N; i++)
        {
            int number;
            std::cin >> number;
            permutation.push_back(number);
        }

        std::cout << (GetMinInversions(permutation, N) % 2 == 0 ? "Carlos" : "Marcelo") << std::endl;
    }
    return 0;
}
