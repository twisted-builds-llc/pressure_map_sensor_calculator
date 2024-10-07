#include "mainwindow.h"
#include "CustomDoubleSpinBox.h"
#include "./ui_mainwindow.h"
#include "helppage.h"
#include "aboutus.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Any additional App pages need the function = new class(this); put below
    HelpPage = new helpPage(this);
    AboutUs = new aboutUs(this);

    // Connect hitting enter in the Your Voltage input to the button for calculate press
    connect(ui->yourVoltageInput, SIGNAL(editingFinished()), this, SLOT(on_calculateButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
    //Any new pages have to be deleted below by calling their function, or all pages will load at GUI launch.
    delete HelpPage;
    delete AboutUs;
}

void MainWindow::on_actionHelp_triggered()
{
    HelpPage->show(); // help menu button was triggered so show() the window.
}


void MainWindow::on_actionClose_triggered()
{
    qApp->exit(); // close menu button was triggered so close the app.
}


void MainWindow::on_actionAbout_triggered()
{
    AboutUs->show(); // about us menu button was triggered so show() the window.
}


void MainWindow::on_calculateButton_clicked()
{
    //This is the code that is called when the calculate button is clicked.

    double intialResult; // This is the initial calculation before any conversion is done, using the raw user inputs.
    double adjustedResult; // This is a calculated output for the end user AFTER converstion for the ABSOLUTE pressure output
    double gaugeKPAout; // This is a calculated output for the end user AFTER conversion for the GAUGE pressure output in KPA
    double gaugeConversion; // This is a place holder for flips between KPA, PSI and vise versa.
    double gaugePSIout; // This is a calcualted output for the end user AFTER conversion for the GAUGE pressure output in PSI
    double absoluteKPAout; // Calculated output for KPA
    double absolutePSIout; // Calculated output for PSI

    //Below are inputs from the UI
    double highPress = ui->highPressureInput->value(); // setting up the input high pressure
    double lowPress = ui->lowPressureInput->value(); // setting up the input low pressure
    double highV = ui->highVoltageInput->value(); // setting up the input high voltage
    double lowV = ui->lowVoltageInput->value(); // setting up the input low voltage
    double yourV = ui->yourVoltageInput->value(); // setting up the input your voltage

    int inputPressureType = ui->inPressureComboBox->currentIndex();
    bool absolutePressureType = ui->absolutePressureComboBox->currentIndex();
    bool gaugePressureType = ui->gaugePressureComboBox->currentIndex();

    //This is the inital calculation once the inputs are gathered from the UI
    intialResult = (highPress - lowPress) / (highV - lowV) * (yourV - lowV) + lowPress;

    //The following if statements are handling KPA to PSI conversions if needed.
    //This one is for the absolute pressure output
    if (inputPressureType == 0) { // If the input presure type is 0, its set to KPA absolute

        //This is obviously a nested loop situation. Logic: if the output is selected to KPA, it just passes it on,
        //If the output is selected to PSI, it does the conversion THEN passes it on.

        //This if is if input is KPA absolute and output is KPA, just pass it on.
        if (absolutePressureType == 0) {
            ui->pressureOutput->setValue(intialResult);
        }

        //This is if the input is KPA absolute and output is PSI, convert the reading then pass it on
        if (absolutePressureType == 1) {
            adjustedResult = intialResult / 6.895; // This converts KPA input to PSI output
            ui->pressureOutput->setValue(adjustedResult);
        }

        //This is if the input is KPA absolute and output is KPA, just pass it on for GAUGE after mathing it first
        if (gaugePressureType == 0) {
            gaugeKPAout = intialResult - 101.3; // Subtract the 101.3kpa from the initial calculated result to get gauge kpa pressure
            ui->gaugeOutput->setValue(gaugeKPAout);
        }

        //This is if the input is KPA absolute and output is PSI, calculate it then pass it on.
        if (gaugePressureType == 1) {
            gaugeConversion = intialResult / 6.895; // This converts KPA input to PSI output
            gaugePSIout = gaugeConversion - 14.696; // This subtracts atmospheric pressure from the output to calculate gauge pressure
            ui->gaugeOutput->setValue(gaugePSIout);
        }
    }

    //The following if statements are for handling PSI gauge to PSI or KPA conversion if needed.
    if (inputPressureType == 1) { //if the input pressure type is 1, its set to PSI gauge

        //Next round of nested if statements, doing the same thing as above just starting with PSI gauge inputs.

        //This if is if the input is PSI gauge and the output is PSI absolute, calculate and pass it on
        if (absolutePressureType == 1) {
            //Pressure was inputed as gauge, this is for absolute pressure output so we need to add atmospheric pressure
            adjustedResult = intialResult + 14.696; // Add atmospheric pressure to make this correct
            ui->pressureOutput->setValue(adjustedResult);
        }

        //This is if the input is PSI gauge, but the output is KPA, convert it over and pass it on
        if (absolutePressureType == 0) {
            absoluteKPAout = (intialResult + 14.696) * 6.895; // This added atmospheric pressure, then converted to KPA absolute
            ui->pressureOutput->setValue(absoluteKPAout);
        }

        //This if is if the input is PSI gauge and the output is PSI gauge, pass it on.
        if (gaugePressureType == 1) {
            ui->gaugeOutput->setValue(intialResult); // Pass the initial result right on out its all the same.
        }

        //This if is if the input is PSI gauge and the output is KPA gauge, calculate and pass it on
        if (gaugePressureType == 0) {
            gaugeKPAout = intialResult * 6.895; // Convert from PSI gauge to PSI gauge
            ui->gaugeOutput->setValue(gaugeKPAout);
        }
    }

    //The following if statements are for handling PSI absolute to PSI or KPA as needed
    if (inputPressureType == 2) { // if the input pressure type is 2, its set to PSI absolute

        //The following is the next round of if statements.
        if (absolutePressureType == 1) {
            ui->pressureOutput->setValue(intialResult); //Input is PSI absolute, output is PSI absolute, just toss the value out.
        }

        if (absolutePressureType == 0) {
            absoluteKPAout = intialResult * 6.895; // Convert absolute psi to absolute KPA
            ui->pressureOutput->setValue(absoluteKPAout);
        }

        if (gaugePressureType == 1) {
            gaugePSIout = intialResult - 14.696; // subtract atmospheric pressure to the absolute input pressure
            ui->gaugeOutput->setValue(gaugePSIout);
        }

        if (gaugePressureType == 0) {
            gaugeKPAout = (intialResult - 14.696) * 6.895;// Subtract atmospheric then convert to KPA
            ui->gaugeOutput->setValue(gaugeKPAout);
        }
    }

    //The following if statements are for handling kpa gauge to PSI or KPA as needed
    if (inputPressureType == 3) { // if the input pressure type is 3, its set to kpa gauge

        //Last round of if statements
        if (absolutePressureType == 0) { // This is KPA output selected
            absoluteKPAout = intialResult + 101.3; // Add 101.3kpa to get to atmospheric pressures.
            ui->pressureOutput->setValue(absoluteKPAout);
        }

        if (absolutePressureType == 1) { // This is PSI output selected
            absolutePSIout = (intialResult + 101.3) / 6.895; // Add atmospheric pressure to the initial gauge kpa value then convert to PSI
            ui->pressureOutput->setValue(absolutePSIout);
        }

        if (gaugePressureType == 0) { // This is KPA output selected
            ui->gaugeOutput->setValue(intialResult); // Just pass along the KPA gauge pressure in to the KPA gauge pressure out
        }

        if (gaugePressureType == 1) { // This is PSI output selected
            gaugePSIout = intialResult / 6.895; // Take KPA gauge and just convert it to PSI gauge
            ui->gaugeOutput->setValue(gaugePSIout);
        }
    }
}

