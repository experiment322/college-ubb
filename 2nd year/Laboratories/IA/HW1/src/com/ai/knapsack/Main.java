package com.ai.knapsack;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintStream;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class Main {
    private static int n;
    private static int capacity;
    private static int[] costs;
    private static int[] weights;
    private static int[] pickedItems;
    private static double[] costPerUnit;

    private static int totalWeight(List<Integer> items) {
        return items.stream()
                .mapToInt(item -> weights[item])
                .sum();
    }

    private static int totalCost(List<Integer> items) {
        return items.stream()
                .mapToInt(item -> costs[item])
                .sum();
    }

    private static void readInput() {
        Scanner scanner = new Scanner(System.in);
        scanner.useDelimiter("(\\s|,)+");

        n = scanner.nextInt();

        weights = new int[n];
        for (int i = 0; i < n; i++) {
            weights[i] = scanner.nextInt();
        }

        costs = new int[n];
        for (int i = 0; i < n; i++) {
            costs[i] = scanner.nextInt();
        }

        pickedItems = new int[n];

        costPerUnit = new double[n];
        for (int i = 0; i < n; i++) {
            costPerUnit[i] = (double) costs[i] / weights[i];
        }

        capacity = scanner.nextInt();

        scanner.close();
    }

    private static void writeSolution() {
        System.out.println(n);
        System.out.println(
                Arrays.toString(pickedItems)
                        .replaceAll("[\\[ \\]]", ""));
        System.out.println(
                Arrays.toString(
                        IntStream.range(0, n)
                                .map(item -> pickedItems[item] == 1 ? costs[item] : 0)
                                .toArray())
                        .replaceAll("[\\[ \\]]", "")
        );
        System.out.println(
                totalCost(IntStream.range(0, n)
                        .filter(item -> pickedItems[item] == 1)
                        .boxed()
                        .collect(Collectors.toList())));
    }

    private static void solveDFS() {
        int bestCost = -1;
        List<Integer> stack = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            if (weights[i] <= capacity) {
                stack.add(i);
            }

            boolean[][] visited = new boolean[n][n];
            while (stack.size() > 0) {
                int currItem = stack.get(stack.size() - 1);
                int nextItem = currItem + 1;
                while (nextItem < n && visited[currItem][nextItem]) {
                    nextItem++;
                }

                if (nextItem < n) {
                    if (totalWeight(stack) + weights[nextItem] <= capacity) {
                        stack.add(nextItem);
                    }
                    visited[currItem][nextItem] = true;
                } else {
                    if (totalCost(stack) > bestCost) {
                        for (int k = 0; k < n; k++) {
                            pickedItems[k] = stack.contains(k) ? 1 : 0;
                        }
                        bestCost = totalCost(stack);
                    }

                    int item = stack.remove(stack.size() - 1);
                    Arrays.fill(visited[item], false);
                }
            }
        }
    }

    private static void solveGreedy() {
        int[] sortedItems = IntStream.range(0, n)
                .boxed()
                .sorted(Comparator.comparingDouble(item -> -costPerUnit[item]))
                .mapToInt(value -> value)
                .toArray();

        int weight = 0;
        for (int i = 0; i < n; i++) {
            int item = sortedItems[i];

            if (weight + weights[item] <= capacity) {
                pickedItems[item] = 1;
                weight += weights[item];
            }
        }
    }

    private static int[] generateHillClimbingSolution() {
        int weight = 0;
        int[] candidateItems = new int[n];
        for (int i = 0; i < n; i++) {
            if (Math.random() >= 0.5) {
                weight += weights[i];
                candidateItems[i] = 1;
            }
        }

        if (weight > capacity) {
            return new int[n];
        }

        while (weight <= capacity) {
            int bestItem = IntStream.range(0, n)
                    .boxed()
                    .filter(item -> candidateItems[item] == 0)
                    .max(Comparator.comparingDouble(item -> costPerUnit[item]))
                    .orElse(-1);

            if (bestItem == -1) {
                return candidateItems;
            } else if (weight + weights[bestItem] <= capacity) {
                candidateItems[bestItem] = 1;
                weight += weights[bestItem];
            } else {
                break;
            }
        }

        return candidateItems;
    }

    private static void solveHillClimbing() {
        int bestCost = 0;
        int occurrences = 0;
        while (occurrences < 100) {
            int[] candidateItems = generateHillClimbingSolution();
            int cost = totalCost(IntStream.range(0, n)
                    .filter(item -> candidateItems[item] == 1)
                    .boxed()
                    .collect(Collectors.toList()));

            if (cost == bestCost) {
                occurrences += 1;
            } else if (cost > bestCost) {
                occurrences = 0;
                bestCost = cost;
                pickedItems = candidateItems;
            }
        }
    }

    private static int validity(int[] individual) {
        return totalWeight(IntStream.range(0, n)
                .filter(chromosome -> individual[chromosome] == 1)
                .boxed()
                .collect(Collectors.toList()));
    }

    private static int fitness(int[] individual) {
        return totalCost(IntStream.range(0, n)
                .filter(chromosome -> individual[chromosome] == 1)
                .boxed()
                .collect(Collectors.toList()));
    }

    private static int[] mutate(int[] parent, double rate) {
        int[] offspring = new int[n];
        for (int i = 0; i < n; i++) {
            offspring[i] = Math.random() <= rate
                    ? (Math.random() < 0.5 ? 0 : 1)
                    : parent[i];
        }

        return offspring;
    }

    private static void solveEvolutionaryAlgorithm() {
        int[] parent = mutate(null, 1);
        int occurrences = 0;

        int iter = 0;
        while (occurrences < 100) {
            double rate = (100 - occurrences) / (double) 100;

            int[] bestSpawn = null;
            int bestSpawnFitness = 0;
            for (int i = 0; i < 100; i++) {
                int[] spawn = mutate(parent, rate);
                int spawnFitness = fitness(spawn);

                if (validity(spawn) <= capacity && spawnFitness > bestSpawnFitness) {
                    bestSpawn = spawn;
                    bestSpawnFitness = spawnFitness;
                }
            }

            if (bestSpawnFitness == fitness(parent)) {
                occurrences += 1;
            } else if (validity(parent) > capacity || bestSpawnFitness > fitness(parent)) {
                parent = bestSpawn;
                occurrences /= 2;
            }

            iter += 1;
            System.out.printf("%8d %8d\n", iter, bestSpawnFitness);
        }

        pickedItems = parent;
    }

    public static void main(String[] args) throws FileNotFoundException {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Select method (greedy/dfs/hill/evo): ");
        String input = scanner.next();

        System.setIn(new FileInputStream("knapsack.txt"));
        readInput();

        switch (input) {
            case "greedy":
                solveGreedy();
                break;
            case "dfs":
                solveDFS();
                break;
            case "hill":
                solveHillClimbing();
                break;
            case "evo":
                solveEvolutionaryAlgorithm();
                break;
            default:
                System.out.println("Invalid option: " + input);
                return;
        }

        System.setOut(new PrintStream(new FileOutputStream("knapsack_computed.txt")));
        writeSolution();
    }
}
