//���ڶ�̬�滮
#include<iostream>
#include<string>
#include<set>
using std::cout;
using std::set;
using std::string;

//�������˷����⣬�е����ϵĶ�̬�滮����
//*p�洢�����ģ���У�����n+1��
//**m�洢��������n*n��
//**s�洢���ŵķָ�㣨n*n��
//nΪ������Ŀ
long Matrix_Chain_Multiply(const int *p, long **m,
	size_t **s, size_t n) {    

	for (size_t i = 0; i < n; ++i)
		m[i][i] = 0;                                      //����Ϊһ�ľ�����������˷�����Ϊ��

	for (size_t r = 2; r <= n; ++r)                       //r���������г���
		for (size_t i = 0; i < n - r + 1; ++i) {          //i�����������׾����ţ�0~n-1)
			size_t j = i + r - 1;                         //j����������β������

			//����ָ���������е�һ����������֮������ĳ˷�����
			m[i][j] = m[i + 1][j] + p[i] *
				p[i + 1] * p[j + 1];
			s[i][j] = i + 1;

			for (size_t k = i + 1; k < j; ++k) {          //k����ָ��
				long tmp = m[i][k] + m[k + 1][j] +
					p[i] * p[k + 1] * p[j + 1];

				//���÷ָ������ĳ˷��������ڵ�ǰ�����ų˷����������滻**m��**s�е�ֵ
				if (tmp < m[i][j]) {
					m[i][j] = tmp;
					s[i][j] = k + 1;
				}
			}
		}

	return m[0][n - 1];                                   //��������ֵ
}


//�������˷����⣬�ݹ鷽�����뱸������
//*p�洢�����ģ���У�����n+1��
//**m�洢������(Ĭ������Ԫ���Ѿ���ʼ��Ϊ0����n*n��
//**s�洢���ŵķָ�㣨������һ������n*n)
//iΪ�������׾����ţ�1~n)
//jΪ������β������
long Matrix_Chain_Multiply(const int *p, long **m,
	size_t **s, size_t i, size_t j) {

	//����Ϊһ�ľ�����������˷�����Ϊ�� 
	if (i == j) return 0;

	//���Ѿ�������������е����Ž⣬������ֱ�ӷ���
	if (m[i - 1][j - 1] != 0) return m[i - 1][j - 1];                   

	for (size_t k = i; k < j; ++k) {                           //k����ָ��
		long tmp = Matrix_Chain_Multiply(p, m, s, i, k) +           
			Matrix_Chain_Multiply(p, m, s, k + 1, j) +
			p[i - 1] * p[k] * p[j];

		//���÷ָ������ĳ˷��������ڵ�ǰ�����ų˷����������滻**m��**s�е�ֵ
		if (m[i - 1][j - 1] == 0 || m[i - 1][j - 1] > tmp) {
			m[i - 1][j - 1] = tmp;
			s[i - 1][j - 1] = k;
		}
	}

	return m[i - 1][j - 1];                                    //��������ֵ
}


//��������������⣬
//*x��*y�������Ŀ�����У����ȷֱ�Ϊxn, yn
//**c�������ֵ����ģΪ(xn+1)*(yn+1)��
unsigned Longest_Common_Subsequence(string x, string y, 
	unsigned **c) {
	size_t xn = x.size(), yn = y.size();

	//x��y�ֱ���ռ��Ƚϣ�����������г���Ϊ��
	for (size_t i = 0; i <= yn; ++i) c[0][i] = 0;  
	for (size_t i = 1; i <= xn; ++i) c[i][0] = 0;

	for (size_t i = 1; i <= xn; ++i)                //i��Ӧx���±�Ϊi-1��Ԫ��
		for (size_t j = 1; j <= yn; ++j) {          //j��Ӧy���±�Ϊj-1��Ԫ��

			if (x[i - 1] == y[j - 1]) 
				c[i][j] = c[i - 1][j - 1] + 1;

			else if (c[i - 1][j] >= c[i][j - 1]) 
				c[i][j] = c[i - 1][j];

			else
				c[i][j] = c[i][j - 1];
		}

	return c[xn][yn];                               //��������ֵ
}

//�������������������һ�����Ž�
void Print_LCS(string x, string y, unsigned **c, size_t i, size_t j) {
	if (i == 0 || j == 0) {
		return;
	}

	if (x[i - 1] == y[j - 1]) {
		Print_LCS(x, y, c, i - 1, j - 1);
		cout << y[j - 1];
	}

	else if (c[i][j] == c[i - 1][j])
		Print_LCS(x, y, c, i - 1, j);

	else Print_LCS(x, y, c, i, j - 1);

	return;
}

