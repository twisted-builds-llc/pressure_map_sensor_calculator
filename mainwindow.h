#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "helppage.h"
#include "aboutus.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionHelp_triggered();

    void on_actionClose_triggered();

    void on_actionAbout_triggered();

    void on_calculateButton_clicked();

private:
    Ui::MainWindow *ui;
    helpPage *HelpPage;
    aboutUs *AboutUs;
};
#endif // MAINWINDOW_H
