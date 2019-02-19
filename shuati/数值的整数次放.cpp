class Solution {
public:
    // 快速幂乘法
    // 11011
    // 第一次算最右边的第一位，r = base
    // 第二次算第二位，此时发现还是1，所以r = 上一次(base) * 这一次(base^2)
    // ...
    // 第四次算第四位，此时发现还是1，所以r = 第一次(base) * 第二次(base^2) * 第三次(不用计算) * 这一次(base^8)
    double Power(double base, int exponent) {
        int n = abs(exponent);
        double r = 1.0f;
        while(n > 0) {
            if (n & 1) r *= base;
            base *= base;
            n >>= 1;
        }
        return exponent < 0 ? 1/r : r;
    }
};
