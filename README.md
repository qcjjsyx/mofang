## 魔方自动复原
本文主要完成了魔方的自动还原。kociemba算法主要参考了：https://github.com/wangxiaoxiaohan/kociemba。   该算法我试了一下不能开箱即用，需要增加**#include<stdint>**在Linux上编译较为简单，直接运行make，windows我编译不来。

对于算法没有改进，只是对代码的结构有一定的修改，因为出于练习c++代码的目的，采用了对象的形式。不加入opencv的情况下可以开箱即用。

对于大多数的魔方，都能够找到20步左右的解法。具体kociemba算法，可以参考：https://blog.csdn.net/qq_23322639/article/details/121004065。简单来说，还是A*算法，但是对于g函数我们通过预处理计算出了各种状态到达最终状态的距离。与传统思路相比，kociemba算法对魔方的编码有很大改变，更适应降群的思想。
