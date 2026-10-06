#include "basic_ui.h"
#include "environment/environment.h"

#include <iostream>
#include <memory>

namespace RAS {
    bool menu() {
        char flag{'0'};
        std::unique_ptr<RAS::Atmosphere> env =
            std::unique_ptr<RAS::Atmosphere>();

        std::string model;
        std::cout << "env model: ";
        std::cin >> model;

        if (model == "ISA") {
            env = std::make_unique<RAS::ISAAtmosphere>();
        }
        if (model == "GRAM") {
            std::make_unique<RAS::GRAMAtmosphere >();
        } else {
            // temporary
            std::cout << "unknown model, defaulting to ISA.\n";
            env = std::make_unique<RAS::ISAAtmosphere>();
        }
        env->info();
        while (flag != 'q') {
            double h{0};
            std::cout << "altitude: ";
            std::cin >> h;

            RAS::AirState state = env->getAirState(h);
            std::cout << "T: " << state.temperature << "\nP: " << state.pressure <<
                "\nrho: " << state.density << "\nsound speed: " << state.sound_speed
                << std::endl;

            std::cout << "press q to quit or anything to continue: ";
            std::cin >> flag;
        }
        return false;
    }
}
