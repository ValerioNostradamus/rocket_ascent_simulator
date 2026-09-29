#include <iostream>
#include "helper/data_handling.h"
#include "rocket/rocket.h"

int main() {
    RAS::Rocket rocket;
    rocket.info();
    char a{'0'};
    std::string file_path;
    std::string method;
    double interpole_to;

    std::cout << "filepath:\t";
    std::cin >> file_path;
    std::cout << "method:\t";
    std::cin >> method;
    RAS::DataCurve data_curve(method);
    data_curve.loadCSV(file_path);

    while (a != 'q') {
        std::cout << "interpole to: ";
        std::cin >> interpole_to;
        std::cout << "result: " << data_curve.interpolate(interpole_to);
        std::cout << "\ninsert q to exit, or anything to continue: ";
        std::cin >> a;
    }

    return 0;
}