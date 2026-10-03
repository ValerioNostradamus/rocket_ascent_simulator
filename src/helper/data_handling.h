#pragma once
#include <vector>
#include <string>
#include <fstream>

namespace RAS {
    struct DataPoint {
        double x{0.0};
        double y{0.0};
    };

    class DataCurve {
    private:
        std::vector<DataPoint> points;
        int method{0};

    public:
        DataCurve();
        DataCurve(const std::string& ext_method);
        bool loadCSV(const std::string& file_path);
        bool loadVectors(const std::vector<double>& x,
            const std::vector<double>& y);
        [[nodiscard]] double interpolate(double target_x) const;
    };
}