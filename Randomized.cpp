//关于随机化算法
#include<random>
#include<ctime>
#include<cmath>
#include<functional>


//随机数引擎，使用当前时间作为种子
std::default_random_engine e(static_cast<unsigned>(time(0)));
//随机数分布，生成0~1间的浮点数随机数
std::uniform_real_distribution<double>u(0, 1);


//蒙特卡洛算法：无法保证解的正确性，求得正确解的概率一般随计算时间增加而增大
//随机投点法计算π值
//n为投点个数
double MonteCarlo(long n) {

	//统计命中点（坐标位于四分之一圆内）个数
	double count = 0;

	//对x、y坐标进行n次随机投点
	for (long i = 0; i < n; ++i) {
		double x = u(e);
		double y = u(e);
		if (x*x + y*y <= 1)
			++count;
	}

	//返回π值
	return 4 * count / n;
}

//计算定积分（1）
//f为待测函数，a、b分别为定积分的的左右界限
//n为投点个数
double MonteCarlo(std::function<double(double)> f, 
	double a, double b, long n) {

	//统计f(x)的总值
	double sum = 0;

	//对x坐标进行n次随机投点
	for (long i = 0; i < n; ++i) {
		double x = u(e)*(b - a);
		sum += f(x);
	}

	//返回定积分值
	return (b - a)*sum / n;
}

//计算定积分（2）
//f为待测函数，a、b分别为定积分的左右界限，d为随机y坐标的最大值
//n为投点个数
double MonteCarlo(std::function<double(double)> f,
	double a, double b, double d, long n) {

	//统计命中点（y坐标位于对应f(x)值范围内）的个数
	unsigned count = 0;

	//对y坐标进行n次随机投点
	for (long i = 0; i < n; ++i) {
		double x = u(e)*(b - a);
		double y = u(e)*d;
		if (y <= f(x))
			++count;
	}

	//返回定积分值
	return (b - a)*d*count / n;
}

//集合相等问题（默认两集合大小相等）
//set1，set2为两待判断集合，集合大小为n
bool MonteCarlo(char *set1, char *set2, size_t n) {

	//从set1从随机取一个元素n次
	for (size_t i = 0; i < n; ++i) {
		size_t pos = e() % n;

		//将随机取得元素与set2中元素比较
		for (size_t j = 0; j < n; ++j) {

			//set2中存在与当前元素相等的元素，继续下一次比较
			if (set1[pos] == set2[j])
				break;

			//set2中不存在与当前元素相等的元素，返回false
			if (j == n - 1)
				return false;
		}
	}

	return true;
}

//主元素问题
//array为待判断集合，集合大小为n
bool Majority(char *set, size_t n) {
	size_t pos = e() % n;
	unsigned count = 0;
	for (size_t i = 0; i < n; ++i)
		if (set[pos] == set[i])
			++count;
	return count > (n / 2);
}

//素数测试（默认待测数>=3）
//费尔马小定理：若p为素数，且0<a<p，则(a^(p-1)) mod p=1
//二次探测定理：若p为素数，且0<x<p，则(x^2) mod p的解衡为x=1，x=p-1
//PrimeHelp函数递归计算a^(p-1) mod p，并在每次递归过程中应用二次探测定理
//isComposite储存二次探测定理的判断结果
unsigned PrimeHelp(unsigned a, unsigned n, unsigned p, bool &isComposite) {

	//递归到达终点
	if (p == 0)
		return 1;

	else {
		//获取下层递归结果
		unsigned tmp = PrimeHelp(a, n, p /2, isComposite);

		//应用二次探测定理
		unsigned result = (tmp*tmp) % n;
		if (result == 1 && tmp != 1 && tmp != n - 1)
			isComposite = true;

		//若p为奇数，修正计算结果
		if (p % 2)
			result = (result*a) % n;

		//返回计算结果
		return result;
	}
}

//Prim函数应用费尔马小定理判断素数
bool Prime(unsigned n) {

	//随机生成a值
	unsigned a = e() % (n - 3) + 2;
	bool isComposite = false;

	//应用费尔马小定理
	unsigned result = PrimeHelp(a, n, n - 1, isComposite);
	if (isComposite || result != 1)
		return false;
	else
		return true;
}


//舍伍德算法：消除算法最坏情况与特定实例之间的关联，总能求出正确解
//随机洗牌方法
//array为待洗牌序列，序列长度为n
char *Sherwood(char *array, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		size_t pos = e() % n;
		char tmp = array[i];
		array[i] = array[pos];
		array[pos] = tmp;
	}
	return array;
}


//拉斯维加斯算法：求得解一定正确，但有时找不到解，求得解的概率一般随计算时间增加而增大
//n皇后问题
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



