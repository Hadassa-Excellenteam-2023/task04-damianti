#include "Controller.h"

/*
* Description: This is a constructor for the Controller class. It opens the file 
specified by the input string and reads the data to populate the m_cities vector.

Parameters:
	fileName: A string that specifies the name of the file to open and read.

Returns: Nothing (constructor).
*/
Controller::Controller(const std::string& fileName) {
	std::ifstream infile(fileName);
	if (!infile) {
		throw std::runtime_error("Error opening file: " + fileName);
	}
	std::string line;

	while (std::getline(infile, line)) {
		City city;
		city.name = line;
		char c;

		std::getline(infile, line);
		std::istringstream iss(line);
		if (!(iss >> city.location.x >> c >> city.location.y)) {
			throw std::runtime_error("error reading file\n");
		}

		m_cities.push_back(city);
	}
}

/* Description: This function searches for a city in the m_cities vector by its name.

Parameters:
	cityName: A string that specifies the name of the city to find.

Returns: The City object that corresponds to the input name. If the city is not found, it throws a runtime error.
*/
City Controller::findCity(const std::string& cityName)
{
	auto it = std::find_if(m_cities.begin(), m_cities.end(),
		[&](const City city) {return city.name == cityName; });

	if (it == m_cities.end())
		throw std::runtime_error("\nERROR: \"" + cityName + "\" isn't found in the city list. Please try again.\n");

	return *it;
	
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
			auto wantedCity = findCity(line);

			std::cout << "\nPlease enter the wanted radius:\n";
			std::cin >> radius;
			if (radius < 0)
				throw std::runtime_error("\nERROR: radius must be non negative\n");

			std::cout << "\nPlease enter the wanted norm (0 – L2, Euclidean distance, 1 – Linf, Chebyshev distance, 2 – L1, Manhattan distance):\n";
			std::cin >> norm;


			auto it = menu.find(norm);
			if (it == menu.end())
				throw std::runtime_error("\nERROR: norm function must be 0, 1, or 2\n");

			searchCitiesInRadius(wantedCity, radius, it->second);
		}
		catch (const std::runtime_error& e) {
			std::cerr << e.what();
		}

		std::cout << "\nPlease enter selected city name (with line break after it):\n";
		std::cin.ignore();
		std::getline(std::cin, line);

	}
}


/* Description: This function finds all cities within a specified radius of a center city 
according to a given distance function.

Parameters:
	center: A City object representing the center city.
	radius: A double representing the radius within which to find cities.
	distanceFunc: A function that takes two Location objects and returns a double representing the 
				distance between them.

Returns: Nothing (void). However, it modifies the closeCities vector.
*/
void Controller::searchCitiesInRadius(const City& center, const double radius, 
	const std::function<double(const Location&, const Location&)>& distanceFunc){

	std::vector<City> closeCities;
	int totalNorthCities, totalCloseCities;

	//copying the cities that are inside the rectangle given by the radius
	std::copy_if(m_cities.begin(), m_cities.end(), std::back_inserter(closeCities),
		[&](const City& city) {
			double distX = std::abs(center.location.x - city.location.x);
			double distY = std::abs(center.location.y - city.location.y);

			return distX <= radius && distY <= radius;
		});

	//erasing the cities inside the rectangle that are outside the circle given by the radius
	closeCities.erase(std::remove_if(closeCities.begin(), closeCities.end(),
		[&](const City& city) {
			double distance = distanceFunc(center.location, city.location);
			return  distance > radius || distance == 0;
		}), closeCities.end());

	
	totalNorthCities = std::count_if(closeCities.begin(), closeCities.end(),
		[&](const City& city) {
			return city.location.y < center.location.y;
		});

	totalCloseCities = closeCities.size();

	std::sort(closeCities.begin(), closeCities.end(),
		[&](const City& a, const City& b) {
			return distanceFunc(center.location, a.location) < distanceFunc(center.location, b.location);
		});


	printCloseCities(closeCities, totalCloseCities, totalNorthCities);
	
}

/*Description: This function prints information about the cities that are within a specified 
	radius of a center city.

Parameters:
	closeCities: A vector of City objects representing the cities within the specified radius.
	totalCloseCities: An integer representing the total number of cities within the radius.
	totalNorthCities: An integer representing the number of cities within the radius that are 
			north of the center city.

Returns: Nothing (void). It prints information to the console.
*/
void Controller::printCloseCities(const std::vector<City>& closeCities, 
	const int totalCloseCities, const int totalNorthCities){

	std::cout << "\nSearch results:\n" <<
		totalCloseCities << " city / cities found in the given radius.\n" <<
		totalNorthCities << " cities are to the north of the selected city.\n";

	std::cout << "City list:\n";
	std::for_each(closeCities.begin(), closeCities.end(), [](const City& city) {
		std::cout << city.name << std::endl;
		});

}


