#include "head.h"
using namespace std;


User::User()
{
	username = Environment.UserName;
	WindowsIdentity windowsIdentity = WindowsIdentity.GetCurrent();
	sid = windowsIdentity.User; userID = get_userID();
	Console.WriteLine("��ǰ�û���Ϣ");
}
User::~User() //������������֤�ͷ�������Ϣ
	{
	}

String User::get_username()
{
	return username;
}
SecurityIdentifier User::get_sid()
{
	return sid;
}
String User::get_userID()
{
	PGPLib pgp = new PGPLib();
	pgp.Hash = HashAlgorithm.MD5; userID = sid.GetHashCode().ToString(); return userID;
}
string[] User::get_all_Authorized_Users()
{
	return all_Authorized_Users;
}
string[] User::get_all_Authorized_Uers_PublicKey()
{
	return all_Authorized_Uers_PublicKey;
}
	//�����ܹ����ʵ��� all_Authorized_Uers_PublicKey;
void User::User_Authorization()
{
	string[] all_Uers_pathString = Directory.GetDirectories(Global.pathString);//�û��ļ���Ŀ
	¼
		if (all_Uers_pathString.Length == 1)
		{
			Console.WriteLine("Ŀǰ���ļ�ϵͳδ��⵽�����û�");
		}
	List<string> _ulist = new List<string>{ Environment.UserName };
	List<string> _list = new List<string>{ Path.Combine(Global.pathStringKey, "public_key_exported.asc") };
	foreach(string element in all_Uers_pathString)
	{
		String name = Path.GetFileName(element);
		String publicKey = Path.Combine(Global.pathString, name, Global.folderName1, "public_key_exported.asc");//�û���Կ�ļ�
		if (name != Environment.UserName && File.Exists(publicKey))
		{
			Console.WriteLine("��⵽�û�{0}", name);
			Console.WriteLine("���Ƿ�ҪΪ�û�{0}���Ÿ��ļ��ĵ���Ȩ�ޣ���Y/N��", name);
			String answer = Console.ReadLine(); while (true)
			{
				if ((answer == "Y") || (answer == "y"))
				{
					_ulist.Add(name); _list.Add(publicKey);

					Console.WriteLine("Ϊ�û�{0}���Ÿ��ļ��ĵ���Ȩ�޳ɹ�", name);
					break;
				}
				else if ((answer == "N") || (answer == "n"))
				{
					Console.WriteLine("Ϊ�û�{0}���Ÿ��ļ��ĵ���Ȩ��ʧ��", name);
					break;
				}
				else
				{
					Console.WriteLine("����ȷ���룡");
					answer = Console.ReadLine();
				}
			}
		}
	}
	all_Authorized_Users = _ulist.ToArray();
	all_Authorized_Uers_PublicKey = _list.ToArray();
}

void User::detect_All_User_Public_key()
{
	List<string> _ulist = new List<string>{};
	List<string> _list = new List<string>{};
	string[] all_Uers_pathString = Directory.GetDirectories(Global.pathString);//�û��ļ���Ŀ
	¼
		foreach(string element in all_Uers_pathString)
	{
		String name = Path.GetFileName(element);
		String publicKey = Path.Combine(Global.pathString, name, Global.folderName1, "public_key_exported.asc");//�û���Կ�ļ�
		if (File.Exists(publicKey))
		{
			_ulist.Add(name); _list.Add(publicKey);
		}
	}
	all_Authorized_Users = _ulist.ToArray();
	all_Authorized_Uers_PublicKey = _list.ToArray();

}
