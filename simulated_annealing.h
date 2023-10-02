#pragma once
/* 
 * simulated_annealing.h
 * Includes all definitions to solve the Knapsack problem using a Simulated Annealing approach
 */
#ifndef SIMULATED_ANNEALING_H_
#define SIMULATED_ANNEALING_H_

#include "knapsack.h"
#include "rng.h"

class SimulatedAnnealingSolver{
    private:
        KnapsackInstance knapsack_instance;
        Knapsack knapsack;
        RNG rng;
        int number_of_steps;
        int initial_temperature;
        float temperature_factor;

        float get_random_float();
        State get_random_neighbour();
    
    public:
        SimulatedAnnealingSolver();
        SimulatedAnnealingSolver(KnapsackInstance knapsack_instance, Knapsack knapsack, RNG rng, int number_of_steps, int initial_temperature, float temperature_factor);
        void solve();
};

#endif