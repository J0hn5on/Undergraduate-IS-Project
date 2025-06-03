#include "head.h"
using namespace std;


User::User()
{
	username = Environment.UserName;
	WindowsIdentity windowsIdentity = WindowsIdentity.GetCurrent();
	sid = windowsIdentity.User; userID = get_userID();
	Console.WriteLine("当前用户信息");
}
User::~User() //析构函数，保证释放敏感信息
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
	//设置能够访问到的 all_Authorized_Uers_PublicKey;
void User::User_Authorization()
{
	string[] all_Uers_pathString = Directory.GetDirectories(Global.pathString);//用户文件夹目
	录
		if (all_Uers_pathString.Length == 1)
		{
			Console.WriteLine("目前该文件系统未检测到其他用户");
		}
	List<string> _ulist = new List<string>{ Environment.UserName };
	List<string> _list = new List<string>{ Path.Combine(Global.pathStringKey, "public_key_exported.asc") };
	foreach(string element in all_Uers_pathString)
	{
		String name = Path.GetFileName(element);
		String publicKey = Path.Combine(Global.pathString, name, Global.folderName1, "public_key_exported.asc");//用户公钥文件
		if (name != Environment.UserName && File.Exists(publicKey))
		{
			Console.WriteLine("检测到用户{0}", name);
			Console.WriteLine("您是否要为用户{0}开放该文件的调阅权限？（Y/N）", name);
			String answer = Console.ReadLine(); while (true)
			{
				if ((answer == "Y") || (answer == "y"))
				{
					_ulist.Add(name); _list.Add(publicKey);

					Console.WriteLine("为用户{0}开放该文件的调阅权限成功", name);
					break;
				}
				else if ((answer == "N") || (answer == "n"))
				{
					Console.WriteLine("为用户{0}开放该文件的调阅权限失败", name);
					break;
				}
				else
				{
					Console.WriteLine("请正确输入！");
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
	string[] all_Uers_pathString = Directory.GetDirectories(Global.pathString);//用户文件夹目
	录
		foreach(string element in all_Uers_pathString)
	{
		String name = Path.GetFileName(element);
		String publicKey = Path.Combine(Global.pathString, name, Global.folderName1, "public_key_exported.asc");//用户公钥文件
		if (File.Exists(publicKey))
		{
			_ulist.Add(name); _list.Add(publicKey);
		}
	}
	all_Authorized_Users = _ulist.ToArray();
	all_Authorized_Uers_PublicKey = _list.ToArray();

}
