#include "Controller.h"

/*
* Description: This is a constructor for the Controller class. It opens the file 
specified by the input string and reads the data to fill the data structures.

Parameters:
	fileName: A string that specifies the name of the file to open and read.

Returns: Nothing (constructor).
*/
Controller::Controller(const std::string& fileName) {

	std::ifstream inputFile(fileName);
	std::string line;

	while (std::getline(inputFile, line)) {
		std::string city = line;

		std::getline(inputFile, line);
		std::istringstream iss(line);

		double x, y;
		char c;
		
		if (!(iss >> x >> c >> y)) {
			throw std::runtime_error("error reading file\n");
		}

		Location location(x, y);
		cityMap[city] = location;

		xMap.insert(std::make_pair(location, city));
		yMap.insert(std::make_pair(location, city));
	}

}

/* Description: This function searches for a city in the cityMap by its name. Runtime of O(1) (mean)

Parameters:
	cityName: A string that specifies the name of the city to find.

Returns: The Location object that corresponds to the input name. If the city is not found, it throws a runtime error.
*/
Location Controller::findLocation(const std::string& cityName)
{
	auto it = cityMap.find(cityName);

	if (it == cityMap.end())
		throw std::runtime_error("\nERROR: \"" + cityName + "\" isn't found in the city list. Please try again.\n");

	return it->second;
	
}

/*Description: This function is the main driver function for the Controller class. It prompts 
the user for a city name, radius, and norm choice, and then finds all cities within the specified 
radius according to the specified norm.

Parameters: None.

Returns: Nothing (void).
*/
void Controller::run()
{
	std::string line;
	std::cout << "Please enter selected city name (with line break after it):\n";
	std::getline(std::cin, line);

	while (line != "0") {
		double radius;
		int norm;

		try {
			auto center = findLocation(line);

			std::cout << "\nPlease enter the wanted radius:\n";
			std::cin >> radius;
			if (radius < 0)
				throw std::runtime_error("\nERROR: radius must be non negative\n");

			std::cout << "\nPlease enter the wanted norm (0 - L2, Euclidean distance, 1 - Linf, Chebyshev distance, 2 - L1, Manhattan distance):\n";
			std::cin >> norm;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

			auto it = menu.find(norm);
			if (it == menu.end())
				throw std::runtime_error("\nERROR: norm function must be 0, 1, or 2\n");

			findCitiesInRadius(center, radius, it->second);
		}
		catch (const std::runtime_error& e) {
			std::cerr << e.what();
		}

		std::cout << "\nPlease enter selected city name (with line break after it):\n";
		std::getline(std::cin, line);
		

	}
}


/* Description: This function finds all cities within a specified radius of a center city 
according to a given distance function.

Parameters:
	center: A Location object representing the center Location of the city selected by user.
	radius: A double representing the radius within which to find cities.
	distanceFunc: A function that takes two Location objects and returns a double representing the 
				distance between them.

Returns: Nothing (void). However, it modifies the closeCities vector.
*/
void Controller::findCitiesInRadius(const Location& center, const double radius, 
	const std::function<double(const Location&, const Location&)>& distanceFunc){


	// Construct Locations as boundaries for x and y
	Location lowerBoundX(center.x - radius, -std::numeric_limits<double>::infinity());
	Location upperBoundX(center.x + radius, std::numeric_limits<double>::infinity());
	Location lowerBoundY(center.y - radius, -std::numeric_limits<double>::infinity());
	Location upperBoundY(center.y + radius, std::numeric_limits<double>::infinity());

	// Find the range of cities within the square boundaries
	auto xRangeBegin = xMap.lower_bound(lowerBoundX);
	auto xRangeEnd = xMap.upper_bound(upperBoundX);
	auto yRangeBegin = yMap.lower_bound(lowerBoundY);
	auto yRangeEnd = yMap.upper_bound(upperBoundY);

	// Copy to vectors in order to intersect both
	std::vector<std::pair<Location, std::string>> xRange(xRangeBegin, xRangeEnd);
	std::vector<std::pair<Location, std::string>> yRange(yRangeBegin, yRangeEnd);

	// sort the vectors (necessary for std::set_intersection)
	std::sort(xRange.begin(), xRange.end());
	std::sort(yRange.begin(), yRange.end());

	// Create a vector for the intersection
	std::vector<std::pair<Location, std::string>> closeCities;

	// Compute the intersection
	std::set_intersection(xRange.begin(), xRange.end(), yRange.begin(), yRange.end(), std::back_inserter(closeCities));


	//erasing the cities inside the rectangle that are outside the circle given by the radius
	closeCities.erase(std::remove_if(closeCities.begin(), closeCities.end(),
		[&](const std::pair<Location, std::string>& city) {
			double distance = distanceFunc(center, city.first);
			return  distance > radius || distance == 0;
		}), closeCities.end());

	
	// count cities that are at a northern point than the center
	__int64 totalNorthCities = std::count_if(closeCities.begin(), closeCities.end(),
		[&](const std::pair<Location, std::string>& city) {
			return city.first.x < center.x;
		});

	auto totalCloseCities = closeCities.size();
	
	//sort closeCities acording to their distance to the center
	std::sort(closeCities.begin(), closeCities.end(),
		[&](const std::pair<Location, std::string>& a, const std::pair<Location, std::string>& b) {
			return distanceFunc(center, a.first) < distanceFunc(center, b.first);
		});

	printCloseCities(closeCities, totalCloseCities, totalNorthCities);

	
}

/* Description: This function prints information about the cities that are within a specified 
	radius of a center city.

Parameters:
	closeCities: A vector of Location objects representing the cities within the specified radius.
	totalCloseCities: An integer representing the total number of cities within the radius.
	totalNorthCities: An integer representing the number of cities within the radius that are 
			north of the center city.

Returns: Nothing (void). It prints information to the console.
*/
void Controller::printCloseCities(const std::vector<std::pair<Location, std::string>>& closeCities,
	const size_t totalCloseCities, const __int64 totalNorthCities){

	std::cout << "\nSearch results:\n" <<
		totalCloseCities << " city / cities found in the given radius.\n" <<
		totalNorthCities << " cities are to the north of the selected city.\n";

	std::cout << "City list:\n";
	std::copy(closeCities.begin(), closeCities.end(), std::ostream_iterator<std::pair<Location, std::string>>(std::cout, "\n"));

}
