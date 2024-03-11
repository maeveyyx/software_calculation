#include "mainwindow.h"
#include "SummaryWindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTime>
#include <QRandomGenerator>
#include <QDebug> // 包含调试用的头文件
#include <QElapsedTimer>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), currentDifficulty(0), correctCount(0), totalCount(0)
{
    ui->setupUi(this);
    setupUI();
    srand(QTime::currentTime().msec());
    timer = new QElapsedTimer(); // 初始化计时器
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer; // 删除计时器
}

void MainWindow::setupUI() {
    // 界面布局和组件初始化
    generateButton = new QPushButton("生成题目", this);
    generateButton->setFixedSize(120, 40); // 设置按钮固定大小
    generateButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; border-radius: 5px; } QPushButton:hover { background-color: #45a049; }"); // 设置按钮样式

    difficultyLabel = new QLabel("难度选择:", this);
    easyButton = new QRadioButton("简单", this);
    mediumButton = new QRadioButton("中等", this);
    hardButton = new QRadioButton("困难", this);
    difficultyLabel->setStyleSheet("QLabel { font-weight: bold; font-size: 16px; }"); // 设置标签样式
    easyButton->setStyleSheet("QRadioButton { font-size: 14px; }"); // 设置单选按钮样式
    mediumButton->setStyleSheet("QRadioButton { font-size: 14px; }");
    hardButton->setStyleSheet("QRadioButton { font-size: 14px; }");

    problemsArea = new QTextEdit(this);
    problemsArea->setReadOnly(true);
    problemsArea->setStyleSheet("QTextEdit { font-size: 16px; }"); // 设置文本编辑框样式

    answerInput = new QLineEdit(this);
    submitAnswerButton = new QPushButton("提交答案", this);
    submitAnswerButton->setFixedSize(120, 40); // 设置按钮固定大小
    submitAnswerButton->setStyleSheet("QPushButton { background-color: #008CBA; color: white; border-radius: 5px; } QPushButton:hover { background-color: #0073e6; }"); // 设置按钮样式

    resultLabel = new QLabel("请输入答案", this);
    resultLabel->setStyleSheet("QLabel { font-weight: bold; font-size: 16px; }"); // 设置标签样式

    timeLabel = new QLabel("答题时长: ", this); // 显示答题时长的标签
    accuracyLabel = new QLabel("正确率: ", this); // 显示正确率的标签

    difficultyGroup = new QButtonGroup(this);
    difficultyGroup->addButton(easyButton, 0);
    difficultyGroup->addButton(mediumButton, 1);
    difficultyGroup->addButton(hardButton, 2);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *difficultyLayout = new QHBoxLayout;
    difficultyLayout->addWidget(difficultyLabel);
    difficultyLayout->addWidget(easyButton);
    difficultyLayout->addWidget(mediumButton);
    difficultyLayout->addWidget(hardButton);
    mainLayout->addLayout(difficultyLayout);
    mainLayout->addWidget(generateButton);
    mainLayout->addWidget(problemsArea);
    mainLayout->addWidget(answerInput);
    mainLayout->addWidget(submitAnswerButton);
    mainLayout->addWidget(resultLabel);
    mainLayout->addWidget(timeLabel); // 添加答题时长标签
    mainLayout->addWidget(accuracyLabel); // 添加正确率标签

    QWidget *window = new QWidget();
    window->setLayout(mainLayout);
    setCentralWidget(window);

    connect(generateButton, &QPushButton::clicked, this, &MainWindow::generateProblems);
    connect(difficultyGroup, QOverload<int>::of(&QButtonGroup::buttonClicked), this, &MainWindow::setDifficulty);
    connect(submitAnswerButton, &QPushButton::clicked, this, &MainWindow::checkAnswer);
    finishQuizButton = new QPushButton("结束答题", this);
    connect(finishQuizButton, &QPushButton::clicked, this, &MainWindow::finishQuiz);
    mainLayout->addWidget(finishQuizButton);

}
    int correctCount;
    int totalCount;
    double accuracyLabel;
void MainWindow::checkAnswer() {
    if (answerInput->text() == currentAnswer) {
        resultLabel->setText("正确！");
        correctCount++; // 答对题数加一
    } else {
        resultLabel->setText("错误，正确答案是: " + currentAnswer);
    }
    answerInput->clear();
    totalCount++; // 总题数加一
    generateProblems(); // 生成新题目

    // 计算正确率并显示
    double accuracy = (double)correctCount / totalCount * 100;
    accuracyLabel->setText("正确率: " + QString::number(accuracy, 'f', 2) + "%");

    // 停止计时并显示答题时长
    timer->invalidate(); // 重置计时器
    timeLabel->setText("答题时长: " + QString::number(timer->elapsed() / 1000) + "秒");
}

void MainWindow::generateProblems() {
    timer->start(); // 开始计时
    QString problem = generateProblem();
    problemsArea->append(problem);
}

void MainWindow::setDifficulty(int difficulty) {
    currentDifficulty = difficulty;
}

int MainWindow::greatestCommonDivisor(int a, int b) {
    if (b == 0)
        return a;
    return greatestCommonDivisor(b, a % b);
}

