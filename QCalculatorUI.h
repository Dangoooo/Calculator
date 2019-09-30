#ifndef QCALCULATORUI_H
#define QCALCULATORUI_H
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include "ICalculator.h"

class QCalculatorUI : public QWidget
{
    Q_OBJECT
protected:
    QLineEdit* m_edit;
    QPushButton* m_button[20];
    ICalculator* m_cal;
    QCalculatorUI();
    bool construct();
private slots:
    void onButtonClicked();
public:
    static QCalculatorUI* NewInstance();
    void show();
    void setCalculator(ICalculator* cal);
    ICalculator* getCalculator();
    ~QCalculatorUI();

};

#endif // QCALCULATORUI_H
