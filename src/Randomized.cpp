//����������㷨
#include<random>
#include<ctime>
#include<cmath>
#include<functional>


//��������棬ʹ�õ�ǰʱ����Ϊ����
std::default_random_engine e(static_cast<unsigned>(time(0)));
//������ֲ�������0~1��ĸ����������
std::uniform_real_distribution<double>u(0, 1);


//���ؿ����㷨���޷���֤�����ȷ�ԣ������ȷ��ĸ���һ�������ʱ�����Ӷ�����
//���Ͷ�㷨�����ֵ
//nΪͶ�����
double MonteCarlo(long n) {

	//ͳ�����е㣨����λ���ķ�֮һԲ�ڣ�����
	double count = 0;

	//��x��y�������n�����Ͷ��
	for (long i = 0; i < n; ++i) {
		double x = u(e);
		double y = u(e);
		if (x*x + y*y <= 1)
			++count;
	}

	//���ئ�ֵ
	return 4 * count / n;
}

//���㶨���֣�1��
//fΪ���⺯����a��b�ֱ�Ϊ�����ֵĵ����ҽ���
//nΪͶ�����
double MonteCarlo(std::function<double(double)> f, 
	double a, double b, long n) {

	//ͳ��f(x)����ֵ
	double sum = 0;

	//��x�������n�����Ͷ��
	for (long i = 0; i < n; ++i) {
		double x = u(e)*(b - a);
		sum += f(x);
	}

	//���ض�����ֵ
	return (b - a)*sum / n;
}

//���㶨���֣�2��
//fΪ���⺯����a��b�ֱ�Ϊ�����ֵ����ҽ��ޣ�dΪ���y��������ֵ
//nΪͶ�����
double MonteCarlo(std::function<double(double)> f,
	double a, double b, double d, long n) {

	//ͳ�����е㣨y����λ�ڶ�Ӧf(x)ֵ��Χ�ڣ��ĸ���
	unsigned count = 0;

	//��y�������n�����Ͷ��
	for (long i = 0; i < n; ++i) {
		double x = u(e)*(b - a);
		double y = u(e)*d;
		if (y <= f(x))
			++count;
	}

	//���ض�����ֵ
	return (b - a)*d*count / n;
}

//����������⣨Ĭ�������ϴ�С��ȣ�
//set1��set2Ϊ�����жϼ��ϣ����ϴ�СΪn
bool MonteCarlo(char *set1, char *set2, size_t n) {

	//��set1�����ȡһ��Ԫ��n��
	for (size_t i = 0; i < n; ++i) {
		size_t pos = e() % n;

		//�����ȡ��Ԫ����set2��Ԫ�رȽ�
		for (size_t j = 0; j < n; ++j) {

			//set2�д����뵱ǰԪ����ȵ�Ԫ�أ�������һ�αȽ�
			if (set1[pos] == set2[j])
				break;

			//set2�в������뵱ǰԪ����ȵ�Ԫ�أ�����false
			if (j == n - 1)
				return false;
		}
	}

	return true;
}

//��Ԫ������
//arrayΪ���жϼ��ϣ����ϴ�СΪn
bool Majority(char *set, size_t n) {
	size_t pos = e() % n;
	unsigned count = 0;
	for (size_t i = 0; i < n; ++i)
		if (set[pos] == set[i])
			++count;
	return count > (n / 2);
}

//�������ԣ�Ĭ�ϴ�����>=3��
//�Ѷ���С������pΪ��������0<a<p����(a^(p-1)) mod p=1
//����̽�ⶨ����pΪ��������0<x<p����(x^2) mod p�Ľ��Ϊx=1��x=p-1
//PrimeHelp�����ݹ����a^(p-1) mod p������ÿ�εݹ������Ӧ�ö���̽�ⶨ��
//isComposite�������̽�ⶨ����жϽ��
unsigned PrimeHelp(unsigned a, unsigned n, unsigned p, bool &isComposite) {

	//�ݹ鵽���յ�
	if (p == 0)
		return 1;

	else {
		//��ȡ�²�ݹ���
		unsigned tmp = PrimeHelp(a, n, p /2, isComposite);

		//Ӧ�ö���̽�ⶨ��
		unsigned result = (tmp*tmp) % n;
		if (result == 1 && tmp != 1 && tmp != n - 1)
			isComposite = true;

		//��pΪ����������������
		if (p % 2)
			result = (result*a) % n;

		//���ؼ�����
		return result;
	}
}

//Prim����Ӧ�÷Ѷ���С�����ж�����
bool Prime(unsigned n) {

	//�������aֵ
	unsigned a = e() % (n - 3) + 2;
	bool isComposite = false;

	//Ӧ�÷Ѷ���С����
	unsigned result = PrimeHelp(a, n, n - 1, isComposite);
	if (isComposite || result != 1)
		return false;
	else
		return true;
}


//������㷨�������㷨�������ض�ʵ��֮��Ĺ��������������ȷ��
//���ϴ�Ʒ���
//arrayΪ��ϴ�����У����г���Ϊn
char *Sherwood(char *array, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		size_t pos = e() % n;
		char tmp = array[i];
		array[i] = array[pos];
		array[pos] = tmp;
	}
	return array;
}


//��˹ά��˹�㷨����ý�һ����ȷ������ʱ�Ҳ����⣬��ý�ĸ���һ�������ʱ�����Ӷ�����
//n�ʺ�����
bool N_Queens(int *result, int n) {
	int *mark = new int[n]();
	unsigned count = 1;
	for (int i = 0; i < n; ++i) {
		if (count > 0) {
			count = 0;
			for (int j = 0; j < n; ++j) {
				int x = e() % n;
				bool isFit = true;
				for (int k = 0; k < n - 1; ++k)
					if (result[k] == j || abs(result[k] - k) == abs(x - i))
						isFit = false;
				if (isFit)
					mark[count++] = j;
			}
			if (count > 0) {
				int x = e() % count;
				result[i] = mark[x];
			}
		}
		else {
			delete[]mark;
			return false;
		}
	}
	delete[]mark;
	if (count)
		return true;
	else
		return false;
}



