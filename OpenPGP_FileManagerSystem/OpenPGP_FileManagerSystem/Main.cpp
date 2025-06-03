#include "head.h"
using namespace std;


void Program::Main(string[] args)
{
	//չʾ�ļ��д���
	Global global = new Global();
	//�û�����
	User user = new User();
	String userID = user.get_userID();
	//��Կ���ɺ͵���
	KeyManage keyManage = new KeyManage();
	//����Ψһ�������û����û����Ͱ�ȫ���к�Ψһ����
	String passwd = (user.get_username() + user.get_sid()).GetHashCode().ToString();
	keyManage.GenerateKeyPairRSA(userID, passwd);
	keyManage.ExportPublicKey(userID, passwd);
	//keyManage.ExportPrivateKey(userID, passwd);//˽Կ������Ϣ���ܵ���
	keyManage.KeyStoreListKeys(passwd);
	//ģʽѡ��ԭ��չʾ/�洢ģʽ/����ģʽ
	//�û�����
	while (true)
	{
		ModeManage modeManage = new ModeManage();
		int Mode = modeManage.mode_input(user); modeManage.mode_control(Mode, user, passwd);
		Console.WriteLine("�����ѽ������� q �˳�������������������û�����...");
		if (Console.ReadLine() == "q")
			break;
	}
}