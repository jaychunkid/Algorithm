//关于贪心算法
#include<algorithm>
#include<string>
using std::string;
using std::sort;

//活动选择问题
//同一个活动的开始和结束时间使用一个pair储存
//开始时间：pair::first，结束时间：pair::second
using time = std::pair<unsigned, unsigned>;
bool Compare_End_Time(const time &, const time &);

//*T存储活动信息，共有n个活动
unsigned Activity_Selector(time *T, size_t n) {

	//将活动按照结束时间从早到晚的顺序排序
	sort(T, T + n, Compare_End_Time);
	
	//result记录最优值，count记录最后一个已选择活动的结束时间
	unsigned result = 0, count = 0;
	for (size_t i = 0; i < n; ++i) {

		//如果当前活动在最后一个已选择活动结束后开始
		//，则将当前活动加入解
		if (T[i].first >= count) {
			count = T[i].second;
			++result;
		}
	}

	return result;          //返回最优值
}

//CompareEndTime函数实现根据活动的结束时间比较大小
bool Compare_End_Time(const time &lt, const time &rt) {
	return lt.second < rt.second;
}


//分数背包问题
//同一件物品的价值和质量用一个pair储存
//价值：pair::first，质量：pair::second
using item = std::pair<double, unsigned>;
bool Compare_Value(const item &, const item &);

//*T存储物品信息，共有n个物品，背包容量为s
double Knapsack(item *T, size_t n, unsigned s) {

	//将物品按照价值、质量比从大到小排序
	sort(T, T + n, Compare_Value);

	double result = 0;          //result计算最优值
	for (size_t i = 0; i < n; ++i) {
		
		//背包容量足以装下整个物品，整个装入
		if (s >= T[i].second) {
			result += T[i].first;
			s -= T[i].second;
		}

		//背包容量不足以装下整个物品，分割后装入
		else {
			result += T[i].first / T[i].second*s;
			s = 0;
			break;
		}
	}

	return result;             //返回最优值
}

//CompareValue函数实现根据物品的价值、质量比比较大小
bool Compare_Value(const item &li, const item &ri) {
	return li.first / li.second > ri.first / ri.second;
}


//删除数字问题
//str为待删除数，k为需要删除的数字个数
//若删除结果为0，则返回空字符串
string Delete_Digits(string str, size_t k) {
	if (str == string())
		return str;

	while (k--)
		//从左到右寻找第一个逆序数字并删除
		for (size_t i = 1; i < str.length();++i)
			if (str[i] < str[i - 1]) {
				str = str.substr(0, i - 1) + str.substr(i);
				break;
			}

	//删除结果中的无效零
	size_t i = 0;
	for (; i < str.length() && str[i] == '0'; ++i);
	str = str.substr(i);

	return str;
}

