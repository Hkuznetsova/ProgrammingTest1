#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

const int intervalNum = 16;

void readFile(string filePath, vector<float>& sumVector)
{
	string buffer;
	int i = 0;
	ifstream fin(filePath);
	if (fin.is_open())
	{
		bool j = true;
		while (true)
		{
			fin >> buffer;
			if (fin)
			{
				sumVector[i] += stof(buffer);
				i++;
			}
			else
				break;
		}
		fin.close();

	}
	return;
}

int findMaxInterval(vector<float>& sumVector)
{
	int maxInterval = 0;
	float maxValue = sumVector[0];
	for (int i = 0; i < intervalNum; i++)
	{
		if (sumVector[i] > maxValue)
		{
			maxInterval = i;
			maxValue = sumVector[i];
		}
	}
	return maxInterval;
}



int main(int argc, char* argv[])
{
	vector<float> sumVector(intervalNum, 0);
	for (int i = 1; i <= 5; i++)
	{
		string folderPath = argv[1];
		readFile(folderPath + "Cash" + to_string(i) + ".txt", sumVector);
	}
	cout << findMaxInterval(sumVector) + 1;
	return 0;
}