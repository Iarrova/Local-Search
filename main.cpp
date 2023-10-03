#include <iostream>

#include "src/knapsack.hpp"
#include "src/greedy.hpp"
#include "src/hill_climbing.hpp"
#include "src/simulated_annealing.hpp"
#include "src/tabu_search.hpp"
#include "src/rng.hpp"

int main(int argc, char *argv[]){
	if (argc != 3){
		std::cout << "[ERROR] You need to provide filename and seed in command line!" << "\n";
		return -1;
	};
	std::string PATH = argv[1];
	int SEED = atoi(argv[2]); 

	// Load the Knapsack Items information
	KnapsackInstance knapsack_instance;
	knapsack_instance.load_instance(PATH);
	knapsack_instance.SEED = SEED;

	std::cout << "------- Knapsack Information -------" << "\n";
	std::cout << "Number of Items: " << knapsack_instance.NUMBER_OF_ITEMS << "\tKnapsack Capacity: " << knapsack_instance.MAX_WEIGHT << "\tSeed: " << knapsack_instance.SEED << "\n\n";

	// Greedy	
	std::cout << "------- Greedy -------" << "\n";
	GreedySolver greedy_solver(knapsack_instance);	
	greedy_solver.solve();

	// Hill-Climbing Best Improvement
	std::cout << "\n------- Hill-Climbing (Best) -------" << "\n";
	HillClimbingSolver hill_climbing_solver_best(knapsack_instance);
	hill_climbing_solver_best.solve("Best-Improvement");

	// Hill-Climbing First Improvement
	std::cout << "\n------- Hill-Climbing (First) -------" << "\n";
	HillClimbingSolver hill_climbing_solver_first(knapsack_instance);
	hill_climbing_solver_first.solve("First-Improvement");

	// Simulated Annealing
	std::cout << "\n------- Simulated Annealing -------" << "\n";
	int number_of_steps = 200;
	int initial_temperature = 100;
	float temperature_factor = 0.97;
	SimulatedAnnealingSolver simulated_annealing_solver(knapsack_instance, number_of_steps, initial_temperature, temperature_factor);
	simulated_annealing_solver.solve();

	std::cout << "\n------- Tabu Search -------" << "\n";
	int number_of_steps_tabu = 200;
	int tabu_list_length = 5;
	TabuSearchSolver tabu_search_solver(knapsack_instance, number_of_steps_tabu, tabu_list_length);
	simulated_annealing_solver.solve();

	return 0;
}