#include <iostream>

#include "knapsack.h"
#include "greedy.h"

GreedySolver::GreedySolver(KnapsackInstance knapsack_instance, Knapsack knapsack){
	this->knapsack_instance = knapsack_instance;
	this->knapsack = knapsack;
};

Item GreedySolver::myopic_function(){
	Item best_item;
	// Iterate over all items of the problem
	// We search for the highest value that we **can** include (not already in, and weight fits)
	for (long unsigned i=0; i<knapsack_instance.items.size(); i++){
		if( (knapsack.weight + knapsack_instance.items[i].weight <= knapsack_instance.MAX_WEIGHT) &&
			(knapsack.state.state[i] == 0)){
			// Look for the highest value item
			if( knapsack_instance.items[i].value > best_item.value){
				best_item = knapsack_instance.items[i];
			};
		};
	};
	//std::cout << "Selected item with index: " << best_item.index << " value: " << best_item.value << " and weight: " << best_item.weight << "\n";
	return best_item;
};

void GreedySolver::solve(){
	Item best_item;
	while(true){
		// Find the highest value item to add to the Knapsack
		best_item = myopic_function();

		// Check if program has finished
		if(best_item.index == -1){
			std::cout << "Final Value: " << knapsack.value << " Final weight: " << knapsack.weight << "\n";
			return;
		};

		// Else, we update the knapsack variables
		knapsack.value = knapsack.value + best_item.value;
		knapsack.weight = knapsack.weight + best_item.weight;
		knapsack.state.state[best_item.index] = 1;
		std::cout << "Knapsack value: " << knapsack.value << " and weight: " << knapsack.weight << "\n";
	};
};