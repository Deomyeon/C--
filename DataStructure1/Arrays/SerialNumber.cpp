#include <iostream>
 
using namespace std;
 
struct {
	string sex;
	int age;
	int year;
	string home;
}typedef Info;
 
struct _Home{
	int size;
	string name;
 
	_Home(int size, const char* name)
	{
		this->size = size;
		this->name = name;
	}
}typedef Home;
 
bool getSerial(string&);
Info getInfo(string&);
string getSex(string&);
int getYear(string&);
int getAge(string&, int year);
string getHome(string&);
bool check(string&);
 
 
int main()
{
	string serialNumber;
	cout << "주민등록번호 입력 : ";
	bool serialCheck = getSerial(serialNumber);
	if (!serialCheck)
	{
		cout << serialNumber << "의 정보를 표기합니다." << endl;
		Info info;
		info = getInfo(serialNumber);
		cout << "성별 : " << info.sex << endl;
		cout << "생년 : " << info.year << endl;
		cout << "나이 : " << info.age << endl;
		cout << "지역 : " << info.home << endl;
	}
	else
	{
		cout << serialNumber << "는 유효하지 않은 주민등록번호입니다." << endl;
	}
}
 
 
bool getSerial(string& serialNumber)
{
	cin >> serialNumber;
	const char* tempSirial = serialNumber.c_str();
	if (serialNumber.length() != 13)
		return true;
	for (int i = 0; i < serialNumber.length(); i++)
	{
		if (!(tempSirial[i] > 47 && tempSirial[i] < 58))
		{
			return true;
		}
	}
	if (atoi(serialNumber.substr(7, 2).c_str()) > 90)
		return true;
	if (serialNumber[6] - '0' > 4 || serialNumber[6] - '0' < 1)
		return true;
	if (check(serialNumber))
		return true;
	return false;
}
 
 
Info getInfo(string& serialNumber) 
{
	Info result;
	result.sex = getSex(serialNumber);
	result.year = getYear(serialNumber);
	result.age = getAge(serialNumber, result.year);
	result.home = getHome(serialNumber);
	return result;
}
 
string getSex(string& serialNumber)
{
	if (serialNumber[6] - '0' % 2)
	{
		return "남성";
	}
	else
	{
		return "여성";
	}
}
 
int getYear(string& serialNumber)
{
	string temp;
	bool is2N = false; // true 일때 20대 이상
	if (serialNumber[6] - '0' > 2)
	{
		temp = "20";
	}
	else
	{
		temp = "19";
	}
	temp.append(serialNumber.substr(0, 2));
	return atoi(temp.c_str());
}
 
int getAge(string& serialNumber, int year)
{
	return (2021 - year + 1);
}
 
string getHome(string& serialNumber)
{
	Home home[11] = { _Home(0, "서울"), _Home(9, "부산"), _Home(13, "인천"), _Home(16, "경기도 주요 도시"), _Home(19, "그 밖의 경기도"), _Home(26, "강원도"), _Home(35, "충청북도"), _Home(40, "충청남도"), _Home(48, "전라북도"), _Home(55, "전라남도"), _Home(67,  "경상도") };
	int j = 0;
	for (int i = 0; i < 90; i++)
	{
		if (home[j].size <= i)
		{
			j++;
		}
		if (atoi(serialNumber.substr(7, 2).c_str()) == i)
		{
			break;
		}
	}
	return home[j - 1].name;
}
 
bool check(string& serialNumber)
{
	const char* temp = serialNumber.c_str();
	bool result = (temp[12] == ((11 - ((temp[0] + temp[1] + temp[2] + temp[3] + temp[4] + temp[5] + temp[6] + temp[7] + temp[8] + temp[9] + temp[10] + temp[11]) % 11) % 10)));
	return result;
}