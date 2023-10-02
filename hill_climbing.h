#pragma once
/* 
 * hill_climbing.h
 * Includes all definitions to solve the Knapsack problem using a Hill-Climbing approach
 */
#ifndef HILL_CLIMBING_H_
#define HILL_CLIMBING_H_

#include <string>

#include "knapsack.h"

class HillClimbingSolver{
    private:
        KnapsackInstance knapsack_instance;
        Knapsack knapsack;

        void best_improvement();
        void first_improvement();

    public:
        HillClimbingSolver();
        HillClimbingSolver(KnapsackInstance knapsack_instance, Knapsack knapsack);
        void solve(std::string method);
};

#endif