#pragma once
#include "Types.h"

class Exception
{
protected:
	String exceptionText;
	SourceLocation srcLocation;
	Vector<Exception> exceptionList;

public:
	Exception(const String& exceptionText, const SourceLocation& srcLocation = SourceLocation::current()) noexcept;
	Exception(String&& exceptionText, SourceLocation&& srcLocation = SourceLocation::current()) noexcept;
	Exception(const String& exceptionText, const Exception& prevException, const SourceLocation& srcLocation = SourceLocation::current()) noexcept;
	Exception(const String& exceptionText, Exception&& prevException, const SourceLocation& srcLocation = SourceLocation::current()) noexcept;

	Exception(const Exception& otherException) noexcept;
	Exception(Exception&& otherException) noexcept;

	Exception& operator=(const Exception& otherException) noexcept;
	Exception& operator=(Exception&& otherException) noexcept;

	virtual operator String() const;

	String GetText() const;
	SourceLocation GetSourceLocation() const;
	const Vector<Exception> GetExceptionList() const;

	static void Throw(const String& exceptionText, const SourceLocation& srcLocation = SourceLocation::current());
	static void Throw(String&& exceptionText, SourceLocation&& srcLocation = SourceLocation::current());

	String ToString() const;

private:
	String SrcLocationToString(const SourceLocation& sourceLocation) const;
	String ExceptionToString(const SourceLocation& sourceLocation, const String& text) const;
};