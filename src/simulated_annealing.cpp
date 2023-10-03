#include <cmath>
#include <random>
#include <chrono>
#include <iostream>

#include "knapsack.hpp"
#include "rng.hpp"
#include "simulated_annealing.hpp"

SimulatedAnnealingSolver::SimulatedAnnealingSolver(KnapsackInstance knapsack_instance, int number_of_steps, int initial_temperature, float temperature_factor){
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
	//std::cout << "Generated random knapsack value: " << knapsack.value << " and weight: " << knapsack.weight << "\n";

    float temperature = initial_temperature;
    State current_state = state;
    State best_state(knapsack_instance);
    for(int i=0; i<number_of_steps; i++){
        // Pick a random neighour
        State neighbour_state = current_state.generate_random_neighbour(rng);

        // Check if new solution is better
        if(neighbour_state.evaluate_state() > current_state.evaluate_state()){
            current_state = neighbour_state;
        }
        else {
            // Calculate probability for changing states
            float random_number = rng.get_random_probability();
            float probability = std::exp(-(current_state.evaluate_state() - neighbour_state.evaluate_state()) / temperature);

            // If probability is higher, we change states
            if(probability > random_number){
                current_state = neighbour_state;
            };
        };
        // Update the temperature
        temperature = temperature * temperature_factor;

        // Save the best state
        if(current_state.evaluate_state() > best_state.evaluate_state()){
            best_state = current_state;
        };
    };
    std::cout << "Knapsack value: " << best_state.evaluate_state() << "\n";
    return;
};