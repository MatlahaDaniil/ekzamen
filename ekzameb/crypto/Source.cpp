#include <iostream>
#include <string>
#include <Windows.h> 
#include <fstream>

using namespace std;

string lib;

int g, m;

string encrypt(string str, int key[], int len)
{
	int temp;
	string encryptText;
	for (int i = 0; i < str.length(); i++)
	{

		for (int j = 0; j < lib.length(); j++)
		{
			if ((char)str[i] == lib[j]) //������� ����� � �������� 
			{
				temp = (j + key[g]) % lib.length();
				g++;
				if (len == g)
					g = 0;
				encryptText += lib[temp];
			}
		}
	}
	g = 0;
	return encryptText;
}

string Decrypt(string str, int key[], int len)
{
	int temp;
	string decryptText;
	for (int i = 0; i < str.length(); i++)
	{
		for (int j = 0; j < lib.length(); j++)
		{
			if ((char)str[i] == lib[j])
			{
				temp = j - key[g];
				g++;
				if (len == g)
					g = 0;

				if (temp < 0)
				{
					temp += lib.length();
					m++;
					if (len == m)
						m = 0;
				}
				else
				{
					temp = (j - key[m]) % lib.length();
					m++;
					if (len == m)
						m = 0;
				}

				decryptText += lib[temp];
			}
		}
	}
	return decryptText;
}

string MakeLib()
{


	for (int i = 65; i <= 90; i++)
	{
		lib += (char)i;
	}
	for (int i = 97; i <= 122; i++)
	{
		lib += (char)i;
	}
	for (int i = 48; i <= 57; i++)
	{
		lib += (char)i;
	}
	for (int i = 123; i <= 190; i++)
	{
		lib += (char)i;
	}
	for (int i = 192; i <= 255; i++)
	{
		lib += (char)i;
	}
	for (int i = 32; i <= 47; i++)
	{
		lib += (char)i;
	}
	lib += (char)63;

	return lib;
}

bool CheckNum(string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (!isdigit(str[i]))
		{
			return false;
		}

		return true;
	}

}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	setlocale(LC_ALL, "Russian");
	string FirstFile = "C:\\Users\\Admin\\source\\repos\\ekzameb\\crypto\\1.txt";
	string SecondFile = "C:\\Users\\Admin\\source\\repos\\ekzameb\\crypto\\2.txt";
	string ThirdFile = "C:\\Users\\Admin\\source\\repos\\ekzameb\\crypto\\3.txt";
	string str;
	string key, k;
	int* key2 = new int[NULL];
	string encryptT;
	int len = 0;

	MakeLib();


	cout << "\t\t\t ������������ ��� ��������� ��� ���������� � ������������ ������  \n";

	ifstream InFile;
	InFile.open(FirstFile);

	while (!InFile.eof())
	{
		string line;
		getline(InFile, line);
		str += line;
	}

	InFile.close();

	if (str != "")
		cout << "��� ����� ��� ���������� � ����� ������� ���������:" + FirstFile + "\n ��� ����������� ������� ����" << endl;
	else
	{
		cout << "������ , �� �� ����� �����!";
		return 1;
	}

	while (true)
	{
		
		getline(cin, key);

		if (CheckNum(key))
		{
			for (int i = 0; i < key.length(); i++)
			{
				k = key[i];
				key2[i] = stoi(k);
				len++;
				k.clear();
			}

			encryptT = encrypt(str, key2, len);
			cout << endl;
			break;

		}
		else
			cout << "������������ ����.���� ������ �������� ������ �� ���� \n";

	}
	
	Sleep(1000);
	ofstream OutFile;
	OutFile.open(SecondFile);
	OutFile << encryptT;
	OutFile.close();

	cout << "���� ������� ������� � �����: " + SecondFile;
	cout << endl;
	cout << endl;
	cout << endl;

	Sleep(1000);

	string decryptText; 
	decryptText = Decrypt(encryptT, key2, len);

	OutFile.open(ThirdFile);
	OutFile << decryptText;
	OutFile.close();

	cout << "������������ ����� ������� ������� � �����: " + ThirdFile;

	cout << endl;
	system("pause");
}
