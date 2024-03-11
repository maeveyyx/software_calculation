#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QRadioButton>
#include <QButtonGroup>
#include <QTextEdit>
#include <QLineEdit>
#include <QElapsedTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QElapsedTimer *timer; // 确保这里声明了 timer
    int currentDifficulty;
        int correctCount;
        int totalCount; // 确保这里声明了 totalCount
        QLabel *accuracyLabel;
        QLabel *timeLabel;
        QPushButton *finishQuizButton;
    ~MainWindow();

private slots:
    void generateProblems();
    void setDifficulty(int difficulty);
    void checkAnswer();
    void finishQuiz(); // 声明槽函数
    int greatestCommonDivisor(int a, int b);

private:
    Ui::MainWindow *ui;
    QPushButton *generateButton;

    QLabel *difficultyLabel;
    QRadioButton *easyButton, *mediumButton, *hardButton;
    QButtonGroup *difficultyGroup;
    QTextEdit *problemsArea;

    QLineEdit *answerInput;
    QPushButton *submitAnswerButton;
    QLabel *resultLabel;

    QString currentAnswer; // 保存当前题目的正确答案
    void setupUI();
    QString generateProblem();
    QString generateFractionProblem();
    QString generateIntegerProblem();
};
#endif // MAINWINDOW_H
