#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <istream>
#include <fstream>
#include <iostream>
#include "neuralnetwork.h"
#include "qcustomplot.h"
#include "perceptron.h"
#include "plotter.h"

class NeuralNetwork;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initializeCharts();
    void delay(int millisecondsWait);
    void printPerceptron(Perceptron &);


private slots:

    //void onGraphClicked(QMouseEvent *);

    void on_generatePB_clicked();

    void on_resetPB_clicked();

    void on_runPB_clicked();

private:
    NeuralNetwork network;
    Ui::MainWindow *ui;
    std::shared_ptr<QMovie> backImg;
    std::shared_ptr<QMovie> kirbo;
    std::shared_ptr<QMovie> yuri;

    std::pair<QVector<double>,QVector<double>> dotsData;
    std::pair<QVector<double>,QVector<double>> dotsDataNeg;
    void openFile();
    void replot();
    void trainNetwork();
    void printPerceptDots();

};
#endif // MAINWINDOW_H
