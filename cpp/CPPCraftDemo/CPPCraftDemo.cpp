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

int main(int argc, _TCHAR* argv[])
{
    using namespace std::chrono;
    // Find a record that contains and measure the perf
	QBRecordCollection recordCollection( "testdata", 10000 );
    auto startTimer = steady_clock::now();
	auto filteredSet = recordCollection.QBFindMatchingRecords( Column::column1, "testdata500" );
	auto filteredSet2 = recordCollection.QBFindMatchingRecords( Column::column2, "24");
    std::cout << "profiler: " << double((steady_clock::now() - startTimer).count()) * steady_clock::period::num / steady_clock::period::den << std::endl;

	recordCollection.QBDeleteRecordByID( 150 );
	auto filteredSet3 = recordCollection.QBFindMatchingRecords( Column::column0, "150");
	auto filteredSet4 = recordCollection.QBFindMatchingRecords( Column::column1, "testdata150");

	return 0;
}

