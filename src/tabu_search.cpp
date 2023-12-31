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

TabuSearchSolver::TabuSearchSolver(const KnapsackInstance& knapsack_instance, int number_of_steps, int tabu_list_length){
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
	//std::cout << "[INFO] Generated random state: " << state << "\n"; 
	//std::cout << "[INFO] Initial state value: " << state.evaluate_state()[0] << " and weight: " << state.evaluate_state()[1] << "\n\n";

    State best_candidate = state;
    State best_state(knapsack_instance);
    for(int i=0; i<number_of_steps; i++){
        std::vector<State> neighbours = best_candidate.get_neighbours();
        float best_candidate_evaluation = -1;
        for(int j=0; j<neighbours.size(); j++){
            // Check if neighbour evaluation is better than the current best candidate
            // Check if the neighbour is not currently in the Tabu List
            if((neighbours[j].evaluate_state()[0] > best_candidate_evaluation) && !(tabu_list.is_in(neighbours[j].state))){
                best_candidate = neighbours[j];
                best_candidate_evaluation = neighbours[j].evaluate_state()[0];
            };
        };
        if(best_candidate_evaluation == -1){
            break;
        };
        if(best_candidate_evaluation > best_state.evaluate_state()[0]){
            best_state = best_candidate;
        };
        tabu_list.push_front(best_candidate.state);
        //std::cout << "[INFO] Moved to state: " << best_candidate << "\n";
		//std::cout << "[INFO] New state value: " << best_candidate.evaluate_state()[0] << " and weight: " << best_candidate.evaluate_state()[1] << "\n\n";
    };
    std::cout << "[RESULT] Final value: " << best_state.evaluate_state()[0] << " final weight: " << best_state.evaluate_state()[1] << "\n";
	std::cout << "[RESULT] Final state: " << best_state << "\n";
    return;
};