#include <chrono>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>

void solve(int part)
{
    std::set<std::pair<long, long>> cur, keep, next; // Sets of ranges in the form (start, len)
    std::ifstream f("../inputs/05.txt");
    if (!f.is_open())
    {
        return;
    }
    // Parse the seeds, depending on the input
    std::string line;
    std::getline(f, line);
    std::istringstream line_stream(line);
    std::string seed_start, seed_len;
    std::getline(line_stream, seed_start, ' '); // Throw away "seeds: " from first line
    while (std::getline(line_stream, seed_start, ' '))
    {
        if (part == 1) // In part 1, treat the seeds like seed ranges of length 1
        {
            cur.insert({std::stol(seed_start), 1});
        }
        else // In part 2, use the seed value pairs
        {
            std::getline(line_stream, seed_len, ' ');
            cur.insert({std::stol(seed_start), std::stol(seed_len)});
        }
    }
    // Parse and apply the piping lines
    while (std::getline(f, line))
    {
        if (line.empty()) // If the line is empty, prepare to start the next map
        {
            cur.insert(next.begin(), next.end());
            next.clear();
            std::getline(f, line); // Throw away "X-to-Y map:\n"
            continue;
        }
        long pipe_dest, pipe_start, pipe_len;
        line_stream.clear(); // Necessary to reuse line_stream
        line_stream.str(line);
        line_stream >> pipe_dest >> pipe_start >> pipe_len;
        // Handle the current ranges, piping and splitting if necessary
        for (auto [range_start, range_len] : cur)
        {
            // Find the lower and upper positions of the intersection between this
            // range and the pipe
            long lower = std::max(range_start, pipe_start);
            long upper = std::min(range_start + range_len, pipe_start + pipe_len);
            if (upper > lower)
            {
                // Push the part of the range in the pipe through the pipe
                next.insert({pipe_dest - pipe_start + lower, upper - lower});
                // Keep the upper/lower portions of the range if not in pipe
                if (range_start + range_len > pipe_start + pipe_len)
                {
                    keep.insert({pipe_start + pipe_len, range_start + range_len - pipe_start - pipe_len});
                }
                if (range_start < pipe_start)
                {
                    keep.insert({range_start, pipe_start - range_start});
                }
            }
            else // The range and pipe do not overlap, so keep the whole range
            {
                keep.insert({range_start, range_len});
            }
        }
        cur.swap(keep);
        keep.clear();
    }
    cur.insert(next.begin(), next.end()); // Include outputs from final iteration
    f.close();
    // Output the start of the "lowest" range (using the fact that cur is sorted)
    std::cout << "Part " << part << ": " << cur.begin()->first << std::endl;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    solve(1);
    solve(2);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Clock time: " << duration.count() << " us" << std::endl;

    return 0;
}