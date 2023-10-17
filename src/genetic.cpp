#include <string>
#include <iostream>
#include <algorithm>

#include "knapsack.hpp"
#include "genetic.hpp"
#include "rng.hpp"

GeneticSolver::GeneticSolver() = default;

GeneticSolver::GeneticSolver(const KnapsackInstance& knapsack_instance, int population_size, int maximum_generations, float crossover_probability, float mutation_probability){
    this->knapsack_instance = knapsack_instance;
    std::vector<State> population(population_size, State(knapsack_instance));
    this->population = population;
    std::vector<float> population_fitness(population_size, 0.0);
    this->population_fitness = population_fitness;
    RNG rng(knapsack_instance.SEED);
    this->rng = rng;
    this->population_size = population_size;
    this->maximum_generations = maximum_generations;
    this->crossover_probability = crossover_probability;
    this->mutation_probability = mutation_probability;

    // Initialization
    for(int i=0; i<population_size; i++){
        this->population[i].generate_random_state(this->rng);
        this->population_fitness[i] = this->population[i].evaluate_state()[0];
    };
};

void GeneticSolver::select(){
    // Find total fitness of the population
    float total_fitness = 0.0;
    for(int i=0; i<population_size; i++){
        total_fitness += population_fitness[i];
    };

    // Calculate relative fitness
    std::vector<float> relative_fitness(population_fitness.size(), 0.0);
    for(int i=0; i<population_size; i++){
        relative_fitness[i] = population_fitness[i] / total_fitness;
    };

    // Calculate cumulative fitness
    std::vector<float> cumulative_fitness(population_fitness.size(), 0.0);
    cumulative_fitness[0] = relative_fitness[0];
    for(int i=1; i<population_size; i++){
        cumulative_fitness[i] = cumulative_fitness[i-1] + relative_fitness[i];
    };

    // Select survivors using cumulative fitness
    float probability;
    std::vector<State> new_population;
    new_population = population;
    for(int i=0; i<population_size; i++){
        probability = rng.get_random_probability();
        if(probability < cumulative_fitness[0]){
            new_population[i] = population[0];
        }
        else{
            for(int j=0; j<population_size; j++){
                if((probability >= cumulative_fitness[j]) && (probability < cumulative_fitness[j+1])){
                    new_population[i] = new_population[j+1];
                };
            };
        };
    };
    // Once a new population is created, we save it
    population = new_population;  
};

void GeneticSolver::crossover(){
    int first=0;
    int split_point;
    float probability;
    int father_index;
    for(int i=0; i<population_size; ++i){
        probability = rng.get_random_probability();
        if(probability < crossover_probability){
            ++first;
            if(first % 2 == 0){
                // Select crossover point
                split_point = rng.get_random_number(knapsack_instance.NUMBER_OF_ITEMS - 1);
                
                // Perform crossover
                std::swap_ranges(population[father_index].state.begin()+split_point, population[father_index].state.end(), population[i].state.begin()+split_point);
            }
            else{
                father_index = i;
            };
        };
    };
};

void GeneticSolver::mutate(){
    float probability;
    for(int i=0; i<population_size; i++){
        for(int j=0; j<knapsack_instance.NUMBER_OF_ITEMS; j++){
            probability = rng.get_random_probability();
            if(probability < mutation_probability){
                population[i].state[j] = 1 - population[i].state[j];
            };
        };
    };
};

void GeneticSolver::evaluate(){
    float evaluation;
    float weight;
    for(int i=0; i<population_size; i++){
        evaluation = 0;
        weight = 0;
        // Calculate capacity and value of the current state knapsack
	    for(long unsigned j=0; j<population[i].state.size(); j++){
		    // Check if the item is currently in the knapsack
		    if (population[i].state[j] == 1){
			    // If it is, we consider its value and weight
			    evaluation = evaluation + knapsack_instance.items[j].value;
			    weight = weight + knapsack_instance.items[j].weight;
		    };
	    };
        if(weight > knapsack_instance.MAX_WEIGHT){
            population_fitness[i] = evaluation - ((295 / 270) * (weight - knapsack_instance.MAX_WEIGHT));
        }
        else{
            population_fitness[i] = evaluation;
        };
    };
};

void GeneticSolver::report(int generation){
    std::cout << "----- Report for generation " << generation << " -----\n";
    for(int i=0; i<population_size; i++){
        std::cout << population[i] << " --> " << population_fitness[i] << "\n";
    };
    std::cout << "\n";
};

void GeneticSolver::save_best(){
    // Find index of the highest value in the population_fitness array
    auto it = std::max_element(population_fitness.begin(), population_fitness.end());
    int index = std::distance(population_fitness.begin(), it);
    best_state = population[index];
};

void GeneticSolver::elitist(){
    population[0] = best_state;
};

void GeneticSolver::solve(){
    int generation = 0;
    report(generation);
    while(generation < maximum_generations){
        generation++;
        select();
        crossover();
        mutate();
        evaluate();
        report(generation);
    };
};