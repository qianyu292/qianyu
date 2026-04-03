#include <vector>
#include <iostream>

std::vector<bool> sieveOfEratosthenes(int n) {
    // 假设所有数都是素数
    std::vector<bool> isPrime(n + 1, true);

    // 0和1不是素数
    if (n >= 0) isPrime[0] = false;
    if (n >= 1) isPrime[1] = false;

    // 从2开始筛
    for (int i = 2; i * i <= n; i++) {
        // 如果i是素数
        if (isPrime[i]) {
            // 从i*i开始标记，因为更小的倍数已经被更小的素数标记过
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }

    return isPrime;
}
