#include <iostream>

#include "knapsack.h"
#include "greedy.h"
#include "hill_climbing.h"
#include "simulated_annealing.h"
#include "tabu_search.h"
#include "rng.h"

int main(int argc, char *argv[]){
	if (argc != 3){
		std::cout << "[ERROR] You need to provide filename and seed in command line!" << "\n";
		return -1;
	};
	std::string PATH = argv[1];
	int SEED = atoi(argv[2]); 
	std::cout << "Argument [1]:" << PATH << " argument [2]: " << SEED << "\n";

	// Load the Knapsack Items information
	KnapsackInstance knapsack_instance;
	knapsack_instance.load_instance(PATH);
	knapsack_instance.SEED = SEED;

	std::cout << "------- Knapsack Information -------" << "\n";
	std::cout << "Number of Items: " << knapsack_instance.NUMBER_OF_ITEMS << "\tKnapsack Capacity: " << knapsack_instance.MAX_WEIGHT << "\tSeed: " << knapsack_instance.SEED << "\n\n";

	// Greedy	
	std::cout << "------- Greedy -------" << "\n";
	Knapsack knapsack_1(knapsack_instance.NUMBER_OF_ITEMS);
	GreedySolver greedy_solver(knapsack_instance, knapsack_1);	
	greedy_solver.solve();

	// Hill-Climbing Best Improvement
	std::cout << "\n------- Hill-Climbing (Best) -------" << "\n";
	Knapsack knapsack_2(knapsack_instance.NUMBER_OF_ITEMS);
	HillClimbingSolver hill_climbing_solver_best(knapsack_instance, knapsack_2);
	hill_climbing_solver_best.solve("Best-Improvement");

	// Hill-Climbing First Improvement
	std::cout << "\n------- Hill-Climbing (First) -------" << "\n";
	Knapsack knapsack_3(knapsack_instance.NUMBER_OF_ITEMS);
	HillClimbingSolver hill_climbing_solver_first(knapsack_instance, knapsack_3);
	hill_climbing_solver_first.solve("First-Improvement");

	// Simulated Annealing
	std::cout << "\n------- Simulated Annealing -------" << "\n";
	int number_of_steps = 200;
	int initial_temperature = 100;
	float temperature_factor = 0.97;
	Knapsack knapsack_4(knapsack_instance.NUMBER_OF_ITEMS);
	RNG rng(knapsack_instance.SEED);
	SimulatedAnnealingSolver simulated_annealing_solver(knapsack_instance, knapsack_4, rng, number_of_steps, initial_temperature, temperature_factor);
	simulated_annealing_solver.solve();

	std::cout << "\n------- Tabu Search -------" << "\n";
	int number_of_steps_tabu = 200;
	int tabu_list_length = 5;
	Knapsack knapsack_5(knapsack_instance.NUMBER_OF_ITEMS);
	RNG rng_1(knapsack_instance.SEED);
	TabuSearchSolver tabu_search_solver(knapsack_instance, knapsack_5, rng_1, number_of_steps_tabu, tabu_list_length);
	simulated_annealing_solver.solve();

	return 0;
}