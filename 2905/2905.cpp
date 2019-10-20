#include <iostream>
#include <vector>

int main()
{
    // Fast reading from input
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    std::cin >> N;

    std::vector<int> durations, costs;

    for (int i = 0; i < N; i++)
    {
        int duration, cost;
        std::cin >> duration >> cost;
        durations.push_back(duration);
        costs.push_back(cost);
    }
}
