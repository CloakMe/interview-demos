#pragma once
#include <string>
#include <vector>
#include "QBRecord.h"

#ifndef uint
#define uint unsigned int
#endif

struct Range
{
	uint start;
	uint stop;
};
/**
	Compare QBRecords. Compare record1 with record2 with respect to entries in "column".
	if( record1."column" <= record2."column" ) return true, else return false
	It is used std::string::compare method for strings.
*/
bool CompareQBRecords(const QBRecord & record1, const QBRecord & record2, Column column);

/**
	Unfortunately when I search for a string under specified column, I also want to display all rows in the database that contain the
	searched string as a substring /not only equal/ as shown in the initial code (see old verstion of QBFindMatchingRecords which is currently in 
	QBRecordCollection::QBFindMatchingRecords ). 
	I use std::string::find.

	Otherwise,
	To check equality (for strings and numbers) one could simply use:
	CompareQBRecords( record1, record2, column) && CompareQBRecords( record2, record1, column).
*/
bool EqualQBRecords(const QBRecord & record1, const QBRecord & record2, Column column);

/**
	might be possible to use std::stable_sort
	https://stackoverflow.com/questions/1577475/c-sorting-and-keeping-track-of-indexes
	The method sorts the indices with respect to a collection of QBRecords.

	arr [in] - array of QBRecords
	indices [in/out] - expects ascending indices array as iunput: 0, 1, 2, ...; outputs specially sorted indices array which sorts <arr>
	size [in] - the number of QBRecords
	col [in] - the column that is being sorted.
*/
void QuickSort(const QBRecord* arr, uint* indices, int size, Column col );

/**
	might be possible to use std::binary_search with proper CompareQBRecords and EqualQBRecords functions / get rid of Column.

	The method searches inside a QBRecord array using specially sorted indices array.

	arr [in] - array of QBRecords
	indices [in] - expects specially sorted indices array which sorts <arr>
	size [in] - the number of QBRecords
	col [in] - the column we are searching in.
	x [in] - the element we are searching for.
*/
Range BinarySearch( const QBRecord* arr, const uint* indices, int size, Column col, const QBRecord& x );
