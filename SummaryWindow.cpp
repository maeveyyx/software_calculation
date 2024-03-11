#include "SummaryWindow.h"
#include <QVBoxLayout>

SummaryWindow::SummaryWindow(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    totalTimeLabel = new QLabel("答题时长: ", this);
    accuracyLabel = new QLabel("正确率: ", this);
    totalQuestionsLabel = new QLabel("总题数: ", this);
    correctQuestionsLabel = new QLabel("正确题数: ", this);
    wrongQuestionsLabel = new QLabel("错误题数: ", this);

    layout->addWidget(totalTimeLabel);
    layout->addWidget(accuracyLabel);
    layout->addWidget(totalQuestionsLabel);
    layout->addWidget(correctQuestionsLabel);
    layout->addWidget(wrongQuestionsLabel);
}

void SummaryWindow::setSummary(int totalTime, double accuracy, int totalQuestions, int correctQuestions, int wrongQuestions)
{
    totalTimeLabel->setText("答题时长: " + QString::number(totalTime) + "秒");
    accuracyLabel->setText("正确率: " + QString::number(accuracy, 'f', 2) + "%");
    totalQuestionsLabel->setText("总题数: " + QString::number(totalQuestions));
    correctQuestionsLabel->setText("正确题数: " + QString::number(correctQuestions));
    wrongQuestionsLabel->setText("错误题数: " + QString::number(totalQuestions - correctQuestions));
}
