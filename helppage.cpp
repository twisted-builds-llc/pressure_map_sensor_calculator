#include "helppage.h"
#include "ui_helppage.h"

helpPage::helpPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::helpPage)
{
    ui->setupUi(this);
}

helpPage::~helpPage()
{
    delete ui;
}
