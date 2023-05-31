Data structures used in the exercise:
std::unordered_map<std::string, Location> (cityMap): This was chosen to map city names to 
their corresponding Location objects. An unordered map was used because the order of the 
elements is not important in this context. It provides O(1) average time complexity for 
lookups and insertions which is beneficial for performance. Also, it allows us to easily 
and quickly find a city by its name.

std::multimap<Location, std::string, xSort> xMap and 
std::multimap<Location, std::string, ySort> yMap: Multimaps were chosen to enable an efficient 
way to find cities within a range based on their x and y coordinates. It was needed to use a 
multimap instead of a regular map because there can be multiple cities with the same x or y coordinate.
The custom comparators xSort and ySort were used to sort the multimaps based on the x and y coordinates respectively.

std::vector<std::pair<Location, std::string>> closeCities, xRange, yRange: These were chosen 
for storing the cities within certain x and y range, and finally, the cities within the radius. 
The vector is a good choice for this purpose because it allows for easy sorting.
We needed to do intersection of xMap and yMap and that is not possible to do in a map, so
a vector was needed here.

std::map<int, std::function<double(const Location&, const Location&)>> (menu): This map was chosen 
to map the norm types (0, 1, 2) to their corresponding distance calculating functions. 
The reason to use a map here is to provide an O(logN) lookup and also maintain the sorting order, 
which could be beneficial for future expansions where more norms might be added.

The selection of these data structures has contributed to making the implementation 
more efficient and maintainable. By using these specific data structures, 
the program will handle a large number of cities and queries in a performance-friendly way.
