
// cFile.cpp

// Implements the cFile class providing an OS-independent abstraction of a file.

#include "Globals.h"  // NOTE: MSVC stupidness requires this to be the same across all modules

#include "cFile.h"






/// Simple constructor - creates an unopened file object, use Open() to open / create a real file
cFile::cFile(void) :
	#ifdef USE_STDIO_FILE
	m_File(NULL)
	#else
	m_File(INVALID_HANDLE_VALUE)
	#endif  // USE_STDIO_FILE
{
	// Nothing needed yet
}





/// Constructs and opens / creates the file specified, use IsOpen() to check for success
cFile::cFile(const char * iFileName, EMode iMode) :
	#ifdef USE_STDIO_FILE
	m_File(NULL)
	#else
	m_File(INVALID_HANDLE_VALUE)
	#endif  // USE_STDIO_FILE
{
	Open(iFileName, iMode);
}





/// Auto-closes the file, if open
cFile::~cFile()
{
	if (IsOpen())
	{
		Close();
	}
}





bool cFile::Open(const char * iFileName, EMode iMode)
{
	assert(!IsOpen());  // You should close the file before opening another one
	
	if (IsOpen())
	{
		Close();
	}
	
	const char * Mode = NULL;
	switch (iMode)
	{
		case fmRead:      Mode = "rb";  break;
		case fmWrite:     Mode = "wb";  break;
		case fmReadWrite: Mode = "ab+"; break;
		default:
		{
			assert(!"Unhandled file mode");
			return false;
		}
	}
	m_File = fopen(iFileName, Mode);
	return (m_File != NULL);
}





void cFile::Close(void)
{
	assert(IsOpen());  // You should not close file objects that don't have an open file.
	
	if (!IsOpen())
	{
		return;
	}

	fclose(m_File);
}





bool cFile::IsOpen(void) const
{
	return (m_File != NULL);
}





bool cFile::IsEOF(void) const
{
	assert(IsOpen());
	
	if (!IsOpen())
	{
		// Unopened files behave as at EOF
		return true;
	}
	
	return (feof(m_File) != 0);
}





/// Reads  up to iNumBytes bytes into iBuffer, returns the number of bytes actually read,    or -1 on failure; asserts if not open
int cFile::Read (void * iBuffer, int iNumBytes)
{
	assert(IsOpen());
	
	if (!IsOpen())
	{
		return -1;
	}
	
	return fread(iBuffer, 1, iNumBytes, m_File);  // fread() returns the portion of Count parameter actually read, so we need to send iNumBytes as Count
}





/// Writes up to iNumBytes bytes from iBuffer, returns the number of bytes actually written, or -1 on failure; asserts if not open
int cFile::Write(const void * iBuffer, int iNumBytes)
{
	assert(IsOpen());
	
	if (!IsOpen())
	{
		return -1;
	}

	return fwrite(iBuffer, 1, iNumBytes, m_File);  // fwrite() returns the portion of Count parameter actually written, so we need to send iNumBytes as Count
}





/// Seeks to iPosition bytes from file start, returns old position or -1 for failure
int cFile::Seek (int iPosition)
{
	assert(IsOpen());
	
	if (!IsOpen())
	{
		return -1;
	}
	
	if (fseek(m_File, iPosition, SEEK_SET) != 0)
	{
		return -1;
	}
	return ftell(m_File);
}






/// Returns the current position (bytes from file start)
int cFile::Tell (void) const
{
	assert(IsOpen());
	
	if (!IsOpen())
	{
		return -1;
	}
	
	return ftell(m_File);
}





/// Returns the size of file, in bytes, or -1 for failure; asserts if not open
int cFile::GetSize(void) const
{
	assert(IsOpen());
	
	if (!IsOpen())
	{
		return -1;
	}
	
	int CurPos = ftell(m_File);
	if (CurPos < 0)
	{
		return -1;
	}
	if (fseek(m_File, 0, SEEK_END) != 0)
	{
		return -1;
	}
	int res = ftell(m_File);
	if (fseek(m_File, CurPos, SEEK_SET) != 0)
	{
		return -1;
	}
	return res;
}




