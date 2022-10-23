#include "Exception.h"

#include <format>
#include <utility>

Exception::Exception(const String& exceptionText, const SourceLocation& srcLocation) noexcept
	: exceptionText(exceptionText), srcLocation(srcLocation)
{
}

Exception::Exception(String&& exceptionText, SourceLocation&& srcLocation) noexcept
	: exceptionText(std::move(exceptionText)), srcLocation(srcLocation)
{
	srcLocation = SourceLocation();
}

Exception::Exception(const String& exceptionText, const Exception& prevException, const SourceLocation& srcLocation) noexcept
	: exceptionText(exceptionText), srcLocation(srcLocation)
{
	exceptionList = prevException.exceptionList;
	exceptionList.push_back(Exception(prevException.exceptionText, prevException.srcLocation));
}

Exception::Exception(const String& exceptionText, Exception&& prevException, const SourceLocation& srcLocation) noexcept
	: exceptionText(exceptionText), srcLocation(srcLocation), exceptionList(std::move(prevException.exceptionList))
{
	exceptionList.push_back(Exception(std::move(prevException)));
}

Exception::Exception(const Exception& otherException) noexcept
	: exceptionText(otherException.exceptionText), srcLocation(otherException.srcLocation), exceptionList(otherException.exceptionList)
{
}

Exception::Exception(Exception&& otherException) noexcept
	: exceptionText(std::move(otherException.exceptionText)),
		srcLocation(otherException.srcLocation), exceptionList(std::move(otherException.exceptionList))
{
	otherException.srcLocation = SourceLocation();
}

Exception& Exception::operator=(const Exception& otherException) noexcept
{
	exceptionText = otherException.exceptionText;
	srcLocation = otherException.srcLocation;
	exceptionList = otherException.exceptionList;

	return *this;
}

Exception& Exception::operator=(Exception&& otherException) noexcept
{
	exceptionText = std::move(otherException.exceptionText);
	srcLocation = otherException.srcLocation;
	otherException.srcLocation = SourceLocation();
	exceptionList = std::move(otherException.exceptionList);

	return *this;
}

Exception::operator String() const
{
	String exception = "Exception: \n" + ExceptionToString(srcLocation, exceptionText);

	for (auto it = exceptionList.crbegin(); it != exceptionList.crend(); ++it)
	{
		exception += "\n" + ExceptionToString(it->GetSourceLocation(), it->GetText());
	}

	return exception;
}

String Exception::GetText() const
{
	return exceptionText;
}

SourceLocation Exception::GetSourceLocation() const
{
	return srcLocation;
}

const Vector<Exception> Exception::GetExceptionList() const
{
	return exceptionList;
}

void Exception::Throw(const String& exceptionText, const SourceLocation& srcLocation)
{
	throw Exception(exceptionText, srcLocation);
}

void Exception::Throw(String&& exceptionText, SourceLocation&& srcLocation)
{
	throw Exception(std::forward<String>(exceptionText), std::forward<SourceLocation>(srcLocation));
}

String Exception::ToString() const
{
	return *this;
}

String Exception::SrcLocationToString(const SourceLocation& sourceLocation) const
{
	return std::format("{}:{} {}", sourceLocation.file_name(), sourceLocation.line(), sourceLocation.function_name());
}

String Exception::ExceptionToString(const SourceLocation& sourceLocation, const String& text) const
{
	return std::format("{}: {}", SrcLocationToString(sourceLocation), text);
}
