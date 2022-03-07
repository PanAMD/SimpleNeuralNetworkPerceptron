#include "perceptron.h"


double Perceptron::getSum(Eigen::VectorXd && row)
{
    return row.dot(*weights) >= 0 ? 1 : 0;
}

Perceptron::Perceptron(int sizeX, int sizeY) : inputs(std::make_shared<Eigen::MatrixXd>(sizeX,sizeY)),
    expectedResults(std::make_shared<Eigen::VectorXd>(0)) ,weights(std::make_shared<Eigen::VectorXd>(2)), etha(0),epochs(10), done(false)
{}

Eigen::MatrixXd Perceptron::toMatrix(std::vector<double> & data, int rows)
{
    return Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>>(data.data(), data.size() / rows, rows);
}

std::shared_ptr<Eigen::MatrixXd> Perceptron::getInputs()
{
    return inputs;
}

Eigen::VectorXd Perceptron::getOutputs()
{
    std::cout<<"Hereduru"<<std::endl;
    Eigen::VectorXd outputs(inputs->rows());
    for(int i(0);i<inputs->rows();i++)
    {
        std::cout<<"Row size: "<<inputs->row(i).size()<<std::endl;
        outputs(i)= (inputs->row(i).dot(*weights))>=0 ? 1 : 0;
        std::cout<<"result"<<outputs(i)<<std::endl;
    }
    return outputs;
}

std::shared_ptr<Eigen::VectorXd> Perceptron::getWeights()
{
    return weights;
}

std::shared_ptr<Eigen::VectorXd> Perceptron::getExpectedOutputs() const
{
    return expectedResults;
}

void Perceptron::setWeights(Eigen::Vector3d & newWeights)
{
    //Eigen::VectorXd newVec(newWeights.data(),newWeights.size());
    *weights=Eigen::VectorXd::Map(newWeights.data(),newWeights.size());
}

void Perceptron::setExpectedResults(std::vector<double> && expResults)
{
    //Eigen::VectorXd newVec(expResults.data(),expResults.size());
    Eigen::IOFormat CommaInitFmt(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", ", ", "", "", "", ";");
    Eigen::VectorXd newVec=Eigen::VectorXd::Map(expResults.data(),expResults.size());
    std::cout<<newVec.format(CommaInitFmt)<<std::endl;
    *expectedResults=newVec;
}

void Perceptron::setExpectedResults(Eigen::VectorXd && newResults)
{
    *expectedResults=newResults;
}

void Perceptron::insertResult(double newResult)
{
    Eigen::IOFormat CommaInitFmt(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", ", ", "", "", "", ";");
    uint32_t lastRow(expectedResults->rows()+1);
    expectedResults->conservativeResize(lastRow, Eigen::NoChange);
    (*expectedResults)(lastRow-1)=newResult;
    std::cout<<"Expected results: "<<std::endl<<expectedResults->format(CommaInitFmt)<<std::endl;
}

void Perceptron::setEpochs(double newEpochs)
{
    epochs=newEpochs;
}

void Perceptron::pushInput(std::vector<double> && uwu)
{
    Eigen::IOFormat CleanFmt(4, 0, ", ", "\n", "[", "]");
    uint32_t lastRow(inputs->rows()+1);

    inputs->conservativeResize(lastRow, Eigen::NoChange);

    inputs->row(lastRow-1)=Eigen::Vector3d(uwu.data());

    std::cout << "x1  x2  y"<<std::endl<<inputs->format(CleanFmt) << std::endl;

}

void Perceptron::pushInput(Eigen::VectorXd && uwu)
{
    Eigen::IOFormat CleanFmt(4, 0, ", ", "\n", "[", "]");
    uint32_t lastRow(inputs->rows()+1);

    inputs->conservativeResize(lastRow, Eigen::NoChange);

    inputs->row(lastRow-1)=uwu;

    std::cout << "x1  x2  y"<<std::endl<<inputs->format(CleanFmt) << std::endl;

}

double Perceptron::getEpochs() const
{
    return epochs;
}

double Perceptron::getEtha() const
{
    return etha;
}

bool Perceptron::isDone()
{
    return done;
}

void Perceptron::print()
{
    Eigen::IOFormat CleanFmt(4, 0, ", ", "\n", "[", "]");
    Eigen::MatrixXd result(*inputs);
    result.conservativeResize(result.rows(), result.cols()+1);
    result.col(result.cols()-1) = getOutputs();
    std::cout << "x1  x2  y"<<std::endl<<result.format(CleanFmt) << std::endl;
}

void Perceptron::setInputs(Eigen::MatrixXd && newInputs)
{
    *inputs=newInputs;
}

void Perceptron::setNewWeights(Eigen::VectorXd && newWeights)
{
    Eigen::IOFormat CommaInitFmt(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", ", ", "", "", "", ";");
    std::cout<<"-------"<<"New weights: "<<newWeights.format(CommaInitFmt)<<std::endl;
    *weights=newWeights;
}

void Perceptron::setEtha(double newEtha)
{
    etha=newEtha;
}

void Perceptron::setStatus(bool stat)
{
    done=stat;
}

std::ostream& operator << (std::ostream& os, Perceptron& s)
{
    return os;
}

std::istream& operator >> (std::istream& is, Perceptron& s)
{
    std::string myStr,element;
    std::getline(is,myStr,'\n');
    std::stringstream temporal(myStr);
    std::vector<double> values(std::istream_iterator<double>(temporal),{});
    *s.inputs=s.toMatrix(values,s.inputs->rows());
    return is;
}

