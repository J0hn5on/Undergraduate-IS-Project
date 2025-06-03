using System;

public class ModeManage
{
    ~ModeManage()//析构函数，保证释放敏感信息
    {
    }
    public int mode_input(User user)
    {
        while (true)
        {
            Console.WriteLine("原理展示请按 A，存储文件请按 B，调阅文件请按 C");
            String Mode = Console.ReadLine();
            if (Mode == "A")
            {
                Console.WriteLine("\n 原理展示");
                Console.WriteLine("-----------------------------------------------------------------------------------------------------------");
                Console.WriteLine("请任意输入想要加密的内容，以另起一行输入\":wq\"结束");
                return 1;
            }
            else if (Mode == "B")
            {
                Console.WriteLine("\n 文件存储");
                Console.WriteLine("-----------------------------------------------------------------------------------------------------------");
                Console.WriteLine("存储文件的安全模式：仅自己请按 1，多用户请按 2");
                while (true)
                {
                    String SubMode = Console.ReadLine();
                    if (SubMode == "1")
                    {
                        Console.WriteLine("该文件由用户{0}创建，并且只能由用户{0}查看", Environment.UserName);
                        Console.WriteLine("请输入文件路径"); 
                        return 21;
                    }
                    else if (SubMode == "2")
                    {
                        user.User_Authorization();
                        Console.WriteLine("请输入文件路径"); 
                        return 22;
                    }
                    else
                    {
                        Console.WriteLine("请重新输入！");
                    }
                }
            }
            else if (Mode == "C")
            {
                Console.WriteLine("\n 文件调阅");
                Console.WriteLine("-----------------------------------------------------------------------------------------------------------");
                Console.WriteLine("请输入文件路径(后缀为.gpg)"); 
                return 3;
            }
            else
            {
                Console.WriteLine("请重新输入！");
            }
        }
    }
    public void mode_control(int Mode, User user, String passwd)
    {
        if (Mode == 1)
        {
            //键盘读入
            String text = "";
            String input = Console.ReadLine();
            String next = Console.ReadLine(); while (true)
            {
                if (next == ":wq")
                {
                    text = text + input;
                    break;
                }
                else
                {
                    text = text + input + "\r\n";
                }
                input = next; next = Console.ReadLine();
            }
            //签名加密字符串
            FileManage fileManage = new FileManage();
            String after_string = fileManage.SignAndEncryptString(text, passwd, user.get_userID());
            Console.WriteLine("\n 键盘输入的字符串为:\n{0}\n\n 用您的私钥先签名，再用您的公钥后加密，得到的字符串为\n{1}", text, after_string);
            //解密并验证签名
            fileManage.DecryptAndVerifyString(after_string, passwd, user.get_userID());
            Console.WriteLine("-----------------------------------------------------------------------------------------------------------\n");
        }
        else if (Mode == 21)
        {
            String File = Console.ReadLine(); while (true)
            {
                if (System.IO.File.Exists(File))
                {
                    //文件签名加密
                    FileManage fileManage = new FileManage(); 
                    user.detect_All_User_Public_key();
                    string output_file = fileManage.SignAndEncryptSinge(passwd, File, user.get_userID());
                    bool check = fileManage.Verify(passwd, output_file, user.get_all_Authorized_Uers_PublicKey(), user.get_all_Authorized_Users(), user.get_userID());
                    if (check == false)
                    {
                        ClearTool clearTool = new ClearTool();
                        clearTool.ClearDeletFile(output_file);
                    }
                    else
                    {
                        Console.WriteLine("文件存储成功，并由用户\"{0}\"签名，在\"{1}\" 中", Environment.UserName, output_file);
                    }
                    //fileManage.SignAndEncryptMultiple(passwd, File);
                    Console.WriteLine("-----------------------------------------------------------------------------------------------------------\n");
                    break;
                }
                else
                {
                    Console.WriteLine("文件不存在，请重新输入文件路径");
                    File = Console.ReadLine();
                }
            }
        }
        else if (Mode == 22)
        {
            String File = Console.ReadLine(); while (true)
            {
                if (System.IO.File.Exists(File))
                {
                    //文件签名加密
                    FileManage fileManage = new FileManage(); 
                    user.detect_All_User_Public_key();
                    string output_file = fileManage.SignAndEncryptMultiple(passwd, File, user.get_all_Authorized_Uers_PublicKey(), user.get_userID());
                    bool check = fileManage.Verify(passwd, output_file, user.get_all_Authorized_Uers_PublicKey(), user.get_all_Authorized_Users(), user.get_userID());
                    if (check == false)
                    {
                        ClearTool clearTool = new ClearTool();
                        clearTool.ClearDeletFile(output_file);
                    }
                    else
                    {
                        Console.WriteLine("文件存储成功，并由用户\"{0}\"签名，在\"{1}\" 中", Environment.UserName, output_file);
                    }
                    Console.WriteLine("-----------------------------------------------------------------------------------------------------------\n");
                    break;
                }
                else
                {
                    Console.WriteLine("文件不存在，请重新输入文件路径");
                    File = Console.ReadLine();
                }
            }
        }
        else if (Mode == 3)
        {
            String File = Console.ReadLine(); while (true)
            {
                if (System.IO.File.Exists(File))
                {
                    //文件签名加密
                    FileManage fileManage = new FileManage(); 
                    user.detect_All_User_Public_key();
                    Console.WriteLine(user.get_all_Authorized_Users().Length);
                    fileManage.DecryptAndVerify(passwd, File, user.get_all_Authorized_Uers_PublicKey(), user.get_all_Authorized_Users(), user.get_userID());
                    Console.WriteLine("-----------------------------------------------------------------------------------------------------------\n");
                    break;
                }
                else
                {
                    Console.WriteLine("文件不存在，请重新输入文件路径");
                    File = Console.ReadLine();
                }
            }

        }
    }
}