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
    //�����б�ͷ
    ui.tableWidget->verticalHeader()->setVisible(false);
    //ui.tableWidget->horizontalHeader()->sectionResizeMode(QHeaderView::Stretch);

    state = 0;
 
}
void test_621::on_display_clicked()
{
    ui.tableWidget->clearContents(); // ������ݵ���ɾ����Ŀ
    ui.tableWidget->setColumnCount(6);
    ui.tableWidget->setColumnWidth(0, 70);
    ui.tableWidget->setColumnWidth(1, 120);
    ui.tableWidget->setColumnWidth(2, 120);
    ui.tableWidget->setColumnWidth(3, 120);
    ui.tableWidget->setColumnWidth(4, 70);
    ui.tableWidget->setColumnWidth(5, 50);
    QStringList header;
    header << QString::fromLocal8Bit("���") << QString::fromLocal8Bit("����") << QString::fromLocal8Bit("���") <<
        QString::fromLocal8Bit("�۸�") << QString::fromLocal8Bit("��λ����") << QString::fromLocal8Bit("״̬");
    ui.tableWidget->setHorizontalHeaderLabels(header);

    GuestRoom grm;
    map<string, GuestRoom> rooms;
    rooms = grm.read_data();
    if (rooms.empty())
    {
        QMessageBox::information(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����ӿͷ���Ϣ���ٽ��в�����"),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }

    ui.tableWidget->setRowCount(rooms.size());
    int i = 0;
    for (auto& room : rooms)
    {
        ui.tableWidget->insertRow(i);		//���������
        ui.tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromLocal8Bit(room.second.get_num().c_str())));
        ui.tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromLocal8Bit(room.second.get_name().c_str())));
        ui.tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromLocal8Bit((to_string(room.second.get_area())+"ƽ��").c_str())));
        ui.tableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromLocal8Bit((to_string(room.second.get_price())+"Ԫ").c_str())));
        ui.tableWidget->setItem(i, 4, new QTableWidgetItem(QString::fromLocal8Bit((to_string(room.second.get_bed_num())+"��").c_str())));
        ui.tableWidget->setItem(i, 5, new QTableWidgetItem(QString::fromLocal8Bit(room.second.show_state().c_str())));
        i++;
    }
    ui.textEdit_1->setVisible(false);
    ui.textEdit_2->setVisible(false);
    ui.textEdit_3->setVisible(false);
    ui.textEdit_4->setVisible(false);
    ui.pushButton_inputok->setVisible(false);
    ui.label_state->setVisible(true);
    ui.label_state->setText(QString::fromLocal8Bit("�ѳɹ���ʾ���пͷ�����"));

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
            // ���ÿͷ�����ģ���add_room()������ӿͷ� 
            m_grm.add_room(room);
            ui.textEdit_1->setVisible(false);
            ui.textEdit_2->setVisible(false);
            ui.textEdit_3->setVisible(false);
            ui.textEdit_4->setVisible(false);
            ui.pushButton_inputok->setVisible(false);
            ui.label_state->setVisible(true);
            ui.label_state->setText(QString::fromLocal8Bit("�ѳɹ���ӿͷ�����"));
        }
        else {
            QMessageBox::information(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("������ͷ���Ϣ"),
                QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        }
    }
    else if (state == 2)
    {
        room_number = ui.textEdit_2->toPlainText().toStdString();
        // ���ÿͷ�����ģ���remove_data()���� 
        if (!room_number.empty())
        {
            m_grm.remove_data(room_number);
            ui.textEdit_1->setVisible(false);
            ui.textEdit_2->setVisible(false);
            ui.textEdit_3->setVisible(false);
            ui.textEdit_4->setVisible(false);
            ui.pushButton_inputok->setVisible(false);
            ui.label_state->setVisible(true);
            ui.label_state->setText(QString::fromLocal8Bit("�ѳɹ�ɾ���ͷ�����"));
        }
        else {
            QMessageBox::information(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("������ͷ���Ϣ"),
                QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        }

    }
    else if (state == 3)
    {
        number = ui.textEdit_2->toPlainText().toStdString();
        // ���ÿͷ�����ģ���remove_data()���� 
        if (!number.empty())
        {
            m_grm.set_room_state(number);
            ui.textEdit_1->setVisible(false);
            ui.textEdit_2->setVisible(false);
            ui.textEdit_3->setVisible(false);
            ui.textEdit_4->setVisible(false);
            ui.pushButton_inputok->setVisible(false);
            ui.label_state->setVisible(true);
            ui.label_state->setText(QString::fromLocal8Bit("�ѳɹ����ÿͷ�����"));
        }
        else {
            QMessageBox::information(NULL, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("������ͷ���Ϣ"),
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
    ui.textEdit_1->setPlaceholderText(QString::fromLocal8Bit("������ͷ�����"));
    ui.textEdit_2->setVisible(true);
    ui.textEdit_2->clear();
    ui.textEdit_2->setPlaceholderText(QString::fromLocal8Bit("������ͷ��۸�"));
    ui.textEdit_3->setVisible(true);
    ui.textEdit_3->clear();
    ui.textEdit_3->setPlaceholderText(QString::fromLocal8Bit("������ͷ�������"));
    ui.textEdit_4->setVisible(true);
    ui.textEdit_4->clear();
    ui.textEdit_4->setPlaceholderText(QString::fromLocal8Bit("������ͷ����"));
    ui.pushButton_inputok->setVisible(true);


}
void test_621::on_delete_2_clicked() {
    state = 2;
    ui.label_state->setVisible(false);
    ui.pushButton_inputok ->setVisible(true);
    ui.textEdit_2->setVisible(true);
    ui.textEdit_2->clear();
    ui.textEdit_2->setPlaceholderText(QString::fromLocal8Bit("��������Ҫɾ���Ŀͷ����"));

}
void test_621::on_seting_clicked()
{
    state = 3;
    ui.label_state->setVisible(false);
    ui.pushButton_inputok->setVisible(true);
    ui.textEdit_2->setVisible(true);
    ui.textEdit_2->clear();
    ui.textEdit_2->setPlaceholderText(QString::fromLocal8Bit("������Ҫ���õĿͷ����"));
}
void test_621::on_close_clicked()
{
    this->close(); 
}

test_621::~test_621()
{}
