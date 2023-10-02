#include <cmath>
#include <random>
#include <chrono>
#include <iostream>

#include "knapsack.h"
#include "rng.h"
#include "simulated_annealing.h"

SimulatedAnnealingSolver::SimulatedAnnealingSolver() = default;

SimulatedAnnealingSolver::SimulatedAnnealingSolver(KnapsackInstance knapsack_instance, Knapsack knapsack, RNG rng, int number_of_steps, int initial_temperature, float temperature_factor){
    this->knapsack_instance = knapsack_instance;
    this->knapsack = knapsack;
    this->rng = rng;
    this->number_of_steps = number_of_steps;
    this->initial_temperature = initial_temperature;
    this->temperature_factor = temperature_factor;
};

float SimulatedAnnealingSolver::get_random_float(){
    int random_number = rng.get_random_number(100);
    return random_number / 100;
};

State SimulatedAnnealingSolver::get_random_neighbour(){
    State neighbour_state = knapsack.state;
    while(true){
        int random_number = rng.get_random_number(knapsack_instance.NUMBER_OF_ITEMS - 1);
        neighbour_state.state[random_number] = 1 - neighbour_state.state[random_number];
        if(neighbour_state.evaluate_state(knapsack_instance) >= 0){
            return neighbour_state;
        };
    };
};

void SimulatedAnnealingSolver::solve(){
    // Begin with a random solution
    knapsack.generate_random_state(knapsack_instance);
	std::cout << "Generated random knapsack value: " << knapsack.value << " and weight: " << knapsack.weight << "\n";

    float temperature = initial_temperature;
    State current_state = knapsack.state;
    State best_state(knapsack_instance.NUMBER_OF_ITEMS);
    for(int i=0; i<number_of_steps; i++){
        // Pick a random neighour
        State neighbour_state = get_random_neighbour();

        // Check if new solution is better
        if(neighbour_state.evaluate_state(knapsack_instance) > current_state.evaluate_state(knapsack_instance)){
            current_state = neighbour_state;
        }
        else {
            // Calculate probability for changing states
            float random_number = get_random_float();
            float probability = std::exp(-(current_state.evaluate_state(knapsack_instance) - neighbour_state.evaluate_state(knapsack_instance)) / temperature);

            // If probability is higher, we change states
            if(probability > random_number){
                current_state = neighbour_state;
            };
        };
        // Update the temperature
        temperature = temperature * temperature_factor;

        // Save the best state
        if(current_state.evaluate_state(knapsack_instance) > best_state.evaluate_state(knapsack_instance)){
            best_state = current_state;
        };
    };
    std::cout << "Knapsack value: " << best_state.evaluate_state(knapsack_instance) << "\n";
    return;
};