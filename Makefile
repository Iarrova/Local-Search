all: knapsack

knapsack: main.o knapsack.o greedy.o hill_climbing.o simulated_annealing.o rng.o tabu_search.o
	g++ -o knapsack main.o knapsack.o greedy.o hill_climbing.o simulated_annealing.o tabu_search.o rng.o 

main.o: main.cpp
	g++ -c main.cpp

knapsack.o: knapsack.cpp
	g++ -c knapsack.cpp

greedy.o: greedy.cpp
	g++ -c greedy.cpp

hill_climbing.o: hill_climbing.cpp
	g++ -c hill_climbing.cpp

simulated_annealing.o: simulated_annealing.cpp
	g++ -c simulated_annealing.cpp

tabu_search.o: tabu_search.cpp
	g++ -c tabu_search.cpp

rng.o: rng.cpp
	g++ -c rng.cpp

clean:
	rm *.o knapsack