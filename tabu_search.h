#pragma once
/* 
 * tabu_search.h
 * 
 */
#ifndef TABU_SEARCH_H_
#define TABU_SEARCH_H_

#include <boost/circular_buffer.hpp>

#include "knapsack.h"
#include "rng.h"


class TabuSearchSolver{
    private:
        KnapsackInstance knapsack_instance;
        Knapsack knapsack;
        RNG rng;
        int number_of_steps;
        boost::circular_buffer<std::vector<int>> tabu_list;
    
    public:
        TabuSearchSolver();
        TabuSearchSolver(KnapsackInstance knapsack_instance, Knapsack knapsack, RNG rng, int number_of_steps, int tabu_list_length);
        void solve();
};

#endif