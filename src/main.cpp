#include <iostream>
#include <cstdlib>
#include "environment/environment.h"
#include "helper/data_handling.h"
#include "integrator/integrator.h"
#include "io/basic_ui.h"
#include "rocket/rocket.h"
#include "rocket/motor.h"

int main() {
    RAS::menu();

    int result = std::system("python3 ../python/plots.py");

    if (result != 0) {
        std::cerr << "Failed to run Python script.\n";
    }

    return 0;
}