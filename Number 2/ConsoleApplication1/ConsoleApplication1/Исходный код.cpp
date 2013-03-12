#include <stdio.h>
#include <iostream>

using namespace std;

class operation
{
	char * stroka;
	int n;
public:
	operation ()
	{
		cout << "Vvedute dliny stroki ";
		cin >> n;

		stroka = (char *) malloc (sizeof(char)*n);
		cout << "Vvedute stroky ";
		cin >> stroka;
	}

	int number ()
	{
		int k = 0;
		for (int i = 0; i < n; i++)
		{
			if ((stroka[i] == '+') || (stroka[i] == '-') || (stroka[i] == '*') || (stroka[i] == '/'))
				k++;
		}
		return k;
	}
};

int main ()
{
	operation _Operation;
	int answer = _Operation.number();
	cout << answer;
	return 0;
}


