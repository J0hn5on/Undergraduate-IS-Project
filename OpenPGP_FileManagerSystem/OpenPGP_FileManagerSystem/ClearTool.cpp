#include "head.h"
using namespace std;


void ClearTool::ClearDelet(string path)
{
	if (File.Exists(path)) ClearDeletFile(path);
	if (Directory.Exists(path)) ClearDeletDirectory(path);
}
	/// <summary>
	/// �����Ŀ¼�е������ļ�����Ŀ¼���ݣ���ɾ����ǰĿ¼
	/// </summary>
void ClearTool::ClearDeletDirectory(string dir)
{
	if (Directory.Exists(dir))
	{
		// ���Ŀ¼�µ������ļ�
		foreach(String iteam in Directory.GetFiles(dir))
		{
			ClearDeletFile(iteam);
		}
		// ���Ŀ¼�µ�������Ŀ¼
		foreach(String iteam in Directory.GetDirectories(dir))
		{
			ClearDeletDirectory(iteam);
		}
		String newName = System.IO.Directory.GetParent(dir).FullName + "\\$"; while (File.Exists(newName)) newName += "$";
		// �����ǰĿ¼
		Directory.Move(dir, newName); // ��������ǰĿ¼�����Ŀ¼����Ϣ
		Directory.Delete(newName); // �����ǰĿ¼
	}
}
	/// <summary>
	/// ������ļ����ݣ���ɾ��
	/// </summary>
void ClearTool::ClearDeletFile(string file)
{
	ClearFile(file); // ����ļ�����
	if (File.Exists(file))
	{
		String newName = System.IO.Directory.GetParent(file).FullName + "\\$"; while (File.Exists(newName)) newName += "$";
		File.Move(file, newName); // �������ļ�������ļ�������Ϣ
		File.Delete(newName); // ɾ���ļ�
	}
}
	/// <summary>
	/// ����ļ�����
	/// </summary>
void ClearTool::ClearFile(string file)
{
	if (File.Exists(file))
	{
		int SIZE = 1024 * 10240;
		byte[] array = new byte[SIZE];
		array.Initialize();
		FileStream s = new FileStream(file, FileMode.Open, FileAccess.ReadWrite, FileShare.ReadWrite, SIZE, FileOptions.RandomAccess);
		// ���ԭ���ļ�����
		while (s.Position + SIZE <= s.Length - 1)
		{
			s.Write(array, 0, SIZE);
		}
		int reminds = (int)(s.Length - s.Position);
		if (reminds > 0) s.Write(array, 0, reminds);
		// ����ļ�������Ϣ
		s.SetLength(0);
		s.Close();
	}
}