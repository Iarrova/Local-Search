#pragma once
/*
 * greedy.h
 * Includes all definitions to solve the Knapsack problem using a Greedy method
 */
#ifndef GREEDY_H_
#define GREEDY_H_

#include "knapsack.h"

class GreedySolver{
    private:
        KnapsackInstance knapsack_instance;
        Knapsack knapsack;

        /**
         * Myopic function for the greedy approach.
         * It will always pick the item with the highest value that is not currently in the Knapsack
         * 
         * @returns The Item struct that corresponds to the highest value that can be added
         */
        Item myopic_function();

    public:
        GreedySolver(KnapsackInstance knapsack_instance, Knapsack knapsack);

        /**
         * Solves the 0/1 Knapsack problem using a Greedy approach
        */
        void solve();
};

#endif