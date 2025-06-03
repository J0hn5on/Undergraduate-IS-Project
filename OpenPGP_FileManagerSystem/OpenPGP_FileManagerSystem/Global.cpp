#include "head.h"
using namespace std;

//文件位置
Global::Global()
{
	Console.WriteLine("/***************************************************************/ ");
	Console.WriteLine("* 本项目为基于 OpenPGP 的文件管理系统 * ");
	Console.WriteLine("/***************************************************************/ \n");
	set_baseName();
	Console.WriteLine("\n 应用所创建的文件夹信息");
	Console.WriteLine("---------------------------------------------------------------------------------------------------------- - ");
	System.IO.Directory.CreateDirectory(pathString);
	Console.WriteLine("在\"{0}\" 创建了文件夹：\"基于 OpenGPG 的文件系统\"的总文件夹\n", pathString);
	System.IO.Directory.CreateDirectory(pathStringUser);
	Console.WriteLine("在\"{0}\" 创建了文件夹：用户{1}的用户文件夹\n", pathStringUser, Environment.UserName);
	System.IO.Directory.CreateDirectory(pathStringKey);
	Console.WriteLine("在\"{0}\" 创建了文件夹：用户{1}的密钥（可以导出公钥）文件夹\n", pathStringKey, Environment.UserName);
	System.IO.Directory.CreateDirectory(pathStringFile);
	Console.WriteLine("在\"{0}\" 创建了文件夹：用户{1}的文件（加密、解密后的文件）的文件夹", pathStringFile, Environment.UserName);
	Console.WriteLine("---------------------------------------------------------------------------------------------------------- - \n");
}
Global::~Global()//析构函数，保证释放敏感信息
{
}
void Global::set_baseName()
{
	Console.WriteLine("请输入项目文件夹的存放位置（默认：D:\\）,输入 q 可跳过");
	String basename = Console.ReadLine();
	if (basename == "q")
	{
		return;
	}
	else
	{
		baseName = basename;
		pathString = System.IO.Path.Combine(baseName, folderName);//总文件夹
		pathStringUser = System.IO.Path.Combine(pathString, Environment.UserName);//用户文件夹
		pathStringKey = System.IO.Path.Combine(pathStringUser, folderName1);//用户密钥文件夹
		pathStringFile = System.IO.Path.Combine(pathStringUser, folderName2);//用户文件文件夹
	}
}