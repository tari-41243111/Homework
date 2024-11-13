#include <iostream>
using namespace std;

template <typename T>
int BinarySearch(T* data, T key, int L, int R)
{
	if (L > R)
		return -1;

	int M = (L + R) / 2;
	if (key == data[M])
		return M;
	else if (key > data[M])
		return BinarySearch(data, key, M + 1, R);
	else
		return BinarySearch(data, key, L, M - 1);
}

int main()
{
	char t;
	int n, q;
	while (cin >> t >> n >> q)
	{
		if (t == 'i')
		{
			long long* data = new long long[n];
			long long target;

			for (int i = 0; i < n; i++)
				cin >> data[i];
			while (q--)
			{
				cin >> target;
				cout << BinarySearch(data, target, 0, n - 1) << endl;
			}
		}
		else
		{
			string* data = new string[n];
			string target;

			for (int i = 0; i < n; i++)
				cin >> data[i];
			while (q--)
			{
				cin >> target;
				cout << BinarySearch(data, target, 0, n - 1) << endl;
			}
		}
	}

	return 0;
}