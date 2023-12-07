#include <iostream>
#include <cmath>

int main() {
    
    // distance = time_pressed * (race_total_time - time_pressed)
    // distance = record
    // use the inequality to find the interval of time_pressed that will beat the records

    double rt, r; // race total time, distance record

    double lower_bound, upper_bound;

    std::cin >> rt >> r;

    lower_bound = std::ceil(rt - std::sqrt(rt * rt - 4 * r)) / 2;
    upper_bound = std::floor(rt + std::sqrt(rt * rt - 4 * r)) / 2;

    std::cout << "Winning range size: " << upper_bound - lower_bound  + 1 << std::endl;

    return 0;
}