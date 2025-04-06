#include "customstring.h"


String::~String() { delete[] chars; }

String::String() { }
String::String(const size_t cap) : current_capacity(cap), chars(new char[cap]()) { }

String::String(const String& str) : current_capacity(str.current_capacity), chars(new char[str.current_capacity]())
{
	for(; count < str.count; ++count)
		chars[count] = str.chars[count];
}

String::String(String&& str) : count(str.count), current_capacity(str.current_capacity), chars(str.chars)
{
	str.count = 0;
	str.current_capacity = 0;
	str.chars = nullptr;
}

String::String(const char* str)
{
	if(!str)
		return;

	const char* temp = str;

	while(*temp)
	{
		++current_capacity;
		++temp;
	}

	chars = new char[current_capacity]();

	while(str != temp)
	{
		chars[count] = *str;
		++count;
		++str;
	}
}

bool String::empty() const { return !count; }
size_t String::size() const { return count; }
size_t String::capacity() const { return current_capacity; }

void String::clear()
{
	count = 0;
	current_capacity = 0;
	delete[] chars;
	chars = nullptr;
}

void String::reserve(const size_t cap)
{
	if(cap <= current_capacity)
		return;

	const char* temp = chars;
	chars = new char[cap]();

	for(size_t t = 0; t < current_capacity; ++t)
		chars[t] = temp[t];

	delete[] temp;
	current_capacity = cap;
}

void String::push_back(const char ch)
{
	if(count == current_capacity)
		reserve(current_capacity * GROWTH_FACTOR > DEFAULT_CAPACITY ? current_capacity * GROWTH_FACTOR : DEFAULT_CAPACITY);

	chars[count++] = ch;
}

String& String::append(const char ch)
{
	push_back(ch);
	return *this;
}

String& String::append(const char* str)
{
	while(*str)
	{
		push_back(*str);
		++str;
	}

	return *this;
}

String& String::append(const String& str)
{
	reserve(count + str.count);
	for(const char ch : str)
		push_back(ch);
	return *this;
}

char* String::begin() { return chars; }
const char* String::begin() const { return chars; }

char* String::end() { return chars + count; }
const char* String::end() const { return chars + count; }

char& String::operator[](const size_t pos) { return chars[pos]; }
const char& String::operator[](const size_t pos) const { return chars[pos]; }

String& String::operator=(const String& str)
{
	delete[] chars;

	count = str.count;
	current_capacity = str.current_capacity;

	for(size_t t = 0; t < count; ++t)
		chars[t] = str.chars[t];

	return *this;
}

String& String::operator=(String&& str)
{
	delete[] chars;

	count = str.count;
	current_capacity = str.current_capacity;
	chars = str.chars;

	str.count = 0;
	str.current_capacity = 0;
	str.chars = nullptr;

	return *this;
}

String& String::operator+=(const char ch) { return append(ch); }
String& String::operator+=(const char* str) { return append(str); }
String& String::operator+=(const String& str) { return append(str); }


String operator+(const String& a, const String& b) { return String(a).append(b); }
String operator+(const String& str, const char ch) { return String(str).append(ch); }
String operator+(const String& str, const char* cstr) { return String(str).append(cstr); }

std::ostream& operator<<(std::ostream& stream, const String& str)
{
	for(const auto& ch : str)
		stream << ch;
	return stream;
}


bool compare_ignore_case(const String& a, const String& b)
{
	if(a.empty())
		return !b.empty();
	else if(b.empty())
		return false;

	const size_t len = a.size() < b.size() ? a.size() : b.size();

	for(size_t t = 0; t < len; ++t)
	{
		const char cha = tolower(a[t]);
		const char chb = tolower(b[t]);

		if(cha == chb)
			continue;

		return cha < chb;
	}

	return a.size() < b.size();
}
