#include "rocket.h"
#include <iostream>
#include <utility>

namespace RAS {
    // Rocket
    Rocket::Rocket() = default;
    Rocket::Rocket(const double mass, const double radius,
        const std::array<double, 3> &inertia,
        std::string drag_curve, const double c_mass_wo_motor):
        radius(radius), mass(mass), inertia(inertia),
        drag_curve(std::move(drag_curve)), c_mass_wo_motor(c_mass_wo_motor) {
        update();
    }

    void Rocket::info() const {
        std::cout << "Rocket Details\n";
        std::cout << "Mass: " << mass << "\n";
        std::cout << "Radius: " << radius << "\n";
        std::cout << "Inertia: [" << inertia[0] << ", " << inertia[1]
            << ", " << inertia[2] << "]" << "\n";
        std::cout << "COM Position (no motor): " << c_mass_wo_motor << "\n";
    }

    void Rocket::update() {
        // updates all data not provided in the costruction, or only
        // calculated when adding components, like the static margin
    }

    void Rocket::addMotor() {

    }

    void Rocket::addSurface() {

    }

    void Rocket::addParachute() {

    }
}