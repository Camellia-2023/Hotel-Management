#include "test_621.h"
#include <qtablewidget.h>
#include<iostream> 
#include<iomanip> 
#include <QMessageBox>
using namespace std;

test_621::test_621(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.textEdit_1->setVisible(false);
    ui.textEdit_2->setVisible(false);
    ui.textEdit_3->setVisible(false);
    ui.textEdit_4->setVisible(false);
    ui.pushButton_inputok->setVisible(false);
    //隐藏列表头
    ui.tableWidget->verticalHeader()->setVisible(false);
    //ui.tableWidget->horizontalHeader()->sectionResizeMode(QHeaderView::Stretch);

    state = 0;
 
}
void test_621::on_display_clicked()
{
    ui.tableWidget->clearContents(); // 清除数据但不删除项目
    ui.tableWidget->setColumnCount(6);
    ui.tableWidget->setColumnWidth(0, 70);
    ui.tableWidget->setColumnWidth(1, 120);
    ui.tableWidget->setColumnWidth(2, 120);
    ui.tableWidget->setColumnWidth(3, 120);
    ui.tableWidget->setColumnWidth(4, 70);
    ui.tableWidget->setColumnWidth(5, 50);
    QStringList header;
    header << QString::fromLocal8Bit("编号") << QString::fromLocal8Bit("名称") << QString::fromLocal8Bit("面积") <<
        QString::fromLocal8Bit("价格") << QString::fromLocal8Bit("床位数量") << QString::fromLocal8Bit("状态");
    ui.tableWidget->setHorizontalHeaderLabels(header);

    GuestRoom grm;
    map<string, GuestRoom> rooms;
    rooms = grm.read_data();
    if (rooms.empty())
    {
        QMessageBox::information(NULL, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("请添加客房信息后再进行操作！"),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }

    ui.tableWidget->setRowCount(rooms.size());
    int i = 0;
    for (auto& room : rooms)
    {
        ui.tableWidget->insertRow(i);		//按需求加行
        ui.tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromLocal8Bit(room.second.get_num().c_str())));
        ui.tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromLocal8Bit(room.second.get_name().c_str())));
        ui.tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromLocal8Bit((to_string(room.second.get_area())+"平方").c_str())));
        ui.tableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromLocal8Bit((to_string(room.second.get_price())+"元").c_str())));
        ui.tableWidget->setItem(i, 4, new QTableWidgetItem(QString::fromLocal8Bit((to_string(room.second.get_bed_num())+"个").c_str())));
        ui.tableWidget->setItem(i, 5, new QTableWidgetItem(QString::fromLocal8Bit(room.second.show_state().c_str())));
        i++;
    }
    ui.textEdit_1->setVisible(false);
    ui.textEdit_2->setVisible(false);
    ui.textEdit_3->setVisible(false);
    ui.textEdit_4->setVisible(false);
    ui.pushButton_inputok->setVisible(false);
    ui.label_state->setVisible(true);
    ui.label_state->setText(QString::fromLocal8Bit("已成功显示所有客房数据"));

}
void test_621::on_pushButton_inputok_clicked()
{
    if (state == 1)
    {
        name = ui.textEdit_1->toPlainText().toStdString();
        price = ui.textEdit_2->toPlainText().toInt();
        bed_num = ui.textEdit_3->toPlainText().toInt();
        area = ui.textEdit_4->toPlainText().toInt();
        if (!name.empty() && price && bed_num && area)
        {
            GuestRoom room(name, price, bed_num, area, FREE);
            // 调用客房管理模块的add_room()函数添加客房 
            m_grm.add_room(room);
            ui.textEdit_1->setVisible(false);
            ui.textEdit_2->setVisible(false);
            ui.textEdit_3->setVisible(false);
            ui.textEdit_4->setVisible(false);
            ui.pushButton_inputok->setVisible(false);
            ui.label_state->setVisible(true);
            ui.label_state->setText(QString::fromLocal8Bit("已成功添加客房数据"));
        }
        else {
            QMessageBox::information(NULL, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("请输入客房信息"),
                QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        }
    }
    else if (state == 2)
    {
        room_number = ui.textEdit_2->toPlainText().toStdString();
        // 调用客房管理模块的remove_data()函数 
        if (!room_number.empty())
        {
            m_grm.remove_data(room_number);
            ui.textEdit_1->setVisible(false);
            ui.textEdit_2->setVisible(false);
            ui.textEdit_3->setVisible(false);
            ui.textEdit_4->setVisible(false);
            ui.pushButton_inputok->setVisible(false);
            ui.label_state->setVisible(true);
            ui.label_state->setText(QString::fromLocal8Bit("已成功删除客房数据"));
        }
        else {
            QMessageBox::information(NULL, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("请输入客房信息"),
                QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        }

    }
    else if (state == 3)
    {
        number = ui.textEdit_2->toPlainText().toStdString();
        // 调用客房管理模块的remove_data()函数 
        if (!number.empty())
        {
            m_grm.set_room_state(number);
            ui.textEdit_1->setVisible(false);
            ui.textEdit_2->setVisible(false);
            ui.textEdit_3->setVisible(false);
            ui.textEdit_4->setVisible(false);
            ui.pushButton_inputok->setVisible(false);
            ui.label_state->setVisible(true);
            ui.label_state->setText(QString::fromLocal8Bit("已成功设置客房数据"));
        }
        else {
            QMessageBox::information(NULL, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("请输入客房信息"),
                QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        }
    }
    else {
        cout << "input erro!" << endl;
        return;
    }

}
void test_621::on_adding_clicked() {
    state = 1;
    ui.label_state->setVisible(false);
    ui.textEdit_1->setVisible(true);
    ui.textEdit_1->clear();
    ui.textEdit_1->setPlaceholderText(QString::fromLocal8Bit("请输入客房名称"));
    ui.textEdit_2->setVisible(true);
    ui.textEdit_2->clear();
    ui.textEdit_2->setPlaceholderText(QString::fromLocal8Bit("请输入客房价格"));
    ui.textEdit_3->setVisible(true);
    ui.textEdit_3->clear();
    ui.textEdit_3->setPlaceholderText(QString::fromLocal8Bit("请输入客房床数量"));
    ui.textEdit_4->setVisible(true);
    ui.textEdit_4->clear();
    ui.textEdit_4->setPlaceholderText(QString::fromLocal8Bit("请输入客房面积"));
    ui.pushButton_inputok->setVisible(true);


}
void test_621::on_delete_2_clicked() {
    state = 2;
    ui.label_state->setVisible(false);
    ui.pushButton_inputok ->setVisible(true);
    ui.textEdit_2->setVisible(true);
    ui.textEdit_2->clear();
    ui.textEdit_2->setPlaceholderText(QString::fromLocal8Bit("请输入您要删除的客房编号"));

}
void test_621::on_seting_clicked()
{
    state = 3;
    ui.label_state->setVisible(false);
    ui.pushButton_inputok->setVisible(true);
    ui.textEdit_2->setVisible(true);
    ui.textEdit_2->clear();
    ui.textEdit_2->setPlaceholderText(QString::fromLocal8Bit("请输入要设置的客房编号"));
}
void test_621::on_close_clicked()
{
    this->close(); 
}

test_621::~test_621()
{}
