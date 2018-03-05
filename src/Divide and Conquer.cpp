//关于分治法
#include<iostream>
using std::cout;

//汉诺塔问题
//n代表要移动的盘子编号（最小为1）
//b代表要移动的盘子所在的柱子
//e代表要盘子移动到的柱子
//t表示空余的第三条柱子
void Hanoi(size_t n, char b, char e, char t) {
	
	//只有一个盘子，直接移动
	if (n == 1) {
		cout << n << ' ' << b << "->" << e << '\n';
		return;
	}

	//若要要移动第n个盘子，先将n-1个盘子移动到空余的柱子上，
	//移动第n个盘子后，再将n-1个盘子移动到第n个盘子上
	Hanoi(n - 1, b, t, e);
	cout << n << ' ' << b << "->" << e << '\n';
	Hanoi(n - 1, t, e, b);
	return;
}


//二分查找
//*array为待查找的数组
//size为数组的长度
//t为带查找的数
void BinarySearch(int *array, size_t size, int t) {
	size_t front = 0, back = size, mid;
	while (front + 1 < back) { 

		//切记-1，否则可能会访问到不存在的尾元素
		mid = (front + back - 1) / 2;               
		if (array[mid] == t) {
			cout << mid;
			return;
		}
		else if (array[mid] > t)
			back = mid;
		else
			front = mid + 1;
	}
	
	//当子序列长度为1时会漏查找头元素
	if (array[front] == t) cout << front;          
	else cout << "Not found!";
}


//归并排序
//*A为待排序的序列
//b为序列头元素下标
//e为序列尾元素的后一个位置下标
void Mergesort(long* A, unsigned b, unsigned e) {
	
	//子序列长度小于等于1，不需要排序
	if (b >= e - 1) return; 

	unsigned mid = (b + e) / 2;
	Mergesort(A, b, mid);          //前半部分排序
	Mergesort(A, mid, e);          //后半部分排序

	//复制排序完成的前半部分序列
	long *tmp = new long[mid - b];
	for (unsigned i = 0; i < mid - b; ++i)          
		tmp[i] = A[i + b];

	//将前后两部分子序列合并
	unsigned i1 = 0, i2 = mid;
	for (unsigned i = b; i < e; ++i) {
		if (i1 == mid - b)
			A[i] = A[i2++];
		else if (i2 == e)
			A[i] = tmp[i1++];
		else if (tmp[i1] < A[i2])
			A[i] = tmp[i1++];
		else
			A[i] = A[i2++];
	}

	delete[]tmp;
}