#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <stack>
#include <utility>

using namespace std;

struct IntervalPoint
{
	int minutes;
	bool isCome;
};

int comp(const IntervalPoint& p1, const IntervalPoint& p2)
{
	if (p1.minutes == p2.minutes)
	{
		if (p1.isCome == p2.isCome)
		{
			return false;
		}
		if (!p1.isCome)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (p1.minutes > p2.minutes)
	{
		return false;
	}
	else
	{
		return true;
	}
}

IntervalPoint stringToIntervalPoint(string minute, bool isCome)
{
	IntervalPoint p;
	int index = 0;
	p.minutes = 0;
	index = minute.find(':', 0);
	string tmp = minute.substr(0, index);
	p.minutes += stoi(tmp) * 60;
	tmp = minute.substr(index + 1, minute.size());
	p.minutes += stoi(tmp);
	p.isCome = isCome;
	return p;
}

vector<IntervalPoint> readFile(string filePath)
{
	vector<IntervalPoint> intervalPoints;
	string buffer;
	ifstream fin(filePath);
	int i = 0;
	if (fin.is_open())
	{
		while (true)
		{
			fin >> buffer;
			if (fin)
			{
				intervalPoints.push_back(stringToIntervalPoint(buffer, i % 2 == 0));
				i++;
			}
			else
				break;
		}
		fin.close();

	}
	return intervalPoints;
}

string resultMinutesToString(int minute)
{
	return ((minute % 60 < 10) ? ("0" + to_string(minute % 60)) : to_string(minute % 60));
}

vector<pair<int, int>>  searchMaximumIntervals(vector<IntervalPoint> intervalPoints)
{
	sort(intervalPoints.begin(), intervalPoints.end(), comp);
	int personNum = 0;
	int maxPersonNum = 0;
	vector<pair<int, int>> resultIntervals;
	for (vector<IntervalPoint>::iterator i = intervalPoints.begin(); i != intervalPoints.end(); ++i)
	{
		if (!(*i).isCome)
		{
			personNum--;
			if (personNum != maxPersonNum - 1) {
				continue;
			}
			if (!resultIntervals.empty()) {
				resultIntervals.back().second = (*i).minutes;
			}
		}
		else
		{
			personNum++;
			if (personNum < maxPersonNum) {
				continue;
			}

			if (personNum > maxPersonNum) {
				maxPersonNum = personNum;
				resultIntervals.clear();
				pair<int, int> interval((*i).minutes, (*i).minutes);
				resultIntervals.push_back(interval);
				continue;
			}

			if (personNum == maxPersonNum) {
				if (!resultIntervals.empty()) {
					if (resultIntervals.back().second == (*i).minutes) {
						continue;
					}
					pair<int, int> interval((*i).minutes, (*i).minutes);
					resultIntervals.push_back(interval);
				}
			}
		}
	}
	return resultIntervals;
}

int main(int argc, char* argv[])
{
	vector<IntervalPoint> intervalPoints = readFile(argv[1]);
	vector<pair<int, int>> resultIntervals = searchMaximumIntervals(intervalPoints);
	
	if (resultIntervals.empty())
	{
		cout << 480 / 60 << ":" << resultMinutesToString(0) << " " << 1200 / 60 << ":" << resultMinutesToString(0) << "\n";
	}
	for (vector<pair<int, int>>::iterator i = resultIntervals.begin(); i != resultIntervals.end(); ++i)
	{

		cout << (*i).first / 60 << ":" << resultMinutesToString((*i).first) << " " << (*i).second / 60 << ":" << resultMinutesToString((*i).second) << "\n";
	}
	return 0;
}