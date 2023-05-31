#pragma once
#include "Utilities.h"

 
class Controller {
public:
    Controller(const std::string& fileName = "data.txt");
    void run();

private:
    void findCitiesInRadius(const Location& center, const double radius,
        const std::function<double(const Location&, const Location&)>& distanceFunc);
    Location findLocation(const std::string& cityName);
    void printCloseCities(const std::vector<std::pair<Location, std::string>>& closeCities, 
        const size_t totalCloseCities, const __int64 totalNorthCities);
    
    std::unordered_map<std::string, Location> cityMap;
    std::multimap<Location, std::string, xSort> xMap;
    std::multimap<Location, std::string, ySort> yMap;

    std::map<int, std::function<double(const Location&, const Location&)>> menu = {
        {0, [](const Location& a, const Location& b) {
            return std::sqrt(std::pow((a.x - b.x), 2) + std::pow((a.y - b.y), 2));
        }},
        {1, [](const Location& a, const Location& b) {
            return std::max(std::abs(a.x - b.x), std::abs(a.y - b.y));
        }},
        {2, [](const Location& a, const Location& b) {
            return std::abs(a.x - b.x) + std::abs(a.y - b.y);
        }},
    };
};

