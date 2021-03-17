#include <iostream>
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

int main()
{
	int choiceMainMenu, choiceBBS, choiceJacobi;

	choiceMainMenu = 0;

	while (choiceMainMenu != -1) {
		switch (choiceMainMenu) {
		case 0:
			cout << "What generator do you want to use?\n1. B.B.S. Generator\n2. Jacobi Generator\n3. Exit\n";
			do {
				cin >> choiceMainMenu;
			} while (choiceMainMenu <= 0 || choiceMainMenu > 3);
			if (choiceMainMenu == 3)
				choiceMainMenu = -1;
			break;
		case 1:
			cout << "BBS Generator\n";
			choiceMainMenu = 0;
			break;
		case 2:
			cout << "Jacobi Generator\n";
			choiceMainMenu = 0;
			break;
		}
	}

	/*c = 0;
	a = RandomBits_ZZ(512);
	b = a;
	while (b != 0) {
		f[c] = b % 2;
		b = (b >> 1);
		c++;
	}

	b = 0;
	for (int i = c - 1; i > 0; i--) {
		b += f[i];
		b = (b << 1);
	}
	b += f[0];

	//c = a * b;
	cout << a << "\n" << c << " " << NumBits(a) << "\n" << b << "\n";

	a = GenPrime_ZZ(512);
	cout << a << "\n" << ProbPrime(a);*/
}