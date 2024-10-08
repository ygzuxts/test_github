#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<math.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    digitbtns = {  {Qt::Key_0, ui->btnnum0},
        {Qt::Key_1, ui->btnnum1},
        {Qt::Key_2, ui->btnnum2},
        {Qt::Key_3, ui->btnnum3},
        {Qt::Key_4, ui->btnnum4},
        {Qt::Key_5, ui->btnnum5},
        {Qt::Key_6, ui->btnnum6},
        {Qt::Key_7, ui->btnnum7},
        {Qt::Key_8, ui->btnnum8},
        {Qt::Key_9, ui->btnnum9},

    };
    foreach (auto btn, digitbtns) {
        connect(btn, SIGNAL(clicked()), this, SLOT(btnnumclick()));
    }
    // connect(ui->btnnum0, SIGNAL(clicked()), this, SLOT(btnnumclick()));
    // connect(ui->btnnum1, SIGNAL(clicked()), this, SLOT(btnnumclick()));
    // connect(ui->btnnum2, SIGNAL(clicked()), this, SLOT(btnnumclick()));
    // connect(ui->btnnum3, SIGNAL(clicked()), this, SLOT(btnnumclick()));
    // connect(ui->btnnum4, SIGNAL(clicked()), this, SLOT(btnnumclick()));
    // connect(ui->btnnum5, SIGNAL(clicked()), this, SLOT(btnnumclick()));
    // connect(ui->btnnum6, SIGNAL(clicked()), this, SLOT(btnnumclick()));
    // connect(ui->btnnum7, SIGNAL(clicked()), this, SLOT(btnnumclick()));
    // connect(ui->btnnum8, SIGNAL(clicked()), this, SLOT(btnnumclick()));
    // connect(ui->btnnum9, SIGNAL(clicked()), this, SLOT(btnnumclick()));
    connect(ui->btnmultiple, SIGNAL(clicked()), this, SLOT(btnbinaryOperatorClicked()));
    connect(ui->btnadd, SIGNAL(clicked()), this, SLOT(btnbinaryOperatorClicked()));
    connect(ui->btndivide, SIGNAL(clicked()), this, SLOT(btnbinaryOperatorClicked()));
    connect(ui->btnminus, SIGNAL(clicked()), this, SLOT(btnbinaryOperatorClicked()));
    connect(ui->btnpercentage, SIGNAL(clicked()), this, SLOT(btnunaryOperatorClicked()));
    connect(ui->btnsquare, SIGNAL(clicked()), this, SLOT(btnunaryOperatorClicked()));
    connect(ui->btnsqrt, SIGNAL(clicked()), this, SLOT(btnunaryOperatorClicked()));
    connect(ui->btninverse, SIGNAL(clicked()), this, SLOT(btnunaryOperatorClicked()));
    connect(ui->btnplus, SIGNAL(clicked()), this, SLOT(btnunaryOperatorClicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::calculation(bool *ok)
{
    double result = 0;

    // 只有在栈中有两个操作数和至少一个操作符时才进行计算
    if (operands.size() == 2 && opcodes.size() > 0) {
        double operand1 = operands.front().toDouble();
        operands.pop_front();
        double operand2 = operands.front().toDouble();
        operands.pop_front();

        QString op = opcodes.front();
        opcodes.pop_front();

        if (op == "+") {
            result = operand1 + operand2;
        } else if (op == "-") {
            result = operand1 - operand2;
        } else if (op == "×") {
            result = operand1 * operand2;
        } else if (op == "÷") {
            if (operand2 != 0) {
                result = operand1 / operand2;
            } else {
                ui->statusbar->showMessage("Error: Division by zero");
                return "Error";
            }
        }

        // 将结果作为新的操作数推入栈
        operands.push_back(QString::number(result));

        // 更新状态栏
        ui->statusbar->showMessage(QString("calculation is in process shu %1, fuhao %2").arg(operands.size()).arg(
                                       opcodes.size()));
    } else {
        ui->statusbar->showMessage(QString("shu %1, fuhao %2").arg(operands.size()).arg(opcodes.size()));
    }

    return QString::number(result);
}
void MainWindow::btnbinaryOperatorClicked()
{
    QString opcode = qobject_cast<QPushButton *>(sender())->text();

    // 如果按了操作符，但没有任何数字输入，直接返回
    if (operand == "" && operands.isEmpty()) {
        return;
    }

    // 如果有输入的数字（operand 不为空），则将其压入操作数栈
    if (operand != "") {
        operands.push_back(operand);
        operand = "";
    }

    // 如果操作数栈中有计算结果，并且按下了新的操作符，则进行处理
    if (operands.size() == 1 && opcodes.isEmpty()) {
        opcodes.push_back(opcode);  // 将操作符推入栈
    }
    // 如果已经有两个操作数，进行计算，显示结果并等待新的输入
    else if (operands.size() == 2) {
        QString result = calculation();
        ui->display->setText(result);
        opcodes.push_back(opcode);  // 推入新的操作符
    }

    // 更新状态栏
    ui->statusbar->showMessage(QString("shu %1,fuhao %2").arg(operands.size()).arg(opcodes.size()));
}




void MainWindow::btnnumclick()
{
    QString digit = qobject_cast<QPushButton *>(sender())->text();
    if (digit == "0" && operand == "0")
        digit = "";
    if (operand == "0" && digit != "0")
        operand = "";
    operand += digit;
    ui->display->setText(operand);

}

void MainWindow::on_btnpoint_clicked()
{

    if (!operand.contains("."))
        operand += qobject_cast<QPushButton *>(sender())->text();
    ui->display->setText(operand);
}


void MainWindow::on_btndel_clicked()
{


    operand = operand.left(operand.length() - 1);
    ui->display->setText(operand);

}


void MainWindow::on_btnclear_clicked()
{
    operands.clear();
    opcode.clear();
    operand.clear();
    ui->display->setText(operand);
    ui->statusbar->showMessage(QString("shu %1, fuhao %2").arg(operands.size()).arg(opcodes.size()));
}

void MainWindow::btnunaryOperatorClicked()
{
    // 检查当前输入的操作数是否为空
    double result;
    if (operand != "") {
        // 使用当前输入的操作数
        result = operand.toDouble();
        operand = "";  // 清空当前输入
    } else if (!operands.isEmpty()) {
        // 如果没有输入，则取操作数栈中的最后一个操作数
        result = operands.top().toDouble();
    } else {
        // 如果操作数栈也为空，则直接返回，不做任何操作
        return;
    }

    QString op = qobject_cast<QPushButton *>(sender())->text();  // 获取操作符文本

    // 处理一元运算符
    if (op == "%") {
        result = result / 100.0; // 计算百分比
    } else if (op == "1/x") {
        if (result != 0) { // 避免除以零
            result = 1 / result;
        } else {
            ui->statusbar->showMessage("Error: Division by zero");
            return;
        }
    } else if (op == "x^2") {
        result *= result; // 计算平方
    } else if (op == "√") {
        if (result < 0) {
            ui->statusbar->showMessage("Error: Negative square root");
            return;
        }
        result = sqrt(result); // 计算平方根
    } else if (op == "±") { // 处理 ± 按钮
        result = -result;  // 切换符号
    }

    // 更新操作数栈
    if (!operands.isEmpty()) {
        operands.pop(); // 移除原来的值
    }
    operands.push(QString::number(result)); // 将新的值推入栈中

    // 更新显示框
    ui->display->setText(QString::number(result));

    // 更新状态栏显示，显示当前操作数和操作符的个数
    ui->statusbar->showMessage(QString("shu %1, fuhao %2").arg(operands.size()).arg(opcodes.size()));
}



void MainWindow::on_btnequal_clicked()
{
    // 如果有未处理的操作数，压入栈中
    if (operand != "") {
        operands.push_back(operand);
        operand = "";
    }

    // 如果栈中有足够的操作数和操作符，进行计算
    if (operands.size() >= 2 && opcodes.size() > 0) {
        QString result = calculation();  // 进行计算并获取结果
        ui->display->setText(result);    // 显示结果
    } else if (!operands.isEmpty()) {
        // 如果没有新的操作符输入，重复显示当前栈顶的结果
        ui->display->setText(operands.top());  // 保持显示栈顶的结果（最后一次运算结果）
    }

    // 清空操作符栈，准备新的运算
    opcodes.clear();

    // 更新状态栏显示，显示当前操作数和操作符的个数
    ui->statusbar->showMessage(QString("shu %1, fuhao %2").arg(operands.size()).arg(opcodes.size()));
}












void MainWindow::on_btnclearall_clicked()
{
    // 清除当前输入的操作数
    operand = ""; // 重置当前输入

    // 如果操作数栈不为空，则显示栈顶的操作数
    if (!operands.isEmpty()) {
        ui->display->setText(operands.top()); // 显示最后一个操作数
    } else {
        ui->display->setText("0"); // 如果没有操作数，则显示 0
    }

    // 更新状态栏显示，显示当前操作数和操作符的个数
    ui->statusbar->showMessage(QString("shu %1, fuhao %2").arg(operands.size()).arg(opcodes.size()));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    foreach (auto btnkey, digitbtns.keys()) {
        if (event->key() == btnkey)
            digitbtns[btnkey]->animateClick();
    }

    // 处理操作符按钮
    switch (event->key()) {
    case Qt::Key_Plus: // +

        ui->btnadd->animateClick(); // 假设 + 的索引为 0

        break;
    case Qt::Key_Minus: // -

        ui->btnminus->animateClick(); // 假设 - 的索引为 1

        break;
    case Qt::Key_Asterisk: // *

        ui->btnmultiple->animateClick(); // 假设 * 的索引为 2

        break;
    case Qt::Key_Slash: // /

        ui->btndivide->animateClick(); // 假设 / 的索引为 3

        break;
    case Qt::Key_Equal: // =

        ui->btnequal->animateClick(); // 假设 = 的按钮为 equalsButton

        break;
    case Qt::Key_Escape: // C

        ui->btnclear->animateClick(); // 假设 CE 的按钮为 clearButton

        break;
    case Qt::Key_Backspace:

        ui->btndel->animateClick(); // 假设 CE 的按钮为 clearButton

    default:
        break;
    }
}





