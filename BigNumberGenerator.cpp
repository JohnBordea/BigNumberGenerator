#include <iostream>
#include <vector>
#include <NTL/ZZ.h>
//#include <zlib.h>

using namespace std;
using namespace NTL;

ZZ generateNumberBBS(unsigned long bitLength) {
	ZZ p, q;
	do {
		do {
			p = GenPrime_ZZ(512);
		} while (p % 4 != 3);
		do {
			q = GenPrime_ZZ(512);
		} while (q % 4 != 3);
	} while (p == q);

	ZZ N = p * q;

	ZZ seed;
	do {
		seed = RandomBnd(N);
	} while (seed % p == 0 || seed % q == 0);

	ZZ randomNumber = (ZZ)0;

	for (int i = 0; i < bitLength; i++) {
		seed = (seed * seed) % N;
		randomNumber = (randomNumber << 1) + (seed % 2);
	}

	return randomNumber;
}

ZZ jacobiSymbol(ZZ n, ZZ k) {
	n %= k;
	int t = 1;
	while (n != 0) {
		while (n % 2 == 0) {
			n /= 2;
			int r = k % 8;
			if (r == 3 || r == 5)
				t = -t;
		}
		swap(n, k);
		if (n % 4 == 3 && k % 4 == 3)
			t = -t;
		n %= k;
	}
	return (k == 1) ? (ZZ)t : (ZZ)0;
}

ZZ jacobiSimbol(ZZ a, ZZ n) {
	ZZ b = a % n;
	ZZ swp;
	ZZ c = n;
	int s = 1;

	while (b > 2) {
		while (b % 4 == 0)
			b /= 4;
		if (b % 2 == 0) {
			if (c % 8 == 3 || c % 8 == 5)
				s = -s;
			b /= 2;
		}
		if (b == 1)
			break;
		if (b % 4 == 3 && c % 4 == 3) {
			s = -s;
			swp = c;
			c = b;
			b = swp % b;
		}
	}

	return b * s;
}

void testPercentage(int iterations, int type) {
	int countZero = 0, countOne = 0, count;
	ZZ number;

	for (int i = 0; i < iterations; i++) {
		switch (type) {
		case 1:
			number = generateNumberBBS(1024);
			break;
		default:
			number = generateNumberBBS(1024);
		}
		while (number != 0) {
			switch (bit(number, 0) /*number % 2*/) {
			case 0:
				countZero++;
				break;
			case 1:
				countOne++;
				break;
			}
			number >>= 1;
		}
	}

	double percentage = 0;

	count = countOne + countZero;
	percentage = static_cast<double>(countZero) / static_cast<double>(count);
	cout << "Percentages of\n0: " << percentage * 100 << "%\n1: " << (1 - percentage) * 100 << "%\n";
}

int main()
{
	int choiceMainMenu, choiceBBS, choiceJacobi;
	unsigned long numberLength = 1024;
	ZZ generatedNumber = (ZZ)0;

	choiceMainMenu = -1;

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
			cout << "BBS Generator\n1. Generate a number\n2. Test the Generator(Percentage of Bits)\n3. Test the Generator(Compresion)\n4. Back\n";
			do {
				cin >> choiceBBS;
			} while (choiceBBS <= 0 || choiceBBS > 4);

			switch (choiceBBS) {
			case 1:
				cout << "Input Number's Bit Length\n";
				cin >> numberLength;
				cout << generateNumberBBS(numberLength) << "\n";
				break;
			case 2:
				testPercentage(20, 1);
				break;
			case 3:
				break;
			case 4:
				choiceMainMenu = 0;
				break;
			}

			break;
		case 2:
			cout << "Jacobi Generator\n1. Generate a number\n2. Test the Generator(Percentage of Bits)\n3. Test the Generator(Compresion)\n4. Back\n";
			do {
				cin >> choiceJacobi;
			} while (choiceJacobi <= 0 || choiceJacobi > 4);

			switch (choiceJacobi) {
			case 1:
				
				break;
			case 2:
				testPercentage(20, 1);
				break;
			case 3:
				break;
			case 4:
				choiceMainMenu = 0;
				break;
			}
			break;
		}
	}

	cout << 1;

	ZZ a, b;

	b = GenPrime_ZZ(512);
	a = RandomBnd(b);

	for (int i = 0; i < 100; i++) {
		b = GenPrime_ZZ(512);
		a = RandomBnd(b);
		cout << "[" << jacobiSymbol(a, b) << " " << Jacobi(a, b) << "]";
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