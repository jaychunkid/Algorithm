//关于回溯法
#include<cmath>


//交换数组*array中下标为i、j的元素
template <typename T>
void swap(T *array, size_t i, size_t j) {
	if (i != j) {
		T tmp = array[i];
		array[i] = array[j];
		array[j] = tmp;
	}
}


//0-1背包问题
class Knapsack {
	int *values;                //物品价值
	unsigned *weights;          //物品质量
	size_t num;                 //物品数量
	unsigned vol;               //背包容量

	bool *preResult;            //当前装入方案
	int preValues;              //当前装入物品总价值
	int restValues;             //未装入物品总价值

	bool *bestResult;           //最优解
	int bestValues;             //最优值
	bool hasRun;                //标记是否已经运行过计算函数
	
	//回溯法实现函数
	void backtrack(size_t i = 0) {

		//到达子集树叶节点
		if (i == num - 1) {

			//判断是否能装入最后一个物品
			if (vol >= weights[i]) {
				preResult[i] = true;
				preValues += values[i];
			}

			//更新最优解和最优值
			if (preValues > bestValues) {
				bestValues = preValues;
				for (size_t j = 0; j < num; ++j)
					bestResult[j] = preResult[j];
			}

			if (preResult[i]) {
				preResult[i] = false;
				preValues -= values[i];
			}

			return;
		}


		//处于子集树中间节点
		restValues -= values[i];

		//遍历左子树
		if (vol >= weights[i]) {
			preResult[i] = true;
			preValues += values[i];
			vol -= weights[i];
			backtrack(i + 1);
			preResult[i] = false;
			preValues -= values[i];
			vol += weights[i];
		}

		//遍历右子树
		if (preValues + restValues > bestValues)
			backtrack(i + 1);

		restValues += values[i];
		return;
	}

public:
	//构造函数
	Knapsack(int *val, unsigned *wei, size_t n,
		unsigned v, unsigned m = 0) :values(val),
		weights(wei), num(n), vol(v), restValues(m),
		preValues(0), bestValues(0), hasRun(false) {

		//未装入物品总价值的初始值为所有物品的总价值
		if (!restValues) {
			for (size_t i = 0; i < num; ++i)
				restValues += values[i];
		}

		preResult = new bool[num];
		bestResult = new bool[num];
		for (size_t i = 0; i < num; ++i)
			preResult[i] = bestResult[i] = false;
	}

	//析构函数
	~Knapsack() {
		delete[]preResult;
		delete[]bestResult;
	}

	//计算并返回最优值
	int getBestValues() {
		if (!hasRun) {
			backtrack();
			hasRun = true;
		}
		return bestValues; 
	}

	//获取最优解的拷贝
	bool *getBestResult() {
		if (!hasRun)
			getBestValues();
		bool *copy = new bool[num];
		for (size_t i = 0; i < num; ++i)
			copy[i] = bestResult[i];
		return copy;
	}
};


//旅行商问题
class Traveling_Salesman {
	int **graph;                  //图
	size_t num;                   //节点数
	size_t outset;                //起点编号

	unsigned *preResult;          //当前路径
	int preDistance;              //当前路程

	unsigned *bestResult;         //最优解
	int bestDistance;             //最优值
	bool hasRun;                  //标记是否已经运行过计算函数
								  
	//回溯法实现函数
	void backtrack(size_t i = 0) {

		//到达子集树叶节点
		if (i == num - 1) {

			//更新最优解和最优值
			if ((bestDistance == 0) || ((preDistance +
				graph[preResult[i]][outset])
				< bestDistance)) {
				bestDistance = preDistance +
					graph[preResult[i]][outset];
				for (size_t j = 0; j < num; ++j)
					bestResult[j] = preResult[j];
			}

			return;
		}

		//处于子集树中间节点
		for (size_t j = i + 1; j < num; ++j) {

			//判断是否继续拓展节点
			if ((bestDistance == 0) || ((preDistance +
				graph[preResult[i]][preResult[j]]) < bestDistance)) {
				preDistance += graph[preResult[i]][preResult[j]];
				swap(preResult, i + 1, j);
				backtrack(i + 1);
				swap(preResult, i + 1, j);
				preDistance -= graph[preResult[i]][preResult[j]];
			}
		}
		return;
	}

public:
	//构造函数
	Traveling_Salesman(int **g, size_t n, size_t out = 0) :
		graph(g), num(n), outset(out), 
		preDistance(0), bestDistance(0), hasRun(false) {
		preResult = new unsigned[num];
		bestResult = new unsigned[num]();
		for (size_t i = 0; i < num; ++i)
			preResult[i] = i;
		swap(preResult, 0, outset);
	}

	//析构函数
	~Traveling_Salesman() {
		delete[]preResult;
		delete[]bestResult;
	}

	//计算并返回最优值
	int getBestDistance() {
		if (!hasRun) {
			backtrack();
			hasRun = true;
		}
		return bestDistance; 
	}

	//获取最优解的拷贝
	unsigned *getBestResult() { 
		if (!hasRun)
			getBestDistance();
		unsigned *copy = new unsigned[num];
		for (size_t i = 0; i < num; ++i)
			copy[i] = bestResult[i];
		return copy; 
	}
};


//批处理作业调度问题
class Batch_Job_Scheduling {
	int **time;                   //各任务所需时间
	size_t num;                   //任务数

	unsigned *preResult;          //当前作业调度
	int preTime1;                 //当前机器1完成时间
	int *preTime2;                //当前机器2各任务
	int preTime;                  //当前总完成时间

	unsigned *bestResult;         //最优解
	int bestTime;                 //最优值
	bool hasRun;                  //标记是否已经运行过计算函数

