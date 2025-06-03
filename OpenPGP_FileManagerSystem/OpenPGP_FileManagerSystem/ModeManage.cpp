#include "head.h"
#include<string>
using namespace std;


int ModeManage::mode_input(User user)
{
	while (true)
	{
		Console.WriteLine("ԭ��չʾ�밴 1���洢�ļ��밴 2�������ļ��밴 3");
		String Mode = Console.ReadLine();
		if (Mode == "1")
		{
			Console.WriteLine("\n ԭ��չʾ");
			Console.WriteLine("-----------------------------------------------------------------------------------------------------------");
			Console.WriteLine("������������Ҫ���ܵ����ݣ�������һ������\":wq\"����"); return 1;
		}
		else if (Mode == "2")
		{
			Console.WriteLine("\n �ļ��洢");
			Console.WriteLine("-----------------------------------------------------------------------------------------------------------");
			Console.WriteLine("�洢�ļ��İ�ȫģʽ�����Լ��밴 1�����û��밴 2");
			while (true)
			{
				String SubMode = Console.ReadLine();
				if (SubMode == "1") {
					Console.WriteLine("���ļ����û�{0}����������ֻ�����û�{0}�鿴", Environment.UserName);
					Console.WriteLine("�������ļ�·��"); return 21;
				}
				else if (SubMode == "2")
				{
					user.User_Authorization();
					Console.WriteLine("�������ļ�·��"); return 22;
				}
				else
				{
					Console.WriteLine("���������룡");
				}
			}
		}
		else if (Mode == "3")
		{
			Console.WriteLine("\n �ļ�����");
			Console.WriteLine("-----------------------------------------------------------------------------------------------------------");
			Console.WriteLine("�������ļ�·��(��׺Ϊ.gpg)"); return 3;
		}
		else
		{
			Console.WriteLine("���������룡");
		}
	}
}
void ModeManage::mode_control(int Mode, User user, String passwd)
{
	if (Mode == 1)
	{
		//���̶���
		String text = "";
		String input = Console.ReadLine();
		String next = Console.ReadLine(); while (true)
		{
			if (next == ":wq")
			{
				text = text + input;
				break;
			}
			else
			{
				text = text + input + "\r\n";
			}
			input = next; next = Console.ReadLine();
		}
		//ǩ�������ַ���
		FileManage fileManage = new FileManage();
		String after_string = fileManage.SignAndEncryptString(text, passwd, user.get_userID());
		Console.WriteLine("\n ����������ַ���Ϊ:\n{0}\n\n ������˽Կ��ǩ�����������Ĺ�Կ����ܣ��õ����ַ���Ϊ\n{ 1 }", text, after_string);
		//���ܲ���֤ǩ��
		fileManage.DecryptAndVerifyString(after_string, passwd, user.get_userID());
		Console.WriteLine("-----------------------------------------------------------------------------------------------------------\n");
	}
	else if (Mode == 21)
	{
		String File = Console.ReadLine(); while (true)
		{
			if (System.IO.File.Exists(File))
			{
				//�ļ�ǩ������
				FileManage fileManage = new FileManage(); user.detect_All_User_Public_key();
				string output_file = fileManage.SignAndEncryptSinge(passwd, File, user.get_userID());

				bool check = fileManage.Verify(passwd, output_file, user.get_all_Authorized_Uers_PublicKey(), user.get_all_Authorized_Users(), user.get_userID());
				if (check == false)
				{
					ClearTool clearTool = new ClearTool();
					clearTool.ClearDeletFile(output_file);
				}
				else
				{
					Console.WriteLine("�ļ��洢�ɹ��������û�\"{0}\"ǩ������\"{1}\" ��", Environment.UserName, output_file);
				}
				//fileManage.SignAndEncryptMultiple(passwd, File);
				Console.WriteLine("-----------------------------------------------------------------------------------------------------------\n");
				break;
			}
			else
			{
				Console.WriteLine("�ļ������ڣ������������ļ�·��");
				File = Console.ReadLine();
			}
		}
	}
	else if (Mode == 22)
	{
		String File = Console.ReadLine(); while (true)
		{
			if (System.IO.File.Exists(File))
			{
				//�ļ�ǩ������
				FileManage fileManage = new FileManage(); user.detect_All_User_Public_key();
				string output_file = fileManage.SignAndEncryptMultiple(passwd, File, user.get_all_Authorized_Uers_PublicKey(), user.get_userID());
				bool check = fileManage.Verify(passwd, output_file, user.get_all_Authorized_Uers_PublicKey(), user.get_all_Authorized_Users(), user.get_userID());
				if (check == false)
				{
					ClearTool clearTool = new ClearTool();
					clearTool.ClearDeletFile(output_file);

				}
				else
				{
					Console.WriteLine("�ļ��洢�ɹ��������û�\"{0}\"ǩ������\"{1}\" ��", Environment.UserName, output_file);
				}
				Console.WriteLine("-----------------------------------------------------------------------------------------------------------\n");
				break;
			}
			else
			{
				Console.WriteLine("�ļ������ڣ������������ļ�·��");
				File = Console.ReadLine();
			}
		}
	}
	else if (Mode == 3)
	{
		String File = Console.ReadLine(); while (true)
		{
			if (System.IO.File.Exists(File))
			{
				//�ļ�ǩ������
				FileManage fileManage = new FileManage(); user.detect_All_User_Public_key();
				Console.WriteLine(user.get_all_Authorized_Users().Length);
				fileManage.DecryptAndVerify(passwd, File, user.get_all_Authorized_Uers_PublicKey(), user.get_all_Authorized_Users(), user.get_userID());
				Console.WriteLine("-----------------------------------------------------------------------------------------------------------\n");
				break;
			}
			else
			{
				Console.WriteLine("�ļ������ڣ������������ļ�·��");
				File = Console.ReadLine();
			}
		}

	}
}