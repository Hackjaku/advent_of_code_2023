#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <chrono>
#include <unordered_map>

#include "models/utilities.h"

int CalculateHash(std::string hash) {
    int result = 0;
    for (int i = 0; i < hash.size(); i++) {
        result += (int) hash[i];
        result *= 17;
        result %= 256;
    }
    return result;
}


int main() {

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::string> lines = Utilities::ParseInput("../inputs/15.txt");

    // boost split string at comma
    std::vector<std::string> hashes;
    boost::split(hashes, lines[0], boost::is_any_of(","));

    long current_value = 0;

    for (auto hash : hashes) {
        current_value += CalculateHash(hash);
    }

    std::cout << "Part 1: " << current_value << std::endl;

    // hash map
    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> hash_map;
    for (auto hash : hashes) {
        // split hash by the = sign
        std::vector<std::string> hash_split;
        boost::split(hash_split, hash, boost::is_any_of("="));
        // if the hash is not in the map, add it

        bool is_removal;

        if (hash_split.size() == 2) {
            is_removal = false;
        } else {
            is_removal = true;
            // delete the last character from label
            hash_split[0].pop_back();
        }

        auto box = CalculateHash(hash_split[0]);

        if (is_removal) {
            // ? IS REMOVAL
            // if the box is in the map, check if it's vector contains the label (hash_split[0])
            if (hash_map.find(std::to_string(box)) != hash_map.end()) {
                // if the label is in the vector, remove it
                for (int i = 0; i < hash_map[std::to_string(box)].size(); i++) {
                    if (hash_map[std::to_string(box)][i].first == hash_split[0]) {
                        hash_map[std::to_string(box)].erase(hash_map[std::to_string(box)].begin() + i);
                        break;
                    }
                }
                // if the vector of the box is empty, remove the box from the map
                if (hash_map[std::to_string(box)].empty()) {
                    hash_map.erase(std::to_string(box));
                }
            }
            // no action if the box is not in the map
        } else {
            // ? IS ADDITION
            // if the box is in the map, check if it's vector contains the label (hash_split[0])
            if (hash_map.find(std::to_string(box)) != hash_map.end()) {
                // if the label is in the vector, add 1 to the count
                bool found = false;
                for (int i = 0; i < hash_map[std::to_string(box)].size(); i++) {
                    if (hash_map[std::to_string(box)][i].first == hash_split[0]) {
                        hash_map[std::to_string(box)][i].second = std::stoi(hash_split[1]);
                        found = true;
                        break;
                    }
                }
                // if the label is not in the vector, add it
                if (!found) {
                    hash_map[std::to_string(box)].push_back(std::make_pair(hash_split[0], std::stoi(hash_split[1])));
                }
            } else {
                // if the box is not in the map, add it and add the label
                hash_map[std::to_string(box)].push_back(std::make_pair(hash_split[0], std::stoi(hash_split[1])));
            }
        }
    }

    long part2 = 0;

    // calculate the value of the boxes
    for (auto box : hash_map) {
        long box_value = 0;
        for (int i = 1; i <= box.second.size(); i++) {
            box_value += (1 + std::stoi(box.first)) * i * box.second[i - 1].second;
        }
        part2 += box_value;
    }

    std::cout << "Part 2: " << part2 << std::endl;


    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Clock time: " << duration.count() << " us" << std::endl;

    return 0;
}