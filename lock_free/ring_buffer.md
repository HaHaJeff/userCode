## 区分缓冲区满或者空
**缓冲区是满或者**
- 总是保持一个存储单元为空

缓冲区中总是有一个存储单元保持未使用状态。缓冲区最多存入(size-1)个数据。如果读写指针指向同一位置，则缓冲区为空。如果写指针位于读指针的相邻后一个位置，则缓冲区为满。这种策略的优点是简单、鲁棒；缺点是语义上实际可存数据量与缓冲区容量不一致，测试缓冲区是否满需要做取余数计算。

- 使用数据计数

这种策略不使用显式的写指针，而是保持着缓冲区内存的数据的计数。因此，测试缓冲区是空是满非常简单；对性能影响可以忽略。缺点是读写操作需要修改这个存储数据计数，对于多线程访问缓冲区需要并发控制。

- 镜像指示位

缓冲区的长度如果是n，逻辑地址空间则为0至n-1；那么，规定n至2n-1为镜像逻辑地址空间。本策略规定读写指针的地址空间为0至2n-1，其中低部分对应于常规的逻辑地址空间，高半部分对应于镜像逻辑地址空间。当指针值大于等于2n时，使其折返到ptr-2n。使用一位表示写指针或读指针是否进入了虚拟的镜像存储区；置位表示进入，不置位表示没进入还在基本存储区。
在读写指针的值相同情况下，如果二者的指示位相同，说明缓冲区为空；如果二者的指示位不同，说明缓冲区为满。这种方法优点是测试缓冲区满/空　很简单；不需要做取余数操作；读写线程可以分别设计专用算法策略，能实现精致的并发控制。缺点是读写指针各需要额外的一位作为指示位。

**如果缓冲区长度是２的幂，则本方法可以省略镜像指示位。**

如果读写指针的值相等，则缓冲区为空；如果读写指针相差n，则缓冲区为满，这可以用条件表达式(写指针　== (读指针　异或　缓冲区长度))来判断。

``` cpp
#include <stdlib.h>
#include <stdio.h>

typedef struct {

} ElemType;

typedef struct {
  int size;
  int start;
  int end;
  ElemType* elems;
} CircularBuffer;

void cbInit(CircularBuffer* cb, int size) {
  cb->size = size;
  cb->start = 0;
  cb->end = 0;
  cb->elems = (ElemType*) calloc (cb->size, sizeof(ElemType));
}

void cbPrint(CircularBuffer* cb) {
  printf("size = 0x%x, start = %d, end = %d\n", cb->size, cb->start, cb->end);
}

// 0 1 2 3
// 0 1 2 3 4 5 6 7
// 此时end = 7, start = 3，但是操作cb[end]===cb[end&(size-1)]，即操作cb[3]，所以此时是满的
// end = start ^ size
int cbIsFull(CircularBuffer* cb) {
  return cb->end == (cb->start ^ cb->size);
}

int cbIsEmpty(CircularBuffer* cb) {
  return cb->end == cb->start;
}


// 递增index，范围为：０ - 2*size - 1，　为什么要两倍的size的操作空间
// 如果只有一倍的size操作空间，没有办法在不设置标志位的情况下直接对full或empty进行判断
// 例如size: 4, start: 0, end: 0，此时是空还是满？
int cbIncr(CircularBuffer* cb, int p) {
  return (p+1) & (2 * cb->size - 1);
}

void cbWrite(CircularBuffer* cb,ElemType* elem) {
    cb->elems[cb->end & (cb->size - 1)] == *elem;
    if (cbIsFull(cb))
        cb->start = cbIncr(cb, cb->start);
    cb->end = cbIncr(cb, cb->end);
}

void cbRead(CircularBuffer* cb, ElemType* elem) {
    *elem = cb->elems[cb->start & (cb->size - 1)];
    cb->start = cbIncr(cb, cb->start);
}
```
