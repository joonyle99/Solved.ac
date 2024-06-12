#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<int> memo(1000, -1);	// Memoization

// ���� ������ ��� vs �ͳ��� ���
// 
// ������̶�� ���� �ͳ����̶�� ���̴�.
// 
// '�ùٸ� ���� ��ȣ ���ϱ�'�� ���� ����������
// ���ÿ� '{'�� �ְ� '}'�� ������ ������ ����ִ� �� Ȯ���ϰ�,
// ������ top�� ¦�� �´� �� Ȯ���ϰ� �ϴ� �Ͱ� ���� '������ ���� �ؾ��� ���� ������ �ִ�' �ڵ��� �ؿԴ�.
//
// ��Ϳ� ���� �ͳ����� ����� � ���̰� ������?
// ���̳븦 ���� ����,, 1 ~ N�� ������ ���̳밡 ���� ��,
// ��� ��� ���̳밡 ������ �� �ִ� ���� �����,
// 1 -> 2 -> 3 -> 4 -> 5 ... ���� ���������� ������ ���̳밡 �����߸��� ������
// ��� ���̳�� ��������.. �� ���� �տ� ���� ���õ��� �����ǰ�, ���Ŀ� ����� ���� ����� �ٷ�
// �ͳ��� �߷� ����̴�.
// 
// ������ �ͳ������� �������ڸ�,
// 1�� ���̳밡 ��������, 2�� ���̳밡 ��������.
// 2�� ���̳밡 ��������, 3�� ���̳밡 ��������.
// K�� ���̳밡 ��������, K + 1�� ���̳밡 ��������.
// �̷��� ������ �� �ִµ�, �̷��� ����ó��
// ��� �Լ��� �ͳ��� ��Ŀ�����,
// 1�� ���̳밡 �������� 2�� ���̳밡 ��������.
// �׷��Ƿ� K�� ���̳밡 �������� K + 1�� ���̳밡 ��������
// => �� �ٷ� �� �� �־�� �Ѵ�.
// ��, �׵��� �ؿ��� ���������� ����� ������ ���� ����� �Ѵ�.
//
// ��� �Լ��� ���ǿ���
// Ư�� �Է¿� ���� �ڱ� �ڽ��� ȣ������ �ʰ� ����Ǿ�� �ϴ� Base Condition or Base Case�� �����ؾ� �ϸ�,
// ��� �Է��� Base Condition���� '����'�ؾ� �Ѵ�.
// i.g) if (n == 0) return
//
// ��Ϳ� ���� ���� 1
// �Լ��� ���ڷ� � ���� �ް�, ������ ����� �� �ڱ� �ڽſ��� �Ѱ����� '��Ȯ�ϰ� ����'�ؾ� �Ѵ�.
//
// ��Ϳ� ���� ���� 2
// ��� ��� �Լ��� '�ݺ���'������ ������ ������ �ϴ� �Լ��� ���� �� �ִ�.
// => �� ���, �ڵ�� ����������, �޸� / �ð������� ���ظ� ���ٴ� ������ �ִ�.
//
// ��Ϳ� ���� ���� 3
// fibo(n) = fibo(n-1) + fibo(n-2)
// �̿� ���� ��� �Լ��� �ڱ� �ڽ��� ���� �� ȣ���ϰ� �Ǹ�,
// �ݺ��Ǵ� ���� �������� ���� ������ ��ȿ������
// Dynamic Programming, Memoization�� �ʿ�
//
// ��Ϳ� ���� ���� 4
// ��� �Լ��� �ڱ� �ڽ��� �θ� ��,
// ���� ������ ��� return address�� �����Ǵµ�,
// �̷��� �Ǹ� ���� �޸� 1MB ���� ��������,
// 10������ ����Լ� ȣ��� ���� ��Ÿ�� ������ �߻��ϰ� ����. (�� ���̿� ���������� ���ϱ� �� �������� ..)
// ���� ��͸� ���� ���� �ϴ� ���, �ݺ������� �ذ��ؾ� �Ѵ�.

