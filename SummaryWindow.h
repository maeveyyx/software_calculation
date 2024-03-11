#ifndef SUMMARYWINDOW_H
#define SUMMARYWINDOW_H

#include <QWidget>
#include <QLabel>

class SummaryWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SummaryWindow(QWidget *parent = nullptr);

    void setSummary(int totalTime, double accuracy, int totalQuestions, int correctQuestions, int wrongQuestions);

private:
    QLabel *totalTimeLabel;
    QLabel *accuracyLabel;
    QLabel *totalQuestionsLabel;
    QLabel *correctQuestionsLabel;
    QLabel *wrongQuestionsLabel;
};

#endif // SUMMARYWINDOW_H
