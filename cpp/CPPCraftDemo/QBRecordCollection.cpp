#include "stdafx.h"
#include "QBRecordCollection.h"
#include <algorithm>
#include "Utilities.h"

QBRecordCollection::QBRecordCollection(const std::string& prefix, uint numRecords)
{
	QBPopulateDummyData(prefix, numRecords);
	//sort populated data column by column
	mOrderedColumnIndices = std::vector< std::vector<uint> >( (int)Column::size /*column count*/, std::vector<uint>(numRecords /*column length, i.e. rows count*/) );
	for( int j = 0; j < (int)Column::size; j++ )
	{
		for( uint i = 0; i < numRecords; i++ )
		{
			mOrderedColumnIndices[j][i] = i;
		}
		QuickSort(&mRecordCollection[0], &mOrderedColumnIndices[j][0], numRecords, (Column)j );
	}
}

QBRecordCollection::QBRecordCollection(const std::vector<QBRecord> & recordCollection) :
	mRecordCollection( recordCollection )
{
	//sort populated data column by column
	uint numRecords = mRecordCollection.size();
	if( numRecords == 0 )
		return;
	mOrderedColumnIndices = std::vector< std::vector<uint> >( (int)Column::size /*column count*/, std::vector<uint>(numRecords /*column length, i.e. rows count*/) );
	for( int j = 0; j < (int)Column::size; j++ )
	{
		for( uint i = 0; i < numRecords; i++ )
		{
			mOrderedColumnIndices[j][i] = i;
		}
		QuickSort(&mRecordCollection[0], &mOrderedColumnIndices[j][0], numRecords, (Column)j );
	}
}

void QBRecordCollection::QBPopulateDummyData(const std::string& prefix, uint numRecords)
{
	mRecordCollection.clear();
    mRecordCollection.reserve(numRecords);
    for (uint i = 0; i < numRecords; i++)
    {
        QBRecord rec = { i, prefix + std::to_string(i), i % 100, std::to_string(i) + prefix };
        mRecordCollection.emplace_back(rec);
    }
}

QBRecordCollection QBRecordCollection::QBFindMatchingRecords(const std::string& columnName, const std::string& matchString)
{
	std::vector<QBRecord> result;
	if( mRecordCollection.size() == 0 )
		return result;
	std::copy_if(mRecordCollection.begin(), mRecordCollection.end(), std::back_inserter(result), [&](QBRecord rec){
		if (columnName == "column0") {
			uint matchValue = std::stoul(matchString);
			return matchValue == rec.column0;
		} else if (columnName == "column1") {
			return rec.column1.find(matchString) != std::string::npos;
		} else if (columnName == "column2") {
			long matchValue = std::stol(matchString);
			return matchValue == rec.column2;
		} else if (columnName == "column3") {
			return rec.column3.find(matchString) != std::string::npos;
		} else {
			return false;
		}
	});
	return QBRecordCollection(result);
}

QBRecordCollection QBRecordCollection::QBFindMatchingRecords(const Column& col, const std::string& matchString )
{
	std::vector<QBRecord> result;
	if( mRecordCollection.size() == 0 )
		return result;
	QBRecord record;
	switch( col )
	{
	case Column::column0:
		record.column0 = std::stoul(matchString);
		break;
	case Column::column1:
		record.column1 = matchString;
		break;
	case Column::column2:
		record.column2 = std::stol(matchString);
		break;
	case Column::column3:
		record.column3 = matchString;
		break;
	}
	Range range = BinarySearch( &mRecordCollection[0], &mOrderedColumnIndices[(int)col][0], mRecordCollection.size(), col, record );
	if( range.start >= 0 )
	{
		for( uint i = range.start; i <= range.stop; i++ )
		{
			result.push_back( mRecordCollection[ mOrderedColumnIndices[(int)col][ i ] ] );
		}
	}
	return result;
}

void QBRecordCollection::QBDeleteRecordByID(uint id)
{
	if( mRecordCollection.size() == 0 )
		return;
	QBRecord record;
	record.column0 = id;
	Range range = BinarySearch( &mRecordCollection[0], &mOrderedColumnIndices[(int)Column::column0][0], mRecordCollection.size(), Column::column0, record );
	if( range.start != -1 )
	{
		uint val0 = mOrderedColumnIndices[(int)Column::column0][range.start];
		for( int col = 0; col < (int)Column::size; col++ )
		{
			uint val = mOrderedColumnIndices[col][range.start];
			mOrderedColumnIndices[col].erase( mOrderedColumnIndices[col].begin() + range.start );
			for( uint i = 0; i < mOrderedColumnIndices[col].size(); i++ )
			{
				if( mOrderedColumnIndices[col][i] > val )
					--mOrderedColumnIndices[col][i];
			}
			if( col == (int)Column::column0 )
				record = mRecordCollection[ val0 ];
			if( col < (int)Column::size - 1 )
				range = BinarySearch( &mRecordCollection[0], &mOrderedColumnIndices[col+1][0], mRecordCollection.size(), (Column)(col+1), record );
		}
		mRecordCollection.erase( mRecordCollection.begin() + val0 );
	}
	
}

size_t QBRecordCollection::size() const
{
	return mRecordCollection.size();
}