#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>
#include "mainwindow.h"
#include "perceptron.h"


class MainWindow;

using output = std::bitset<32>;

class NeuralNetwork
{
private:
    std::map<int,std::shared_ptr<Perceptron>> neurons;
    std::unordered_map<output,int> possibleOutputs;
    Eigen::MatrixXd inputs;
    std::unordered_map<int,Eigen::VectorXd> expectedOutputs;
    bool isError;
    bool trained;
    int neuronCounter;
    int epochs;
    std::queue<int> freeIds;
public:
    MainWindow *parent;
    NeuralNetwork(MainWindow *parent);
    NeuralNetwork(MainWindow *parent,int,int);

    void addPerceptron(Perceptron&);
    void addGenericPerceptron();

    void removePerceptron(int);

    void train();
    void updatePerceptrons(Eigen::VectorXd &&, double error);

    bool isTrained();

    friend std::ostream& operator << (std::ostream&, NeuralNetwork&);
    friend std::istream& operator >> (std::istream&, NeuralNetwork&);
};

#endif // NEURALNETWORK_H
