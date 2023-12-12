#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

std::set<unsigned> empty_rows;
std::set<unsigned> empty_cols;
std::vector<std::pair<unsigned, unsigned>> galaxies; // vector of (row, col) pairs

void setup()
{
    std::ifstream f("11-input.txt");
    if (!f.is_open())
    {
        return;
    };

    // Get width of input
    std::string line;
    std::getline(f, line);
    f.seekg(0);
    // Put all columns into empty_cols, then erase the ones that are not empty
    for (unsigned c = 0; c < line.size(); c++)
    {
        empty_cols.insert(empty_cols.end(), c);
    }

    unsigned r = 0;
    while (std::getline(f, line))
    {
        size_t c = -1;
        while ((c = line.find('#', c + 1)) != std::string::npos)
        {
            empty_cols.erase(c);
            galaxies.emplace_back(r, c);
        }
        if (galaxies.back().first != r)
        {
            empty_rows.insert(r);
        }
        r++;
    }
}

void solve()
{
    unsigned long p1 = 0, p2 = 0;
    // For each galaxy pair...
    for (unsigned i = 0; i < galaxies.size(); i++)
    {
        for (unsigned j = i + 1; j < galaxies.size(); j++)
        {
            unsigned r_lo = std::min(galaxies[i].first, galaxies[j].first);
            unsigned r_hi = std::max(galaxies[i].first, galaxies[j].first);
            unsigned c_lo = std::min(galaxies[i].second, galaxies[j].second);
            unsigned c_hi = std::max(galaxies[i].second, galaxies[j].second);
            unsigned expansion = 0;
            // Count the number of empty rows in between the galaxies.
            expansion += std::count_if(empty_rows.begin(), empty_rows.end(),
                                    [r_lo, r_hi](unsigned r)
                                    { return r > r_lo && r < r_hi; });
            // Count the number of empty cols in between the galaxies.
            expansion += std::count_if(empty_cols.begin(), empty_cols.end(),
                                    [c_lo, c_hi](unsigned c)
                                    { return c > c_lo && c < c_hi; });
            // Calculate the distance between the galaxies, adding the expansion,
            // scaled appropriately for each part.
            p1 += r_hi - r_lo + c_hi - c_lo + expansion;
            p2 += r_hi - r_lo + c_hi - c_lo + expansion * 999999;
        }
    }
    std::cout << "Part 1: " << p1 << std::endl;
    std::cout << "Part 2: " << p2 << std::endl;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    setup();
    solve();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Clock time: " << duration.count() << " us" << std::endl;

    return 0;
}