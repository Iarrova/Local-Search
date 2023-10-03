#pragma once

#ifndef KNAPSACK_HPP_
#define KNAPSACK_HPP_

#include <vector>
#include <string>
#include "rng.hpp"

/**
 * Struct to hold all information related to a specific item of the instance
*/
struct Item{
	int index {-1};
	float value {0};
	float weight {0};
};

/**
 * Holds all variables regarding the specific Knapsack Instance we are solving
 * This should be initialized at the beggining only and then its just used to access its variables
*/
struct KnapsackInstance{
	int NUMBER_OF_ITEMS {0};		// Number of items available to choose from (SIZE)
	float MAX_WEIGHT {0.0};			// Maximum weight allowed by the Knapsack
	std::vector<Item> items; 		// Items for the Knapsack instance (with index, value and weight)
	int SEED {0};
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
		KnapsackInstance knapsack_instance;
		std::vector<int> state;

		State();
		State(KnapsackInstance);

		/**
		 * Evaluates the current state for the Knapsack problem
		 * Measure the current value of the Knapsack
		 * It also verifies factibility (ensures we are not over the maximum capacity).
		 * 
		 * @return The current value of all the items in the Knapsack. 
		 * 		If the weight exceeds the maximum returns -1.
		*/
		float evaluate_state();

		/**
		 * Get the neighbours of the current state
		 * Neighbours will be found using the bit-flipping movement
		 * This means that every bit in the state will be flipped one at a time
		 * 
		 * @returns An array of all possible neighbours for the state s
		*/
		std::vector<State> get_neighbours();

		/**
		 * Sets the internal state to a randomly initialized possible state
		 * The function makes sure that the random state is factible
		*/
		void generate_random_state(RNG &rng);

		/**
		 * Generates a randomly chosen neighbour for the current state
		 * 
		 * @returns A state corresponding to the random neighbour
		*/
		State generate_random_neighbour(RNG &rng);
};

#endif