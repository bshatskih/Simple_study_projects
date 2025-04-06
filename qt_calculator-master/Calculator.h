#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QtWidgets>
#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <QClipboard>
#include <QGuiApplication>
#include <iostream>
#include <QJSEngine>

class Calculator : public QWidget {
Q_OBJECT
    QString expression;
    QString toCopy;
    double ans;
    QJSEngine parser;
    /* Примерное дерево всех лейаутов и их содержимого
     * mainLayout
     *     exprLabel: "Expression:"
     *     textLayout
     *         text: Текст выражения
     *         engineerModeToggler: Переключатель режимов
     *     utilLayout
     *         ansBtn: Кнопка ANS
     *         ansLayout
     *             ansLabel: "Last answer:"
     *             ansText: Текст последнего ответа
     *         cpyBtn: Кнопка "скопировать ответ"
     *     buttonsLayout
     *         digitsLayout
     *             digits: Цифры, '.', 'C'
     *         operatorsLayout
     *             operators: + - * / ( ) =
     *         engineerLayout
     *             engineerButtons: Инженерные кнопки
     */
    QVBoxLayout *mainLayout;
    QLabel *exprLabel;
    QHBoxLayout *textLayout;
    QLineEdit *text;
    QCheckBox *engineerModeToggler;
    QHBoxLayout *utilLayout;
    QPushButton *ansBtn;
    QVBoxLayout *ansLayout;
    QLabel *ansLabel;
    QLineEdit *ansText;
    QPushButton *cpyBtn;
    QHBoxLayout *buttonsLayout;
    QGridLayout *digitsLayout;
    QVector<QPushButton *> digits;
    QGridLayout *operatorsLayout;
    QVector<QPushButton *> operators;
    QGridLayout *engineerLayout;
    QVector<QPushButton *> engineerButtons;
 protected:
    void paintEvent(QPaintEvent *event);
public:
    explicit Calculator(QWidget *parent = nullptr);

friend class MainWindow;

public slots:

    void buttonPressed();

    void textChanged(const QString &);

    void copyToClipboard();

    void evaluate();

signals:

    void sigExpressionChanged(const QString &); //!!! const QString &
    void sigAnsChanged(const QString &);    //!!! const QString &
};

#endif // CALCULATOR_H
