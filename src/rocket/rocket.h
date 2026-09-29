#pragma once
#include <array>
#include <vector>
#include <string>
#include <fstream>

namespace RAS {
    class Rocket {
    private:
        double radius{0};
        double mass{0};
        std::array<double, 3> inertia{0, 0, 0};
        std::string drag_curve{};
        double c_mass_wo_motor{0};

        double c_pressure{0};
        std::vector<double> static_margin{};

    public:
        Rocket();
        Rocket(double mass, double radius, const std::array<double, 3> &inertia,
            std::string drag_curve, double c_mass_wo_motor);
        void info() const;
        void update();
        void addMotor();
        void addSurface();
        void addParachute();

        double interpolate(const std::string& data_path, double interp_to,
            const std::string& method);

        [[nodiscard]] double getMass() const { return mass; }
        [[nodiscard]] double getRadius() const { return radius; }
        [[nodiscard]] const std::array<double, 3>& getInertia() const
            { return inertia; }
    };
}