#include <chrono>
#include <iostream>

#include "src/knapsack.hpp"
#include "src/greedy.hpp"
#include "src/hill_climbing.hpp"
#include "src/simulated_annealing.hpp"
#include "src/tabu_search.hpp"
#include "src/genetic.hpp"
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

	std::cout << "\n------- Knapsack Information -------" << "\n";
	std::cout << "Number of Items: " << knapsack_instance.NUMBER_OF_ITEMS << "\tKnapsack Capacity: " << knapsack_instance.MAX_WEIGHT << "\tSeed: " << knapsack_instance.SEED << "\n\n";

	// Greedy	
	std::cout << "------- Greedy -------" << "\n";
	GreedySolver greedy_solver(knapsack_instance);
	auto start = std::chrono::high_resolution_clock::now();	
	greedy_solver.solve();
	auto stop = std::chrono::high_resolution_clock::now();
	std::cout << "[INFO] Time taken: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << " microseconds\n\n";

	// Hill-Climbing Best Improvement
	std::cout << "\n------- Hill-Climbing (Best) -------" << "\n";
	HillClimbingSolver hill_climbing_solver_best(knapsack_instance);
	start = std::chrono::high_resolution_clock::now();	
	hill_climbing_solver_best.solve("Best-Improvement");
	stop = std::chrono::high_resolution_clock::now();
	std::cout << "[INFO] Time taken: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << " microseconds\n\n";

	// Hill-Climbing First Improvement
	std::cout << "\n------- Hill-Climbing (First) -------" << "\n";
	HillClimbingSolver hill_climbing_solver_first(knapsack_instance);
	start = std::chrono::high_resolution_clock::now();	
	hill_climbing_solver_first.solve("First-Improvement");
	stop = std::chrono::high_resolution_clock::now();
	std::cout << "[INFO] Time taken: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << " microseconds\n\n";

	// Simulated Annealing
	std::cout << "\n------- Simulated Annealing -------" << "\n";
	int number_of_steps = 100;
	int initial_temperature = 100;
	float temperature_factor = 0.97;
	SimulatedAnnealingSolver simulated_annealing_solver(knapsack_instance, number_of_steps, initial_temperature, temperature_factor);
	start = std::chrono::high_resolution_clock::now();	
	simulated_annealing_solver.solve();
	stop = std::chrono::high_resolution_clock::now();
	std::cout << "[INFO] Time taken: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << " microseconds\n\n";

	std::cout << "\n------- Tabu Search -------" << "\n";
	int number_of_steps_tabu = 100;
	int tabu_list_length = 5;
	TabuSearchSolver tabu_search_solver(knapsack_instance, number_of_steps_tabu, tabu_list_length);
	start = std::chrono::high_resolution_clock::now();	
	tabu_search_solver.solve();
	stop = std::chrono::high_resolution_clock::now();
	std::cout << "[INFO] Time taken: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << " microseconds\n\n";

	std::cout << "\n------- Genetic Algorithm -------" << "\n";
	int population_size = 20;
	int maximum_generations = 30;
	float crossover_probability = 0.8;
	float mutation_probability = 0.05;
	GeneticSolver genetic_solver(knapsack_instance, population_size, maximum_generations, crossover_probability, mutation_probability);
	start = std::chrono::high_resolution_clock::now();	
	genetic_solver.solve();
	stop = std::chrono::high_resolution_clock::now();
	std::cout << "[INFO] Time taken: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << " microseconds\n\n";

	return 0;
}