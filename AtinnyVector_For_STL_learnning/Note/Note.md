# Vector类引用关系

![Vector类引用关系](Vector类引用关系.png)



# vector.h

实现的接口如下：

**begin(), end(), size(), capacity(),  empty(),  operator[],  push_back(),  pop_back()** 

## allocator.h

实现的接口如下：

**allocate(), deallocate()**          // 调用simpleAlloc的接口

### simpleAlloc.h

实现的接口如下：

**allocate(), deallocate()**      //对malloc和free的简单封装

//SGI STL 2.91 版本中使用二级配置器，效率更优。当申请的内存大于128字节时使用第一级配置器（malloc和free），当申请的内存小于128字节时使用第二级配置器（向自定义的链表维护的内存申请）；

## memory.h

实现的接口如下：

**construct(), destory(), unintialized_fill_n(), unitialized_fill(), unintialized_copy()**

//五个工具，在申请的内存中初始化对象，析构对象。

### type_traites.h

//提取对象的类型

**为什么需要提取对象的类型？**
	对于c++本身支持的int，char等类型，采取更有效率的复制手法。对于用户自定义的类型，采用最安全保险的方法。 
``` c++
template<typrname T>

type_triates<T>::value_type  //获得对象T的类型
```
### iterator_traites.h

//提取迭代器所指对象的类型

``` c++
template<typrname T>

iterator_triates<T>::value_type  //获得迭代器T所指对象的类型
iterator_triates<T>::category   //获得迭代器T的类型（单向，双向，随机迭代器）
```