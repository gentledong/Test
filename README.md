# MyHeap< Elem , Storage<Elem> , Comp<ELem> >, ELem是元素类型，Storage是存储器，Comp是比较器


MyHeap和make_heap，push_heap，pop_heap都可以模仿priority的实现。

MyHeap里面实现的siftDown会优先选择左孩子来交换(当左右孩子相等时)，MyHeap里面的popHeap、pushHeap和sortHeap更安全，要提前判断makeHeap已经做过才执行。
而pop_heap，push_heap，sort_heap没有这种检查。

less<int>(),greater<int>()，cmp<int>()是二元仿函数，函数可以当做参数来传递。
模板里面用less<int>,cmp<int>，函数里面用less<int>()，cmp<int>()。
