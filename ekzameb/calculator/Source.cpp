#include <iostream>
#include <stack>
using namespace std;

struct TypeAndValue
{
	char type; 
	double value; 
};

bool Maths(stack <TypeAndValue>& StackN, stack <TypeAndValue>& StackO, TypeAndValue& item)
{ 
	
	double a, b, c;
	a = StackN.top().value;
	StackN.pop();
	switch (StackO.top().type)
	{  
	case '+': 
		b = StackN.top().value;
		StackN.pop();
		c = a + b;
		item.type = 'N';
		item.value = c;
		StackN.push(item);
		StackO.pop();
		break;

	case '-':
		b = StackN.top().value;
		StackN.pop();
		c = b - a;
		item.type = 'N';
		item.value = c;
		StackN.push(item);
		StackO.pop();
		break;

	case '*':
		b = StackN.top().value;
		StackN.pop();
		c = a * b;
		item.type = 'N';
		item.value = c;
		StackN.push(item);
		StackO.pop();
		break;

	case '/':
		b = StackN.top().value;
		if (a == 0) {
			cout << "\nНа 0 делить нельзя!\n";
			return false;
		}
		else 
		{
			StackN.pop();
			c = (b / a);
			item.type = 'N';
			item.value = c;
			StackN.push(item);
			StackO.pop();
			break;
		}
	default:
		cout << "\nОшибка!\n";
		return false;
		break;
	}
	return true;
}

int RangOp(char Ch) 
{ 
	if (Ch == '+' || Ch == '-')
		return 1;

	if (Ch == '*' || Ch == '/')
		return 2;

	else 
		return 0;
}

int main()
{
	setlocale(LC_ALL, "rus");

	char Ch;
	double value;
	bool flag = 1;

	stack <TypeAndValue> StackNum;
	stack <TypeAndValue> StackOp;
	TypeAndValue item;
	
	
	cout << "\t\t\t\t\t\tKалькулятор\nВведи выраженние: ";

	while (true)
	{
		Ch = cin.peek();
		if (Ch == '\n')
			break;

		if (Ch == ' ')
		{
			cin.ignore();
			continue;
		}

		if (Ch >= '0' && Ch <= '9' || Ch == '-' && flag == 1)
		{
			cin >> value;
			item.type = 'N';
			item.value = value;
			StackNum.push(item);
			flag = 0;
			continue;
		}
		if (Ch == '+' || Ch == '-' && flag == 0 || Ch == '*' || Ch == '/')
		{
			if (StackOp.size() == 0) 
			{
				item.type = Ch;
				item.value = 0;
				StackOp.push(item);
				cin.ignore();
				continue;
			}
			if (StackOp.size() != 0 && RangOp(Ch) > RangOp(StackOp.top().type))
			{
				item.type = Ch;
				item.value = 0;
				StackOp.push(item);
				cin.ignore();
				continue;
			}
			if (StackOp.size() != 0 && RangOp(Ch) <= RangOp(StackOp.top().type))
			{
				if (Maths(StackNum, StackOp, item) == false) 
				{
					system("pause");
					return 0;
				}
				continue;
			}
		}		
		if (Ch == '(')
		{
			item.type = Ch;
			item.value = 0;
			StackOp.push(item);
			cin.ignore();
			continue;
		}
		if (Ch == ')')
		{
			while (StackOp.top().type != '(')
			{
				if (Maths(StackNum, StackOp, item) == false)
				{
					system("pause");
					return 0;
				}
				else 
					continue;
			}
			StackOp.pop();
			cin.ignore();
			continue;
		}
		else
		{
			cout << "\nНеверно введено выражение!\n";
			system("pause");
			return 0;
		}
	}
	while (StackOp.size() != 0)
	{
		if (Maths(StackNum, StackOp, item) == false)
		{
			system("pause");
			return 0;
		}
		else 
			continue; 	
	}
	cout << "Ответ: " << StackNum.top().value << endl;
	

	system("pause");
}