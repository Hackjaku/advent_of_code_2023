#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <exception>
#include <algorithm>
#include <string_view>
#include <queue>
#include <map>
#include <set>

// todo two ideas
// one: can still try integration; just do only top and bottom. for loops
// just shade and unshade. may even be simpler than the scanline heap approach
// below.
//
// heap bug below means there may be vert events only involving ends, not
// starts. Need to pop those too, not just look for starts
// UPDATE: This was the missing piece! Nice!

constexpr char filepath[] = "../inputs/18.txt";

struct Dig {
    char dir;
    long steps;
};

void my_assert(const bool cond, const std::string_view msg) {
    if (!cond) {
        std::cout << msg << '\n';
        throw std::exception();
    }
}

Dig dig_from(const std::string& rgb) {
    // 2 because of (#
    const auto steps = std::stoi(rgb.substr(2, 5), nullptr, 16);
    const auto second_to_last = *(rgb.crbegin() + 1);
    switch (second_to_last) {
        case '0':return {'R', steps};
        case '1':return {'D', steps};
        case '2':return {'L', steps};
        case '3':return {'U', steps};
        default: throw std::exception();
    }
}

std::pair<std::vector<Dig>, std::vector<Dig>> read_digs() {
    if (auto fs = std::fstream(filepath)) {
        std::vector<Dig> out1, out2;
        long steps = 0;
        char dir;
        std::string rgb;
        while (fs >> dir) {
            fs >> steps >> rgb;
            out1.push_back({dir, steps});
            out2.push_back(dig_from(rgb));
        }
        return {out1, out2};
    } else {
        throw std::exception();
    }
}

// x, top, bottom, is_up
// top means low number of row, bottom means high number
// i.e. in a grid
using Vertical = std::tuple<long, long, long, bool>;

// left, right
// row will be stored as key in map
using Horizontal = std::pair<long, long>;

auto get_x(const Vertical &vert) {
    return std::get<0>(vert);
}

auto get_top(const Vertical &vert) {
    return std::get<1>(vert);
}

auto get_bottom(const Vertical &vert) {
    return std::get<2>(vert);
}

auto is_up(const Vertical &vert) {
    return std::get<3>(vert);
}

bool less_top(const Vertical &a, const Vertical &b) {
    return get_top(a) < get_top(b);
}

class GreaterBottom {
public:
    bool operator() (const Vertical &a, const Vertical &b) {
        return get_bottom(a) > get_bottom(b);
    }
};

auto make_edges(const std::vector<Dig> &digs) {
    std::vector<Vertical> out;
    std::map<long, std::vector<Horizontal>> out_horiz;
    long x = 0, row = 0;
    for (const auto &dig : digs) {
        const auto old_x = x;
        switch (dig.dir) {
            case 'L': {
                x -= dig.steps;
                auto [iter, worked] = out_horiz.insert({row, std::vector<Horizontal>()});
                iter->second.emplace_back(x, old_x);  // x < old_x
                break;
            }
            case 'R': {
                x += dig.steps;
                auto [iter, worked] = out_horiz.insert({row, std::vector<Horizontal>()});
                iter->second.emplace_back(old_x, x);  // x > old_x
                break;
            }
            case 'U': {
                const auto old_row = row;
                row -= dig.steps;
                out.emplace_back(x, row, old_row, true);
                break;
            }
            case 'D': {
                const auto old_row = row;
                row += dig.steps;
                out.emplace_back(x, old_row, row, false);
            }
        }
    }
    std::sort(out.begin(), out.end(), less_top);
    for (auto &[key, value] : out_horiz) {
        std::sort(value.begin(), value.end());
    }
    return std::make_pair(out, out_horiz);
}

auto recompute_cross_section(const std::set<Vertical> &heap_set) {
    long cross_section = 0;
    // expect heap size to be even now
    // expect from left to right all unique x
    // expect turn on off on off in that order, don't even care about clockwise
    bool entering = true;
    long last_x = 0; // unused on first iteration
    for (const auto &vert : heap_set) {
        const auto this_x = get_x(vert);
        if (!entering) {
            cross_section += this_x - last_x + 1;
        }
        entering = !entering;
        last_x = this_x;
    }
    return cross_section;
}

