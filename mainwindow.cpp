#include "mainwindow.h"
#include "ui_mainwindow.h"

constexpr int DOTS_PLOT = 0;
constexpr int DOTS_NEG_PLOT = 1;
constexpr int LINES_PLOT = 2;

void MainWindow::delay(int millisecondsWait)
{
    QEventLoop loop;
    QTimer t;
    t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
    t.start(millisecondsWait);
    loop.exec();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , perceptron(0,3), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Q_INIT_RESOURCE(Resources);

    setWindowIcon(QIcon(":/Images/assets/images/icon.png"));

    backImg= std::make_shared<QMovie>(this);
    backImg->setFileName(":/Images/assets/images/background2.gif");
    backImg->setScaledSize(QSize(681,450));
    ui->background->setMovie(backImg.get());
    backImg->start();

    kirbo= std::make_shared<QMovie>(this);
    kirbo->setFileName(":/Images/assets/images/kirbo.gif");
    kirbo->setScaledSize(QSize(131,121));
    ui->kirbo->setMovie(kirbo.get());
    kirbo->start();

    yuri= std::make_shared<QMovie>(this);
    yuri->setFileName(":/Images/assets/images/Sayori.gif");
    yuri->setScaledSize(QSize(140,290));
    ui->yuri->setMovie(yuri.get());
    yuri->setCacheMode(QMovie::CacheAll);
    yuri->jumpToFrame(22);
    connect(ui->plotField,SIGNAL(mousePress(QMouseEvent*)),SLOT(onGraphClicked(QMouseEvent *)));
    initializeCharts();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::printPerceptron(Perceptron & percept)
{
    QVector<double> positiveXs;
    QVector<double> positiveYs;

    QVector<double> negativeXs;
    QVector<double> negativeYs;

    QVector<double> lineXs;
    QVector<double> lineYs;

    auto outputs = percept.getOutputs();
    for(int i(0);i<percept.getInputs()->rows();i++)
    {
        if(outputs.coeff(i)>0)
        {
            std::cout<<"positive"<<std::endl;
            positiveXs.push_back(percept.getInputs()->row(i).coeff(0,1));
            positiveYs.push_back(percept.getInputs()->row(i).coeff(0,2));
        }
        else
        {
            std::cout<<"negative"<<std::endl;
            negativeXs.push_back(percept.getInputs()->row(i).coeff(0,1));
            negativeYs.push_back(percept.getInputs()->row(i).coeff(0,2));
        }

    }

    int i=5;
    double A=(percept.getWeights()->coeff(1)*-1)/(percept.getWeights()->coeff(2));
    double b=(percept.getWeights()->coeff(0))/(percept.getWeights()->coeff(2));
    while(i!=-5)
    {
        lineXs.push_back(i);
        double result(A*i+b);
        std::cout<<"COORDs "<<"x: "<<i<<" y: "<<result<<std::endl;
        lineYs.push_back(result);
        i--;
    }
    //perceptron.print();
    ui->plotField->graph(DOTS_PLOT)->setData(positiveXs, positiveYs);
    ui->plotField->replot();

    ui->plotField->graph(DOTS_NEG_PLOT)->setData(negativeXs, negativeYs);
    ui->plotField->replot();

    ui->plotField->graph(LINES_PLOT)->setData(lineXs, lineYs);
    ui->plotField->replot();
}

void MainWindow::replot()
{
    ui->plotField->replot();
    ui->plotField->update();
}

void MainWindow::openFile()
{
    QString fileName;
    fileName=QFileDialog::getOpenFileName(this,"Commodore 64 FILE HANDLER","","Text files(*.txt)");
    //std::cout<<"IESSSS"<<fileName.toStdString();
    Eigen::IOFormat CommaInitFmt(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", ", ", "", "", "", ";");
    if(fileName.length()>0)
    {
        std::cout<<"IESSSS"<<fileName.toStdString();

        int trainingPatterns(0);
        std::string inputSrc;
        std::ifstream inputSource(fileName.toStdString(),std::ios::in|std::ios::beg);
        std::cout<<"IESSSS"<<fileName.toStdString();

        if(inputSource.is_open())
        {
            std::cout<<"IESSSS"<<fileName.toStdString();
        }
        std::getline(inputSource,inputSrc);
        std::cout<<inputSrc<<std::endl;
        std::getline(inputSource,inputSrc,'\n');
        trainingPatterns=std::stoi(inputSrc);
        std::cout<<std::endl<<trainingPatterns;
        for(int i(0);i<trainingPatterns;i++)
        {
            std::getline(inputSource,inputSrc,'\n');
            std::stringstream temporal(inputSrc);
            perceptron.pushInput(std::vector<double>(std::istream_iterator<double>(temporal),{}));
        }
        std::getline(inputSource,inputSrc,'\n');
        std::stringstream temporal(inputSrc);
        perceptron.setExpectedResults(std::vector<double>(std::istream_iterator<double>(temporal),{}));
    }
}

void MainWindow::trainNetwork()
{
    network.train();
    if(!network.isTrained())
    {
        QMessageBox msgAux;
        msgAux.setText("ERROR");
        msgAux.setIcon(QMessageBox::Critical);
        msgAux.setWindowIcon(QIcon(":/Icons/assets/icons/alert.ico"));
        msgAux.setInformativeText("The problem couldn't be resolved, we ran out of epochs :C");
        msgAux.setDefaultButton(QMessageBox::Ok);
        msgAux.exec();
    }
}

void MainWindow::printPerceptDots()
{
    QVector<double> positiveXs;
    QVector<double> positiveYs;

    QVector<double> negativeXs;
    QVector<double> negativeYs;

    QVector<double> lineXs;
    QVector<double> lineYs;

    auto outputs = perceptron.getExpectedOutputs();
    for(int i(0);i<perceptron.getInputs()->rows();i++)
    {
        if(outputs->coeff(i)>0)
        {
            std::cout<<"positive"<<std::endl;
            positiveXs.push_back(perceptron.getInputs()->row(i).coeff(0,1));
            positiveYs.push_back(perceptron.getInputs()->row(i).coeff(0,2));
        }
        else
        {
            std::cout<<"negative"<<std::endl;
            negativeXs.push_back(perceptron.getInputs()->row(i).coeff(0,1));
            negativeYs.push_back(perceptron.getInputs()->row(i).coeff(0,2));
        }

    }
    ui->plotField->graph(DOTS_PLOT)->setData(positiveXs, positiveYs);
    ui->plotField->replot();

    ui->plotField->graph(DOTS_NEG_PLOT)->setData(negativeXs, negativeYs);
    ui->plotField->replot();
}

void MainWindow::initializeCharts()
{
    ui->plotField->addGraph();
    ui->plotField->graph(DOTS_PLOT)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plotField->graph(DOTS_PLOT)->setLineStyle(QCPGraph::lsNone);
    ui->plotField->xAxis->setLabel("x1");
    ui->plotField->yAxis->setLabel("x2");
    ui->plotField->xAxis->setRange(-5, 5);
    ui->plotField->yAxis->setRange(-5, 5);

    ui->plotField->addGraph();
    ui->plotField->graph(DOTS_NEG_PLOT)->setScatterStyle(QCPScatterStyle::ssCross);
    ui->plotField->graph(DOTS_NEG_PLOT)->setLineStyle(QCPGraph::lsNone);

    ui->plotField->addGraph();

    ui->plotField->replot();
}

/*
void MainWindow::onGraphClicked(QMouseEvent * event)
{
    int resultType(ui->insertTypeCB->currentIndex() == 0 ? 0 : 1  );
    QPoint mousePos(event->pos());
    double x(ui->plotField->xAxis->pixelToCoord(mousePos.x()));
    double y(ui->plotField->yAxis->pixelToCoord(mousePos.y()));
    perceptron.pushInput(std::vector<double>{-1,x,y});
    perceptron.insertResult(resultType);
    if(resultType)
    {
        dotsData.first.append(x);
        dotsData.second.append(y);
        ui->plotField->graph(DOTS_PLOT)->setData(dotsData.first,dotsData.second);
    }
    else
    {
        dotsDataNeg.first.append(x);
        dotsDataNeg.second.append(y);
        ui->plotField->graph(DOTS_NEG_PLOT)->setData(dotsDataNeg.first,dotsDataNeg.second);

    }
    replot();
    std::cout<<"CURRENT POSS: "<<"x: "<<x<<" y: "<<y<<std::endl;

}
*/
void MainWindow::on_generatePB_clicked()
{
    openFile();
    std::default_random_engine gen(time(0));
    std::uniform_int_distribution<> dis(5,10);
    auto uni = [&](){ return dis(gen); };
    std::cout<<"UNU"<<std::endl;
    Eigen::Vector3d testVec = Eigen::Vector3d::NullaryExpr(uni);
    std::cout<<"UNU2"<<std::endl;
    perceptron.setEtha(ui->ethaLE->text().toDouble());
    perceptron.setEpochs(ui->epochsLE->text().toDouble());
    std::cout<<"UNU3"<<std::endl;

    perceptron.setWeights(testVec);
    std::cout<<"UNU4"<<std::endl;

    //printPerceptron(perceptron,*ui->plotField);
    printPerceptDots();
    yuri->start();
    delay(1000);
    yuri->stop();
}


void MainWindow::on_resetPB_clicked()
{
    dotsData.first.clear();
    dotsData.second.clear();

    dotsDataNeg.second.clear();
    dotsDataNeg.first.clear();

    Eigen::MatrixXd cleanMatrix(0,3);
    perceptron.setInputs(Eigen::MatrixXd(0,3));
    perceptron.setExpectedResults(Eigen::VectorXd());
    perceptron.print();
    for(int i(0);i<ui->plotField->graphCount();i++)
    {
        ui->plotField->graph(i)->data().data()->clear();
    }
    ui->plotField->replot();
    perceptron.setStatus(false);
}



void MainWindow::on_runPB_clicked()
{
    yuri->start();
    delay(1000);
    yuri->stop();
    trainPerceptron(perceptron);
}

