#include "environment.h"
#include <cmath>
#include <iostream>
#include <ostream>
#include <iomanip>

namespace RAS {
    // ISA
    ISAAtmosphere::ISAAtmosphere() {
        initializeISA();
    }
    void ISAAtmosphere::initializeISA() {
        layers = {
            {0.0, 288.15, 101325.0, -0.0065},
            {11000.0, 216.65, 0.0, 0.0},
            {20000.0, 216.65, 0.0, 0.0010},
            {32000.0, 228.65, 0.0, 0.0028},
            {47000.0, 270.65, 0.0, 0.0},
            {51000.0, 270.65, 0.0, -0.0028},
            {71000.0, 214.65, 0.0, -0.0020},
        };

        for (size_t i = 1; i < layers.size(); ++i) {
            const auto& prev_layer = layers[i-1];
            const double dh = layers[i].h_base - prev_layer.h_base;

            if (std::abs(prev_layer.lapse) < 0.0001) {
                layers[i].p_base = prev_layer.p_base * std::exp(
                    (-g0/(R_air*prev_layer.T_base)) * dh);
            } else {
                double T_next = prev_layer.T_base + prev_layer.lapse * dh;
                layers[i].p_base = prev_layer.p_base * std::pow(
                    T_next/prev_layer.T_base,-g0/(prev_layer.lapse * R_air));
            }
        }
    }
    AirState ISAAtmosphere::getAirState(double altitude) const {
        if (altitude < 0) altitude = 0;

        int layer_id{-1};
        for (int i = 0; i < layers.size(); ++i) {
            if (altitude >= layers[i].h_base) {
                layer_id = i;
            } else break;
        }
        const auto& layer = layers[layer_id];
        double dh = altitude - layer.h_base;

        double T = layer.T_base + dh*layer.lapse;
        double P{0};
        if (std::abs(layer.lapse) < 1e-9) {
            P = layer.p_base*std::exp(-g0/(R_air*layer.T_base)*dh);
        } else {
            P = layer.p_base*std::pow(T/layer.T_base,-g0/(layer.lapse*R_air));
        }
        double density = P/(R_air*T);
        double sound_speed = std::sqrt(gamma*T*R_air);

        return AirState(T,P,density,sound_speed);
    }
    void ISAAtmosphere::info() const {
        std::cout << "Info on ISA atmosphere model\n";
        std::cout << std::left << std::setw(16) << "Altitude(m)" << "| ";
        for (const auto& layer : layers) {
            std::cout << std::left << std::setw(12) << layer.h_base;
        }
        std::cout << "\n";
        std::cout << std::left << std::setw(16) << "Temperature(K)" << "| ";
        for (const auto& layer : layers) {
            std::cout << std::left << std::setw(12) << layer.T_base;
        }
        std::cout << "\n";
        std::cout << std::left << std::setw(16) << "Pressure(Pa)" << "| ";
        for (const auto& layer : layers) {
            std::cout << std::left << std::setw(12) << layer.p_base;
        }
        std::cout << "\n";
        std::cout << std::left << std::setw(16) << "Lapse(-)" << "| ";
        for (const auto& layer : layers) {
            std::cout << std::left << std::setw(12) << layer.lapse;
        }
        std::cout << "\n\n";
    }
    // to be implemented
    SecondAtmosphere::SecondAtmosphere() {
        initializeSecondAtmosphere();
    }
    void SecondAtmosphere::initializeSecondAtmosphere() {

    }
    AirState SecondAtmosphere::getAirState(double altitude) const {

        return AirState(0.0,0.0,0.0,0.0);
    }
    void SecondAtmosphere::info() const {

    }
}
