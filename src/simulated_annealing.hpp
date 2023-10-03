#pragma once

#ifndef SIMULATED_ANNEALING_HPP_
#define SIMULATED_ANNEALING_HPP_

#include "knapsack.hpp"
#include "rng.hpp"

class SimulatedAnnealingSolver{
    private:
        KnapsackInstance knapsack_instance;
        State state;
        RNG rng;
        int number_of_steps;
        int initial_temperature;
        float temperature_factor;
    
    public:
        SimulatedAnnealingSolver(KnapsackInstance knapsack_instance, int number_of_steps, int initial_temperature, float temperature_factor);
        void solve();
};

#endif