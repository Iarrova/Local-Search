#pragma once

#ifndef GREEDY_HPP_
#define GREEDY_HPP_

#include "knapsack.hpp"

class GreedySolver{
    private:
        KnapsackInstance knapsack_instance;
        State state;
        float value = 0;
        float weight = 0;

        /**
         * Myopic function for the greedy approach.
         * It will always pick the item with the highest value that is not currently in the Knapsack
         * 
         * @returns The Item struct that corresponds to the highest value that can be added
         */
        Item myopic_function();

    public:
        GreedySolver(const KnapsackInstance& knapsack_instance);

        /**
         * Solves the 0/1 Knapsack problem using a Greedy approach
         * 
         * @returns The State of the solution found
        */
        void solve();
};

#endif