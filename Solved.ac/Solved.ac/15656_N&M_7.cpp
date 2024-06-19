#include <bits/stdc++.h>
using namespace std;

int N, M;
int a[10];
int res[10];

void Func(int curCount) {
    if (curCount == M) {
        for (int i = 0; i < curCount; i++) {
            cout << res[i] << ' ';
        }
        cout << '\n';
        return;
    }
    // �迭 ��ȸ
    for (int i = 0; i < N; i++) {
        int n = a[i];
        res[curCount] = n;
        Func(curCount + 1);
    }
}

int main()
{
    // Break the ios for C and C++
    std::ios::sync_with_stdio(false);

    // Untie the streams that bind cin and cout (Output cout before cin's buffer is empty)
    std::cin.tie(nullptr);

    // Title : N�� M (7)

    // ���� ���� ���� �� ��� �ȴ� i.e)

    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }

    // ���� ������ �����ؾ� �ϱ� ������
    std::sort(a, a + N);

    Func(0);

    return 0;
}