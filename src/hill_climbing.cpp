#include <string>
#include <iostream>

#include "knapsack.hpp"
#include "hill_climbing.hpp"
#include "rng.hpp"

HillClimbingSolver::HillClimbingSolver(const KnapsackInstance& knapsack_instance){
	this->knapsack_instance = knapsack_instance;
	State state(knapsack_instance);
	this->state = state;
	RNG rng(knapsack_instance.SEED);
    this->rng = rng;
};

void HillClimbingSolver::best_improvement(){
	// Begin with a random solution
	state.generate_random_state(rng);
	//std::cout << "Generated random knapsack value: " << knapsack.value << " and weight: " << knapsack.weight << "\n";
	State current_state = state;
	std::vector<State> neighbours;
	while(true){
		neighbours = current_state.get_neighbours(); 
		State next_state;
		float next_evaluation = -1;
		//int next_state_index = -1;

		// Search all neighbours for the best node
		for (long unsigned i=0; i<neighbours.size(); i++){
			// Check if the new neighbour is better
			if (neighbours[i].evaluate_state() > next_evaluation){
				// Save the neighbour as the new state and calculate new evaluation
				next_state = neighbours[i];
				next_evaluation = neighbours[i].evaluate_state();
				//next_state_index = i;
			};
		};
		// If the next evaluation is lower than our current state, we have reached an optimum
		// This is because we iterated over all neighbours above and we couldn't find a better neighbour
		if (next_evaluation <= current_state.evaluate_state()){
			//std::cout << "Final Value: " << knapsack.value << " Final weight: " << knapsack.weight << "\n";
			std::cout << "Knapsack value: " << current_state.evaluate_state() << "\n";
			return;
		};
		current_state = next_state;
		//knapsack.value = knapsack.value + knapsack_instance.items[next_state_index].value;
		//knapsack.weight = knapsack.weight + knapsack_instance.items[next_state_index].weight;
		//std::cout << "Knapsack value: " << knapsack.value << " and weight: " << knapsack.weight << "\n";
	};
};

void HillClimbingSolver::first_improvement(){
	// Begin with a random solution
	state.generate_random_state(rng);
	//std::cout << "Generated random knapsack value: " << knapsack.value << " and weight: " << knapsack.weight << "\n";

	State current_state = state;
	std::vector<State> neighbours;
	while(true){
		neighbours = current_state.get_neighbours();
		int new_state_index = -1;

		// Search all neighbours for the first improvement
		for (long unsigned i=0; i<neighbours.size(); i++){
			// Check if the new neighbour is better
			if (neighbours[i].evaluate_state() > current_state.evaluate_state()){
				// Save the neighbour as the new state and calculate new evaluation
				current_state = neighbours[i];
				new_state_index = i;
				break;
			};
		};
		// If no better neighbour was found, we exit
		if (new_state_index == -1){
			//std::cout << "Final Value: " << knapsack.value << " Final weight: " << knapsack.weight << "\n";
			std::cout << "Knapsack value: " << current_state.evaluate_state() << "\n";
			return;
		};
		//knapsack.value = knapsack.value + knapsack_instance.items[new_state_index].value;
		//knapsack.weight = knapsack.weight + knapsack_instance.items[new_state_index].weight;
		//std::cout << "Knapsack value: " << knapsack.value << " and weight: " << knapsack.weight << "\n";
	};
};

void HillClimbingSolver::solve(std::string method){
	if(method.compare("Best-Improvement") == 0){
		best_improvement();
	};
	if(method.compare("First-Improvement") == 0){
		first_improvement();
	};
	return; 
};