#pragma once

#include<string>


class Global {
	static String baseName = "D:\\";
	static String folderName = "OpenPGP_File_Manage_show";
	static String folderName1 = "Key";
	static String folderName2 = "File";
	static String pathString = System.IO.Path.Combine(baseName, folderName);//���ļ���
	static String pathStringUser = System.IO.Path.Combine(pathString, Environment.UserName);//�û��ļ���
	static String pathStringKey = System.IO.Path.Combine(pathStringUser, folderName1);//�û���Կ�ļ���
	static String pathStringFile = System.IO.Path.Combine(pathStringUser, folderName2);//�û��ļ��ļ���
	Global();
	~Global();
	void set_baseName();

};
class User {
private:
	String username;//�û���
	SecurityIdentifier sid;//�û���ȫ��ʶ��
	String userID;
	string[] all_Authorized_Users;
	string[] all_Authorized_Uers_PublicKey;//�����û�Ŀ¼�ļ�
	User();
	~User();//������������֤�ͷ�������Ϣ
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
	~Program();//������������֤�ͷ�������Ϣ
	static void Main(string[] args);


};
class ModeManage {
	~ModeManage();//������������֤�ͷ�������Ϣ
public:
	int mode_input(User user);
	void mode_control(int Mode, User user, String passwd);




};
class KeyManage {
	~KeyManage();//������������֤�ͷ�������Ϣ
	//RSA ��Կ����
	void GenerateKeyPairRSA(String userID, String passwd);
	//������Կ
	void ExportPublicKey(String userID, String passwd);
	//����˽Կ
	void ExportPrivateKey(String userID, String passwd);
	//�����ʾ���������� GnuPG/gpg �ķ�ʽ�г�����ӡ��Կ��
	void KeyStoreListKeys(String passwd);



};
class FileManage {
	~FileManage();//������������֤�ͷ�������Ϣ
public:
	//ǩ���ͼ��ܣ����ˣ�
	string SignAndEncryptMultiple(String passwd, String File, string[]all_Authorized_Uers_PublicKey, String userID);
	//ǩ���ͼ��ܣ����ˣ�
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
	/// ���Ŀ¼���ļ�
	/// </summary>
	void ClearDelet(string path);
	/// <summary>
	/// �����Ŀ¼�е������ļ�����Ŀ¼���ݣ���ɾ����ǰĿ¼
	/// </summary>
	void ClearDeletDirectory(string dir);
	/// <summary>
	/// ������ļ����ݣ���ɾ��
	/// </summary>
	void ClearDeletFile(string file);
	/// <summary>
	/// ����ļ�����
	/// </summary>
	static void ClearFile(string file);



};