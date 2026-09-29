#include "data_handling.h"
#include <iostream>
#include <string>
#include <sstream>

namespace RAS {
    // DataCurve
    DataCurve::DataCurve() {
        method = 0;
    };
    DataCurve::DataCurve(const std::string& ext_method) {
        if (ext_method == "clamp" or ext_method == "0") method = 0;
        if (ext_method == "maintain" or ext_method == "1") method = 1;
    }
    bool DataCurve::loadCSV(const std::string& file_path) {
        std::ifstream file(file_path);
        if (!file.is_open()) {
            std::cerr << "Failed to open: " << file_path << "\n";
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;

            std::stringstream ss(line);
            std::string x_str, y_str;

            if (std::getline(ss, x_str, ',') &&
                std::getline(ss, y_str, ',')) {
                if (!y_str.empty() && y_str.back() == '\r') {
                    y_str.pop_back();
                }
                points.push_back({.x = std::stod(x_str),
                    .y = std::stod(y_str)});
            }
        }
        std::sort(points.begin(), points.end(),
            [](const DataPoint& a, const DataPoint& b)
            {return a.x < b.x; });
        return !points.empty();
    }
    bool DataCurve::loadVectors(const std::vector<double>& x,
        const std::vector<double>& y) {
        if (x.size() != y.size()) {
            return false;
        }
        for (int i = 0; i < x.size(); ++i) {
            points.push_back({.x = x[i], .y = y[i]});
        }
        std::sort(points.begin(), points.end(),
            [](const DataPoint& a, const DataPoint& b)
            {return a.x < b.x; });
        return !points.empty();
    }
    [[nodiscard]] double DataCurve::interpolate(const
        double target_x) const {
        if (points.empty()) return 0.0;

        if (target_x < points.front().x) {
            switch (method) {
                case 0:
                    return 0.0;
                case 1:
                    return points.front().y;
                default:
                    return 0.0;
            }
        }
        if (target_x > points.back().x) {
            switch (method) {
                case 0:
                    return 0.0;
                case 1:
                    return points.back().y;
                default:
                    return 0.0;
            }
        }

        for (size_t i = 0; i < points.size() - 1; ++i) {
            if (target_x >= points[i].x && target_x <= points[i+1].x) {
                double x1 = points[i].x;
                double y1 = points[i].y;
                double x2 = points[i+1].x;
                double y2 = points[i+1].y;

                return y1 + ((target_x - x1) / (x2 - x1)) * (y2 - y1);
            }
        }
        return 0.0;
    }
}