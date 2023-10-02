#pragma once
/* 
 * knapsack.h
 * Includes all definitions for the 0/1 Knapsack problem
 */
#ifndef KNAPSACK_H_
#define KNAPSACK_H_

#include <vector>
#include <string>

struct Item{
	int index {-1};
	float value {};
	float weight {};
};

/**
 * Holds all variables regarding the specific Knapsack Instance we are solving
 * This should be initialized at the beggining only and then just used to access its variables
*/
struct KnapsackInstance{
	int NUMBER_OF_ITEMS {};			// Number of items available to choose from (SIZE)
	float MAX_WEIGHT {};			// Maximum weight allowed by the Knapsack
	std::vector<Item> items; 		// Items for the Knapsack instance (with index, value and weight)
	int SEED {};
	void load_instance(std::string filename);
};

/**
 * Implementation of the Representation (State) of the Knapsack Problem
 * 
 * The current state of the Knapsack will be represented with a binary array
 * The array will be of shape [1 x n], where `n` is the number of items to choose from
 * Values of the array will be in the domain {0, 1}
 * 
 * A 0 indicates that the object is not inside the Knapsack
 * A 1 indicates that the object is currently inside the Knapsack
 * 
 * The state does not consider any restrictions for the problem
*/
class State{
	public:
		State();
		State(int number_of_items);

		std::vector<int> state;

		/**
		 * Get the neighbours of the current state
		 * 
		 * Neighbours will be found using the bit-flipping movement
		 * This means that every bit in the state will be flipped one at a time
		 * 
		 * @returns An array of all possible neighbours for the state s
		*/
		std::vector<State> get_neighbours();

		/**
		 * Evaluates the current state for the Knapsack problem
		 * Measure the current value of the Knapsack
		 * It also verifies factibility (ensures we are not over the maximum capacity).
		 * 
		 * @param Knapsack A Knapsack problem instance with the values and weights of the items
		 * 
		 * @return The current value of all the items in the Knapsack. 
		 * 		If the weight exceeds the maximum returns -1.
		*/
		float evaluate_state(KnapsackInstance knapsack_instance);
};

class Knapsack{
	public:
		Knapsack();
		Knapsack(int number_of_items);

		float value;	// Current value of the Knapsack
		float weight;	// Current weight of the Knapsack
		State state;

		void generate_random_state(KnapsackInstance knapsack_instance);
};

#endif