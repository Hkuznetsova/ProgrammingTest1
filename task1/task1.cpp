#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

vector<float> readFile(string filePath)
{
	vector<float> inputVector;
	string buffer;
	ifstream a;

	ifstream fin(filePath);
	if (fin.is_open())
	{
		while (true)
		{
			fin >> buffer;
			if (fin)
			{
				inputVector.push_back(stoi(buffer));
			}
			else
				break;
		}
		fin.close();

	}
	return inputVector;
}

float Percentile(float percNum, vector<float> inputVector)
{
	if (inputVector.empty()) 
	{
		return 0;
	}
	if (inputVector.size() == 1)
	{
		return inputVector[0];
	}
	double 	interval = 1.0 / (inputVector.size() - 1);
	int lower = (int)((percNum / 100.0) / interval);

	int upper;
	if (lower == inputVector.size() - 1)
	{
		upper = lower;
	}
	else
	{
		upper = lower + 1;
	}

	return (((percNum / 100.0) - interval * lower) / interval) 
		* (inputVector[upper] - inputVector[lower])
		+ inputVector[lower];
}

float AverageValue(vector<float> inputVector)
{
	if (inputVector.empty()) 
	{
		return 0;
	}
	float sum = 0;
	for (vector<float>::iterator i = inputVector.begin(); i != inputVector.end(); ++i)
	{
		sum += *i;
	}
	return sum / inputVector.size();
}

int main(int argc, char* argv[])
{
	int precision = 2;
	vector<float> inputVector = readFile(argv[1]);
	sort(inputVector.begin(), inputVector.end());
	float max = inputVector.empty() ? 0 : inputVector.back();
	float min = inputVector.empty() ? 0 : inputVector.front();
	cout << fixed << setprecision(precision) << Percentile(90.0, inputVector) << '\n';
	cout << fixed << setprecision(precision) << Percentile(50.0, inputVector) << '\n';
	cout << fixed << setprecision(precision) << max << '\n';
	cout << fixed << setprecision(precision) << min << '\n';
	cout << fixed << setprecision(precision) << AverageValue(inputVector) << '\n';
	return 0;
}