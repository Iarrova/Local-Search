#pragma once

#ifndef GENETIC_HPP_
#define GENETIC_HPP_

#include <string>

#include "knapsack.hpp"
#include "rng.hpp"

class GeneticSolver{
    private:
        KnapsackInstance knapsack_instance;
        std::vector<State> population;
        std::vector<float> population_fitness;
        RNG rng;

        int population_size;
        int maximum_generations;
        float crossover_probability;
        float mutation_probability;

        State best_state;   // Used to elitist function

        void select();
        void crossover();
        void mutate();
        void evaluate();
        void report(int generation);
        void save_best();
        void elitist();

    public:
        GeneticSolver();
        GeneticSolver(const KnapsackInstance& knapsack_instance, int population_size, int maximum_generations, float crossover_probability, float mutation_probability);
        void solve();
};

#endif