//���ڻ��ݷ�
#include<cmath>


//��������*array���±�Ϊi��j��Ԫ��
template <typename T>
void swap(T *array, size_t i, size_t j) {
	if (i != j) {
		T tmp = array[i];
		array[i] = array[j];
		array[j] = tmp;
	}
}


//0-1��������
class Knapsack {
	int *values;                //��Ʒ��ֵ
	unsigned *weights;          //��Ʒ����
	size_t num;                 //��Ʒ����
	unsigned vol;               //��������

	bool *preResult;            //��ǰװ�뷽��
	int preValues;              //��ǰװ����Ʒ�ܼ�ֵ
	int restValues;             //δװ����Ʒ�ܼ�ֵ

	bool *bestResult;           //���Ž�
	int bestValues;             //����ֵ
	bool hasRun;                //����Ƿ��Ѿ����й����㺯��
	
	//���ݷ�ʵ�ֺ���
	void backtrack(size_t i = 0) {

		//�����Ӽ���Ҷ�ڵ�
		if (i == num - 1) {

			//�ж��Ƿ���װ�����һ����Ʒ
			if (vol >= weights[i]) {
				preResult[i] = true;
				preValues += values[i];
			}

			//�������Ž������ֵ
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


		//�����Ӽ����м�ڵ�
		restValues -= values[i];

		//����������
		if (vol >= weights[i]) {
			preResult[i] = true;
			preValues += values[i];
			vol -= weights[i];
			backtrack(i + 1);
			preResult[i] = false;
			preValues -= values[i];
			vol += weights[i];
		}

		//����������
		if (preValues + restValues > bestValues)
			backtrack(i + 1);

		restValues += values[i];
		return;
	}

public:
	//���캯��
	Knapsack(int *val, unsigned *wei, size_t n,
		unsigned v, unsigned m = 0) :values(val),
		weights(wei), num(n), vol(v), restValues(m),
		preValues(0), bestValues(0), hasRun(false) {

		//δװ����Ʒ�ܼ�ֵ�ĳ�ʼֵΪ������Ʒ���ܼ�ֵ
		if (!restValues) {
			for (size_t i = 0; i < num; ++i)
				restValues += values[i];
		}

		preResult = new bool[num];
		bestResult = new bool[num];
		for (size_t i = 0; i < num; ++i)
			preResult[i] = bestResult[i] = false;
	}

	//��������
	~Knapsack() {
		delete[]preResult;
		delete[]bestResult;
	}

	//���㲢��������ֵ
	int getBestValues() {
		if (!hasRun) {
			backtrack();
			hasRun = true;
		}
		return bestValues; 
	}

	//��ȡ���Ž�Ŀ���
	bool *getBestResult() {
		if (!hasRun)
			getBestValues();
		bool *copy = new bool[num];
		for (size_t i = 0; i < num; ++i)
			copy[i] = bestResult[i];
		return copy;
	}
};


//����������
class Traveling_Salesman {
	int **graph;                  //ͼ
	size_t num;                   //�ڵ���
	size_t outset;                //�����

	unsigned *preResult;          //��ǰ·��
	int preDistance;              //��ǰ·��

	unsigned *bestResult;         //���Ž�
	int bestDistance;             //����ֵ
	bool hasRun;                  //����Ƿ��Ѿ����й����㺯��
								  
