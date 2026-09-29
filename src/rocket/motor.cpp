#include "motor.h"

namespace RAS {
    Motor::Motor() {
        update();
    }

    void Motor::update() {
        prop_mass = mass - dry_mass;
    }
}