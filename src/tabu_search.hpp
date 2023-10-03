#pragma once

#ifndef TABU_SEARCH_HPP_
#define TABU_SEARCH_HPP_

#include <boost/circular_buffer.hpp>

#include "knapsack.hpp"
#include "rng.hpp"

class TabuList{    
    public:
        TabuList();
        TabuList(int tabu_list_length);

        boost::circular_buffer<std::vector<int>> tabu_list;

        bool is_in(std::vector<int>);
        void push_front(std::vector<int>);
};


class TabuSearchSolver{
    private:
        KnapsackInstance knapsack_instance;
        State state;
        TabuList tabu_list;
        RNG rng;
        int number_of_steps;
    
    public:
        TabuSearchSolver(const KnapsackInstance& knapsack_instance, int number_of_steps, int tabu_list_length);
        void solve();
};

#endif