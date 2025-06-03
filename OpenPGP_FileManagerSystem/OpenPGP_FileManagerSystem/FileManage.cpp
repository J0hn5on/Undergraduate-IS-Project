#include "head.h"
using namespace std;
using DidiSoft.Pgp;

stringFileManageSignAndEncryptMultiple(String passwd, String File, string[]all_Authorized_Uers_PublicKey, String userID)
{
	//��ȡ�ļ�����������չ����
	String extension = Path.GetExtension(File);
	String fileNameWithoutExtension = Path.GetFileNameWithoutExtension(File);// û����չ�����ļ��� "default" 
	String fileNameRandom = Path.GetRandomFileName();
	String fileNameRandomWithoutExtension = Path.GetFileNameWithoutExtension(fileNameRandom);
	String newFile = fileNameWithoutExtension + fileNameRandomWithoutExtension + extension + ".gpg";
	// create an instance of the library
	PGPLib pgp = new PGPLib();
	// ASCII armor or binary
	bool asciiArmor = true;
	// append integrity protection check, set to true for compatibility with GnuPG 2.2.8+
	bool withIntegrityCheck = false;
	//�ļ�Ŀ¼
	string[] input_file = { @File };
	String file_public_key = System.IO.Path.Combine(Global.pathStringKey, "public_key_exported.asc");
	String file_private_key = System.IO.Path.Combine(Global.pathStringKey, "private_key_exported.asc");
	String output_file = System.IO.Path.Combine(Global.pathStringFile, newFile);
	string[] recipientsPublicKeys = all_Authorized_Uers_PublicKey;
	KeyManage keyManage = new KeyManage();
	keyManage.ExportPrivateKey(userID, passwd);//����˽Կ
	ClearTool clearTool = new ClearTool();
	pgp.SignAndEncryptFiles(@input_file, file_private_key, passwd, recipientsPublicKeys, @output_file, asciiArmor, withIntegrityCheck);
	clearTool.ClearDeletFile(file_private_key);//ɾ��˽Կ������Ϣ
	return output_file;
}
	//ǩ���ͼ��ܣ����ˣ�
string FileManage::SignAndEncryptSinge(String passwd, String File, String userID)
{
	//��ȡ�ļ�����������չ����
	String extension = Path.GetExtension(File);
	String fileNameWithoutExtension = Path.GetFileNameWithoutExtension(File);// û����չ�����ļ��� "default" 
	String fileNameRandom = Path.GetRandomFileName();
	String fileNameRandomWithoutExtension = Path.GetFileNameWithoutExtension(fileNameRandom);
	String newFile = fileNameWithoutExtension + fileNameRandomWithoutExtension + extension + ".gpg";
	// create an instance of the library
	PGPLib pgp = new PGPLib();
	// is output ASCII or binary
	bool asciiArmor = true;
	// should integrity check information be added, set to true for compatibility with GnuPG2.2.8 +
	bool withIntegrityCheck = false;
	//�ļ�Ŀ¼
	String input_file = File;
	String file_public_key = System.IO.Path.Combine(Global.pathStringKey, "public_key_exported.asc");
	String file_private_key = System.IO.Path.Combine(Global.pathStringKey, "private_key_exported.asc");
	String output_file = System.IO.Path.Combine(Global.pathStringFile, newFile);
	KeyManage keyManage = new KeyManage();
	keyManage.ExportPrivateKey(userID, passwd);//����˽Կ
	ClearTool clearTool = new ClearTool();
	// sign and encrypt
	pgp.SignAndEncryptFile(@input_file, @file_private_key, passwd, @file_public_key, @output_file, asciiArmor, withIntegrityCheck);
	clearTool.ClearDeletFile(file_private_key);//ɾ��˽Կ������Ϣ
	return output_file;
}

