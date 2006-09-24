#pragma once

///////////////////////////////////////////////////////////////
// include base class
///////////////////////////////////////////////////////////////

#include "HierachicalInStreamBase.h"

///////////////////////////////////////////////////////////////
//
// CBinaryInStreamBase
//
//		Base class for all binary read streams. Data can
//		be extracted in single bytes or chunks of data.
//		Attempts to read beyond the stream's end return NULL
//		values.
//
///////////////////////////////////////////////////////////////

class CBinaryInStreamBase : public CHierachicalInStreamBase
{
private:

	// our current read position

	const unsigned char* current;

protected:

	// not ment to be instantiated

	// construction: nothing to do here

	CBinaryInStreamBase ( CCacheFileInBuffer* buffer
					    , STREAM_INDEX index);

	// data access

	size_t GetSize() const
	{
		return last - first;
	}

	size_t GetRemaining() const
	{
		return last - current;
	}

	unsigned char GetByte()
	{
		if (current == last)
			return 0;

		return *(current++);
	}

	const unsigned char* GetData (size_t size)
	{
		if (GetRemaining() < size)
			return NULL;

		const unsigned char* result = current;
		current += size;

		return current;
	}

public:

	// destruction

	virtual ~CBinaryInStreamBase() {};

	// data access

	virtual void Reset()
	{
		current = first;
	}

	bool EndOfStream() const
	{
		return current == last;
	}
};

///////////////////////////////////////////////////////////////
//
// CBinaryInStream
//
//		instantiable sub-class of CBinaryInStreamBase.
//
///////////////////////////////////////////////////////////////

class CBinaryInStream : public CInStreamImplBase< CBinaryInStream
												, CBinaryInStreamBase
						                        , BINARY_STREAM_TYPE_ID>
{
public:

	typedef CInStreamImplBase< CBinaryInStream
							 , CBinaryInStreamBase
							 , BINARY_STREAM_TYPE_ID> TBase;

	// construction / destruction: nothing special to do

	CBinaryInStream ( CCacheFileInBuffer* buffer
				    , STREAM_INDEX index);
	virtual ~CBinaryInStream() {};

	// public data access methods

	using TBase::GetSize;
	using TBase::GetRemaining;
	using TBase::GetByte;
	using TBase::GetData;
};
