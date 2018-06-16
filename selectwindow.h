#ifndef SELECTWINDOW_H
#define SELECTWINDOW_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class SelectWindow;
}

class SelectWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SelectWindow(QString str, QWidget *parent = 0);
    ~SelectWindow();
    void startText();

private slots:


    void on_pushButton_pressed();

    void on_pushButton_2_pressed();

    void on_pushButton_3_pressed();

    void on_backButton_clicked();

    void on_nextButton_clicked();
private:
    Ui::SelectWindow *ui;
    QPalette p1, p2;
};

#endif // SELECTWINDOW_H
