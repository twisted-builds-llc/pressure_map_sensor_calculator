#ifndef HELPPAGE_H
#define HELPPAGE_H

#include <QDialog>

namespace Ui {
class helpPage;
}

class helpPage : public QDialog
{
    Q_OBJECT

public:
    explicit helpPage(QWidget *parent = nullptr);
    ~helpPage();

private:
    Ui::helpPage *ui;
};

#endif // HELPPAGE_H
