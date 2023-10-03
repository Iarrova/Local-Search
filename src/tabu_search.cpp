#include <iostream>

#include "knapsack.hpp"
#include "rng.hpp"
#include "tabu_search.hpp"

TabuList::TabuList() = default;

TabuList::TabuList(int tabu_list_length){
    boost::circular_buffer<std::vector<int>> tabu_list(tabu_list_length);
    this->tabu_list = tabu_list;
};

bool TabuList::is_in(std::vector<int> state){
    for(int i=0; i<tabu_list.capacity(); i++){
        if(state == tabu_list[i]){
            return true;
        };
    };
    return false;
};

void TabuList::push_front(std::vector<int> state){
    tabu_list.push_front(state);
};

TabuSearchSolver::TabuSearchSolver(KnapsackInstance knapsack_instance, int number_of_steps, int tabu_list_length){
    this->knapsack_instance = knapsack_instance;
    State state(knapsack_instance);
	this->state = state;
    TabuList tabu_list(tabu_list_length);
    this->tabu_list = tabu_list;
    RNG rng(knapsack_instance.SEED);
    this->rng = rng;
    this->number_of_steps = number_of_steps;
};

void TabuSearchSolver::solve(){
    // Begin with a random solution
    state.generate_random_state(rng);
	//std::cout << "Generated random knapsack value: " << knapsack.value << " and weight: " << knapsack.weight << "\n";

    State best_candidate = state;
    State best_state(knapsack_instance);
    for(int i=0; i<number_of_steps; i++){
        std::vector<State> neighbours = best_candidate.get_neighbours();
        float best_candidate_evaluation = -1;
        for(int j=0; j<neighbours.size(); j++){
            // Check if neighbour evaluation is better than the current best candidate
            // Check if the neighbour is not currently in the Tabu List
            if((neighbours[j].evaluate_state() > best_candidate_evaluation) && !(tabu_list.is_in(neighbours[j].state))){
                best_candidate = neighbours[j];
                best_candidate_evaluation = neighbours[j].evaluate_state();
            };
        };
        if(best_candidate_evaluation == -1){
            break;
        };
        if(best_candidate_evaluation > best_state.evaluate_state()){
            best_state = best_candidate;
        };
        tabu_list.push_front(best_candidate.state);
    };
    std::cout << "Knapsack value: " << best_state.evaluate_state() << "\n";
};