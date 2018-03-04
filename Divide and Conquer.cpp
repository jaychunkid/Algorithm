//���ڷ��η�
#include<iostream>
using std::cout;

//��ŵ������
//n����Ҫ�ƶ������ӱ�ţ���СΪ1��
//b����Ҫ�ƶ����������ڵ�����
//e����Ҫ�����ƶ���������
//t��ʾ����ĵ���������
void Hanoi(size_t n, char b, char e, char t) {
	
	//ֻ��һ�����ӣ�ֱ���ƶ�
	if (n == 1) {
		cout << n << ' ' << b << "->" << e << '\n';
		return;
	}

	//��ҪҪ�ƶ���n�����ӣ��Ƚ�n-1�������ƶ�������������ϣ�
	//�ƶ���n�����Ӻ��ٽ�n-1�������ƶ�����n��������
	Hanoi(n - 1, b, t, e);
	cout << n << ' ' << b << "->" << e << '\n';
	Hanoi(n - 1, t, e, b);
	return;
}


//���ֲ���
//*arrayΪ�����ҵ�����
//sizeΪ����ĳ���
//tΪ�����ҵ���
void BinarySearch(int *array, size_t size, int t) {
	size_t front = 0, back = size, mid;
	while (front + 1 < back) { 

		//�м�-1��������ܻ���ʵ������ڵ�βԪ��
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
	
	//�������г���Ϊ1ʱ��©����ͷԪ��
	if (array[front] == t) cout << front;          
	else cout << "Not found!";
}


//�鲢����
//*AΪ�����������
//bΪ����ͷԪ���±�
//eΪ����βԪ�صĺ�һ��λ���±�
void Mergesort(long* A, unsigned b, unsigned e) {
	
	//�����г���С�ڵ���1������Ҫ����
	if (b >= e - 1) return; 

	unsigned mid = (b + e) / 2;
	Mergesort(A, b, mid);          //ǰ�벿������
	Mergesort(A, mid, e);          //��벿������

	//����������ɵ�ǰ�벿������
	long *tmp = new long[mid - b];
	for (unsigned i = 0; i < mid - b; ++i)          
		tmp[i] = A[i + b];

	//��ǰ�������������кϲ�
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