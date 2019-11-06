#include <iostream>
#include <iomanip>
#include <vector>
#include <bits/stdc++.h>

std::vector<float> dp;
std::vector<int> durations;
std::vector<float> discounts = {1, .5, .25, .25, .25, .25};
std::vector<float> costs;

float GetMinCost(int trip_index)
{
    if (trip_index >= durations.size())
        return 0;

    if (dp[trip_index] != -1)
        return dp[trip_index];

    float total_cost = FLT_MAX;
    float trip_cost = 0;
    int trip_duration = 0;

    for (int i = 0; trip_duration < 120 && i < discounts.size() && (trip_index + i) < durations.size(); i++)
    {
        trip_cost += costs[trip_index + i] * discounts[i];
        total_cost = std::min(total_cost, trip_cost + GetMinCost(trip_index + i + 1));

        trip_duration += durations[trip_index + i];
    }

    dp[trip_index] = total_cost;

    return dp[trip_index];
}

int main()
{
    // Fast reading from input
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    std::cin >> N;

    for (int i = 0; i < N; i++)
    {
        int duration;
        float cost;
        std::cin >> duration >> cost;
        durations.push_back(duration);
        costs.push_back(cost);
        dp.push_back(-1);
    }

    std::cout << std::fixed << std::setprecision(2) << GetMinCost(0) << std::endl;

    return 0;
}
