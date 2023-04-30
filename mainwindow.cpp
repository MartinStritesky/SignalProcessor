#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "spline.h"


/*!
 * \brief A class MainWindow. ff
 * \param parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);  //!<  User interface initialization.
    plotData(scale, mtp, fcn); //!<  Plotting the data with default settings.
}

/*!
 * \brief plotData function calculated and plots all original, sampled and interpolated signal points.
 * \param scale a number of available points on the x and y axis.
 * \param mtp a signal frequency multiplicator.
 * \param fcn an integer argument representing one of the predefined functions.
 */
void MainWindow::plotData(double scale, int mtp, int fcn)
{
    QVector<double> x(scale), y(scale); //  Declaration of list of x and y values.
    int j = 0; //  A iterative number to iterate over list of sampled values.
    int pocetSample = std::ceil(scale / sampling); //   Definition of sample count.
    QVector<double> sampledX(pocetSample), sampledY(pocetSample); //   Declaration of list of sampled values.
    QVector<double> interpX(scale), interpY(scale); //  Declaration of list of interpolated values.

    // Calculation of frequency.
    if (fcn == 1)
        fqcy =  mtp * (1/(2*3.142));
    else if (fcn == 2)
        fqcy =  mtp * ((0.05*2*3.14*4)/(2*3.142));
    else if (fcn == 3)
        fqcy =  mtp * (1/(2*3.142));

    // Calculating the incoming signal values.
    for (int i=0; i<scale; ++i)
    {
        x[i] = 0;
        y[i] =0;

        x[i] =  (i/(scale/2)-1); // x goes from -1 to 1
        switch (fcn){
            case 1:
                y[i] = sin(mtp * x[i]); //  Sine function.
                break;
            case 2:
                y[i] = exp(-((x[i]*x[i])*5))*sin(mtp* 0.05 * 2*3.14*4*x[i]); // Wavelet function.
                break;
            case 3:
                y[i] = sin(2*3.14*x[i]/(30.0/mtp))+0.3*sin(6*3.14*x[i]/(30.0/mtp)) + 0.15*sin(10*3.14*x[i]/(30.0/mtp)); // Square wave function.
                break;

        }

        // Getting all values spaced by sampling value.
        if(i % sampling == 0){

            sampledX[j] =  x[i];
            sampledY[j] = y[i];
            j++;
            }
    }

    double level[quant_levels];//  A actual list of quantization levels available to be matched as closets to the actual sample value.
    if(quantize){
            for(int i = 0; i <= ((quant_levels-1)); i++){
            level[i] = -1.0 + i * (2.0/(quant_levels-1)) ;
            }

            for(int j = 0; j <= ((quant_levels-1)); j++){
                for (int i=0; i<pocetSample; ++i){
                if(std::abs(sampledY[i] - level[j]) < ((2.0/(quant_levels-1))/2)){ // Decision making if we are on closest quantization level or not.
                                sampledY[i]  = level[j];
                            }
                }
            }
    }


    std::vector <double> X(sampledX.size()); // Vector for storing sampledX list values.
    std::vector <double> Y(sampledX.size()); // Vector for storing sampledY list values.

    copy(sampledX.begin(), sampledX.end(), X.begin()); // Copy all values from list sampledX to vector X.
    copy(sampledY.begin(), sampledY.end(), Y.begin()); // Copy all values from list sampledY to vector Y.

    tk::spline s2; // Definition of spline object.
    s2.set_points(X,Y, tk::spline::cspline); // Setting X and Y values to C2 spline.

    // Assigning interpolatied values from vector variable to list variable for plotting.
    for (int i = 0; i < scale; i++){
            interpX[i] = x[i];
            interpY[i] = s2(x[i]);
    }

    ui->lblSampling->setText(QString::number((scale / sampling)/2, 'f' ,1)); // Updating label of sampling frequency.
    ui->lblFrequency->setText(QString::number(fqcy, 'f', 1)); // Updating label of initial signal frequency.
    ui->lblfreqRatio->setText(QString::number((0.5*scale/sampling)/fqcy, 'f', 1)); // Updating label of frequency ratios.

    // Create graph of original signal
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);
    ui->customPlot->graph(0)->setPen(QPen(QColor(122, 142, 252)));
    // Give the axes some labels
    ui->customPlot->xAxis->setLabel("time (s)");
    ui->customPlot->yAxis->setLabel("f(x)");

    // Create scatterplot of sampled data
    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setData(sampledX, sampledY);
    ui->customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::red, Qt::white, 7));

    // Adjusting range and making the graph interactive.
    ui->customPlot->yAxis->setRangeLower(lowRange);
    ui->customPlot->yAxis->setRangeUpper(highRange);
    ui->customPlot->xAxis->setRangeLower(-1);
    ui->customPlot->xAxis->setRangeUpper(1);
    ui->customPlot->replot();
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    // Create second plot and displaying scatterplot of sampled data.
    ui->customPlot2->xAxis->setLabel("time (s)");
    ui->customPlot2->yAxis->setLabel("f(x)");
    ui->customPlot2->addGraph();
    ui->customPlot2->graph(0)->setData(sampledX, sampledY);
    ui->customPlot2->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot2->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::red, Qt::white, 7));
    ui->customPlot2->yAxis->setRangeLower(lowRange);
    ui->customPlot2->yAxis->setRangeUpper(highRange);
    ui->customPlot2->xAxis->setRangeLower(-1);
    ui->customPlot2->xAxis->setRangeUpper(1);
    ui->customPlot2->replot();
    ui->customPlot2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    // Creating new graph with interpolated spline.
   ui->customPlot2->addGraph();
   ui->customPlot2->graph(1)->setData(interpX, interpY);

   // Updating visibility of sampled and interpolated data.
   if (interpVis == 1)
            ui->customPlot2->graph(1)->setVisible(1);
   else
            ui->customPlot2->graph(1)->setVisible(0);
   ui->customPlot2->replot();

   if (samplingVis){
            ui->customPlot->graph(1)->setVisible(1);
            ui->customPlot2->graph(0)->setVisible(1);
   } else {
            ui->customPlot->graph(1)->setVisible(0);
            ui->customPlot2->graph(0)->setVisible(0);
   }

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_rbtnSine_clicked()
{
    fcn = 1;
    mtp = 30;
    plotData(scale, mtp, fcn);
}


