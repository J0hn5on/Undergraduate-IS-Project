#include "head.h"
using namespace std;


void Program::Main(string[] args)
{
	//展示文件夹创建
	Global global = new Global();
	//用户创建
	User user = new User();
	String userID = user.get_userID();
	//密钥生成和导出
	KeyManage keyManage = new KeyManage();
	//密码唯一，且由用户的用户名和安全序列号唯一生成
	String passwd = (user.get_username() + user.get_sid()).GetHashCode().ToString();
	keyManage.GenerateKeyPairRSA(userID, passwd);
	keyManage.ExportPublicKey(userID, passwd);
	//keyManage.ExportPrivateKey(userID, passwd);//私钥敏感信息不能导出
	keyManage.KeyStoreListKeys(passwd);
	//模式选择：原理展示/存储模式/调阅模式
	//用户界面
	while (true)
	{
		ModeManage modeManage = new ModeManage();
		int Mode = modeManage.mode_input(user); modeManage.mode_control(Mode, user, passwd);
		Console.WriteLine("程序已结束，按 q 退出，按其他任意键返回用户界面...");
		if (Console.ReadLine() == "q")
			break;
	}
}