String FileManage::SignAndEncryptString(String plainText, String passwd, String userID)
{
	// create an instance of the library
	PGPLib pgp = new PGPLib();
	String file_public_key = System.IO.Path.Combine(Global.pathStringKey, "public_key_exported.asc");
	String file_private_key = System.IO.Path.Combine(Global.pathStringKey, "private_key_exported.asc");
	KeyManage keyManage = new KeyManage();
	keyManage.ExportPrivateKey(userID, passwd);//����˽Կ
	ClearTool clearTool = new ClearTool();
	// sign and enrypt
	String encryptedAndSignedString = pgp.SignAndEncryptString(plainText, new FileInfo(file_private_key), passwd, new FileInfo(file_public_key));
	clearTool.ClearDeletFile(file_private_key);//ɾ��˽Կ������Ϣ
	return encryptedAndSignedString;
}
bool FileManage::Verify(String passwd, String File, string[] All_User_Public_key, string[] All_Users, String userID)
{
	String originalFile = Path.GetFileNameWithoutExtension(File);
	String extension = Path.GetExtension(File); //-->.txt
	String filetmp = originalFile + "Tmp" + extension;
	// create an instance of the library
	PGPLib pgp = new PGPLib();
	//�ļ�Ŀ¼
	String input_file = File;//gpg
	String file_private_key = System.IO.Path.Combine(Global.pathStringKey, "private_key_exported.asc");
	String output_file = System.IO.Path.Combine(Global.pathStringFile, filetmp);
	KeyManage keyManage = new KeyManage();
	keyManage.ExportPrivateKey(userID, passwd);//����˽Կ
	ClearTool clearTool = new ClearTool();
	for (int i = 0; i < All_Users.Length; i++)
	{
		// check the signature and extract the data
		//The supplied data is not only signed but also encrypted. Please use the
		DecryptAndVerify or Decrypt methods in order to extract the encrypted contents.��
			//���ֻ���Ƚ�������֤ǩ��
			SignatureCheckResult signatureCheck =
			pgp.DecryptAndVerifyFile(@input_file, @file_private_key, passwd, @All_User_Public_key[i], @output_file);
		clearTool.ClearDeletFile(file_private_key);//ɾ��˽Կ������Ϣ
		clearTool.ClearDeletFile(output_file);
		if (signatureCheck == SignatureCheckResult.SignatureVerified && All_Users[i] == Environment.UserName)
		{
			Console.WriteLine($"�����֤�ɹ����������Ϊ{All_Users[i]},�����ļ��ɹ�");
			return true;
		}
		else
		{
			Console.WriteLine($"�����֤ʧ�ܣ��������Ϊ{All_Users[i]},�����ļ�ʧ��");
			return false;
		}
	}
	return false;
}
void FileManage::DecryptAndVerify(String passwd, String File, string[] All_User_Public_key, string[] All_Users, String userID)
{
	String originalFile = Path.GetFileName(File);
	// create an instance of the library
	PGPLib pgp = new PGPLib();
	//�ļ�Ŀ¼
	String input_file = File;//gpg
	String file_private_key = System.IO.Path.Combine(Global.pathStringKey, "private_key_exported.asc");
	String output_file = System.IO.Path.Combine(Global.pathStringFile, originalFile);
	KeyManage keyManage = new KeyManage();
	keyManage.ExportPrivateKey(userID, passwd);//����˽Կ
	ClearTool clearTool = new ClearTool();
	// decrypt and obtain the original file name
	// of the decrypted file
	string originalFileName =
		pgp.DecryptFile(@input_file, @file_private_key, passwd, @output_file);
	Console.WriteLine("�������Ϊ�û�\"{0}\"", Environment.UserName);
	Console.WriteLine("�ļ����ĳɹ���ԭ�ļ���Ϊ{0},���ܺ���ļ���{1}��", originalFileName, output_file);
	for (int i = 0; i < All_Users.Length; i++)
	{
		// check the signature and extract the data
		//The supplied data is not only signed but also encrypted. Please use the
		DecryptAndVerify or Decrypt methods in order to extract the encrypted contents.��
			//���ֻ���Ƚ�������֤ǩ��
			SignatureCheckResult signatureCheck =
			pgp.DecryptAndVerifyFile(@input_file, @file_private_key, passwd, @All_User_Public_key[i], @output_file);
		clearTool.ClearDeletFile(file_private_key);//ɾ��˽Կ������Ϣ
		if (signatureCheck == SignatureCheckResult.SignatureVerified)
		{
			Console.WriteLine("ǩ����֤�ɹ������ļ������û�{0}������", All_Users[i]);
			break;
		}
		else if (signatureCheck == SignatureCheckResult.NoSignatureFound)
		{
			Console.WriteLine("���ļ�δ����ǩ��");
			break;
		}
		else if (signatureCheck == SignatureCheckResult.SignatureBroken)
		{
			Console.WriteLine("�ļ���ǩ�����𻵻�α�� ");
			break;
		}
		else if (i == All_Users.Length - 1 && signatureCheck ==
			SignatureCheckResult.PublicKeyNotMatching)
		{
			Console.WriteLine("�ṩ�Ĺ�Կ��ǩ����ƥ��");
		}
	}
}
void FileManage::DecryptAndVerifyString(String signedAndEncryptedMessage, String passwd, String userID)
{

	String file_public_key = System.IO.Path.Combine(Global.pathStringKey, "public_key_exported.asc");
	String file_private_key = System.IO.Path.Combine(Global.pathStringKey, "private_key_exported.asc");
	String plainTextExtracted;
	// create an instance of the library
	PGPLib pgp = new PGPLib();
	KeyManage keyManage = new KeyManage();
	keyManage.ExportPrivateKey(userID, passwd);//����˽Կ
	ClearTool clearTool = new ClearTool();
	// decrypt and verify
	SignatureCheckResult signatureCheck =
		pgp.DecryptAndVerifyString(signedAndEncryptedMessage, new FileInfo(@file_private_key), passwd, new FileInfo(@file_public_key), out plainTextExtracted);
	clearTool.ClearDeletFile(file_private_key);//ɾ��˽Կ������Ϣ
	// print the results
	if (signatureCheck == SignatureCheckResult.SignatureVerified)
	{
		Console.WriteLine("ǩ����֤�ɹ�");
	}
	else if (signatureCheck == SignatureCheckResult.SignatureBroken)
	{
		Console.WriteLine("�ļ���ǩ�����𻵻�α�� ");
	}
	else if (signatureCheck == SignatureCheckResult.PublicKeyNotMatching)
	{
		Console.WriteLine("�ṩ�Ĺ�Կ��ǩ����ƥ��");
	}
	else if (signatureCheck == SignatureCheckResult.NoSignatureFound)
	{
		Console.WriteLine("���ļ�δ����ǩ��");
	}
	Console.WriteLine("������˽Կ�Ƚ��ܣ��������Ĺ�Կ��֤ǩ�����õ����ַ���Ϊ\n{ 0 }", plainTextExtracted);
}