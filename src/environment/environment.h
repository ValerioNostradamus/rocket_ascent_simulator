#pragma once
#include <string>
#include <vector>
#include <cmath>

namespace RAS {
    struct ISALayer {
        double h_base{0.0};
        double T_base{0.0};
        double p_base{0.0};
        double lapse{0.0};
    };
    struct AirState {
        double temperature{0.0};
        double pressure{0.0};
        double density{0.0};
        double sound_speed{0.0};
    };
    // generic class
    class Atmosphere {
    public:
        virtual ~Atmosphere() = default;
        [[nodiscard]] virtual AirState getAirState(double altitude) const = 0;
        virtual void info() const = 0;
    };
    // ISA
    class ISAAtmosphere : public Atmosphere {
    private:
        static constexpr double g0 = 9.80665;
        static constexpr double R_air = 287.05287;
        static constexpr double gamma = 1.4;
        std::vector<ISALayer> layers;

        void initializeISA();

    public:
        ISAAtmosphere();
        [[nodiscard]] AirState getAirState(double altitude) const override;
        void info() const override;
    };
    // to be implemented
    class SecondAtmosphere : public Atmosphere {
    private:
        void initializeSecondAtmosphere();
    public:
        SecondAtmosphere();
        [[nodiscard]] AirState getAirState(double altitude) const override;
        void info() const override;
    };
}
