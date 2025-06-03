#include "head.h"
#include<string>
using namespace std;


void KeyManage::GenerateKeyPairRSA(String userID, String passwd)
{
	Console.WriteLine("�����û���Կ");
	Console.WriteLine("-----------------------------------------------------------------------------------------------------------");
	// initialize the key store where the generated key
	// will be produced, if the file does not exist
	// it will be created
	String file = System.IO.Path.Combine(Global.pathStringKey, "key.store");
	if (!System.IO.File.Exists(file))
	{
		KeyStore ks = new KeyStore(@file, passwd);
		// Preferred symmetric key algorithms for this key
		CypherAlgorithm[] cypher = { CypherAlgorithm.CAST5, CypherAlgorithm.AES_128 };
		// Preferred digital signature (hash) algorithms for this key
		HashAlgorithm[] hashing = { HashAlgorithm.SHA1, HashAlgorithm.MD5, HashAlgorithm.SHA256 };
		// Preferred compression algorithms for this key
		CompressionAlgorithm[] compression =
		{ CompressionAlgorithm.ZIP, CompressionAlgorithm.UNCOMPRESSED };
		int keySizeInBits = 2048;
		ks.GenerateKeyPair(keySizeInBits, userID, KeyAlgorithm.RSA, passwd, compression, hashing, cypher);
		// Now we can use the key from the KeyStore or export it
		Console.WriteLine("�û�{0}����Կ����˽Կ�������ɣ���\"{1}\"��\n", Environment.UserName, file);
	}
	else
	{
		Console.WriteLine("�û�{0}����Կ�Ѵ��ڣ���\"{1}\"��\n", Environment.UserName, file); return;
	}
}
	//������Կ
void KeyManage::ExportPublicKey(String userID, String passwd)
{
	// initialize the KeyStore
	String file_store = System.IO.Path.Combine(Global.pathStringKey, "key.store");
	String file_public_key = System.IO.Path.Combine(Global.pathStringKey, "public_key_exported.asc");
	KeyStore ks = KeyStore.OpenFile(@file_store, passwd);
	// should the exported files be ASCII or binary
	bool asciiArmored = true;
	// export both public and secret key with all sub keys in one file
	if (!System.IO.File.Exists(file_public_key))
		ks.ExportPublicKey(@file_public_key, userID, asciiArmored);
	Console.WriteLine("�û�{0}�Ĺ�Կ�ѵ�������\"{1}\"��\n", Environment.UserName, file_public_key);
}
	//����˽Կ
void KeyManage::ExportPrivateKey(String userID, String passwd)
{
	String file_store = System.IO.Path.Combine(Global.pathStringKey, "key.store");
	String file_private_key = System.IO.Path.Combine(Global.pathStringKey, "private_key_exported.asc");
	// initialize the key store
	KeyStore ks = KeyStore.OpenFile(@file_store, passwd);
	// should the exported files be ASCII or binary
	bool asciiArmored = true;
	// export secret key, this is usually our own key. ks.ExportPrivateKey(@file_private_key, userID, asciiArmored);
}
	//�����ʾ���������� GnuPG/gpg �ķ�ʽ�г�����ӡ��Կ��
void KeyManage::KeyStoreListKeys(String passwd)
{
	Console.WriteLine("��ǰ��Կ��ϢΪ��");
	String file = System.IO.Path.Combine(Global.pathStringKey, "key.store");
	// initialize the key store
	KeyStore ks = KeyStore.OpenFile(file, passwd);
	KeyPairInformation[] keys = ks.GetKeys();
	StringBuilder sb = new StringBuilder();
	sb.Append("Username".PadRight(15));
	sb.Append("Type".PadRight(10));
	sb.Append("Key Id".PadRight(30));
	sb.Append("Created".PadRight(20));
	sb.Append("User Id");
	Console.WriteLine(sb.ToString());
	foreach(KeyPairInformation key in keys)
	{
		sb.Remove(0, sb.Length);
		sb.Append(Environment.UserName.PadRight(15));
		String keyType = null;
		if (key.HasPrivateKey)
		{
			keyType = "pub/sec";
		}
		else
		{
			keyType = "pub";
		}
		sb.Append(keyType.PadRight(10));
		sb.Append(Convert.ToString(key.KeyId).PadRight(30));
		sb.Append(key.CreationTime.ToShortDateString().PadRight(20));
		foreach(String id in key.UserIds)
		{
			sb.Append(id);
		}
		Console.WriteLine(sb.ToString());
		Console.WriteLine("-----------------------------------------------------------------------------------------------------------\n");
	}
}