#include "Calculator.h"

Calculator::Calculator(QWidget *parent)

        : QWidget(parent), ans(0.0) {
    // создаём виджеты-обёртки
    auto *textWidget = new QWidget(this);
    auto *utilWidget = new QWidget(this);
    auto *ansWidget = new QWidget(utilWidget);
    auto *buttonsWidget = new QWidget(this);
    auto *digitsWidget = new QWidget(buttonsWidget);
    auto *operatorsWidget = new QWidget(buttonsWidget);
    auto *engineerWidget = new QWidget(buttonsWidget);

    // создаём лейауты для этих виджетов обёрток
    mainLayout = new QVBoxLayout(this);
    textLayout = new QHBoxLayout(textWidget);
    utilLayout = new QHBoxLayout(utilWidget);
    ansLayout = new QVBoxLayout(ansWidget);
    buttonsLayout = new QHBoxLayout(buttonsWidget);
    digitsLayout = new QGridLayout(digitsWidget);
    operatorsLayout = new QGridLayout(operatorsWidget);
    engineerLayout = new QGridLayout(engineerWidget);

//    parent->setLayout(mainLayout);
    // подключаем лейауты
    setLayout(mainLayout);
    textWidget->setLayout(textLayout);
    utilWidget->setLayout(utilLayout);
    ansWidget->setLayout(ansLayout);
    buttonsWidget->setLayout(buttonsLayout);
    digitsWidget->setLayout(digitsLayout);
    operatorsWidget->setLayout(operatorsLayout);
    engineerWidget->setLayout(engineerLayout);

    // создаём элементы
    exprLabel = new QLabel("Expression:", this);
    text = new QLineEdit(textWidget);
    engineerModeToggler = new QCheckBox("Engineer mode", textWidget);
    ansBtn = new QPushButton("ANS", utilWidget);
    ansLabel = new QLabel("Last answer:", ansWidget);
    ansText = new QLineEdit(ansWidget);
    cpyBtn = new QPushButton("Copy", utilWidget);

    // раскладываем всё по лейаутам
    mainLayout->addWidget(exprLabel);
    mainLayout->addWidget(textWidget);
    mainLayout->addWidget(utilWidget);
    mainLayout->addWidget(buttonsWidget);

    textLayout->addWidget(text);
    textLayout->addWidget(engineerModeToggler);

    utilLayout->addWidget(ansBtn);
    utilLayout->addWidget(ansWidget);
    utilLayout->addWidget(cpyBtn);

    ansLayout->addWidget(ansLabel);
    ansLayout->addWidget(ansText);

    buttonsLayout->addWidget(digitsWidget);
    buttonsLayout->addWidget(operatorsWidget);
    buttonsLayout->addWidget(engineerWidget);

    // настраиваем всё
    constexpr int fontSize = 22;
    QFont calculatorFont = QFontDatabase::systemFont(QFontDatabase::FixedFont); // моноширинный
    calculatorFont.setPointSize(fontSize);
    setFont(calculatorFont); // распространяется на детей this
    text->setMaxLength(100);
    text->resize(QSize(300, 30));
//    exprLabel->setSizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);
    ansBtn->setMaximumWidth(100);
    ansBtn->setMinimumHeight(50);
    ansText->setReadOnly(true);
    ansText->setMaxLength(30);
    ansText->setMaximumWidth(500);
    ansText->setMinimumHeight(50);
    cpyBtn->setMaximumWidth(100);
    cpyBtn->setMinimumHeight(50);
    ansText->setStyleSheet("QLineEdit { background-color : green; color : red; }");

    engineerModeToggler->setCheckState(Qt::CheckState::Unchecked);

    // создаём цифры
    auto row = 0;
    auto col = 0;
    std::vector<std::string> numbers = {"1", "2", "3", "4", "5", "6", "7", "8", "9", ".", "0", "C"};
    for (auto &i: numbers) {
        digits.push_back(new QPushButton(i.c_str(), digitsWidget));
        digitsLayout->addWidget(digits.back(), row, col);
        QObject::connect(digits.back(), SIGNAL(clicked()),
                         this, SLOT(buttonPressed())
        );
        ++col;
        if (col == 3) {
            row++;
            col = 0;
        }
    }

    // создаём операторы
    std::unordered_map<std::string, std::pair<int, int>> operatorsPositions;
    operatorsPositions["+"] = std::make_pair(0, 0);
    operatorsPositions["-"] = std::make_pair(0, 1);
    operatorsPositions["*"] = std::make_pair(1, 0);
    operatorsPositions["/"] = std::make_pair(1, 1);
    operatorsPositions["("] = std::make_pair(2, 0);
    operatorsPositions[")"] = std::make_pair(2, 1);
    operatorsPositions["="] = std::make_pair(3, 0);
    std::vector<std::string> operatorsStrings = {"+", "-", "*", "/", "(", ")", "="};
    for (auto &op: operatorsStrings) {
        operators.push_back(new QPushButton(op.c_str(), operatorsWidget));
        auto pos = operatorsPositions[op];
        if (op == "=") {
            operatorsLayout->addWidget(operators.back(), pos.first, pos.second, 1, 2);
            QObject::connect(operators.back(), SIGNAL(clicked()),
                             this, SLOT(evaluate())
            );
        } else {
            operatorsLayout->addWidget(operators.back(), pos.first, pos.second);
            QObject::connect(operators.back(), SIGNAL(clicked()),
                             this, SLOT(buttonPressed())
            );
        }
    }

    // создаём инженерные кнопки
    std::unordered_map<std::string, std::pair<int, int>> engineerButtonsPositions;
    engineerButtonsPositions["sin"] = std::make_pair(0, 0);
    engineerButtonsPositions["cos"] = std::make_pair(1, 0);
    engineerButtonsPositions["tan"] = std::make_pair(2, 0);
    engineerButtonsPositions["sinh"] = std::make_pair(0, 1);
    engineerButtonsPositions["cosh"] = std::make_pair(1, 1);
    engineerButtonsPositions["tanh"] = std::make_pair(2, 1);
    engineerButtonsPositions["exp"] = std::make_pair(0, 2);
    engineerButtonsPositions["log"] = std::make_pair(1, 2);
    engineerButtonsPositions["log10"] = std::make_pair(2, 2);
    engineerButtonsPositions["pi"] = std::make_pair(3, 0);
    engineerButtonsPositions["e"] = std::make_pair(3, 1);
    engineerButtonsPositions[","] = std::make_pair(3, 2);
    engineerButtonsPositions["^"] = std::make_pair(2, 3);
    engineerButtonsPositions["sqrt"] = std::make_pair(0, 3);
    engineerButtonsPositions["cbrt"] = std::make_pair(1, 3);
    std::vector<std::string> engineerStrings = {"sin", "cos", "tan", "sinh", "cosh", "tanh", "exp", "log", "log10",
                                                "pi", "e", "^", ",", "sqrt", "cbrt"};
    for (auto &op: engineerStrings) {
        engineerButtons.push_back(new QPushButton(op.c_str(), engineerWidget));
        auto &pos = engineerButtonsPositions[op];
        if (op == ",")
            engineerLayout->addWidget(engineerButtons.back(), pos.first, pos.second, 1, 2);
        else
            engineerLayout->addWidget(engineerButtons.back(), pos.first, pos.second);
        QObject::connect(engineerButtons.back(), SIGNAL(clicked()),
                         this, SLOT(buttonPressed())
        );
    }
    engineerWidget->setVisible(false);
    QObject::connect(engineerModeToggler, SIGNAL(toggled(bool)),
                     engineerWidget, SLOT(setVisible(bool)));
    QObject::connect(text, SIGNAL(textEdited(QString)),
                     this, SLOT(textChanged(QString)));
    QObject::connect(text, SIGNAL(returnPressed()),
                     this, SLOT(evaluate()));
    QObject::connect(ansBtn, SIGNAL(clicked()),
                     this, SLOT(buttonPressed()));
    QObject::connect(this, SIGNAL(sigAnsChanged(QString)),
                     ansText, SLOT(setText(QString)));
    QObject::connect(cpyBtn, SIGNAL(clicked()),
                     this, SLOT(copyToClipboard()));
    QObject::connect(this, SIGNAL(sigExpressionChanged(QString)),
                     text, SLOT(setText(QString)));
}

