//关于动态规划
#include<iostream>
#include<string>
#include<set>
using std::cout;
using std::set;
using std::string;

//矩阵链乘法问题，有底向上的动态规划方法
//*p存储矩阵规模序列（长度n+1）
//**m存储计算结果（n*n）
//**s存储最优的分割点（n*n）
//n为矩阵数目
long Matrix_Chain_Multiply(const int *p, long **m,
	size_t **s, size_t n) {    

	for (size_t i = 0; i < n; ++i)
		m[i][i] = 0;                                      //长度为一的矩阵序列所需乘法次数为零

	for (size_t r = 2; r <= n; ++r)                       //r代表子序列长度
		for (size_t i = 0; i < n - r + 1; ++i) {          //i代表子序列首矩阵编号（0~n-1)
			size_t j = i + r - 1;                         //j代表子序列尾矩阵编号

			//计算分割点在子序列第一、二个矩阵之间所需的乘法次数
			m[i][j] = m[i + 1][j] + p[i] *
				p[i + 1] * p[j + 1];
			s[i][j] = i + 1;

			for (size_t k = i + 1; k < j; ++k) {          //k代表分割点
				long tmp = m[i][k] + m[k + 1][j] +
					p[i] * p[k + 1] * p[j + 1];

				//若该分割方法所需的乘法次数少于当前的最优乘法次数，则替换**m和**s中的值
				if (tmp < m[i][j]) {
					m[i][j] = tmp;
					s[i][j] = k + 1;
				}
			}
		}

	return m[0][n - 1];                                   //返回最优值
}


//矩阵链乘法问题，递归方法加入备忘机制
//*p存储矩阵规模序列（长度n+1）
//**m存储计算结果(默认所有元素已经初始化为0）（n*n）
//**s存储最优的分割点（的其中一个）（n*n)
//i为子序列首矩阵编号（1~n)
//j为子序列尾矩阵编号
long Matrix_Chain_Multiply(const int *p, long **m,
	size_t **s, size_t i, size_t j) {

	//长度为一的矩阵序列所需乘法次数为零 
	if (i == j) return 0;

	//若已经计算过该子序列的最优解，不计算直接返回
	if (m[i - 1][j - 1] != 0) return m[i - 1][j - 1];                   

	for (size_t k = i; k < j; ++k) {                           //k代表分割点
		long tmp = Matrix_Chain_Multiply(p, m, s, i, k) +           
			Matrix_Chain_Multiply(p, m, s, k + 1, j) +
			p[i - 1] * p[k] * p[j];

		//若该分割方法所需的乘法次数少于当前的最优乘法次数，则替换**m和**s中的值
		if (m[i - 1][j - 1] == 0 || m[i - 1][j - 1] > tmp) {
			m[i - 1][j - 1] = tmp;
			s[i - 1][j - 1] = k;
		}
	}

	return m[i - 1][j - 1];                                    //返回最优值
}


//最长公共子序列问题，
//*x，*y存放两条目标序列，长度分别为xn, yn
//**c存放最优值（规模为(xn+1)*(yn+1)）
unsigned Longest_Common_Subsequence(string x, string y, 
	unsigned **c) {
	size_t xn = x.size(), yn = y.size();

	//x，y分别与空集比较，最长公共子序列长恒为零
	for (size_t i = 0; i <= yn; ++i) c[0][i] = 0;  
	for (size_t i = 1; i <= xn; ++i) c[i][0] = 0;

	for (size_t i = 1; i <= xn; ++i)                //i对应x中下标为i-1的元素
		for (size_t j = 1; j <= yn; ++j) {          //j对应y中下标为j-1的元素

			if (x[i - 1] == y[j - 1]) 
				c[i][j] = c[i - 1][j - 1] + 1;

			else if (c[i - 1][j] >= c[i][j - 1]) 
				c[i][j] = c[i - 1][j];

			else
				c[i][j] = c[i][j - 1];
		}

	return c[xn][yn];                               //返回最优值
}

