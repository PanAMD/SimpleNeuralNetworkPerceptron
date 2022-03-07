#ifndef PLOTTER_H
#define PLOTTER_H

#include "qcustomplot.h"

class Plotter
{
public:
    Plotter(std::shared_ptr<QCustomPlot> input);

    void plot();
    void addDot(double,double);
    void replotDot(double,double);
    void drawLine();

    std::pair<QVector<double>,QVector<double>> & getDotsData();
    QVector<std::pair<double,double>> & getLineData();

    std::shared_ptr<QCustomPlot> getPlot();
private:
    std::shared_ptr<QCustomPlot> plotty;

    std::pair<QVector<double>,QVector<double>> dotsData;
    QVector<std::pair<double,double>> lineData;

};

#endif // PLOTTER_H
