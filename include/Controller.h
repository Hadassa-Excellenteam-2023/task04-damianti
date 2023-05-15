#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <map>
#include <fstream>
#include <sstream>
#include <functional>

#include "Utilities.h"

class Controller {
public:
	Controller(const std::string& fileName = "data.txt");
	void run();
	
private:
	void searchCitiesInRadius(const City& center, const double radius,
		const std::function<double(const Location&, const Location&)>& distanceFunc);
	City findCity(const std::string& cityName);
	void printCloseCities(const std::vector<City>& closeCities, const int totalCloseCities, const int totalNorthCities);
	std::vector<City> m_cities;

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
