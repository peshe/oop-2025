#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdexcept>
#include <utility>
#include <iterator>
#include <cstddef>
#include <cctype>
#include <cstdio>

class String
{
	static constexpr std::size_t initialCapacity = 15;
	static inline char emptyString[] = "";
	char* str;
	size_t sz, cap;
public:
	typedef char* iterator;
	typedef const char* const_iterator;
	static constexpr std::size_t npos = -1;
	String(): str(emptyString), sz(), cap() {}
	String(const char* s): String(s, std::strlen(s)) {}
	String(const char* s, std::size_t n): str(new char[n + 1]), sz(n), cap(n)
	{
		std::memcpy(str, s, n);
		str[n] = 0;
	}
	String(std::size_t n, char c): str(new char[n + 1]), sz(n), cap(n)
	{
		std::memset(str, c, n);
		str[n] = 0;
	}
	String(const String& s): String(s.str, s.sz) {}
	String(String&& s) noexcept: str(s.str), sz(s.sz), cap(s.cap)
	{
		s.str = emptyString;
		s.sz = s.cap = 0;
	}
	/*String& operator=(String s) noexcept
	{
		std::swap(str, s.str);
		std::swap(sz, s.sz);
		std::swap(cap, s.cap);
		return *this;
	}*/
	String& operator=(const String& s)
	{
		if(this != &s)
		{
			if(cap < s.sz)
			{
				char* t = new char[s.sz + 1];
				if(str != emptyString) delete[] str;
				str = t;
				cap = s.sz;
			}
			sz = s.sz;
			std::memcpy(str, s.str, s.sz + 1);
		}
		return *this;
	}
	String& operator=(String&& s) noexcept
	{
		std::swap(str, s.str);
		std::swap(sz, s.sz);
		std::swap(cap, s.cap);
		return *this;
	}
	~String()
	{
		if(str != emptyString) delete[] str;
	}
	std::size_t capacity() const noexcept
	{
		return cap;
	}
	std::size_t size() const noexcept
	{
		return sz;
	}
	bool empty() const noexcept
	{
		return !sz;
	}
	void reserve(std::size_t new_cap)
	{
		if(new_cap <= cap) return;
		char* t = new char[new_cap + 1];
		cap = new_cap;
		std::memcpy(t, str, sz + 1);
		if(str != emptyString) delete[] str;
		str = t;
	}
	char operator[](std::size_t n) const
	{
		return str[n];
	}
	char& operator[](std::size_t n)
	{
		return str[n];
	}
	char at(std::size_t n) const
	{
		if(n >= sz) throw std::out_of_range("out of range");
		return str[n];
	}
	char& at(std::size_t n)
	{
		if(n >= sz) throw std::out_of_range("out of range");
		return str[n];
	}
	void push_back(char c)
	{
		if(sz >= cap) reserve(std::max(2 * cap + 1, initialCapacity));
		str[sz] = c;
		str[++sz] = 0;
	}
	void pop_back()
	{
		erase(sz - 1);
	}
	const char* c_str() const noexcept
	{
		return str;
	}
	String& erase(std::size_t index = 0, std::size_t count = npos)
	{
		if(index > sz) throw std::out_of_range("out of range");
		count = std::min(count, sz - index);
		std::memmove(str + index, str + index + count, sz - index - count + 1);
		sz -= count;
		return *this;
	}
	String& insert(std::size_t index, const String& s)
	{
		if(index > sz) throw std::out_of_range("out of range");
		reserve(sz + s.sz);
		std::memmove(str + index + s.sz, str + index, sz - index + 1);
		std::memcpy(str + index, s.str, s.sz);
		sz += s.sz;
		return *this;
	}
	String& operator+=(const String& s)
	{
		reserve(sz + s.sz);
		std::memcpy(str + sz, s.str, s.sz + 1);
		sz += s.sz;
		return *this;
	}
	String& operator+=(char c)
	{
		push_back(c);
		return *this;
	}
	iterator begin() noexcept
	{
		return iterator(str);
	}
	const_iterator begin() const noexcept
	{
		return const_iterator(str);
	}
	const_iterator cbegin() const noexcept
	{
		return const_iterator(str);
	}
	iterator end() noexcept
	{
		return iterator(str + sz);
	}
	const_iterator end() const noexcept
	{
		return const_iterator(str + sz);
	}
	const_iterator cend() const noexcept
	{
		return const_iterator(str + sz);
	}
	std::size_t find(const String& s, std::size_t pos = 0)
	{
		if(pos >= sz) return npos;
		const char* p = std::search(str + pos, str + sz, s.str, s.str + s.sz);
		return p != str + sz ? p - str : npos;
	}
	std::size_t find(const char* s, std::size_t pos = 0)
	{
		if(pos >= sz) return npos;
		const char* p = std::search(str + pos, str + sz, s, s + std::strlen(s));
		return p != str + sz ? p - str : npos;
	}
	std::size_t find(char c, std::size_t pos = 0)
	{
		if(pos >= sz) return npos;
		const char* p = reinterpret_cast<char*>(std::memchr(str + pos, c, sz - pos));
		return p ? p - str : npos;
	}
	bool operator<(const String& s) const
	{
		int tmp = std::memcmp(str, s.str, std::min(sz, s.sz));
		return tmp ? tmp < 0 : sz < s.sz;
	}
	bool operator>(const String& s) const
	{
		return s < *this;
	}
	bool operator<=(const String& s) const
	{
		return !(s < *this);
	}
	bool operator>=(const String& s) const
	{
		return !(*this < s);
	}
	bool operator==(const String& s) const
	{
		return sz != s.sz ? false : !std::memcmp(str, s.str, sz);
	}
	bool operator!=(const String& s) const
	{
		return !(*this == s);
	}
	friend std::ostream& operator<<(std::ostream& os, const String& s)
	{
		return os << s.str;
	}
};

String operator+(const String& s1, const String& s2)
{
	String res;
	res.reserve(s1.size() + s2.size());
	return (res += s1) += s2;
}

String operator+(const String& s, char c)
{
	String res;
	res.reserve(s.size() + 1);
	(res += s).push_back(c);
	return res;
}

String operator+(char c, const String& s)
{
	String res;
	res.reserve(s.size() + 1);
	res.push_back(c);
	return res += s;
}

std::istream& operator>>(std::istream& is, String& str)
{
	std::istream::sentry s(is);
	if(!s) return is;
	str.erase();
	int ch = is.peek();
	try
	{
		while(ch != EOF && !std::isspace((unsigned char)ch))
		{
			if(is.width() && static_cast<std::streamsize>(str.size()) >= is.width()) break;
			str.push_back(is.get());
			ch = is.peek();
		}
	}
	catch(const std::bad_alloc& e)
	{
		try { is.setstate(std::ios_base::badbit); }
		catch(...)
		{
			is.width(0);
			throw e;
		}
	}
	is.width(0);
	return is;
}

std::istream& getline(std::istream& is, String& str, char delim = '\n')
{
	std::istream::sentry s(is, true);
	if(!s) return is;
	str.erase();
	int ch = is.get();
	try
	{
		while(is && ch != delim)
		{
			str.push_back(ch);
			ch = is.get();
		}
	}
	catch(const std::bad_alloc& e)
	{
		try { is.setstate(std::ios_base::badbit); }
		catch(...)
		{
			throw e;
		}
	}
	return is;
}

int main()
{
	String s;
	getline(std::cin, s);
	std::cout << s << std::endl;
	return 0;
}
