#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include "knapsack.h"
#include "rng.h"

void KnapsackInstance::load_instance(std::string filename){
	std::ifstream infile(filename);

	int counter = 0;
	float value, weight;

	// Get the knapsack instance values from the first line of the file
	std::string first_line;
	std::getline(infile, first_line);
	std::stringstream ss(first_line);
	std::string split_string;
	std::vector<int> knapsack_instance_values;
	while(std::getline(ss, split_string, ' ')){
		knapsack_instance_values.push_back(std::stoi(split_string));
	};
	NUMBER_OF_ITEMS = knapsack_instance_values[0];
	MAX_WEIGHT = knapsack_instance_values[1];
	

	// Read file line by line and saving values to items array
	while(infile >> value >> weight){
		Item item;
		item.index = counter;
		item.value = value;
		item.weight = weight;
		items.push_back(item);
		counter++;
	}
	infile.close();

	return;
};

State::State() = default;

State::State(int number_of_items){
	// Initialize state as all 0's
	std::vector<int> state(number_of_items, 0);
	this->state = state;
};

float State::evaluate_state(KnapsackInstance knapsack_instance){
	int value = 0;
	int weight = 0;

	// Calculate capacity and value of the current state knapsack
	for(long unsigned i=0; i<knapsack_instance.items.size(); i++){
		// Check if the item is currently in the knapsack
		if (state[i] == 1){
			// If it is, we consider its value and weight 
			value = value + knapsack_instance.items[i].value;
			weight = weight + knapsack_instance.items[i].weight;
		};
	};

	// If capacity exceeds the maximum capacity, return -1 as it is an impossible solution
	if (weight > knapsack_instance.MAX_WEIGHT){
		return -1;
	};
	// Else, we return the value of the knapsack
	return value;
};

std::vector<State> State::get_neighbours(){
	std::vector<State> neighbours(state.size());
	// Iterate over size to generate all possible neighbours
	for (long unsigned i=0; i<state.size(); i++){
		neighbours[i].state = state;							// Copy state to neighbours
		neighbours[i].state[i] = 1 - neighbours[i].state[i];	// Bit flip a single item
	};
	return neighbours;
};

Knapsack::Knapsack() = default;

Knapsack::Knapsack(int number_of_items){
	this->value = 0;
	this->weight = 0;
	State state(number_of_items);
	this->state = state;
};

void Knapsack::generate_random_state(KnapsackInstance knapsack_instance){
	RNG rng(knapsack_instance.SEED);
	int random_number;
	while(true){
		for (long unsigned i=0; i<state.state.size(); i++){
			// Get a random number integer number in the range [0, 1]
			random_number = rng.get_random_number(1);
			state.state[i] = random_number;
		};
		// Check if solution is factible
		if (state.evaluate_state(knapsack_instance) >= 0){
			// If it is factible, update the Knapsack values
			value = 0;
			weight = 0;
			for (long unsigned i=0; i<state.state.size(); i++){
				if (state.state[i] == 1){ 
					value = value + knapsack_instance.items[i].value;
					weight = weight + knapsack_instance.items[i].weight;
				};
			};
			return;
		};
	};
};