#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>

long long Merge(std::vector<int> &xor_indexes, std::vector<int> &tmp, int left, int mid, int right)
{
    long long inversions = 0LL;

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
            inversions += mid - i;
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

long long MergeSort(std::vector<int> &xor_indexes, std::vector<int> &tmp, int left, int right)
{
    long long inversions = 0LL;
    if (right > left)
    {
        int mid = (left + right) / 2;

        inversions = MergeSort(xor_indexes, tmp, left, mid);
        inversions += MergeSort(xor_indexes, tmp, mid + 1, right);

        inversions += Merge(xor_indexes, tmp, left, mid + 1, right);
    }

    return inversions;
}

long long GetMinInversions(std::vector<int> &xor_indexes, int N)
{
    std::vector<int> tmp(N);
    return MergeSort(xor_indexes, tmp, 0, N - 1);
}

long long GetMinXOROperations(std::vector<int> &before, std::vector<int> &after, int N)
{
    std::vector<int> xor_before;
    std::vector<int> xor_after;
    std::unordered_map<int, std::vector<int>> xor_after_reference;

    for (int i = 0; i < N - 1; i++)
        xor_before.push_back(before[i] ^ before[i + 1]);

    for (int i = 0; i < N - 1; i++)
    {
        int xor_bitwise_value = after[i] ^ after[i + 1];
        xor_after.push_back(xor_bitwise_value);
        xor_after_reference[xor_bitwise_value].push_back(i);
    }

    if (!(before[0] == after[0] && before[N - 1] == after[N - 1]))
        return -1LL;

    else if (std::multiset<int>(xor_before.begin(), xor_before.end()) != std::multiset<int>(xor_after.begin(), xor_after.end()))
        return -1LL;

    else if (xor_before == xor_after)
        return 0LL;

    else
    {
        std::vector<int> xor_indexes(N - 1);
        for (int i = 0; i < N - 1; i++)
        {
            xor_indexes[i] = xor_after_reference[xor_before[i]].front();
            xor_after_reference[xor_before[i]].erase(xor_after_reference[xor_before[i]].begin());
        }
        return GetMinInversions(xor_indexes, N - 1);
    }
}

int main()
{
    // Fast reading from xor_indexes
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    std::cin >> N;

    std::vector<int> vector_before(N), vector_after(N);

    for (int i = 0; i < N; i++)
        std::cin >> vector_before[i];

    for (int i = 0; i < N; i++)
        std::cin >> vector_after[i];

    long long min_operations = GetMinXOROperations(vector_before, vector_after, N);

    std::cout << (min_operations >= 0LL ? std::to_string(min_operations) : "IMPOSSIBLE") << std::endl;

    return 0;
}
