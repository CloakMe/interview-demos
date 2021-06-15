#include "stdafx.h"
#include "Utilities.h"


bool CompareQBRecords(const QBRecord & record1, const QBRecord & record2, Column column)
{
	int result = 0;
	switch( column )
	{
	case Column::column0:
		if( record1.column0 <= record2.column0 )
			return true;
		//else
		return false;
	case Column::column1:
		result = record1.column1.compare( record2.column1 );
		if( result <= 0 )
			return true;
		//else
		return false;
	case Column::column2:
		if( record1.column2 <= record2.column2 )
			return true;
		//else
		return false;
	case Column::column3:
		result = record1.column3.compare( record2.column3 );
		if( result <= 0 )
			return true;
		//else
		return false;
	}

	return false;
}

//bool EqualQBRecords(const QBRecord & record1, const QBRecord & record2, Column column)
//{
//	size_t result = 0;
//	switch( column )
//	{
//	case Column::column0:
//		if( record1.column0 == record2.column0 )
//			return true;
//		//else
//		return false;
//	case Column::column1:
//		result = record1.column1.find( record2.column1 );
//		if( result != std::string::npos )
//			return true;
//		//else
//		return false;
//	case Column::column2:
//		if( record1.column2 == record2.column2 )
//			return true;
//		//else
//		return false;
//	case Column::column3:
//		result = record1.column3.find( record2.column3 );
//		if( result != std::string::npos )
//			return true;
//		//else
//		return false;
//	}
//
//	return false;
//}

void QuickSort(const QBRecord* arr, uint* indices, int size, Column column )
{
	if(size < 2)
	{
		return;
	}
	int pivotIndex = size/2;
	uint temp;
	uint pivot = indices[pivotIndex];
	int leftIndex=0, rightIndex = size-1;
	while(leftIndex != rightIndex)
	{
		while(leftIndex != rightIndex)
		{
			if( CompareQBRecords(arr[pivot], arr[indices[leftIndex]], column) )
			{
				break;
			}
			leftIndex++;
		}
		while(leftIndex != rightIndex)
		{
			if( CompareQBRecords( arr[indices[rightIndex]], arr[pivot], column ) && 
				!( CompareQBRecords( arr[indices[rightIndex]], arr[indices[leftIndex]], column ) && 
				   CompareQBRecords( arr[indices[leftIndex]], arr[indices[rightIndex]], column ) 
				 ) 
			  )
			{
				break;
			}
			rightIndex--;
		}
		
		temp = indices[leftIndex];
		indices[leftIndex] = indices[rightIndex];
		indices[rightIndex] = temp;
	}
	if(leftIndex == 0)
	{
		QuickSort(arr, &indices[1], size-1, column);
		return;
	}
	if(leftIndex == size-1)
	{
		QuickSort(arr, &indices[0], size-1, column);
		return;
	}
	QuickSort(arr, &indices[0], leftIndex, column);
	QuickSort(arr, &indices[leftIndex+1], size-1-leftIndex, column);
}

Range BinarySearch( const QBRecord* arr, const uint* indices, int size, Column column, const QBRecord& x ) 
{
	Range range;
	range.start = -1;
	uint left = 0;
	uint right = size - 1;
	while( left <= right )
	{
		int mid = left + (right - left) / 2;

		if( CompareQBRecords( arr[indices[mid]], x, column ) && CompareQBRecords( x, arr[indices[mid]], column ) ) // equal
		{
			uint i = 1;
			if( CompareQBRecords( arr[indices[left]], x, column ) && CompareQBRecords( x, arr[indices[left]], column ) )
			{
				range.start = left;
			}
			else
			{
				while( CompareQBRecords( arr[indices[mid-i]], x, column ) && CompareQBRecords( x, arr[indices[mid-i]], column ) )
				{
					i++;
				}
				range.start = mid - i + 1;
			}
			
			uint j = 1;
			if( CompareQBRecords( arr[indices[right]], x, column ) && CompareQBRecords( x, arr[indices[right]], column ) )
			{
				range.stop = right;
			}
			else
			{
				while( CompareQBRecords( arr[indices[mid+j]], x, column ) && CompareQBRecords( x, arr[indices[mid+j]], column ) )
				{
					j++;
				}
				range.stop = mid + j - 1;
			}
						
			return range;
		} 
		else if ( CompareQBRecords( arr[indices[mid]], x, column ) ) // less ( equal is already checked ); 
		{ //arr[indices[mid]] < x
			left = mid + 1;
		} 
		else  // greater
		{ //arr[indices[mid]] > x
			right = mid - 1;
		}
	}

	return range;
}

