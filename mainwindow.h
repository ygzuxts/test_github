#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include<QKeyEvent>
#include<QMap>
#include<QPushButton>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString operand;
    QString opcode;
    QStack<QString >operands;
    QStack<QString >opcodes;
    QMap<int, QPushButton *> digitbtns;
    QString calculation(bool *ok = NULL);
private slots:
    void btnnumclick();


    void on_btnpoint_clicked();

    void on_btndel_clicked();

    void on_btnclear_clicked();

    void btnbinaryOperatorClicked();

    void on_btnequal_clicked();

    void btnunaryOperatorClicked();
    void on_btnclearall_clicked();

    virtual void keyPressEvent(QKeyEvent *event);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
