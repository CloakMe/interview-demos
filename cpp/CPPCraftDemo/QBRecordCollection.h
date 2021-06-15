#pragma once
#include <vector>
#include "QBRecord.h"

//typedef std::vector<QBRecord> QBRecordCollection;

class QBRecordCollection
{
public:
	QBRecordCollection( const std::string& prefix, uint numRecords );
	QBRecordCollection( const std::vector<QBRecord> & recordCollection );
private:

	std::vector<QBRecord> mRecordCollection;
	std::vector< std::vector<uint> > mOrderedColumnIndices; //when indices <mOrderedColumnIndices[j]> are applied on column <j>, it becomes ascending ordered.


	/**
		Utility to populate a record collection
		prefix - prefix for the string value for every record
		numRecords - number of records to populate in the collection
	*/
	void QBPopulateDummyData(const std::string& prefix, uint numRecords);

public:
	/**
	This is the old function
		Return records that contains a string in the StringValue field
		records - the initial set of records to filter
		columnName - specifies the column
		matchString - the string to search for
	*/
	QBRecordCollection QBFindMatchingRecords(const std::string& columnName, const std::string& matchString);

	/**
	This is the new function
		Return records that contains a string in the StringValue field
		records - the initial set of records to filter
		column - specifies the column
		orderedIndices - indices which order the records so that the current column gains ascending order
		matchString - the string to search for
	*/
	QBRecordCollection QBFindMatchingRecords(const Column& column, const std::string& matchString );

	QBRecordCollection QBFindMatchingRecordsNew( const std::string& columnName, const std::string& matchString);

	/**
		id - id of the element that has to be deleted
	*/
	void QBDeleteRecordByID(uint id);

	/**
		returns the size, i.e. row count in the collection
	*/
	size_t size() const;
};
