#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

long gcd(long a, long b) {
	long nod = 1L;
	long tmp;
	if (a == 0L)
		return b;
	if (b == 0L)
		return a;
	if (a == b)
		return a;
	if (a == 1L || b == 1L)
		return 1L;
	while (a != 0 && b != 0) {
		if (((a & 1L) | (b & 1L)) == 0L) {
			nod <<= 1L;
			a >>= 1L;
			b >>= 1L;
			continue;
		}
		if (((a & 1L) == 0L) && (b & 1L)) {
			a >>= 1L;
			continue;
		}
		if ((a & 1L) && ((b & 1L) == 0L)) {
			b >>= 1L;
			continue;
		}
		if (a > b) {
			tmp = a;
			a = b;
			b = tmp;
		}
		tmp = a;
		a = (b - a) >> 1L;
		b = tmp;
	}
	if (a == 0)
		return nod * b;
	else
		return nod * a;
}

long Yacobi(long a, long b)
{
	int r = 1;
	while (a != 0){
		int t = 0;
		while ((a & 1) == 0)
		{
			t++;
			a >>= 1;
		}
		if ((t & 1) != 0){
			long temp = b % 8;
			if (temp == 3 || temp == 5){
				r = -r;
			}
		}
		long a4 = a % 4, b4 = b % 4;
		if (a4 == 3 && b4 == 3){
			r = -r;
		}
		long c = a;
		a = b % c;
		b = c;
	}
	return r;
}

int expMod(int a, int p, int n){
	int base = a;
	int ret = 1;
	while (p != 0){
		if ((p & 1) != 0)
			ret = (ret * base) % n;
		p = p >> 1;
		base = (base * base) % n;
	}
	return ret;
}

int main() {
	int N;
	int A;
	const int reliability = 100;
    
	cout << "[!] Enter number: ";
	cin >> N;

	srand(time(NULL));

	if ((N & 1) == 0){
		cout << "[-] Composite!" << endl;
		return 0;
	}

	for (int k = 0; k < reliability; ++k){
		int A = rand() % (N - 1) + 1;
		if (gcd(A, N) != 1){
			cout << "[-] Composite!" << endl;
			return 0;
		}

		int j = Yacobi(A, N);
		if (j < 0) j += N;

		int J = expMod(A, (N - 1) >> 1, N);

		if (j != J){
			cout << "[-] Composite!" << endl;
			return 0;
		}
	}
	cout << "[+] Prime with High Probability!" << endl;
	return 0;
}
