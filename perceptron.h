#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>
#include <iostream>
#include <cstdio>
#include <functional>
#include "qcustomplot.h"
#include "Eigen"
#include "Core"

class Perceptron
{
private:
    std::shared_ptr<Eigen::MatrixXd> inputs;
    std::shared_ptr<Eigen::VectorXd> expectedResults;
    std::shared_ptr<Eigen::VectorXd> weights;

    double etha;
    double epochs;
    bool done;

public:
    Perceptron(int sizeX, int sizeY);
    Eigen::MatrixXd toMatrix(std::vector<double>&,int);
    std::shared_ptr<Eigen::MatrixXd> getInputs();
    Eigen::VectorXd getOutputs();
    std::shared_ptr<Eigen::VectorXd> getWeights();
    std::shared_ptr<Eigen::VectorXd> getExpectedOutputs() const;
    void setWeights(Eigen::Vector3d &);
    void setExpectedResults(std::vector<double>&&);
    void setExpectedResults(Eigen::VectorXd&&);
    void insertResult(double);
    void setEpochs(double);
    void pushInput(std::vector<double>&&);
    void pushInput(Eigen::VectorXd&&);
    void print();

    void setInputs(Eigen::MatrixXd&&);
    void setNewWeights(Eigen::VectorXd&&);


    void setEtha(double);
    void setStatus(bool);

    double getEpochs() const;
    double getEtha() const;

    double getSum(Eigen::VectorXd &&);

    bool isDone();

    friend std::ostream& operator << (std::ostream&, Perceptron&);
    friend std::istream& operator >> (std::istream&, Perceptron&);
};

#endif // PERCEPTRON_H