	//���ݷ�ʵ�ֺ���
	void backtrack(size_t i = 0) {

		//�����Ӽ���Ҷ�ڵ�
		if (i == num - 1) {

			//�������Ž������ֵ
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

		//�����Ӽ����м�ڵ�
		for (size_t j = i + 1; j < num; ++j) {

			//�ж��Ƿ������չ�ڵ�
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
	//���캯��
	Traveling_Salesman(int **g, size_t n, size_t out = 0) :
		graph(g), num(n), outset(out), 
		preDistance(0), bestDistance(0), hasRun(false) {
		preResult = new unsigned[num];
		bestResult = new unsigned[num]();
		for (size_t i = 0; i < num; ++i)
			preResult[i] = i;
		swap(preResult, 0, outset);
	}

	//��������
	~Traveling_Salesman() {
		delete[]preResult;
		delete[]bestResult;
	}

	//���㲢��������ֵ
	int getBestDistance() {
		if (!hasRun) {
			backtrack();
			hasRun = true;
		}
		return bestDistance; 
	}

	//��ȡ���Ž�Ŀ���
	unsigned *getBestResult() { 
		if (!hasRun)
			getBestDistance();
		unsigned *copy = new unsigned[num];
		for (size_t i = 0; i < num; ++i)
			copy[i] = bestResult[i];
		return copy; 
	}
};


//��������ҵ��������
class Batch_Job_Scheduling {
	int **time;                   //����������ʱ��
	size_t num;                   //������

	unsigned *preResult;          //��ǰ��ҵ����
	int preTime1;                 //��ǰ����1���ʱ��
	int *preTime2;                //��ǰ����2������
	int preTime;                  //��ǰ�����ʱ��

	unsigned *bestResult;         //���Ž�
	int bestTime;                 //����ֵ
	bool hasRun;                  //����Ƿ��Ѿ����й����㺯��

	//���ݷ�ʵ�ֺ���
	void backtrack(size_t i = 0) {

		//�����Ӽ���Ҷ�ڵ�
		if (i == num - 1) {
			preTime1 += time[0][preResult[i]];
			if (i == 0 || preTime2[i - 1] < preTime1)
				preTime2[i] = preTime1 + time[1][preResult[i]];
			else
				preTime2[i] = preTime2[i - 1] + time[1][preResult[i]];

			//�������Ž������ֵ
			if (bestTime == 0 || preTime + preTime2[i] < bestTime) {
				bestTime = preTime + preTime2[i];
				for (size_t j = 0; j < num; ++j)
					bestResult[j] = preResult[j];
			}

			preTime1 -= time[0][preResult[i]];
			return;
		}

		//�����Ӽ����м�ڵ�
		for (size_t j = i; j < num; ++j) {
			swap(preResult, i, j);
			preTime1 += time[0][preResult[i]];
			if (i == 0 || preTime2[i - 1] < preTime1)
				preTime2[i] = preTime1 + time[1][preResult[i]];
			else
				preTime2[i] = preTime2[i - 1] + time[1][preResult[i]];
			preTime += preTime2[i];

			//�ж��Ƿ������չ�ڵ�
			if (bestTime == 0 || preTime < bestTime)
				backtrack(i + 1);

			preTime -= preTime2[i];
			preTime1 -= time[0][preResult[i]];
			swap(preResult, i, j);
		}
		return;
	}

public:
	//���캯��
	Batch_Job_Scheduling(int **t, size_t n) :time(t), 
		num(n), preTime1(0), preTime(0), bestTime(0),
		hasRun(false) {
		preResult = new unsigned[num];
		bestResult = new unsigned[num]();
		preTime2 = new int[num]();

		for (size_t i = 0; i < num; ++i)
			preResult[i] = i;
	}

	//��������
	~Batch_Job_Scheduling() {
		delete[]preResult;
		delete[]preTime2;
		delete[]bestResult;
	}

	//���㲢��������ֵ
	int getBestTime() { 
		if (!hasRun) {
			backtrack();
			hasRun = true;
		}
		return bestTime;
	}

	//��ȡ���Ž�Ŀ���
	unsigned *getBestResult() {
		if (!hasRun)
			getBestTime();
		unsigned *copy = new unsigned[num];
		for (size_t i = 0; i < num; ++i)
			copy[i] = bestResult[i];
		return copy;
	}
};


//��������������
class Triangle {
	size_t num;                   //�����ε�һ�еķ�����Ŀ
	unsigned sum;                 //ͳ�Ʒ�������������������
	bool hasRun;                  //����Ƿ��Ѿ����й����㺯��

	unsigned count;               //ͳ�Ƶ�ǰ�������м�����Ŀ
	unsigned **triangle;          //���������εķ���

	//���ݷ�ʵ�ֺ���
	void backtrack(size_t i = 0) {

		//������Ŀ�����������ܷ�������һ�룬��֦
		if (count > (1 + num)*num / 4)
			return;

		//�����Ӽ�����Ҷ�ڵ�֮��
		if (i == num) {
			++sum;
			return;
		}

		//�����Ӽ������м�ڵ�
		unsigned tmp = 0;          //ͳ�Ƶ�ǰб���м�����Ŀ

		//��������
		for (size_t j = 0; j < 2; ++j) {
			triangle[0][j] = j;
			tmp = j;

			//���ݵ�һ���������������б����������
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
	//���캯��
	Triangle(size_t n) :num(n), count(0), sum(0), 
		hasRun(false) {
		triangle = new unsigned*[num];
		for (size_t i = 0; i < num; ++i)
			triangle[i] = new unsigned[num]();
	}

	//��������
	~Triangle() {
		for (size_t i = 0; i < num; ++i)
			delete[]triangle[i];
		delete[]triangle;
	}

	//���㲢��ȡ����Ľ�
	unsigned getResult() {
		if ((num*(num + 1) / 2) % 2 == 0 || !hasRun) {
			backtrack();
			hasRun = true;
		}
		return sum;
	}
};


//n�ʺ�����
class N_Queens {
	size_t num;                   //�ʺ���Ŀ
	unsigned sum;                 //ͳ�Ʒ������������з�������
	bool hasRun;                  //����Ƿ��Ѿ����й����㺯��

	unsigned *preResult;          //��ǰn���ʺ����λ��

	//���ݷ�ʵ�ֺ���
	void backtrack(size_t i = 0) {
		
		//�����Ӽ��������ڵ�֮��
		if (i == num) {
			++sum;
			return;
		}

		//�����Ӽ������м�ڵ�
		bool isFit = true;          //����i�ʺ�ǰ����λ���Ƿ����

		//��������
		for (size_t j = 0; j < num; ++j) {
			preResult[i] = j;

			//�ж�i�ʺ�λ���Ƿ����
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
	//���캯��
	N_Queens(size_t n) :num(n), sum(0), hasRun(false) {
		preResult = new unsigned[num]();
	}

	//��������
	~N_Queens() {
		delete[]preResult;
	}

	//���㲢��������Ľ�
	unsigned getResult() {
		if (!hasRun) {
			backtrack();
			hasRun = true;
		}
		return sum;
	}
};