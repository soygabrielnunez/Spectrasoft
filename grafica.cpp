#include "grafica.h"

Grafica::Grafica(QCustomPlot *graficaExt, QMainWindow *padreExt, QString tituloExt, QString etqX, QString etqY)
{
    grafica = graficaExt;
    padre = padreExt;
    n = 0;

    QCPPlotTitle *titulo = new QCPPlotTitle(grafica);
    titulo->setText(tituloExt);
    titulo->setFont(QFont("sans", 12, QFont::Bold));

    QVector<double> ticks;
    int j = 400;

    for(int i = 0; i < 31; ++i){
        ticks.push_back(double(j));
        x.push_back(j);
        j+=10;
    }

    grafica->plotLayout()->insertRow(0);
    grafica->plotLayout()->addElement(0, 0, titulo);
    grafica->xAxis->setRange(400, 700);
    grafica->xAxis->setLabel(etqX);
    grafica->yAxis->setLabel(etqY);
    grafica->xAxis->setAutoTicks(false);
    grafica->xAxis->setTickVector(ticks);
    grafica->xAxis->setTickLabelPadding(5);
    grafica->xAxis->setTickLabelRotation(-45);
    grafica->setInteraction(QCP::iRangeDrag, true);
    grafica->setInteraction(QCP::iRangeZoom, true);
}

void Grafica::agregarCurva(QVector<double> y)
{
    QCPScatterStyle myScatter;
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(1);

    myScatter.setShape(QCPScatterStyle::ssDisc);
    myScatter.setPen(pen);
    myScatter.setSize(5);
    grafica->addGraph();
    grafica->graph(n)->setData(x, y);
    grafica->graph(n)->setScatterStyle(myScatter);
    grafica->graph(n)->setPen(QPen(Qt::black));
    grafica->yAxis->setRange(0, 100);
    grafica->replot();

    n++;
}

bool Grafica::numCurvas()
{
    return n;
}

void Grafica::quitarCurva()
{
    grafica->removeGraph(n - 1);
    n--;
}

void Grafica::ajustarGrafica(QString axis, const QCPRange &newRange, double lower, double upper)
{
    QCPRange boundedRange = newRange;

    double lowerRangeBound = lower;
    double upperRangeBound = upper;

    if(boundedRange.size() > upperRangeBound - lowerRangeBound){
        boundedRange = QCPRange(lowerRangeBound, upperRangeBound);
    }else{
        double oldSize = boundedRange.size();

        if(boundedRange.lower < lowerRangeBound){
            boundedRange.lower = lowerRangeBound;
            boundedRange.upper = lowerRangeBound + oldSize;
        }

        if(boundedRange.upper > upperRangeBound){
            boundedRange.lower = upperRangeBound - oldSize;
            boundedRange.upper = upperRangeBound;
        }
    }

    if(axis == "x"){
        grafica->xAxis->setRange(boundedRange);
    }else{
        grafica->yAxis->setRange(boundedRange);
    }
}

Grafica::~Grafica()
{

}

