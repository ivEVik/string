
#ifndef CUSTOM_STRING_H
#define CUSTOM_STRING_H


#include <ostream>


struct String final
{
	static constexpr float GROWTH_FACTOR = 1.5f;
	static constexpr size_t DEFAULT_CAPACITY = 16;

	static_assert(GROWTH_FACTOR > 1.0f, "Invalid string growth.");
	static_assert(DEFAULT_CAPACITY > 0, "Invalid default string capacity.");

public:
	~String();

	String();
	String(const size_t cap);
	String(const String& str);
	String(String&& str);
	String(const char* str);

	bool empty() const;
	size_t size() const;

	void clear();
	void reserve(const size_t cap);

	void push_back(const char ch);
	String& append(const char ch);
	String& append(const char* str);
	String& append(const String& str);

	char& operator[](const size_t pos);
	const char& operator[](const size_t pos) const;

	String& operator=(const String& str);
	String& operator=(String&& str);

	String& operator+=(const char ch);
	String& operator+=(const char* str);
	String& operator+=(const String& str);

	friend String operator+(const String& a, const String& b);
	friend String operator+(const String& str, const char ch);
	friend String operator+(const String& str, const char* cstr);

	friend std::ostream& operator<<(std::ostream& stream, const String& str);

private:
	size_t count = 0;
	size_t current_capacity = 0;
	char* chars = nullptr;
};

bool compare_ignore_case(const String& a, const String& b);


#endif
