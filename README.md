# City Proximity Finder

City Proximity Finder is a comprehensive tool, developed by Damian Tissembaum, designed to 
provide users with an analysis of geographical proximity between cities. The purpose of this 
tool is to help users find cities that are within a given radius of a selected city, based on 
different mathematical norms for calculating distance.

## Distance Norms

The tool takes into account three distinct types of distance norms:

- **Euclidean Distance (L2 Norm)**: Often recognized as the "ordinary" straight-line distance 
	between two points in Euclidean space.
- **Chebyshev Distance (Linf Norm)**: This distance metric represents the maximum absolute 
	difference along any coordinate dimension.
- **Manhattan Distance (L1 Norm)**: Also known as the taxicab distance, this is the total sum 
	of the difference along each dimension.

## Functionality

The program allows users to select a city and a radius, and then calculates and displays all the cities 
within the specified radius according to the selected distance norm. In addition, the program also sorts 
the cities in increasing order of distance and indicates how many of these cities are to the north of 
the selected city.


## Usage

Launch the program and follow the prompts. Enter the name of your selected city, specify a radius, and 
choose the distance norm you wish to use (0 for Euclidean, 1 for Chebyshev, 2 for Manhattan). 
The program will then provide a list of cities within the given radius based on the selected distance norm.

To terminate the program, simply input "0" when asked to enter a city name.

Please note that the city names must match exactly with the names stored in the program's database, 
which are loaded from a file at the beginning of the program.

## Development

The City Proximity Finder was developed using C++17. It makes extensive use of modern C++ features 
and libraries, including STL containers and algorithms,lambda functions, and exception handling, 
to ensure efficient and robust performance.