// row with transition of verts
// (it's quite remarkable that this is correct; was implemented at midnight having woken up
// 3:50 am that day, last meal at noonish.
auto compute_transition_cross_section(const std::set<Vertical> &heap_set, const long row, const bool is_clockwise, const std::vector<Horizontal> &horiz) {
    long cross_section = 0;
    auto next_h = horiz.cbegin();
    auto cur_v = heap_set.cbegin();
    while (cur_v != heap_set.cend()) {
        // todo: assert each vertical includes row
        const auto cur_x = get_x(*cur_v);
        if (next_h != horiz.cend() && cur_x == next_h->first) {
            cross_section += next_h->second - next_h->first + 1;
            ++next_h;
            ++cur_v;
        } else {
            const auto cur_top = get_top(*cur_v);
            const auto cur_bottom = get_bottom(*cur_v);
            if (cur_top != row && cur_bottom != row) { ++cross_section; }
            if (is_up(*cur_v)) {
                auto next_v = cur_v;
                ++next_v;
                if (next_v != heap_set.cend()) {
                    cross_section += get_x(*next_v) - cur_x - 1;  // todo?
                }
            }
            ++cur_v;
        }
    }
    while (next_h != horiz.cend()) {
        if (get_x(*cur_v) == next_h->first) {
            cross_section += next_h->second - next_h->first + 1;
            ++next_h;
        } else {
            my_assert(get_x(*cur_v) < next_h->first, " intersect");
            auto next_v = cur_v;
            ++next_v;
            if (is_up(*cur_v)) {
                cross_section += get_x(*next_v) - get_x(*cur_v) - 1;
            }
        }
        ++cur_v;
    }
    return cross_section;
}

bool compute_if_clockwise(const std::vector<Vertical> &verts) {
    auto left_vert = verts.front();
    for (const auto &vert : verts) {
        if (get_x(vert) < get_x(left_vert)) {
            left_vert = vert;
        }
    }
    return is_up(left_vert);
}

long solve(const std::vector<Vertical> &verts, const std::map<long, std::vector<Horizontal>> &horiz) {
    // min_heap, peek has smallest bottom
    std::priority_queue<Vertical, std::vector<Vertical>, GreaterBottom> heap;
    // keep matched so can quickly iterate through by x
    std::set<Vertical> heap_set;
    const bool is_clockwise = compute_if_clockwise(verts);
    auto iter = verts.cbegin();
    // top has only starting
    auto last_row = get_top(*iter);  // last as in prev, not final
    int push_count = 0;
    while (last_row == get_top(*iter)) {
        heap_set.insert(*iter);
        heap.push(*iter);
        ++iter;
        ++push_count;
    }
    auto cross_section = recompute_cross_section(heap_set);
    long area = cross_section;  // first row trivially included
    while (iter != verts.cend()) {
        my_assert(!heap.empty(), "heap empty");
        // every beginning of vert in iter has an end of a vert in heap
        // WOW, this was the last piece of puzzle. I had get_top(*iter) here;
        // once I changed to std::min, part 1 for data worked perfectly.
        // rationale: a transition may happen only with verts exiting heap
        // but NOT entering from iter.
        const auto next = std::min(get_top(*iter), get_bottom(heap.top()));
        area += cross_section * (next - last_row - 1);
        // put new ones in heap first so we can calculate cross section of just
        // this row
        while (iter != verts.cend() && next == get_top(*iter)) {
            heap_set.insert(*iter);
            heap.push(*iter);
            ++iter;
            ++push_count;
        }
        // idea: separate into finishing, entering, and starting
        const auto transition = compute_transition_cross_section(heap_set, next, is_clockwise, horiz.at(next));
        area += transition;
        // no need to check if heap empty; cannot empty until while loop terminates
        while (next == get_bottom(heap.top())) {
            heap_set.erase(heap.top());
            heap.pop();
        }
        // exiting verticals don't participate in next cross-section
        cross_section = recompute_cross_section(heap_set);
        last_row = next;
    }
    my_assert(!heap.empty() && !heap_set.empty(), "heap not empty at end");
    cross_section = recompute_cross_section(heap_set);
    const auto next = get_bottom(heap.top());
    const auto foo = get_top(heap.top());
    return area + cross_section * (next - last_row);  // todo
}

int main() {
    const auto [digs1, digs2] = read_digs();
    const auto [verts1, horiz1] = make_edges(digs1);
    const auto [verts2, horiz2] = make_edges(digs2);
    const auto part1 = solve(verts1, horiz1);
    std::cout << "part 1 = " << part1 << '\n';  // 49897
    const auto part2 = solve(verts2, horiz2);
    std::cout << "part 2 = " << part2 << '\n';  // 194033958221830
}