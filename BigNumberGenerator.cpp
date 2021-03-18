#include <iostream>
#include <vector>
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

ZZ generateNumberBBS(unsigned long bitLength) {
	ZZ p, q;
	do {
		do {
			p = GenPrime_ZZ(bitLength / 2);
		} while (p % 4 != 3);
		do {
			q = GenPrime_ZZ(bitLength / 2);
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

ZZ generateNumberBBS(ZZ p, ZZ q, unsigned long bitLength) {
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

ZZ generateNumberJacobi(unsigned long bitLength) {
	ZZ a, n;

	n = GenPrime_ZZ(bitLength);
	a = RandomBnd(n);

	ZZ randomNumber = (ZZ)0;

	for (int i = 0; i < bitLength; i++) {
		randomNumber <<= 1;
		if (jacobiSymbol(a + i, n) != (ZZ)-1)
			randomNumber += 1;
	}

	return randomNumber;
}

void testPercentage(int iterations, int type) {
	int countZero = 0, countOne = 0, count;
	ZZ number;
	ZZ p, q, n;

	for (int i = 0; i < iterations; i++) {
		switch (type) {
		case 1:
			do {
				do {
					p = GenPrime_ZZ(512);
				} while (p % 4 != 3);
				do {
					q = GenPrime_ZZ(512);
				} while (q % 4 != 3);
			} while (p == q);
			number = generateNumberBBS(p, q, 1024);
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
			cout << "BBS Generator\n1. Generate a number\n2. Test the Generator(Percentage of Bits)\n3. Back\n";
			do {
				cin >> choiceBBS;
			} while (choiceBBS <= 0 || choiceBBS > 3);

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
				choiceMainMenu = 0;
				break;
			}

			break;
		case 2:
			cout << "Jacobi Generator\n1. Generate a number\n2. Test the Generator(Percentage of Bits)\n3. Back\n";
			do {
				cin >> choiceJacobi;
			} while (choiceJacobi <= 0 || choiceJacobi > 3);

			switch (choiceJacobi) {
			case 1:
				cout << "Input Number's Bit Length\n";
				cin >> numberLength;
				cout << generateNumberJacobi(numberLength) << "\n";
				break;
			case 2:
				testPercentage(10, 2);
				break;
			case 3:
				choiceMainMenu = 0;
				break;
			}
			break;
		}
	}
}