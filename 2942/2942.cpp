#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

std::vector<int> auxiliar;
std::vector<int> xor_indexes;

long long MergeSort(int low, int high)
{
    if (low >= high)
        return 0LL;

    int mid = (low + high) / 2;
    long long low_mid = 0LL;
    long long mid_high = 0LL;
    low_mid = MergeSort(low, mid);
    mid_high = MergeSort(mid + 1, high);

    long long inversions = 0LL;
    int i = low;
    int j = mid + 1;
    int k = low;

    while (i <= mid and j <= high)
    {
        if (xor_indexes[i] <= xor_indexes[j])
            auxiliar[k++] = xor_indexes[i++];

        else
        {
            auxiliar[k++] = xor_indexes[j++];
            inversions += std::abs(mid + 1 - i);
        }
    }

    while (i <= mid)
        auxiliar[k++] = xor_indexes[i++];

    while (j <= high)
        auxiliar[k++] = xor_indexes[j++];

    for (int i = low; i <= high; i++)
        xor_indexes[i] = auxiliar[i];

    return inversions + low_mid + mid_high;
}

long long GetMinXOROperations(std::vector<int> before, std::vector<int> after, int N)
{
    std::vector<int> xor_before;
    std::vector<int> xor_after;

    for (int i = 0; i < N - 1; i++)
        xor_before.push_back(before[i] ^ before[i + 1]);

    for (int i = 0; i < N - 1; i++)
        xor_after.push_back(after[i] ^ after[i + 1]);

    if (before[0] != after[0] || before[N - 1] != after[N - 1])
        return -1;

    else if (std::multiset<int>(xor_before.begin(), xor_before.end()) != std::multiset<int>(xor_after.begin(), xor_after.end()))
        return -1;

    else
    {
        xor_indexes = std::vector<int>(N - 1);
        auxiliar = std::vector<int>(N - 1);
        for (int i = 0; i < N - 1; i++)
        {
            auto it = std::find(xor_before.begin(), xor_before.end(), xor_after[i]);
            int position = it - xor_before.begin();

            xor_indexes[position] = i;
            xor_after[i] = -1;
            xor_before[position] = -1;
        }
        return MergeSort(0, N - 2);
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