/// <summary>
/// 1���� N������ ���� ����ϴ� �Լ�
/// 
/// ���������� ������
/// => �Լ��� '�����ϴ� �帧'�� �״�� ���󰣴�
///	=> �׵��� �Ϲ������� ������ �Դ� ��
/// -> 3 �Է�
/// -> func1(2) ȣ��
/// -> func1(1) ȣ��
/// -> func1(0) ȣ��
/// -> 1 ���
/// -> 2 ���
/// -> 3 ���
/// 
/// �ͳ��� ������
/// => ������ �ϳ� �ϳ� ���󰡴� ���, �ͳ����� ����� ���ؼ� �����ؾ� �Ѵ�.
/// -> func1(1)�� 1�� ����Ѵ�
/// -> func1(k)�� k, k-1, k-2 ... 1�� ����ϸ� (������ �ߴ�)
/// -> func1(k+1)�� k+1, k, k-1 ... 1�� ����Ѵ�
/// 
/// </summary>
/// <param name="N"></param>
void func1(int N) {
	if (N == 0) return;
	func1(N - 1);
	cout << N << ' ';
}

int func2(int a, int b, int m)
{
	int val = 1;
	while (b--) val *= a;
	return val % m;
}
int func3(int base, int exponent, int modular)
{
	// O(N)�� �ð� ���⵵
	// N: exponent / While(exponent--)
	// ���࿡ exponent�� 20���̶� O(N)���ε� �ذ��� �� �������� ��� �ؾ��ϳ���?
	// cf O(N)�� ��� N�� 1000������ Ŀ���� �����ϴ�

	int value = 1;
	while(exponent--) value = value * base % modular;		// �� ���� �� modular operation�� ������� �����Ѵ�.
	return value;
}
ll func4(ll A, ll B, ll C)
{
	// A�� B�� ���� ���� C�� ���� �������� ����Ѵ�.

	// A^1 % C = X^1
	// A^2 % C = X^2
	// A^B % C = X^B

	// base condition
	if (B == 1) return A % C;
	// recursive
	ll res = func4(A, B / 2, C);
	// only keep modular value
	res = res * res % C;
	// exception (b is odd or even)
	if (B % 2 == 0) return res;
	// odd case
	return res * A % C;
}

//  1���� N������ ���� ���ϴ� �Լ�
//
int Sum(int N)	// ���ڸ� Ȱ���ؾ� �Ѵ�
{
	// N���� 1���� �ٿ����� ���� ���Ѵ�
	if (N > 0) {
		N += Sum(N - 1);
	}

	return N;
}

// ���丮�� ����ϱ�
// 
// ���� n�� �־��� ��, n! (���丮��)�� ��� �Լ��� ����Ͽ� ����ϴ� ���α׷��� �ۼ��Ͻÿ�.
// ���� �Է� : n = 5
// ���� ��� : 120
// 0! = 1
// 1! = 1
int Factorial(int n)
{
	if (n == 0) return 1;
	n *= Factorial(n - 1);
	return n;
}

// �Ǻ���ġ ����
// 
// ���� n�� �־��� ��, �Ǻ���ġ ������ n��° ���� ��� �Լ��� ����Ͽ� ���ϴ� ���α׷��� �ۼ��Ͻÿ�.
// ���� �Է� : n = 7
// ���� ��� : 13
// ù° �� ��°���� ������ 1
// Fibonacci (1) = 1
// Fibonacci (2) = 1
// Fibonacci (3) = Fibonacci (2) + Fibonacci (1)
// Fibonacci (k) = Fibonacci (k-1) + Fibonacci (k-2)
int Fibonacci(int n)
{
	if (n <= 2) return 1;

	if (memo[n] != -1) return memo[n]; // Memoization

	cout << "fibonacci(" << n << ")�� ȣ���" << '\n';
	memo[n] = Fibonacci(n - 1) + Fibonacci(n - 2);

	return memo[n];
}

int main()
{

	return 0;
}