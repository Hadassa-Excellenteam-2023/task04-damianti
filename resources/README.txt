Data structures used in the exercise:
std::vector<City> m_cities: I chose to use a std::vector of City. Each City is a struct that has a name (std::sting) 
and a Location. Location is a struct that has two double variables for the location.
This vector stores all the city data read from the file. The program uses a vector because it provides efficient access 
to elements in any order. I thought about using std::map or std::unordered_map, in order to do searching in a better runtime,
but the searching is only done when the user inputs a name of a city. Everywhere else, the program has to check every element of
the file in order to know if its inside the radio. So the runtime was not affected in a hard way.


std::map<int, std::function<double(const Location&, const Location&)>> menu:
This map is used to map integers (the user's choice of norm) to corresponding distance functions. A map is used here because 
it provides an efficient key-value mapping, allowing easy access to the distance functions based on the user's input.

std::vector<City> closeCities:
This vector is used to store the cities that are within a certain radius of a given city.
A vector is used because its the same data structure than the m_cities

std::istringstream iss(line):
This is an input string stream used to parse city coordinates from a line in the file. 
A string stream provides convenient extraction operators (like >>) for parsing string content.

std::function<double(const Location&, const Location&)> distanceFunc:
This is a function object, used as a parameter to the searchCitiesInRadius function. 
It represents a distance function that takes two Location objects and returns a double. 
The use of std::function allows for any callable entity (function, lambda, etc.) matching the signature to be passed,
providing flexibility in choosing the distance calculation method.

