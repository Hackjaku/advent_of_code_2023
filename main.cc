#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/integer/common_factor.hpp>

#include "./models/utilities.h"

class MapNode {
private:
    std::string name;
    MapNode* leftNode;
    MapNode* rightNode;
public:
    MapNode(std::string);
    void SetLeftNode(MapNode*);
    void SetRightNode(MapNode*);

    std::string GetName();
    MapNode* GetLeftNode();
    MapNode* GetRightNode();
};

long least_common_multiple(std::vector<long> numbers);


int main() {
    Utilities utils;
    std::vector<std::string> lines = utils.ParseInput("../inputs/08.txt");

    // read until blank line: directions
    std::vector<std::string> directions;
    for (int i = 0; i < lines.size(); ++i) {
        if (lines[i] == "") {
            break;
        }
        directions.push_back(lines[i]);
    }
    // concatenate directions into one string
    std::string directionsString = "";
    for (int i = 0; i < directions.size(); ++i) {
        directionsString += directions[i];
    }

    // read until end of file: nodes

    std::vector<std::string> nodes;
    bool skipDirections = true;
    for (int i = 0; i < lines.size(); ++i) {

        // first blank line is the end of the directions
        if (lines[i] != "" && skipDirections) {
            continue;
        } else if (skipDirections) {
            skipDirections = false;
            continue;
        }

        nodes.push_back(lines[i]);
        
    }

    // create map
    // nodes are in this format
    // AAA = (BBB, CCC)
    // AAA is the name of the node
    // BBB is the name of the left node
    // CCC is the name of the right node

    // create map
    std::map<std::string, MapNode*> map;
    for (int i = 0; i < nodes.size(); ++i) {
        std::vector<std::string> nodeParts;
        boost::split(nodeParts, nodes[i], boost::is_any_of(" "));
        std::string nodeName = nodeParts[0];
        // leftNodeName is in position 2. Remove the opening parenthesis and the trailing comma
        std::string leftNodeName = nodeParts[2].substr(1, nodeParts[2].length() - 2);

        // rightNodeName is in position 3. Remove the trailing parenthesis
        std::string rightNodeName = nodeParts[3].substr(0, nodeParts[3].length() - 1);

        // check if node exists in map
        if (map.find(nodeName) == map.end()) {
            // node does not exist in map
            MapNode* node = new MapNode(nodeName);
            map[nodeName] = node;
        }

        // check if left node exists in map
        if (map.find(leftNodeName) == map.end()) {
            // node does not exist in map
            MapNode* node = new MapNode(leftNodeName);
            map[leftNodeName] = node;
        }

        // check if right node exists in map
        if (map.find(rightNodeName) == map.end()) {
            // node does not exist in map
            MapNode* node = new MapNode(rightNodeName);
            map[rightNodeName] = node;
        }

        // set left and right nodes
        map[nodeName]->SetLeftNode(map[leftNodeName]);
        map[nodeName]->SetRightNode(map[rightNodeName]);
    }

    // // follow directions
    // MapNode* currentNode = map["AAA"];
    // int i = 0;
    // int steps = 0;

    // while (currentNode != map["ZZZ"]) {
    //     // if i is higher than the length of the directions, we have reached the end of the directions
    //     // reset i to 0
    //     if (i >= directionsString.length()) {
    //         i = 0;
    //     }

    //     // get the current direction
    //     std::string direction = directionsString.substr(i, 1);
    //     if (direction == "L") {
    //         currentNode = currentNode->GetLeftNode();
    //     } else if (direction == "R") {
    //         currentNode = currentNode->GetRightNode();
    //     }

    //     ++i;
    //     ++steps;
    // }

    // std::cout << "Part 1: " << steps << std::endl;


    std::vector<MapNode*> currentNodes;
    std::vector<MapNode*> endingNodes;

    // find all nodes that ends with "A"
    // find all nodes that ends with "Z"

    for (auto it = map.begin(); it != map.end(); ++it) {
        if (it->first.substr(2, 1) == "A") {
            currentNodes.push_back(it->second);
        } else if (it->first.substr(2, 1) == "Z") {
            endingNodes.push_back(it->second);
        }
    }

    int i = 0;
    long steps = 0;

    std::vector<long> stepsTaken;

    for (int j = 0; j < currentNodes.size(); ++j) {

        // if i is higher than the length of the directions, we have reached the end of the directions

        i = 0;
        steps = 0;

        // until current node name does not end with "Z"
        while (currentNodes[j]->GetName().substr(2, 1) != "Z") {
            // if i is higher than the length of the directions, we have reached the end of the directions
            // reset i to 0
            if (i >= directionsString.length()) {
                i = 0;
            }

            // get the current direction
            std::string direction = directionsString.substr(i, 1);
            if (direction == "L") {
                currentNodes[j] = currentNodes[j]->GetLeftNode();
            } else if (direction == "R") {
                currentNodes[j] = currentNodes[j]->GetRightNode();
            }

            ++i;
            ++steps;
        }

        stepsTaken.push_back(steps);
    }

    std::cout << "Part 2: " << least_common_multiple(stepsTaken) << std::endl;

    return 0;
}

long least_common_multiple(std::vector<long> numbers) {
    long lcm = numbers[0];
    for (int i = 1; i < numbers.size(); ++i) {
        lcm = lcm * numbers[i] / boost::integer::gcd(lcm, numbers[i]);
    }
    return lcm;
}

MapNode::MapNode(std::string name) {
    this->name = name;
    this->leftNode = nullptr;
    this->rightNode = nullptr;
}

void MapNode::SetLeftNode(MapNode* node) {
    this->leftNode = node;
}

void MapNode::SetRightNode(MapNode* node) {
    this->rightNode = node;
}

std::string MapNode::GetName() {
    return this->name;
}

MapNode* MapNode::GetLeftNode() {
    return this->leftNode;
}

MapNode* MapNode::GetRightNode() {
    return this->rightNode;
}