void Calculator::buttonPressed() {
    auto symbol = sender()->property("text").toString();
    if (symbol == "C") {
        expression.clear();
        toCopy = expression;
        emit sigExpressionChanged(expression);
    } else {
        expression += symbol;
        toCopy = expression;
        emit sigExpressionChanged(expression);
    }
}

void Calculator::copyToClipboard() {
    QGuiApplication::clipboard()->setText(toCopy);
    toCopy = expression;
}

void Calculator::textChanged(const QString &newExpr) {
    expression = newExpr;
    toCopy = newExpr;
//    emit sigExpressionChanged(expression);
}

void Calculator::evaluate() {
    if (expression.isEmpty()) return;
    QVector<QPair<QString, QString>> replacements{{"pi",       "Math.PI"},
                                                  {"e",        "Math.E"},
                                                  {"sin",      "Math.sin"},
                                                  {"cos",      "Math.cos"},
                                                  {"tan",      "Math.tan"},
                                                  {"sinh",     "Math.sinh"},
                                                  {"cosh",     "Math.cosh"},
                                                  {"tanh",     "Math.tanh"},
                                                  {"exp",      "Math.exp"},
                                                  {"log",      "Math.log"},
                                                  {"log10",    "Math.log10"},
                                                  {"sqrt",     "Math.sqrt"},
                                                  {"cbrt",     "Math.cbrt"},
                                                  {"Math.Exp", "Math.exp"}}; // exp -> Math.Exp -> Math.exp
    auto jsExpression = expression;
    for (const auto &[item, replacement]: replacements) {
        jsExpression.replace(item, replacement);
    }
    auto jsResult = parser.evaluate(jsExpression);
    expression = jsResult.toString();
    emit sigExpressionChanged(expression);
    if (not expression.contains("Error")) {
        ans = jsResult.toNumber();
        emit sigAnsChanged(expression);
        expression.clear();
    }
}
void Calculator::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));

  painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
  painter.drawEllipse(100, 50, 150, 150);
  QRectF rectangle(90.0, 340.0, 80.0, 60.0);
  int startAngle = 30 * 16;
  int spanAngle = 120 * 16;
  painter.drawPie(rectangle, startAngle, spanAngle);
  painter.drawRect(490.0, 290.0, 80.0, 60.0);
}

