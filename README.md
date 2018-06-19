## date目录
### CDate类

- 通过string传入时间(format: 2018-05-12 23:35:12)
- 通过parse接口将其转换为两个unsigned int
- 使用linux内核计算日期时间的方法进行时间统计，代码如下
```
unsigned int GetDays() const {
	int year  = GetYear();
	int month = GetMonth();
	int day   = GetDay();

	if (0 >= (int)(month -= 2)) {
		month += 12;
		year -= 1;
	}

	return (year/4 - year/100 + year/400 + 367*month/12 + day) + year*365 - 719499;
    }
```

## design_pattern目录
### 实现一些经典的实设计模式
- agent
- decorator
- factory
- factory-method
- prototype
- strategy
- ...

## leetcode
### 偶尔刷题的一些记录

## shell
### 平常用到的一些脚本
- chmod_dir_and_file.sh
	将windows下的目录拷贝到虚拟机内时，目录的权限可能会出现一些问题，对于有强迫症的我而言...，所以该脚本对该目录下的文件以及文件进行了权限修正
	
## socket
### 封装了一些套接字的基本调用

## corountine
### 使用ucontext_t完成上下文切换
代码参考自phxrpc，从中剥离出来了协成相关的文件
### 复用已经完成工作的协程空间
CoContextRuntime通过vector对协程进行保存，完成工作的协程通过一种类似链表的方式组织起来，从而可以起到协程的复用
