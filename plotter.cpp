#include "plotter.h"

Plotter::Plotter(std::shared_ptr<QCustomPlot>)
{

}

void Plotter::plot()
{

}

void Plotter::addDot(double x, double y)
{
    dotsData.first.append(x);
    dotsData.second.append(y);
}

void Plotter::replotDot(double, double)
{

}

void Plotter::drawLine()
{

}

std::pair<QVector<double>,QVector<double>> &Plotter::getDotsData()
{
    return dotsData;
}

QVector<std::pair<double, double> > &Plotter::getLineData()
{
    return lineData;
}

std::shared_ptr<QCustomPlot> Plotter::getPlot()
{
    return plotty;
}
