// CustomDoubleSpinBox.cpp

#include "CustomDoubleSpinBox.h"

CustomDoubleSpinBox::CustomDoubleSpinBox(QWidget *parent)
    : QDoubleSpinBox(parent)
{
}

void CustomDoubleSpinBox::focusInEvent(QFocusEvent *event)
{
    QDoubleSpinBox::focusInEvent(event);
    if (this->objectName() == "lowPressureInput")
    {
        this->clear();
    }

    QDoubleSpinBox::focusInEvent(event);
    if (this->objectName() == "lowVoltageInput")
    {
        this->clear();
    }

    QDoubleSpinBox::focusInEvent(event);
    if (this->objectName() == "highPressureInput")
    {
        this->clear();
    }

    QDoubleSpinBox::focusInEvent(event);
    if (this->objectName() == "highVoltageInput")
    {
        this->clear();
    }

    QDoubleSpinBox::focusInEvent(event);
    if (this->objectName() == "yourVoltageInput")
    {
        this->clear();
    }
}
