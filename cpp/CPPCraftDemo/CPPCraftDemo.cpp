#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

#include <assert.h>
#include <chrono>
#include <iostream>
#include <ratio>
#include "QBRecord.h"
#include "QBRecordCollection.h"
#include "Utilities.h"

#ifndef uint
#define uint unsigned int
#endif


//QBRecordCollection QBFindMatchingRecords(const QBRecordCollection& records, const std::string& columnName, const std::string& matchString)
//{
//	QBRecordCollection result;
//	for( std::vector<QBRecord>::const_iterator rec = records.begin(); rec != records.end(); rec++ )
//	{
//		if( columnName == "column0" )
//		{
//			uint matchValue = std::stoul(matchString);
//			if ( matchValue == rec->column0 )
//			{
//				result.emplace_back( *rec );
//			}
//		} else if (columnName == "column1") {
//			if( rec->column1.find(matchString) != std::string::npos )
//			{
//				result.emplace_back( *rec );
//			}
//		} else if (columnName == "column2") 
//		{
//			long matchValue = std::stol( matchString );
//			if( matchValue == rec->column2 )
//			{
//				result.emplace_back( *rec );
//			}
//		} else if (columnName == "column3") {
//			if( rec->column3.find(matchString) != std::string::npos )
//			{
//				result.emplace_back( *rec );
//			}
//		}
//	}
//
//	return result;
//}



int main(int argc, _TCHAR* argv[])
{
    using namespace std::chrono;
    // Find a record that contains and measure the perf
	QBRecordCollection recordCollection( "testdata", 1000 );
    auto startTimer = steady_clock::now();
	auto filteredSet = recordCollection.QBFindMatchingRecords( Column::column1, "testdata500" );
	auto filteredSet2 = recordCollection.QBFindMatchingRecords( Column::column2, "24");
    std::cout << "profiler: " << double((steady_clock::now() - startTimer).count()) * steady_clock::period::num / steady_clock::period::den << std::endl;

	recordCollection.QBDeleteRecordByID( 150 );
	auto filteredSet3 = recordCollection.QBFindMatchingRecords( Column::column0, "150");
	auto filteredSet4 = recordCollection.QBFindMatchingRecords( Column::column1, "testdata150");
    // make sure that the function is correct
    assert(filteredSet.size() == 1);
	assert(filteredSet3.size() == 0);
	assert(filteredSet4.size() == 0);
	return 0;
}

