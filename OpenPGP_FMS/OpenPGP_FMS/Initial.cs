using System;

//文件位置
public class Initial
{
    public static String baseName = "D:\\";
    public static String folderName = "OpenPGP_File_Manage_show";
    public static String folderName1 = "Key";
    public static String folderName2 = "File";
    public static String pathString = System.IO.Path.Combine(baseName, folderName);//总文件夹
    public static String pathStringUser = System.IO.Path.Combine(pathString, Environment.UserName);//用户文件夹
    public static String pathStringKey = System.IO.Path.Combine(pathStringUser, folderName1);//用户密钥文件夹
    public static String pathStringFile = System.IO.Path.Combine(pathStringUser, folderName2);//用户文件文件夹
    public Initial()
    {
        Console.WriteLine("/***************************************************************/ ");
        Console.WriteLine("* 本项目为基于 OpenPGP 的文件管理系统*");
        Console.WriteLine("/***************************************************************/\n");
        set_baseName();
        Console.WriteLine("\n 应用所创建的文件夹信息");
        Console.WriteLine("-----------------------------------------------------------------------------------------------------------");
        System.IO.Directory.CreateDirectory(pathString);
        Console.WriteLine("已创建\"{0}\" \n", pathString);
        System.IO.Directory.CreateDirectory(pathStringUser);
        Console.WriteLine("已创建\"{0}\" \n", pathStringUser);
        System.IO.Directory.CreateDirectory(pathStringKey);
        Console.WriteLine("已创建\"{0}\" \n", pathStringKey);
        System.IO.Directory.CreateDirectory(pathStringFile);
        Console.WriteLine("已创建\"{0}\" ", pathStringFile);
        Console.WriteLine("-----------------------------------------------------------------------------------------------------------\n");
    }
    ~Initial()//析构函数，保证释放敏感信息
    {
    }
    public void set_baseName()
    {
        Console.WriteLine("请输入文件夹想要的存放位置（默认：D:\\）,输入 q 可跳过");
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
}