void MainWindow::on_rbtnSinePack_clicked()
{
    fcn = 2;
    mtp = 30;
    plotData(scale, mtp, fcn);

}


void MainWindow::on_rbtnSineAdd_clicked()
{
    fcn = 3;
    mtp = 30;
    plotData(scale, mtp, fcn);
}


void MainWindow::on_sldrMTP_valueChanged(int value)
{
    mtp = value;
    plotData(scale, mtp, fcn);
}


void MainWindow::on_sldrSampl_valueChanged(int value)
{
    sampling = value;
    plotData(scale, mtp, fcn);
}


void MainWindow::on_chbox_quantize_clicked(bool checked)
{
    if(checked){
            quantize = 1;
            plotData(scale, mtp, fcn);
    } else {
            quantize = 0;
            plotData(scale, mtp, fcn);
    }
}



void MainWindow::on_chbox_interpVis_clicked(bool checked)
{
    if (checked)
    {
             ui->customPlot2->graph(1)->setVisible(1);
             interpVis  = 1;
    }
    else
    {
             ui->customPlot2->graph(1)->setVisible(0);
             interpVis  = 0;
    }
    ui->customPlot2->replot();
}



void MainWindow::on_cbBits_textActivated(const QString &arg1)
{
    if (quantize){
        if (arg1 == "2 bit"){
                quant_levels = 4;
        }else if (arg1 == "3 bit"){
                quant_levels = 8;
        }else if (arg1 == "4 bit"){
                quant_levels = 16;
        }else if (arg1 == "5 bit"){
                quant_levels = 32;
        }
        plotData(scale, mtp, fcn);
    }
}


void MainWindow::on_chbox_samplingVis_toggled(bool checked)
{
    if (checked){
        samplingVis  = 1;
        ui->customPlot->graph(1)->setVisible(1);
        ui->customPlot2->graph(0)->setVisible(1);
    } else {
        samplingVis  = 0;
        ui->customPlot->graph(1)->setVisible(0);
        ui->customPlot2->graph(0)->setVisible(0);
    }

     ui->customPlot->replot();
     ui->customPlot2->replot();
}