//输出最长公共子序列问题的一个最优解
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

//输出最长公共子序列问题的所有最优解（回溯法）
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


//最大子数组问题
//*array为待查询数组，其大小为n
//b，e储存最大子数组的首尾元素位置（1~n）
int Find_Maximum_SubArray(int *array, size_t n, size_t &b, size_t&e) {
	
	//sum储存最优值，tmp储存当前计算子数组的和
	//tmp_b储存当前计算子数组的首元素位置
	int sum = 0, tmp = 0;          
	b = e = 0;
	size_t tmp_b = 0;

	for (size_t i = 0; i < n; ++i) {

		//当前计算子数组的和为正数，累加
		if (array[i] < tmp + array[i])
			tmp += array[i];

		//若下一个元素为正数且当前计算子数组和为负数，
		//将该元素设置为计算子数组的首元素
		else {
			tmp = array[i];
			tmp_b = i + 1;
		}

		//当前计算子数组的和大于之前最大子数组的和，
		//则更新sum,b,e的值
		if (sum < tmp) {
			sum = tmp;
			b = tmp_b;
			e = i + 1;
		}
	}

	return sum;
}


//0-1背包问题
//*values对应物品价值，*weights对应物品重量
//n代表物品数量，s代表背包最大容量
//**c储存最优值计算结果（n*（s+1））
int Knapsack(int *values, unsigned *weights, size_t n, size_t s, int **c) {
	
	//第一个物品（由尾向前）待判断的情况：
	for (size_t j = 0; j <= s; ++j) {

		//当前背包剩余容量大于该物品质量，背包内物品价值为该物品价值
		if (j >= weights[n - 1])                  
			c[n - 1][j] = values[n - 1];

		//否则，背包内物品价值和为零
		else c[n - 1][j] = 0;
	}

	//i代表待处理的物品编号（2~n-1）
	//j代表背包剩余容量（0~s-1）
	for (size_t i = n - 1; i > 1; --i)
		for (size_t j = 0; j < s; ++j) {

			//如果背包能装下该物品，根据之前计算的最优值选择是否装下该物品
			if (j >= weights[i - 1])
				c[i - 1][j] = c[i][j] > (c[i][j - weights[i - 1]] + values[i - 1]) ?
				c[i][j] : (c[i][j - weights[i - 1]] + values[i - 1]);

			else c[i - 1][j] = c[i][j];
		}
	
	//在有至少两个物品的情况下，对于第一个物品，只需计算容量为s时的情况
	if (n > 1) {
		if (s > weights[0])
			c[0][s] = c[1][s] > (c[1][s - weights[0]] + values[0]) ?
			c[0][s] : (c[1][s - weights[0]] + values[0]);
		else
			c[0][s] = c[1][s];
	}

	return c[0][s];          //返回最优值
}

//输出0-1背包问题的一个最优解
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


//最长上升子序列问题
//*array为待查找序列，序列长度为n
unsigned Longest_Increasing_Subsequence(int *array, size_t n) {

	unsigned *result = new unsigned[n]();          //存储临时计算结果
	unsigned max = 0;                              //储存当前的最优值

	//result[i]记录下标0~i的子序列的最长上升子序列大小
	for (size_t i = 0; i < n; ++i) {

		result[i] = 1;                             //初始值为1

		//遍历该子序列中包含的所有子序列（序列尾编号为0~i-1）
		for (size_t j = 0; j < i; ++j)

			//尾编号为j的子序列尾元素小于当前子序列的尾元素
			if (array[i] > array[j])

				//判断是否更新当前子序列的问题最优值
				result[i] = result[j] + 1 > result[i] ? result[j] + 1 : result[i];
		
		//该子序列最优值大于当前最优值，则更新最优值
		if (result[i] > max)
			max = result[i];
	}
	return max;                                    //返回最优值
}

