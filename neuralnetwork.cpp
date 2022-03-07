#include "neuralnetwork.h"

NeuralNetwork::NeuralNetwork(MainWindow *parent) : inputs(0,3), isError(false), trained(false), neuronCounter(0), epochs(0)
{
    this->parent = parent;
}

NeuralNetwork::NeuralNetwork(MainWindow *parent, int rows, int columns) : inputs(rows,columns) , isError(false), trained(false), neuronCounter(0), epochs(0)
{
    this->parent = parent;
}

void NeuralNetwork::addPerceptron(Perceptron & newNeuron)
{
    if(!freeIds.empty())
    {
        neurons.insert(std::make_pair(freeIds.front(),new Perceptron(newNeuron)));
        freeIds.pop();
    }
    else
    {
        neurons.insert(std::make_pair(neuronCounter,new Perceptron(newNeuron)));
    }
    neuronCounter++;
}

void NeuralNetwork::addGenericPerceptron()
{
    if(!freeIds.empty())
    {
        neurons.emplace(std::make_pair(freeIds.front(),Perceptron(0,3)));
        freeIds.pop();
    }
    else
    {
        neurons.emplace(std::make_pair(freeIds.front(),Perceptron(0,3)));
    }
    neuronCounter++;
}

void NeuralNetwork::removePerceptron(int key)
{
    if(neurons.find(key)!=neurons.end())
    {
        neurons.erase(key);
        freeIds.push(key);
        neuronCounter--;
    }
}

void NeuralNetwork::train()
{
    Eigen::IOFormat CommaInitFmt(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", ", ", "", "", "", ";");
    Eigen::IOFormat CleanFmt(4, 0, ", ", "\n", "[", "]");
        while(epochs>0 || (isError==true))
        {
            for(int i(0);i<neuronCounter;i++)
            {
                auto currNeuron = neurons.find(i)->second;
                for(int i(0);i<inputs.rows();i++)
                {
                    double funcResult(currNeuron->getSum(inputs.row(i)));
                    double error ((*currNeuron->getExpectedOutputs())(i)-(funcResult));
                    std::cout<<"unu"<<std::endl;
                    if(error!=0)
                    {
                        isError=true;
                        updatePerceptrons(inputs.row(i),error);
                        parent->delay(5);
                        parent->printPerceptron(*currNeuron);
                    }
                }
            }
            if(!isError)
            {
                break;
            }
            epochs--;
        }
}

void NeuralNetwork::updatePerceptrons(Eigen::VectorXd && row, double error)
{
    Eigen::IOFormat CommaInitFmt(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", ", ", "", "", "", ";");
    Eigen::IOFormat CleanFmt(4, 0, ", ", "\n", "[", "]");
    for(int i(0);i<neuronCounter;i++)
    {
        auto currNeuron = neurons.find(i)->second;
        auto currWeights = currNeuron->getWeights();
        currNeuron->setNewWeights(*currWeights+((currNeuron->getEtha()*error)*row).transpose());
        std::cout<<"Fitting new weights: "<<std::endl<< currNeuron->getWeights()->format(CommaInitFmt)<<std::endl;
    }
}

bool NeuralNetwork::isTrained()
{
    return trained;
}
