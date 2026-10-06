#pragma once
#include <string>
#include <vector>

namespace RAS {
    enum class GRAMModel {
        MET = 1,
        MSIS = 2,
        JB2008 = 3
    };
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
    struct GRAMInput {
        std::string SpicePath{"../src/environment/spice/"};
        std::string DataPath{"../src/environment/data/"};
        std::string ListFileName{"../output/gram_interface/myref_LIST"};
        std::string ColumnFileName{"../output/gram_interface/myref_OUTPUT"};

        int Year{2000};
        int Month{1};
        int Day{1};
        int Hour{0};
        int Minute{0};
        double Second{0.0};

        double RandomPerturbationScale{1.6};
        double HorizontalWindPerturbationScale{1.75};
        double VerticalWindPerturbationScale{2.0};

        int NumberOfMonteCarloRuns{1};
        int ThermosphereModel{static_cast<int>(GRAMModel::MET)};

        bool InitializePerturbations{false};
        double InitialDensityPerturbation{0};
        double InitialTemperaturePerturbation{0};
        double InitialEWWindPerturbation{0};
        double InitialNSWindPerturbation{0};
        double InitialVerticalWindPerturbation{0};

        bool UseTrajectoryFile{false};
        std::string TrajectoryFileName{"null"};

        bool FastModeOn{false};
        bool ExtraPrecision{false};
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
    // GRAM
    // still needs the actual program and related files, and the function
    // to call it
    class GRAMAtmosphere : public Atmosphere {
    private:
        static void initializeGRAMAtmosphere();
        static void initializeGRAMAtmosphere(const GRAMInput& input);
        static bool createGRAMInputFile(const GRAMInput& input);
    public:
        GRAMAtmosphere();
        GRAMAtmosphere(const GRAMInput& input);
        [[nodiscard]] AirState getAirState(double altitude) const override;
        void info() const override;
    };
}