QString MainWindow::generateProblem() {
    QString problem;
    //int commonDenominator=1;
    double answer; // 将答案改为 double 类型以支持小数
    // 基于难易度和题目类型生成题目
    if (currentDifficulty == 2) {
        int numerator1 = QRandomGenerator::global()->bounded(1, 10);
        int denominator1 = QRandomGenerator::global()->bounded(1, 10);
        int numerator2 = QRandomGenerator::global()->bounded(1, 10);
        int denominator2 = QRandomGenerator::global()->bounded(1, 10);
        QString operation;
        int operationIndex = QRandomGenerator::global()->bounded(4);

            int numeratorResult;
                int denominatorResult;
                int commonDenominator;
                switch (operationIndex) {
                    case 0: // 加法
                        operation = "+";
                        numeratorResult = numerator1 * denominator2 + numerator2 * denominator1;
                        commonDenominator = denominator1 * denominator2;
                        break;
                    case 1: // 减法
                        operation = "-";
                        numeratorResult = numerator1 * denominator2 - numerator2 * denominator1;
                        commonDenominator = denominator1 * denominator2;
                        break;
                    case 2: // 乘法
                        operation = "*";
                        numeratorResult = numerator1 * numerator2;
                        commonDenominator = denominator1 * denominator2;
                        break;
                    case 3: // 除法
                        operation = "/";
                        // 保证除数不为0
                        if (numerator2 == 0) numerator2 = 1;
                        if (denominator1 == 0) denominator1 = 1;
                        numeratorResult = numerator1 * denominator2;
                        commonDenominator = numerator2 * denominator1;
                        break;
                }
                // 计算最大公约数以简化分数
                int gcd = greatestCommonDivisor(numeratorResult, commonDenominator);
                int simplifiedNumerator = numeratorResult / gcd;
                int simplifiedDenominator = commonDenominator / gcd;

                // 设置答案
                if (simplifiedDenominator == 1) { // 如果分母为1，则只显示分子
                    currentAnswer = QString::number(simplifiedNumerator);
                } else {
                    currentAnswer = QString("%1/%2").arg(simplifiedNumerator).arg(simplifiedDenominator);
                }

                // 设置问题
                problem = QString("%1/%2 %3 %4/%5 = ?")
                                .arg(numerator1).arg(denominator1)
                                .arg(operation)
                                .arg(numerator2).arg(denominator2);
              } else if (currentDifficulty == 1) {
        // 中等模式
        int a = rand() % 200 + 1;
        int b = rand() % 200 + 1;
        int operationIndex = QRandomGenerator::global()->bounded(4); // 0: 加法, 1: 减法, 2: 乘法, 3: 除法
        switch (operationIndex) {
            case 0:
                problem = QString::number(a) + " + " + QString::number(b) + " = ?";
                answer = a + b;
                break;
            case 1:
                problem = QString::number(a) + " - " + QString::number(b) + " = ?";
                answer = a - b;
                break;
            case 2:
                problem = QString::number(a) + " * " + QString::number(b) + " = ?";
                answer = a * b;
                break;
            case 3:
                if (b != 0) {
                    answer = static_cast<double>(a) / static_cast<double>(b);
                    problem = QString::number(a) + " / " + QString::number(b) + " = ?";
                } else {
                    // 避免除数为零
                    b = 1;
                    answer = static_cast<double>(a) / static_cast<double>(b);
                    problem = QString::number(a) + " / " + QString::number(b) + " = ?";
                }
                break;
        }
        if (qFuzzyCompare(answer - static_cast<int>(answer), 0.0)) {
            currentAnswer = QString::number(static_cast<int>(answer)); // 如果小数点后两位为00，则只显示整数部分
        } else {
            currentAnswer = QString::number(answer, 'f', 2); // 否则保留两位小数
        }
    } else {
        // 简单模式
        int a = rand() % 20 + 1;
        int b = rand() % 20 + 1;
        int operationIndex = QRandomGenerator::global()->bounded(4); // 0: 加法, 1: 减法, 2: 乘法, 3: 除法
        switch (operationIndex) {
            case 0:
                problem = QString::number(a) + " + " + QString::number(b) + " = ?";
                answer = a + b;
                break;
            case 1:
                problem = QString::number(a) + " - " + QString::number(b) + " = ?";
                answer = a - b;
                break;
            case 2:
                problem = QString::number(a) + " * " + QString::number(b) + " = ?";
                answer = a * b;
                break;
            case 3:
                if (b != 0) {
                    answer = static_cast<double>(a) / static_cast<double>(b);
                    problem = QString::number(a) + " / " + QString::number(b) + " = ?";
                } else {
                    // 避免除数为零
                    b = 1;
                    answer = static_cast<double>(a) / static_cast<double>(b);
                    problem = QString::number(a) + " / " + QString::number(b) + " = ?";
                }
                break;
        }
        if (qFuzzyCompare(answer - static_cast<int>(answer), 0.0)) {
            currentAnswer = QString::number(static_cast<int>(answer)); // 如果小数点后两位为00，则只显示整数部分
        } else {
            currentAnswer = QString::number(answer, 'f', 2); // 否则保留两位小数
        }
    }
    return problem;
}
void MainWindow::finishQuiz() {
    int wrongCount = totalCount - correctCount;
    // 假设答题时长以秒为单位
    int totalTime = timer->elapsed() / 1000;
    double accuracy = (double)correctCount / totalCount * 100;

    SummaryWindow *summaryWindow = new SummaryWindow();
    summaryWindow->setSummary(totalTime, accuracy, totalCount, correctCount, wrongCount);
    summaryWindow->show();
}

