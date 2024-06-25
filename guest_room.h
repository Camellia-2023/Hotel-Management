#pragma once
#pragma once 
#include <string> 
#include<map> 
using namespace std;
//����enum ROOM_STATEö�����ͣ���ʾ�ͷ�״̬�����С���ס 
enum ROOM_STATE { FREE = 0, CHECK_IN };
//����ͷ��� 
class GuestRoom
{
public:
	GuestRoom() = default;       //�ṩĬ�Ϲ��캯�� 
	GuestRoom(string, int, int, int, ROOM_STATE);  //�вι��캯�� 
	string generate_number();      //���ɿͷ���� 
	string show_state();       //��ʾ�ͷ�״̬ 
	bool save_data(map<string, GuestRoom>&);   //�������� 
	map<string, GuestRoom> read_data();    //��ȡ���� 
public:
	string get_num();        //��ȡ�ͷ���� 
	string get_name();        //��ȡ�ͷ����� 
	int get_price();        //��ȡ�ͷ��۸� 
	int get_area();        //��ȡ�ͷ���� 
	int get_bed_num();        //��ȡ�ͷ���λ���� 
	void set_state();        //���ÿͷ�״̬ 
private:
	string m_number;        //�ͷ���� 
	int m_price;         //�ͷ��۸� 
	int m_area;         //�ͷ���� 
	int m_bed_number;        //�ͷ���λ���� 
	string m_name;         //�ͷ����� 
	enum  ROOM_STATE m_state;      //�ͷ�״̬ 
};