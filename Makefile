all: knapsack

knapsack: main.o knapsack.o greedy.o hill_climbing.o simulated_annealing.o rng.o tabu_search.o
	g++ -o knapsack build/main.o build/knapsack.o build/greedy.o build/hill_climbing.o build/simulated_annealing.o build/tabu_search.o build/rng.o 

main.o: main.cpp
	g++ -c main.cpp -o ./build/main.o

knapsack.o: src/knapsack.cpp
	g++ -c src/knapsack.cpp -o ./build/knapsack.o

greedy.o: src/greedy.cpp
	g++ -c src/greedy.cpp -o ./build/greedy.o

hill_climbing.o: src/hill_climbing.cpp
	g++ -c src/hill_climbing.cpp -o ./build/hill_climbing.o

simulated_annealing.o: src/simulated_annealing.cpp
	g++ -c src/simulated_annealing.cpp -o ./build/simulated_annealing.o

tabu_search.o: src/tabu_search.cpp
	g++ -c src/tabu_search.cpp -o ./build/tabu_search.o

rng.o: src/rng.cpp
	g++ -c src/rng.cpp -o ./build/rng.o

clean:
	rm ./build/*.o knapsack