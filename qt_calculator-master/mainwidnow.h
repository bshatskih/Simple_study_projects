#ifndef CALCULATOR_MAINWIDNOW_H
#define CALCULATOR_MAINWIDNOW_H

#include <QMainWindow>
#include "Calculator.h"


class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr) : calc(new Calculator(this)) {
        setCentralWidget(calc);
        initialSizeWidth = width();
        setWindowTitle("Calculator (classic mode)");
        setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        QObject::connect(
                calc->engineerModeToggler,
                SIGNAL(stateChanged(int)),
                this,
                SLOT(onCheckBox(int))
        );
    }

public slots:

    void onCheckBox(int state) {
        if (state == 2) {
            if (engineerSizeWidth == -1)
                engineerSizeWidth = width();
            else
                setFixedWidth(engineerSizeWidth);
            setWindowTitle("Calculator (engineer mode)");
        } else {
            setFixedWidth(initialSizeWidth);
            setWindowTitle("Calculator (classic mode)");
        }
    }

private:
    /*
     * Высота окна не меняется.
     * В конструкторе при инициализации будет запомнена изначальная ширина окна (см. строка 14).
     * При первом включении будет запомнена ширина окна в инженерном режиме (см. строка 29).
     * При переключении режимов будет выставляться соответствующая ширина окна.
     * */
    int initialSizeWidth = -1;
    int engineerSizeWidth = -1;
    Calculator *calc;
};

#endif //CALCULATOR_MAINWIDNOW_H
