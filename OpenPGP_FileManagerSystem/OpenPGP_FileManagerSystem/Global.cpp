#include "head.h"
using namespace std;

//�ļ�λ��
Global::Global()
{
	Console.WriteLine("/***************************************************************/ ");
	Console.WriteLine("* ����ĿΪ���� OpenPGP ���ļ�����ϵͳ * ");
	Console.WriteLine("/***************************************************************/ \n");
	set_baseName();
	Console.WriteLine("\n Ӧ�����������ļ�����Ϣ");
	Console.WriteLine("---------------------------------------------------------------------------------------------------------- - ");
	System.IO.Directory.CreateDirectory(pathString);
	Console.WriteLine("��\"{0}\" �������ļ��У�\"���� OpenGPG ���ļ�ϵͳ\"�����ļ���\n", pathString);
	System.IO.Directory.CreateDirectory(pathStringUser);
	Console.WriteLine("��\"{0}\" �������ļ��У��û�{1}���û��ļ���\n", pathStringUser, Environment.UserName);
	System.IO.Directory.CreateDirectory(pathStringKey);
	Console.WriteLine("��\"{0}\" �������ļ��У��û�{1}����Կ�����Ե�����Կ���ļ���\n", pathStringKey, Environment.UserName);
	System.IO.Directory.CreateDirectory(pathStringFile);
	Console.WriteLine("��\"{0}\" �������ļ��У��û�{1}���ļ������ܡ����ܺ���ļ������ļ���", pathStringFile, Environment.UserName);
	Console.WriteLine("---------------------------------------------------------------------------------------------------------- - \n");
}
Global::~Global()//������������֤�ͷ�������Ϣ
{
}
void Global::set_baseName()
{
	Console.WriteLine("��������Ŀ�ļ��еĴ��λ�ã�Ĭ�ϣ�D:\\��,���� q ������");
	String basename = Console.ReadLine();
	if (basename == "q")
	{
		return;
	}
	else
	{
		baseName = basename;
		pathString = System.IO.Path.Combine(baseName, folderName);//���ļ���
		pathStringUser = System.IO.Path.Combine(pathString, Environment.UserName);//�û��ļ���
		pathStringKey = System.IO.Path.Combine(pathStringUser, folderName1);//�û���Կ�ļ���
		pathStringFile = System.IO.Path.Combine(pathStringUser, folderName2);//�û��ļ��ļ���
	}
}