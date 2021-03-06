# 什么是virtual memory

- 虚拟内存是操作系统用来做地址映射的
  - 操作系统可以将虚拟地址映射到物理地址空间
    - 映射为物理内存
    - 映射为硬件设备
      - PCI设备
      - GPU RAM
- 优势
  - 每一个进程可以有不同的内存映射
    - 一个进程的RAM对于其他进程来说是不可见的 **内存保护**
    - 内核内存对用户进程是不可见的
  - 内存可以被移动
  - 内存可以被交换到磁盘
  - 硬件设备内存能够被映射到进程地址空间 **需要内核执行mapping**
  - 物理RAM能够被同时映射到多个进程 **共享内存**
  - 内存区域能够有访问权限 **read write execute**

# MMU 

- 对所有来自Load/Store的内存访问指令进行翻译
  - 将虚拟地址映射到系统RAM
  - 将虚拟地址映射到外设
  - 处理权限问题
  - 对一个无效地址产生一个异常 **page fault**
    - 未映射的地址或无效的权限

# Page Faults

- page fault是一个CPU异常，当软件试图使用一个无效的虚拟地址时产生
  1. 虚拟地址没有被映射到它所请求的进程
  2. 进程没有权限访问这些地址
  3. 虚拟地址是有效的，但是已经被交换了

  