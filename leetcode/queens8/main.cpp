/*************************************************************************
  > File Name: main.cpp
  > Author: MSGF_NGINX
  > Mail: 327767852@qq.com
  > Created Time: 2017年09月29日 星期五 15时55分17秒
 ************************************************************************/

#include <iostream>
#include <vector>
#define ABS(x) ((x) < 0 ? (-x):(x))

using namespace std;


template <typename T>
T abs(T t) {

    return t < 0 ? -t : t;
}

//不能在同一行 同一列 对角线上
bool Check(const vector<int> &arr, int num) {

    for(int i = 2; i <= num; i++) {
        for(int j = 1; j < i; j++) {
            if(arr[i] == arr[j] || abs(arr[i] - arr[j]) == i - j)
                return false;
        }

    }

    return true;

}


void Print(const vector<int> &arr) {

    static int count = 0;
    int len = arr.size();

    cout << "the case " << count++ << endl;
    for(int i = 1; i < len; i++) {

        cout << arr[i] << "\t";

    }

    cout << endl;

}

void QueensEightRecv(vector<int> &arr, int num) {

    int len = arr.size();

    if(num >= len) {

        Print(arr);
    } else {

        for(int i = 1; i < len; i++) {
            arr[num] = i;
            if(Check(arr, num))
                QueensEightRecv(arr, num+1);
        }

    }
    return;

}

void QueensEightCircle(vector<int> &arr, int num) {

    int k = 1;

    while(k > 0) {

        arr[k] = arr[k] + 1;

        while(arr[k] <= num && !Check(arr, k)) arr[k] = arr[k] + 1;

        //找到合适摆放位置
        if(arr[k] <= num) {
            if(k == num) Print(arr);
            else {
                k += 1;
                arr[k] = 0;
            }
        } else {
                k -= 1;
        }
    }

    return ;
}


int main(void)
{

    vector<int> arr(9, 0);

//    QueensEightRecv(arr, 1);
    QueensEightCircle(arr, 8);
    return 0;
}
