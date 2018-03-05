//����̰���㷨
#include<algorithm>
#include<string>
using std::string;
using std::sort;

//�ѡ������
//ͬһ����Ŀ�ʼ�ͽ���ʱ��ʹ��һ��pair����
//��ʼʱ�䣺pair::first������ʱ�䣺pair::second
using time = std::pair<unsigned, unsigned>;
bool Compare_End_Time(const time &, const time &);

//*T�洢���Ϣ������n���
unsigned Activity_Selector(time *T, size_t n) {

	//������ս���ʱ����絽���˳������
	sort(T, T + n, Compare_End_Time);
	
	//result��¼����ֵ��count��¼���һ����ѡ���Ľ���ʱ��
	unsigned result = 0, count = 0;
	for (size_t i = 0; i < n; ++i) {

		//�����ǰ������һ����ѡ��������ʼ
		//���򽫵�ǰ������
		if (T[i].first >= count) {
			count = T[i].second;
			++result;
		}
	}

	return result;          //��������ֵ
}

//CompareEndTime����ʵ�ָ��ݻ�Ľ���ʱ��Ƚϴ�С
bool Compare_End_Time(const time &lt, const time &rt) {
	return lt.second < rt.second;
}


//������������
//ͬһ����Ʒ�ļ�ֵ��������һ��pair����
//��ֵ��pair::first��������pair::second
using item = std::pair<double, unsigned>;
bool Compare_Value(const item &, const item &);

//*T�洢��Ʒ��Ϣ������n����Ʒ����������Ϊs
double Knapsack(item *T, size_t n, unsigned s) {

	//����Ʒ���ռ�ֵ�������ȴӴ�С����
	sort(T, T + n, Compare_Value);

	double result = 0;          //result��������ֵ
	for (size_t i = 0; i < n; ++i) {
		
		//������������װ��������Ʒ������װ��
		if (s >= T[i].second) {
			result += T[i].first;
			s -= T[i].second;
		}

		//��������������װ��������Ʒ���ָ��װ��
		else {
			result += T[i].first / T[i].second*s;
			s = 0;
			break;
		}
	}

	return result;             //��������ֵ
}

//CompareValue����ʵ�ָ�����Ʒ�ļ�ֵ�������ȱȽϴ�С
bool Compare_Value(const item &li, const item &ri) {
	return li.first / li.second > ri.first / ri.second;
}


//ɾ����������
//strΪ��ɾ������kΪ��Ҫɾ�������ָ���
//��ɾ�����Ϊ0���򷵻ؿ��ַ���
string Delete_Digits(string str, size_t k) {
	if (str == string())
		return str;

	while (k--)
		//������Ѱ�ҵ�һ���������ֲ�ɾ��
		for (size_t i = 1; i < str.length();++i)
			if (str[i] < str[i - 1]) {
				str = str.substr(0, i - 1) + str.substr(i);
				break;
			}

	//ɾ������е���Ч��
	size_t i = 0;
	for (; i < str.length() && str[i] == '0'; ++i);
	str = str.substr(i);

	return str;
}

