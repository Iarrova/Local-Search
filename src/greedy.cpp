#include <iostream>

#include "knapsack.hpp"
#include "greedy.hpp"

GreedySolver::GreedySolver(const KnapsackInstance& knapsack_instance){
	this->knapsack_instance = knapsack_instance;
	State state(knapsack_instance);
	this->state = state;
};

Item GreedySolver::myopic_function(){
	Item best_item;
	// Iterate over all items of the problem
	// We search for the highest value that we **can** include (not already in, and weight fits)
	for (long unsigned i=0; i<knapsack_instance.items.size(); i++){
		if((weight + knapsack_instance.items[i].weight <= knapsack_instance.MAX_WEIGHT) && (state.state[i] == 0)){
			// Look for the highest value item
			if(knapsack_instance.items[i].value > best_item.value){
				best_item = knapsack_instance.items[i];
			};
		};
	};
	return best_item;
};

void GreedySolver::solve(){
	Item best_item;
	while(true){
		// Find the highest value item to add to the Knapsack
		best_item = myopic_function();

		// Check if program has finished
		if(best_item.index == -1){
			std::cout << "[RESULT] Final value: " << value << " final weight: " << weight << "\n";
			std::cout << "[RESULT] Final state: " << state << "\n";
			return;
		};

		// Else, we update the knapsack variables
		value = value + best_item.value;
		weight = weight + best_item.weight;
		state.state[best_item.index] = 1;
		//std::cout << "[INFO] Picked item with index: " << best_item.index << " value: " << best_item.value << " and weight: " << best_item.weight << "\n";
		//std::cout << "[INFO] Knapsack value: " << value << " and weight: " << weight << "\n\n";
	};
};