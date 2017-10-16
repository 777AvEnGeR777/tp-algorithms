#include <iostream>
#include <vector>
using std::cin;
using std::vector;

struct CSegment {
	int Left;
	int Right;

	// Сравнение по правому краю. Если равны, то по левому
	bool operator<(const CSegment& right) const;
	bool operator<=(const CSegment& right) const;
	bool operator>(const CSegment& right) const;
	bool operator>=(const CSegment& right) const;
	CSegment() : Left (0), Right(0) {}
	CSegment(int left, int right): Left(left), Right(right) {}
};


bool CSegment::operator<(const CSegment& right) const
{
	return( Right < right.Right) || (Right == right.Right && Left < right.Left);
}

bool CSegment::operator<=(const CSegment& right) const
{
	return !(right < *this);
}

bool CSegment::operator>(const CSegment& right) const
{
	return right < *this;
}

bool CSegment::operator>=(const CSegment& right) const
{
	return !( *this < right);	
}

struct CSegmentFunctor
{
public:
	bool operator()(const CSegment& left, const CSegment& right) { return left < right; } 
};

template<class T, class COMPARER>
inline void BubbleSort(vector<T>& arr, COMPARER& comparer)
{
	const int n = static_cast<int>(arr.size());
	for(int i = 0; i < n - 1; i++)
	{
		bool swapped = false;
		for(int j = 0; j < n - 1 - i; j++)
		{
			if(comparer(arr[j + 1], arr[j]))
			{
				std::swap(arr[j], arr[j + 1]);
				swapped = true;
			}
		}
		if(!swapped)
			break;
	}
};

bool SegmentComparer(const CSegment& left, const CSegment& right)
{
	return left < right;
}

int main()
{
	vector<CSegment> arr;
	int left = 0;
	int right = 0;

	while(cin >> left >> right) {
		arr.push_back(CSegment(left, right));
	}
	CSegmentFunctor functor;
	BubbleSort(arr, functor);
	for(const CSegment& segment : arr) {
		std::cout << segment.Left << " " << segment.Right << std::endl;
	}

	return 0;
}