	//回溯法实现函数
	void backtrack(size_t i = 0) {

		//到达子集树叶节点
		if (i == num - 1) {
			preTime1 += time[0][preResult[i]];
			if (i == 0 || preTime2[i - 1] < preTime1)
				preTime2[i] = preTime1 + time[1][preResult[i]];
			else
				preTime2[i] = preTime2[i - 1] + time[1][preResult[i]];

			//更新最优解和最优值
			if (bestTime == 0 || preTime + preTime2[i] < bestTime) {
				bestTime = preTime + preTime2[i];
				for (size_t j = 0; j < num; ++j)
					bestResult[j] = preResult[j];
			}

			preTime1 -= time[0][preResult[i]];
			return;
		}

		//处于子集树中间节点
		for (size_t j = i; j < num; ++j) {
			swap(preResult, i, j);
			preTime1 += time[0][preResult[i]];
			if (i == 0 || preTime2[i - 1] < preTime1)
				preTime2[i] = preTime1 + time[1][preResult[i]];
			else
				preTime2[i] = preTime2[i - 1] + time[1][preResult[i]];
			preTime += preTime2[i];

			//判断是否继续拓展节点
			if (bestTime == 0 || preTime < bestTime)
				backtrack(i + 1);

			preTime -= preTime2[i];
			preTime1 -= time[0][preResult[i]];
			swap(preResult, i, j);
		}
		return;
	}

public:
	//构造函数
	Batch_Job_Scheduling(int **t, size_t n) :time(t), 
		num(n), preTime1(0), preTime(0), bestTime(0),
		hasRun(false) {
		preResult = new unsigned[num];
		bestResult = new unsigned[num]();
		preTime2 = new int[num]();

		for (size_t i = 0; i < num; ++i)
			preResult[i] = i;
	}

	//析构函数
	~Batch_Job_Scheduling() {
		delete[]preResult;
		delete[]preTime2;
		delete[]bestResult;
	}

	//计算并返回最优值
	int getBestTime() { 
		if (!hasRun) {
			backtrack();
			hasRun = true;
		}
		return bestTime;
	}

	//获取最优解的拷贝
	unsigned *getBestResult() {
		if (!hasRun)
			getBestTime();
		unsigned *copy = new unsigned[num];
		for (size_t i = 0; i < num; ++i)
			copy[i] = bestResult[i];
		return copy;
	}
};


//符号三角形问题
class Triangle {
	size_t num;                   //三角形第一行的符号数目
	unsigned sum;                 //统计符合条件的三角形总数
	bool hasRun;                  //标记是否已经运行过计算函数

	unsigned count;               //统计当前三角形中减号数目
	unsigned **triangle;          //储存三角形的符号

	//回溯法实现函数
	void backtrack(size_t i = 0) {

		//减号数目超过三角形总符号数的一半，剪枝
		if (count > (1 + num)*num / 4)
			return;

		//到达子集树的叶节点之后
		if (i == num) {
			++sum;
			return;
		}

		//处于子集树的中间节点
		unsigned tmp = 0;          //统计当前斜行中减号数目

		//遍历子树
		for (size_t j = 0; j < 2; ++j) {
			triangle[0][j] = j;
			tmp = j;

			//根据第一行新填入符号填入斜行其他符号
			for (size_t k = 1; k <= i; ++k) {
				triangle[k][i - k] = triangle[k - 1][i - k] 
					^ triangle[k - 1][i - k + 1];
				tmp += triangle[k][i - k];
			}

			count += tmp;
			backtrack(i + 1);
			count -= tmp;
			tmp = 0;
		}
	}

public:
	//构造函数
	Triangle(size_t n) :num(n), count(0), sum(0), 
		hasRun(false) {
		triangle = new unsigned*[num];
		for (size_t i = 0; i < num; ++i)
			triangle[i] = new unsigned[num]();
	}

	//析构函数
	~Triangle() {
		for (size_t i = 0; i < num; ++i)
			delete[]triangle[i];
		delete[]triangle;
	}

	//计算并获取问题的解
	unsigned getResult() {
		if ((num*(num + 1) / 2) % 2 == 0 || !hasRun) {
			backtrack();
			hasRun = true;
		}
		return sum;
	}
};


//n皇后问题
class N_Queens {
	size_t num;                   //皇后数目
	unsigned sum;                 //统计符合条件的排列方法总数
	bool hasRun;                  //标记是否已经运行过计算函数

	unsigned *preResult;          //当前n个皇后的列位置

	//回溯法实现函数
	void backtrack(size_t i = 0) {
		
		//到达子集树树根节点之后
		if (i == num) {
			++sum;
			return;
		}

		//处于子集树的中间节点
		bool isFit = true;          //代表i皇后当前的列位置是否合适

		//遍历子树
		for (size_t j = 0; j < num; ++j) {
			preResult[i] = j;

			//判断i皇后位置是否合适
			for (size_t k = 0; k < i; ++k) {
				if (preResult[k] == preResult[i] ||
					std::abs(static_cast<int>(k - i))
					== std::abs(static_cast<int>(preResult[k]
						- preResult[i])))
					isFit = false;
			}

			if(isFit)
				backtrack(i + 1);
			isFit = true;
		}
	}

public:
	//构造函数
	N_Queens(size_t n) :num(n), sum(0), hasRun(false) {
		preResult = new unsigned[num]();
	}

	//析构函数
	~N_Queens() {
		delete[]preResult;
	}

	//计算并返回问题的解
	unsigned getResult() {
		if (!hasRun) {
			backtrack();
			hasRun = true;
		}
		return sum;
	}
};