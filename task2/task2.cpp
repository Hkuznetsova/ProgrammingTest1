#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <fstream>
#include <regex>

using namespace std;

struct Point {
	double x, y;

	bool operator== (Point p)
	{
		return (x == p.x) && (y == p.y);
	}
	bool operator!= (Point p)
	{
		return (x != p.x) || (y != p.y);
	}
};

vector<Point> readFile(string filePath)
{
	vector<Point> inputVector;
	string buffer;

	ifstream fin(filePath);
	if (fin.is_open())
	{
		Point p;
		bool j = true;
		while (true)
		{
			fin >> buffer;
			if (fin)
			{
				if (j)
				{
					p.x = stof(buffer);
					j = false;
				}
				else
				{
					p.y = stof(buffer);
					inputVector.push_back(p);
					j = true;
				}
			}
			else
				break;
		}
		fin.close();

	}
	return inputVector;
}

double pointBelongToSegment(Point A, Point B, Point checkedPoint)
{
	return ((checkedPoint.x - A.x) * (B.y - A.y) - (checkedPoint.y - A.y) * (B.x - A.x));
}

int checkPointRelativeToQuadrilateral(Point checkedPoint, vector<Point> quadranglPoints)
{
	for (vector<Point>::iterator i = quadranglPoints.begin(); i != quadranglPoints.end(); ++i)
	{
		if (*i == checkedPoint)
		{
			return 0;
		}

	}
	vector<int> pointsRelativeToSide;
	for (vector<Point>::iterator i = quadranglPoints.begin(); i != quadranglPoints.end(); ++i)
	{
		if (*i != quadranglPoints.back())
		{
			pointsRelativeToSide.push_back(pointBelongToSegment(*i, *(i + 1), checkedPoint));
		}
		else
		{
			pointsRelativeToSide.push_back(pointBelongToSegment(*i, *(quadranglPoints.begin()), checkedPoint));
		}
	}

	if (pointsRelativeToSide[0] >= 0 && pointsRelativeToSide[1] >= 0 && pointsRelativeToSide[2] >= 0 && pointsRelativeToSide[3] >= 0)
	{
		if (pointsRelativeToSide[0] == 0 || pointsRelativeToSide[1] == 0 || pointsRelativeToSide[2] == 0 || pointsRelativeToSide[3] == 0)
			return 1;
		else
			return 2;
	}
	else
		return 3;
}

int main(int argc, char* argv[])
{
	vector<Point> quadranglPoints = readFile(argv[1]);
	vector<Point> checkedPoints = readFile(argv[2]);
	for (vector<Point>::iterator i = checkedPoints.begin(); i != checkedPoints.end(); ++i)
	{
		cout << checkPointRelativeToQuadrilateral(*i, quadranglPoints) << "\n";
	}
	return 0;
}