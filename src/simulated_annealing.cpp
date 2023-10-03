#include <cmath>
#include <random>
#include <chrono>
#include <iostream>

#include "knapsack.hpp"
#include "rng.hpp"
#include "simulated_annealing.hpp"

SimulatedAnnealingSolver::SimulatedAnnealingSolver(const KnapsackInstance& knapsack_instance, int number_of_steps, int initial_temperature, float temperature_factor){
    this->knapsack_instance = knapsack_instance;
    State state(knapsack_instance);
	this->state = state;
    RNG rng(knapsack_instance.SEED);
    this->rng = rng;
    this->number_of_steps = number_of_steps;
    this->initial_temperature = initial_temperature;
    this->temperature_factor = temperature_factor;
};

void SimulatedAnnealingSolver::solve(){
    // Begin with a random solution
    state.generate_random_state(rng);
	//std::cout << "[INFO] Generated random state: " << state << "\n"; 
	//std::cout << "[INFO] Initial state value: " << state.evaluate_state()[0] << " and weight: " << state.evaluate_state()[1] << "\n\n";

    float temperature = initial_temperature;
    State current_state = state;
    State best_state(knapsack_instance);
    for(int i=0; i<number_of_steps; i++){
        // Pick a random neighour
        State neighbour_state = current_state.generate_random_neighbour(rng);
        //std::cout << "[INFO] Generated neighbour: " << neighbour_state << "\n";
        //std::cout << "[INFO] Neighbour value: " << neighbour_state.evaluate_state()[0] << " and weight: " << neighbour_state.evaluate_state()[1] << "\n";

        // Check if new solution is better
        if(neighbour_state.evaluate_state() > current_state.evaluate_state()){
            current_state = neighbour_state;
            //std::cout << "[INFO] Better solution. Switched to new neighbour" << "\n\n";
        }
        else {
            // Calculate probability for changing states
            float random_number = rng.get_random_probability();
            float probability = std::exp(-(current_state.evaluate_state()[0] - neighbour_state.evaluate_state()[0]) / temperature);

            // If probability is higher, we change states
            if(probability > random_number){
                //std::cout << "[INFO] Probability: " << probability << " random number: " << random_number << "\n"; 
                //std::cout << "[INFO] Switched to worse solution." << "\n\n";
                current_state = neighbour_state;
            }
            //else{
                //std::cout << "\n";
            //};
        };
        // Update the temperature
        temperature = temperature * temperature_factor;

        // Save the best state
        if(current_state.evaluate_state() > best_state.evaluate_state()){
            best_state = current_state;
        };
    };
    std::cout << "[RESULT] Final value: " << best_state.evaluate_state()[0] << " final weight: " << best_state.evaluate_state()[1] << "\n";
	std::cout << "[RESULT] Final state: " << best_state << "\n";
    return;
};