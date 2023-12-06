#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

#include <boost/algorithm/string.hpp>

#include "models/utilities.h"

class MapRange {
private:
    int dstStart;
    int dstEnd;
    int srcStart;
    int srcEnd;
public:
    MapRange(int, int, int);
    int Convert(int);
};

class Map {
private:
    std::vector<MapRange> ranges;
public:
    Map();
    void AddRange(MapRange);
    int Convert(int);
};

int main() {
    Utilities utils;
    std::vector<std::string> lines = utils.ParseInput("../inputs/05.txt");

    // first row is seeds
    // seeds: 79 14 55 13
    std::vector<int> seeds;
    std::vector<std::string> seedStrings;
    boost::split(seedStrings, lines[0], boost::is_any_of(" "));
    // drop the first element
    seedStrings.erase(seedStrings.begin());
    
    for (auto seedString : seedStrings) {
        seeds.push_back(std::stoi(seedString));
    }

    Map seed_soil;
    Map soil_fertilizer;
    Map fertilizer_water;
    Map water_light;
    Map light_temperature;
    Map temperature_humidity;
    Map humidity_location;

    int currentRow = 3; // first seed to soil line
    // until we hit the empty line
    while (lines[currentRow].length() > 0) {
        std::vector<std::string> seedSoilStrings;
        boost::split(seedSoilStrings, lines[currentRow], boost::is_any_of(" "));
        int soil = std::stoi(seedSoilStrings[0]);
        int seed = std::stoi(seedSoilStrings[1]);
        int length = std::stoi(seedSoilStrings[2]);
        seed_soil.AddRange(MapRange(soil, seed, length));
        currentRow++;
    }

    currentRow += 2; // skip empty line and title
    // until we hit the empty line
    while (lines[currentRow].length() > 0) {
        std::vector<std::string> soilFertilizerStrings;
        boost::split(soilFertilizerStrings, lines[currentRow], boost::is_any_of(" "));
        int fertilizer = std::stoi(soilFertilizerStrings[0]);
        int soil = std::stoi(soilFertilizerStrings[1]);
        int length = std::stoi(soilFertilizerStrings[2]);
        soil_fertilizer.AddRange(MapRange(fertilizer, soil, length));
        currentRow++;
    }

    currentRow += 2; // skip empty line and title
    // until we hit the empty line
    while (lines[currentRow].length() > 0) {
        std::vector<std::string> fertilizerWaterStrings;
        boost::split(fertilizerWaterStrings, lines[currentRow], boost::is_any_of(" "));
        int water = std::stoi(fertilizerWaterStrings[0]);
        int fertilizer = std::stoi(fertilizerWaterStrings[1]);
        int length = std::stoi(fertilizerWaterStrings[2]);
        fertilizer_water.AddRange(MapRange(water, fertilizer, length));
        currentRow++;
    }

    currentRow += 2; // skip empty line and title
    // until we hit the empty line
    while (lines[currentRow].length() > 0) {
        std::vector<std::string> waterLightStrings;
        boost::split(waterLightStrings, lines[currentRow], boost::is_any_of(" "));
        int light = std::stoi(waterLightStrings[0]);
        int water = std::stoi(waterLightStrings[1]);
        int length = std::stoi(waterLightStrings[2]);
        water_light.AddRange(MapRange(light, water, length));
        currentRow++;
    }

    currentRow += 2; // skip empty line and title
    // until we hit the empty line
    while (lines[currentRow].length() > 0) {
        std::vector<std::string> lightTemperatureStrings;
        boost::split(lightTemperatureStrings, lines[currentRow], boost::is_any_of(" "));
        int temperature = std::stoi(lightTemperatureStrings[0]);
        int light = std::stoi(lightTemperatureStrings[1]);
        int length = std::stoi(lightTemperatureStrings[2]);
        light_temperature.AddRange(MapRange(temperature, light, length));
        currentRow++;
    }

    currentRow += 2; // skip empty line and title
    // until we hit the empty line
    while (lines[currentRow].length() > 0) {
        std::vector<std::string> temperatureHumidityStrings;
        boost::split(temperatureHumidityStrings, lines[currentRow], boost::is_any_of(" "));
        int humidity = std::stoi(temperatureHumidityStrings[0]);
        int temperature = std::stoi(temperatureHumidityStrings[1]);
        int length = std::stoi(temperatureHumidityStrings[2]);
        temperature_humidity.AddRange(MapRange(humidity, temperature, length));
        currentRow++;
    }

    currentRow += 2; // skip empty line and title
    // until we hit the empty line
    while (currentRow < lines.size() && lines[currentRow].length() > 0) {
        std::vector<std::string> humidityLocationStrings;
        boost::split(humidityLocationStrings, lines[currentRow], boost::is_any_of(" "));
        int location = std::stoi(humidityLocationStrings[0]);
        int humidity = std::stoi(humidityLocationStrings[1]);
        int length = std::stoi(humidityLocationStrings[2]);
        humidity_location.AddRange(MapRange(location, humidity, length));
        currentRow++;
    }

    std::vector<int> locations;
    // now we have all the maps, we can start the simulation
    for (auto seed : seeds) {
        int soil = seed_soil.Convert(seed);
        int fertilizer = soil_fertilizer.Convert(soil);
        int water = fertilizer_water.Convert(fertilizer);
        int light = water_light.Convert(water);
        int temperature = light_temperature.Convert(light);
        int humidity = temperature_humidity.Convert(temperature);
        int location = humidity_location.Convert(humidity);
        locations.push_back(location);
    }

    // cout lowest location
    std::cout << *std::min_element(locations.begin(), locations.end()) << std::endl;

    return 0;
}


MapRange::MapRange(int dstStart, int srcStart, int length) {
    this->dstStart = dstStart;
    this->dstEnd = dstStart + length - 1;
    this->srcStart = srcStart;
    this->srcEnd = srcStart + length - 1;
}

int MapRange::Convert(int src) {
    if (src < this->srcStart || src > this->srcEnd) {
        return src; // out of range
    }
    int dst = this->dstStart + (src - this->srcStart);
    return dst;
}

Map::Map() {
    this->ranges = std::vector<MapRange>();
}

void Map::AddRange(MapRange range) {
    this->ranges.push_back(range);
}

int Map::Convert(int src) {
    for (auto range : this->ranges) {
        int dst = range.Convert(src);
        if (dst != src) {
            return dst;
        }
    }
    return src;
}