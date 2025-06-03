using DidiSoft.Pgp;
using DidX.BouncyCastle.Asn1.X509;
using System;
using System.IO;

public class FileManage
{
    ~FileManage()//析构函数，保证释放敏感信息
    {
    }
    //签名和加密（多人）
    public string SignAndEncryptMultiple(String passwd, String File, string[] all_Authorized_Uers_PublicKey, String userID)
    {
        //获取文件名（不含拓展名）
        String extension = Path.GetExtension(File);
        String fileNameWithoutExtension = Path.GetFileNameWithoutExtension(File);// 没有扩展名的文件名 "default"
        String fileNameRandom = Path.GetRandomFileName();
        String fileNameRandomWithoutExtension =
        Path.GetFileNameWithoutExtension(fileNameRandom);
        String newFile = fileNameWithoutExtension + fileNameRandomWithoutExtension + extension + ".gpg";
        // create an instance of the library
        PGPLib pgp = new PGPLib();
        // ASCII armor or binary
        bool asciiArmor = true;
        // append integrity protection check, set to true for compatibility with GnuPG 2.2.8+
        bool withIntegrityCheck = false;
        //文件目录
        string[] input_file = { @File };
        String file_public_key = System.IO.Path.Combine(Initial.pathStringKey, "public_key_exported.asc");
        String file_private_key = System.IO.Path.Combine(Initial.pathStringKey, "private_key_exported.asc");
        String output_file = System.IO.Path.Combine(Initial.pathStringFile, newFile);
        string[] recipientsPublicKeys = all_Authorized_Uers_PublicKey;
        KeyManage keyManage = new KeyManage();
        keyManage.ExportPrivateKey(userID, passwd);//导出私钥
        ClearTool clearTool = new ClearTool();
        pgp.SignAndEncryptFiles(@input_file, file_private_key, passwd, recipientsPublicKeys, @output_file, asciiArmor, withIntegrityCheck);
        clearTool.ClearDeletFile(file_private_key);//删除私钥敏感信息
        return output_file;
    }
    //签名和加密（单人）
    public string SignAndEncryptSinge(String passwd, String File, String userID)
    {
        //获取文件名（不含拓展名）
        String extension = Path.GetExtension(File);
        String fileNameWithoutExtension = Path.GetFileNameWithoutExtension(File);// 没有扩展名的文件名 "default"
        String fileNameRandom = Path.GetRandomFileName();
        String fileNameRandomWithoutExtension =
        Path.GetFileNameWithoutExtension(fileNameRandom);
        String newFile = fileNameWithoutExtension + fileNameRandomWithoutExtension + extension + ".gpg";
        // create an instance of the library
        PGPLib pgp = new PGPLib();
        // is output ASCII or binary
        bool asciiArmor = true;
        // should integrity check information be added, set to true for compatibility with GnuPG2.2.8 +
        bool withIntegrityCheck = false;
        //文件目录
        String input_file = File;
        String file_public_key = System.IO.Path.Combine(Initial.pathStringKey, "public_key_exported.asc");
        String file_private_key = System.IO.Path.Combine(Initial.pathStringKey, "private_key_exported.asc");
        String output_file = System.IO.Path.Combine(Initial.pathStringFile, newFile);
        KeyManage keyManage = new KeyManage();
        keyManage.ExportPrivateKey(userID, passwd);//导出私钥
        ClearTool clearTool = new ClearTool();
        // sign and encrypt
        pgp.SignAndEncryptFile(@input_file, @file_private_key, passwd, @file_public_key, @output_file, asciiArmor, withIntegrityCheck);
        clearTool.ClearDeletFile(file_private_key);//删除私钥敏感信息
        return output_file;
    }
    public String SignAndEncryptString(String plainText, String passwd, String userID)
    {
        // create an instance of the library
        PGPLib pgp = new PGPLib();
        String file_public_key = System.IO.Path.Combine(Initial.pathStringKey, "public_key_exported.asc");
        String file_private_key = System.IO.Path.Combine(Initial.pathStringKey, "private_key_exported.asc");
        KeyManage keyManage = new KeyManage();
        keyManage.ExportPrivateKey(userID, passwd);//导出私钥
        ClearTool clearTool = new ClearTool();
        // sign and enrypt
        String encryptedAndSignedString =
        pgp.SignAndEncryptString(plainText, new FileInfo(file_private_key), passwd, new FileInfo(file_public_key));
        clearTool.ClearDeletFile(file_private_key);//删除私钥敏感信息
        return encryptedAndSignedString;
    }
    public bool Verify(String passwd, String File, string[] All_User_Public_key, string[]
    All_Users, String userID)
    {
        String originalFile = Path.GetFileNameWithoutExtension(File);
        String extension = Path.GetExtension(File); //-->.txt
        String filetmp = originalFile + "Tmp" + extension;
        // create an instance of the library
        PGPLib pgp = new PGPLib();
        //文件目录
        String input_file = File;//gpg
        String file_private_key = System.IO.Path.Combine(Initial.pathStringKey, "private_key_exported.asc");
        String output_file = System.IO.Path.Combine(Initial.pathStringFile, filetmp);
        KeyManage keyManage = new KeyManage();
        keyManage.ExportPrivateKey(userID, passwd);//导出私钥
        ClearTool clearTool = new ClearTool();
        for (int i = 0; i < All_Users.Length; i++)
        {
            // check the signature and extract the data
            //The supplied data is not only signed but also encrypted. Please use the DecryptAndVerify or Decrypt methods in order to extract the encrypted contents.”
            //因此只能先解密再验证签名
            SignatureCheckResult signatureCheck = pgp.DecryptAndVerifyFile(@input_file, @file_private_key, passwd, @All_User_Public_key[i], @output_file);
            clearTool.ClearDeletFile(file_private_key);//删除私钥敏感信息
            clearTool.ClearDeletFile(output_file);
            if (signatureCheck == SignatureCheckResult.SignatureVerified && All_Users[i] == Environment.UserName)
            {
                Console.WriteLine($"身份认证成功，您的身份为{All_Users[i]},创建文件成功");
                return true;
            }
            else
            {
                Console.WriteLine($"身份认证失败，您的身份为{All_Users[i]},创建文件失败");
                return false;
            }
        }
        return false;
    }
    public void DecryptAndVerify(String passwd, String File, string[]
    All_User_Public_key, string[] All_Users, String userID)
    {
        String originalFile = Path.GetFileName(File);
        // create an instance of the library
        PGPLib pgp = new PGPLib();
        //文件目录
        String input_file = File;//gpg
        String file_private_key = System.IO.Path.Combine(Initial.pathStringKey, "private_key_exported.asc");
        String output_file = System.IO.Path.Combine(Initial.pathStringFile, originalFile);
        KeyManage keyManage = new KeyManage();
        keyManage.ExportPrivateKey(userID, passwd);//导出私钥
        ClearTool clearTool = new ClearTool();
        // decrypt and obtain the original file name
        // of the decrypted file
        string originalFileName = pgp.DecryptFile(@input_file, @file_private_key, passwd, @output_file);
        Console.WriteLine("您的身份为用户\"{0}\"", Environment.UserName);
        Console.WriteLine("文件调阅成功，原文件名为{0},解密后的文件在{1}中", originalFileName, output_file);
        for (int i = 0; i < All_Users.Length; i++)
        {
            // check the signature and extract the data
            //The supplied data is not only signed but also encrypted. Please use the DecryptAndVerify or Decrypt methods in order to extract the encrypted contents.”
            //因此只能先解密再验证签名
            SignatureCheckResult signatureCheck = pgp.DecryptAndVerifyFile(@input_file, @file_private_key, passwd, @All_User_Public_key[i], @output_file);
            clearTool.ClearDeletFile(file_private_key);//删除私钥敏感信息
            if (signatureCheck == SignatureCheckResult.SignatureVerified)
            {
                Console.WriteLine("签名验证成功，该文件是由用户{0}创建的", All_Users[i]);
                break;
            }
            else if (signatureCheck == SignatureCheckResult.NoSignatureFound)
            {
                Console.WriteLine("此文件未数字签名");
                break;
            }
            else if (signatureCheck == SignatureCheckResult.SignatureBroken)
            {
                Console.WriteLine("文件的签名已损坏或伪造 ");
                break;
            }
            else if (i == All_Users.Length - 1 && signatureCheck ==
            SignatureCheckResult.PublicKeyNotMatching)
            {
                Console.WriteLine("提供的公钥与签名不匹配");
            }
        }
    }
    public void DecryptAndVerifyString(String signedAndEncryptedMessage, String passwd, String userID)
    {

        String file_public_key = System.IO.Path.Combine(Initial.pathStringKey, "public_key_exported.asc");
        String file_private_key = System.IO.Path.Combine(Initial.pathStringKey, "private_key_exported.asc");
        String plainTextExtracted;
        // create an instance of the library
        PGPLib pgp = new PGPLib();
        KeyManage keyManage = new KeyManage();
        keyManage.ExportPrivateKey(userID, passwd);//导出私钥
        ClearTool clearTool = new ClearTool();
        // decrypt and verify
        SignatureCheckResult signatureCheck = pgp.DecryptAndVerifyString(signedAndEncryptedMessage, new FileInfo(@file_private_key), passwd, new FileInfo(@file_public_key), out plainTextExtracted);
        clearTool.ClearDeletFile(file_private_key);//删除私钥敏感信息
                                                   // print the results
        if (signatureCheck == SignatureCheckResult.SignatureVerified)
        {
            Console.WriteLine("签名验证成功");
        }
        else if (signatureCheck == SignatureCheckResult.SignatureBroken)
        {
            Console.WriteLine("文件的签名已损坏或伪造 ");
        }
        else if (signatureCheck == SignatureCheckResult.PublicKeyNotMatching)
        {
            Console.WriteLine("提供的公钥与签名不匹配");
        }
        else if (signatureCheck == SignatureCheckResult.NoSignatureFound)
        {
            Console.WriteLine("此文件未数字签名");
        }
        Console.WriteLine("用您的私钥先解密，再用您的公钥验证签名，得到的字符串为\n{0}", plainTextExtracted);
    }
}