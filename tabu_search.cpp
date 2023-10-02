#include <iostream>
#include <boost/circular_buffer.hpp>  

#include "knapsack.h"
#include "rng.h"
#include "tabu_search.h"

TabuSearchSolver::TabuSearchSolver() = default;

TabuSearchSolver::TabuSearchSolver(KnapsackInstance knapsack_instance, Knapsack knapsack, RNG rng, int number_of_steps, int tabu_list_length){
    this->knapsack_instance = knapsack_instance;
    this->knapsack = knapsack;
    this->rng = rng;
    this->number_of_steps = number_of_steps;
    boost::circular_buffer<std::vector<int>> tabu_list(tabu_list_length);
    this->tabu_list = tabu_list;
};

void TabuSearchSolver::solve(){
    // Begin with a random solution
    knapsack.generate_random_state(knapsack_instance);
	std::cout << "Generated random knapsack value: " << knapsack.value << " and weight: " << knapsack.weight << "\n";

    State best_candidate = knapsack.state;
    State best_state(knapsack_instance.NUMBER_OF_ITEMS);
    bool is_in_tabu;

    for(int i=0; i<number_of_steps; i++){
        std::vector<State> neighbours = best_candidate.get_neighbours();
        float best_candidate_evaluation = -1;
        for(int j=0; j<neighbours.size(); j++){
            // Check if neighbour evaluation is better than the current best candidate
            if(neighbours[j].evaluate_state(knapsack_instance) > best_candidate_evaluation){
                // Check if the neighbour is not currently in the Tabu List
                for(int k=0; k<tabu_list.capacity(); k++){
                    if(neighbours[j].state == tabu_list[k]){
                        is_in_tabu = true;
                    };
                };
                if(is_in_tabu){
                    is_in_tabu = false;
                    continue;
                };
                best_candidate = neighbours[j];
                best_candidate_evaluation = neighbours[j].evaluate_state(knapsack_instance);
            };
        };
        if(best_candidate_evaluation == -1){
            break;
        };
        if(best_candidate_evaluation > best_state.evaluate_state(knapsack_instance)){
            best_state = best_candidate;
        };
        tabu_list.push_front(best_candidate.state);
    };
    std::cout << "Knapsack value: " << best_state.evaluate_state(knapsack_instance) << "\n";
};

// TODO: Move Tabu List to its own class with the is_in() method to check if an element is inside