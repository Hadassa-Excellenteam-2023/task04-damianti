#pragma once
#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <functional>

struct Location {
	double x, y;
	Location(double x, double y) : x(x), y(y) {}
    Location() = default;
    bool operator<(const Location& other) const {
        if (x == other.x) return y < other.y;
        return x < other.x;
    }
};

//sorts built for the miltimap sort
struct xSort {
    bool operator()(const Location& loc1, const Location& loc2) const {
        return loc1.x < loc2.x;
    }
};

struct ySort {
    bool operator()(const Location& loc1, const Location& loc2) const {
        return loc1.y < loc2.y;
    }
};

//for the printing
inline std::ostream& operator<<(std::ostream& os, const std::pair<Location, std::string>& p)
{
    os << p.second;
    return os;
}