using DidiSoft.Pgp;
using System;
using System.Collections.Generic;
using System.IO;
using System.Security.Principal;

public class User
{
    private String username;//用户名
    private SecurityIdentifier sid;//用户安全标识符
    private String userID;
    private string[] all_Authorized_Users;
    private string[] all_Authorized_Uers_PublicKey;//所有用户目录文件
    public User()
    {
        username = Environment.UserName;
        WindowsIdentity windowsIdentity = WindowsIdentity.GetCurrent();
        sid = windowsIdentity.User; userID = get_userID();
        Console.WriteLine("当前用户信息");
    }
    ~User() //析构函数，保证释放敏感信息
    {
    }
    public String get_username()
    {
        return username;
    }
    public SecurityIdentifier get_sid()
    {
        return sid;
    }
    public String get_userID()
    {
        PGPLib pgp = new PGPLib();
        pgp.Hash = HashAlgorithm.MD5; userID = sid.GetHashCode().ToString(); return userID;
    }
    public string[] get_all_Authorized_Users()
    {
        return all_Authorized_Users;
    }
    public string[] get_all_Authorized_Uers_PublicKey()
    {
        return all_Authorized_Uers_PublicKey;
    }
    //设置能够访问到的 all_Authorized_Uers_PublicKey;
    public void User_Authorization()
    {
        string[] all_Uers_pathString = Directory.GetDirectories(Initial.pathString);//用户文件夹目录
        if (all_Uers_pathString.Length == 1)
        {
            Console.WriteLine("目前该文件系统未检测到其他用户");
        }
        List<string> _ulist = new List<string> { Environment.UserName };
        List<string> _list = new List<string> { Path.Combine(Initial.pathStringKey, "public_key_exported.asc") };
        foreach (string element in all_Uers_pathString)
        {
            String name = Path.GetFileName(element);
            String publicKey = Path.Combine(Initial.pathString, name, Initial.folderName1, "public_key_exported.asc");//用户公钥文件
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
    public void detect_All_User_Public_key()
    {
        List<string> _ulist = new List<string> { };
        List<string> _list = new List<string> { };
        string[] all_Uers_pathString = Directory.GetDirectories(Initial.pathString);//用户文件夹目录
        foreach (string element in all_Uers_pathString)
        {
            String name = Path.GetFileName(element);
            String publicKey = Path.Combine(Initial.pathString, name, Initial.folderName1, "public_key_exported.asc");//用户公钥文件
            if (File.Exists(publicKey))
            {
                _ulist.Add(name); _list.Add(publicKey);
            }
        }
        all_Authorized_Users = _ulist.ToArray();
        all_Authorized_Uers_PublicKey = _list.ToArray();

    }
}