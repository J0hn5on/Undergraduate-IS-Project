#pragma once

#include<string>


class Global {
	static String baseName = "D:\\";
	static String folderName = "OpenPGP_File_Manage_show";
	static String folderName1 = "Key";
	static String folderName2 = "File";
	static String pathString = System.IO.Path.Combine(baseName, folderName);//总文件夹
	static String pathStringUser = System.IO.Path.Combine(pathString, Environment.UserName);//用户文件夹
	static String pathStringKey = System.IO.Path.Combine(pathStringUser, folderName1);//用户密钥文件夹
	static String pathStringFile = System.IO.Path.Combine(pathStringUser, folderName2);//用户文件文件夹
	Global();
	~Global();
	void set_baseName();

};
class User {
private:
	String username;//用户名
	SecurityIdentifier sid;//用户安全标识符
	String userID;
	string[] all_Authorized_Users;
	string[] all_Authorized_Uers_PublicKey;//所有用户目录文件
	User();
	~User();//析构函数，保证释放敏感信息
public:
	String get_username();
	SecurityIdentifier get_sid();
	String get_userID();
	string[] get_all_Authorized_Users();
	string[] get_all_Authorized_Uers_PublicKey();
	void User_Authorization();
	void detect_All_User_Public_key();

};;
class Program {
	~Program();//析构函数，保证释放敏感信息
	static void Main(string[] args);


};
class ModeManage {
	~ModeManage();//析构函数，保证释放敏感信息
public:
	int mode_input(User user);
	void mode_control(int Mode, User user, String passwd);




};
class KeyManage {
	~KeyManage();//析构函数，保证释放敏感信息
	//RSA 密钥生成
	void GenerateKeyPairRSA(String userID, String passwd);
	//导出公钥
	void ExportPublicKey(String userID, String passwd);
	//导出私钥
	void ExportPrivateKey(String userID, String passwd);
	//下面的示例以类似于 GnuPG/gpg 的方式列出并打印密钥：
	void KeyStoreListKeys(String passwd);



};
class FileManage {
	~FileManage();//析构函数，保证释放敏感信息
public:
	//签名和加密（多人）
	string SignAndEncryptMultiple(String passwd, String File, string[]all_Authorized_Uers_PublicKey, String userID);
	//签名和加密（单人）
	string SignAndEncryptSinge(String passwd, String File, String userID);

	String SignAndEncryptString(String plainText, String passwd, String userID);
	bool Verify(String passwd, String File, string[] All_User_Public_key, string[] All_Users, String userID);
	void DecryptAndVerify(String passwd, String File, string[] All_User_Public_key, string[] All_Users, String userID);
	void DecryptAndVerifyString(String signedAndEncryptedMessage, String passwd, String userID);


};
class ClearTool {
	~ClearTool();
public:
	/// <summary>
	/// 清空目录或文件
	/// </summary>
	void ClearDelet(string path);
	/// <summary>
	/// 先清空目录中的所有文件和子目录内容，再删除当前目录
	/// </summary>
	void ClearDeletDirectory(string dir);
	/// <summary>
	/// 先清空文件内容，再删除
	/// </summary>
	void ClearDeletFile(string file);
	/// <summary>
	/// 清空文件内容
	/// </summary>
	static void ClearFile(string file);



};