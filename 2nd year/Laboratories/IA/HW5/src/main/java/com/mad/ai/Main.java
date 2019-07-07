package com.mad.ai;

import io.jenetics.Genotype;
import io.jenetics.Mutator;
import io.jenetics.engine.Codec;
import io.jenetics.engine.Engine;
import io.jenetics.engine.EvolutionResult;
import io.jenetics.ext.SingleNodeCrossover;
import io.jenetics.ext.util.Tree;
import io.jenetics.prog.ProgramChromosome;
import io.jenetics.prog.ProgramGene;
import io.jenetics.prog.op.MathOp;
import io.jenetics.prog.op.Op;
import io.jenetics.prog.op.Var;
import io.jenetics.util.ISeq;
import org.neuroph.core.NeuralNetwork;
import org.neuroph.core.data.DataSet;
import org.neuroph.core.data.DataSetRow;
import org.neuroph.nnet.MultiLayerPerceptron;
import org.neuroph.util.data.norm.MaxMinNormalizer;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Date;
import java.util.List;

public class Main {
    private static Integer cols;
    private static Integer rows;
    private static Double[][] data;

    private static void readData() {
        try {
            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
            cols = Integer.parseInt(reader.readLine());
            rows = Integer.parseInt(reader.readLine());
            data = new Double[rows][];
            for (int i = 0; i < rows; i++) {
                String[] strCols = reader.readLine().split(",");
                data[i] = new Double[cols];
                for (int j = 0; j < cols; j++) {
                    data[i][j] = Double.parseDouble(strCols[j]);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    private static void solveANN() {
        DataSet mainDataSet = new DataSet(cols - 1, 1);
        for (Double[] row : data) {
            mainDataSet.addRow(
                    Arrays.stream(row, 0, cols - 1).mapToDouble(Double::doubleValue).toArray(),
                    Arrays.stream(row, cols - 1, cols).mapToDouble(Double::doubleValue).toArray()
            );
        }
        mainDataSet.shuffle();

        MaxMinNormalizer normalizer = new MaxMinNormalizer();
        normalizer.normalize(mainDataSet);

        DataSet[] dataSets = mainDataSet.createTrainingAndTestSubsets(70, 30);
        DataSet testingSet = dataSets[1];
        DataSet trainingSet = dataSets[0];

        NeuralNetwork neuralNetwork = new MultiLayerPerceptron(cols - 1, 16, 1);
        System.out.printf("BEGIN LEARNING %s\n", new Date(System.currentTimeMillis()));
        neuralNetwork.learn(trainingSet);
        System.out.printf("FINISH LEARNING %s\n", new Date(System.currentTimeMillis()));

        double errorSum = 0.0;
        double maxError = Double.NEGATIVE_INFINITY;
        for (DataSetRow testingSetRow : testingSet) {
            neuralNetwork.setInput(testingSetRow.getInput());
            neuralNetwork.calculate();
            double error = Math.abs(neuralNetwork.getOutput()[0] - testingSetRow.getDesiredOutput()[0]);
            maxError = error > maxError ? error : maxError;
            errorSum += error;
        }
        System.out.printf("Error: %f (max), %f (avg)\n", maxError, errorSum / testingSet.size());
    }

    private static double errorGP(final ProgramGene<Double> program) {
        return Arrays.stream(data).mapToDouble(sample -> {
            final Double[] xs = Arrays.copyOfRange(sample, 0, cols - 1);
            final Double y = sample[cols - 1];
            final Double r = program.apply(xs);
            return Math.abs(y - r);
        }).sum();
    }

    private static void solveGP() {
        List<Op<Double>> vars = new ArrayList<>();
        for (int i = 0; i < cols - 1; i++) {
            vars.add(Var.of("x" + i, i));
        }

        final Codec<ProgramGene<Double>, ProgramGene<Double>> codec =
                Codec.of(
                        Genotype.of(ProgramChromosome.of(
                                5, // Program tree depth.
                                ch -> errorGP(ch.getGene()) < 0.5 && ch.getRoot().size() <= 50, // Chromosome validator.
                                ISeq.of(MathOp.ADD, MathOp.SUB, MathOp.MUL, MathOp.SQRT, MathOp.SIN, MathOp.COS), // Program operations.
                                ISeq.of(vars) // Program terminals.
                        )),
                        Genotype::getGene
                );

        final Engine<ProgramGene<Double>, Double> engine = Engine
                .builder(Main::errorGP, codec)
                .minimizing()
                .alterers(
                        new SingleNodeCrossover<>(),
                        new Mutator<>()
                ).build();

        System.out.printf("BEGIN GENERATING %s\n", new Date(System.currentTimeMillis()));
        final ProgramGene<Double> program = engine.stream()
                .limit(1000)
                .collect(EvolutionResult.toBestGenotype())
                .getGene();
        System.out.println(Tree.toString(program));
        System.out.printf("FINISH GENERATING %s\n", new Date(System.currentTimeMillis()));

        Double errorSum = 0.0;
        Double maxError = Double.NEGATIVE_INFINITY;
        for (int i = 0; i < rows; i++) {
            Double error = Math.abs(program.apply(Arrays.copyOf(data[i], cols - 1)) - data[i][cols - 1]);
            maxError = error > maxError ? error : maxError;
            errorSum += error;
        }
        System.out.printf("Error: %f (max), %f (avg)\n", maxError, errorSum / rows);
    }

    public static void main(String[] args) {
        readData();
        solveANN();
        solveGP();
    }
}
