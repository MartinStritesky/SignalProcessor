#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>
#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QVector>
#include <cmath>
#include <cstdio>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



/*!
 * \brief The MainWindow class
 *
 * Class representing the graphic interface and it is holding all events and functions.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //! A constructor of MainWindow.
    MainWindow(QWidget *parent = nullptr);

    //! A destructor of MainWindow.
    ~MainWindow();

    /*!
     * \brief plotData function calculated and plots all original, sampled and interpolated signal points.
     * \param scale a number of available points on the x and y axis.
     * \param mtp a signal frequency multiplicator.
     * \param fcn an integer argument representing one of the predefined functions.
     */
    void plotData(double scale, int mtp, int fcn);

private slots:
    //! An event for choosing the Sine function.
    void on_rbtnSine_clicked();
    //! An event for choosing the Wavelet function.
    void on_rbtnSinePack_clicked();
    //! An event for choosing the Square Wave function.
    void on_rbtnSineAdd_clicked();
    //! A slider event for frequency multiplication.
    void on_sldrMTP_valueChanged(int value);
    //! A slider event for sampling frequency change.
    void on_sldrSampl_valueChanged(int value);
    //! A checkbox to toggle quantization ON/OFF.
    void on_chbox_quantize_clicked(bool checked);
    //! A checkbox to toggle visibility of interpolated function ON/OFF.
    void on_chbox_interpVis_clicked(bool checked);
    //! A combo box to select number of converter bits.
    void on_cbBits_textActivated(const QString &arg1);
    //! A checkbox to toggle visibility of sampling scatter plot ON/OFF.
    void on_chbox_samplingVis_toggled(bool checked);

private:
    Ui::MainWindow *ui;

    double scale = 500.0; //!< A number of available points on the x and y axis.
    int mtp = 30; //!< A signal frequency multiplicator.
    int fcn = 1; //!< An integer argument representing one of the predefined functions.
    int sampling = 20;  //!< Spacing between sampled points.
    bool quantize = 0; //!< A boolean toggling quantization ON/OFF.
    bool interpVis = 0; //!< A boolean toggling visiblity of interpolated graph ON/OFF.
    bool samplingVis = 0; //!< A boolean toggling visibility of sampling scatter plot ON/OFF.
    int quant_levels = 8; //!< A number of quantization levels.
    double lowRange = -1.1;  //!< Lowest range for plotting.
    double highRange = 1.1; //!< Highest range for plotting.
    double fqcy =  mtp * (1/(2*3.142)); //!< A function frequency value.


};
#endif // MAINWINDOW_H
