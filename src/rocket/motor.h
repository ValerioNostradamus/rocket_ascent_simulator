#pragma once
#include <array>
#include <vector>

namespace RAS {
    class Motor {
    private:
        char motor_type{'s'};
        double mass{0};
        double dry_mass{0};

        double prop_mass{0};

    public:
        Motor();
        void update();
    };
}