//��������������������������Ž⣨���ݷ���
set<string> Print_All_LCS(string x, string y, unsigned **c, size_t i, size_t j) {
	set<string> result;
	
	if (i == 0 || j == 0) {
		result.insert(string());
		return result;
	}

	if (x[i - 1] == y[j - 1]) {
		set<string> tmp = Print_All_LCS(x, y, c, i - 1, j - 1);
		for (string str : tmp)
			result.insert(str + y[j - 1]);
		return result;
	}

	else if (c[i - 1][j] == c[i][j - 1]) {
		set<string> tmp1 = Print_All_LCS(x, y, c, i - 1, j);
		for (const string &str : tmp1)
			result.insert(str);
		set<string> tmp2 = Print_All_LCS(x, y, c, i, j - 1);
		for (const string &str : tmp2)
			result.insert(str);
		return result;
	}

	else if (c[i][j] == c[i - 1][j])
		return Print_All_LCS(x, y, c, i - 1, j);
	else
		return Print_All_LCS(x, y, c, i, j - 1);
}


//�������������
//*arrayΪ����ѯ���飬���СΪn
//b��e����������������βԪ��λ�ã�1~n��
int Find_Maximum_SubArray(int *array, size_t n, size_t &b, size_t&e) {
	
	//sum��������ֵ��tmp���浱ǰ����������ĺ�
	//tmp_b���浱ǰ�������������Ԫ��λ��
	int sum = 0, tmp = 0;          
	b = e = 0;
	size_t tmp_b = 0;

	for (size_t i = 0; i < n; ++i) {

		//��ǰ����������ĺ�Ϊ�������ۼ�
		if (array[i] < tmp + array[i])
			tmp += array[i];

		//����һ��Ԫ��Ϊ�����ҵ�ǰ�����������Ϊ������
		//����Ԫ������Ϊ�������������Ԫ��
		else {
			tmp = array[i];
			tmp_b = i + 1;
		}

		//��ǰ����������ĺʹ���֮ǰ���������ĺͣ�
		//�����sum,b,e��ֵ
		if (sum < tmp) {
			sum = tmp;
			b = tmp_b;
			e = i + 1;
		}
	}

	return sum;
}


//0-1��������
//*values��Ӧ��Ʒ��ֵ��*weights��Ӧ��Ʒ����
//n������Ʒ������s�������������
//**c��������ֵ��������n*��s+1����
int Knapsack(int *values, unsigned *weights, size_t n, size_t s, int **c) {
	
	//��һ����Ʒ����β��ǰ�����жϵ������
	for (size_t j = 0; j <= s; ++j) {

		//��ǰ����ʣ���������ڸ���Ʒ��������������Ʒ��ֵΪ����Ʒ��ֵ
		if (j >= weights[n - 1])                  
			c[n - 1][j] = values[n - 1];

		//���򣬱�������Ʒ��ֵ��Ϊ��
		else c[n - 1][j] = 0;
	}

	//i������������Ʒ��ţ�2~n-1��
	//j������ʣ��������0~s-1��
	for (size_t i = n - 1; i > 1; --i)
		for (size_t j = 0; j < s; ++j) {

			//���������װ�¸���Ʒ������֮ǰ���������ֵѡ���Ƿ�װ�¸���Ʒ
			if (j >= weights[i - 1])
				c[i - 1][j] = c[i][j] > (c[i][j - weights[i - 1]] + values[i - 1]) ?
				c[i][j] : (c[i][j - weights[i - 1]] + values[i - 1]);

			else c[i - 1][j] = c[i][j];
		}
	
	//��������������Ʒ������£����ڵ�һ����Ʒ��ֻ���������Ϊsʱ�����
	if (n > 1) {
		if (s > weights[0])
			c[0][s] = c[1][s] > (c[1][s - weights[0]] + values[0]) ?
			c[0][s] : (c[1][s - weights[0]] + values[0]);
		else
			c[0][s] = c[1][s];
	}

	return c[0][s];          //��������ֵ
}

//���0-1���������һ�����Ž�
void Print_Knapsack_Answer(unsigned *weights, size_t n, size_t s, int **c) {
	size_t i = 0, j = s;
	for (; i < n - 1; ++i) {
		if (c[i][j] == c[i + 1][j])
			cout << "0 ";
		else {
			cout << "1 ";
			j -= weights[i];
		}
	}
	if (j > weights[i])
		cout << "1 ";
	else
		cout << "0 ";
}


//���������������
//*arrayΪ���������У����г���Ϊn
unsigned Longest_Increasing_Subsequence(int *array, size_t n) {

	unsigned *result = new unsigned[n]();          //�洢��ʱ������
	unsigned max = 0;                              //���浱ǰ������ֵ

	//result[i]��¼�±�0~i�������е�����������д�С
	for (size_t i = 0; i < n; ++i) {

		result[i] = 1;                             //��ʼֵΪ1

		//�������������а��������������У�����β���Ϊ0~i-1��
		for (size_t j = 0; j < i; ++j)

			//β���Ϊj��������βԪ��С�ڵ�ǰ�����е�βԪ��
			if (array[i] > array[j])

				//�ж��Ƿ���µ�ǰ�����е���������ֵ
				result[i] = result[j] + 1 > result[i] ? result[j] + 1 : result[i];
		
		//������������ֵ���ڵ�ǰ����ֵ�����������ֵ
		if (result[i] > max)
			max = result[i];
	}
	return max;                                    //��������ֵ
}

