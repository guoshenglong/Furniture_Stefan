// Copyright 2007-2013 metaio GmbH. All rights reserved.
#ifndef __AS_STLCOMPATIBILITY_H_INCLUDED__
#define __AS_STLCOMPATIBILITY_H_INCLUDED__

#if !defined(METAIO_DLL_API)
#if !defined(AS_USE_METAIOSDKDLL)
	#define METAIO_DLL_API	// we don't have a dll file
#else
#ifdef AS_METAIOSDKDLL_EXPORTS
	#ifdef AS_ANDROID
		#define METAIO_DLL_API __attribute__ ((visibility("default")))
	#else
		#define METAIO_DLL_API __declspec(dllexport)
	#endif
#else
	#define METAIO_DLL_API __declspec(dllimport)
#endif
#endif
#endif


#include <metaioSDK/BackwardCompatibility.h>

#include <cassert>
#include <climits>
#include <sstream>
#include <string>
#include <vector>

namespace metaio
{
namespace stlcompat
{

const char* const EMPTY_STRING_CONSTANT = "";

/**
 * Minimal string implementation that converts to std::string and is mostly immutable
 */
class METAIO_DLL_API String
{
public:
	static const unsigned long npos = ULONG_MAX;

	/// Constructor for empty string
	String() :
		m_pData(0),
		m_length(0)
	{
	}

	/**
	 * Constructor from zero-terminated C string
	 *
	 * \param str C string (must be zero-terminated)
	 */
	String(const char* str)
	{
		m_length = (unsigned long)strlen(str);
		m_pData = new char[m_length+1];
		memcpy(m_pData, str, m_length+1);
	}

	/**
	 * Constructor from zero-terminated C string with given length
	 *
	 * \param str C string (does not have to be zero-terminated)
	 * \param length Number of characters to copy from str
	 */
	String(const char* str, unsigned long length)
	{
		m_length = length;
		m_pData = new char[m_length+1];
		memcpy(m_pData, str, m_length);
		m_pData[m_length] = 0;
	}

	/// Destructor
	~String()
	{
		if (m_pData)
			delete[] m_pData;
	}

	/// Copy constructor
	String(const String& other)
	{
		if (other.m_pData)
		{
			m_length = other.m_length;
			m_pData = new char[m_length+1];
			memcpy(m_pData, other.m_pData, m_length+1);
		}
		else
		{
			m_pData = 0;
			m_length = 0;
		}
	}

	/// Assignment operator
	String& operator=(const String& other)
	{
		if (this != &other)
		{
			if (m_pData)
				delete[] m_pData;

			m_pData = 0;
			m_length = 0;

			if (other.m_pData)
			{
				m_length = other.m_length;
				m_pData = new char[m_length+1];
				memcpy(m_pData, other.m_pData, m_length+1);
			}
		}

		return *this;
	}

	/// Assignment operator from zero-terminated C string
	String& operator=(const char* str)
	{
		if (m_pData)
			delete[] m_pData;

		m_length = (unsigned long)strlen(str);
		m_pData = new char[m_length+1];
		memcpy(m_pData, str, m_length+1);

		return *this;
	}

	/// std::string-compatible constructor
	String(const std::string& str)
	{
		if (!str.empty())
		{
			m_length = str.length();
			m_pData = new char[m_length+1];
			memcpy(m_pData, str.c_str(), m_length);
			m_pData[m_length] = 0;
		}
		else
		{
			m_pData = 0;
			m_length = 0;
		}
	}

	/// Assignment operator from std::string
	String& operator=(const std::string& str)
	{
		if (m_pData)
			delete[] m_pData;

		m_pData = 0;
		m_length = 0;

		if (!str.empty())
		{
			m_length = str.length();
			m_pData = new char[m_length+1];
			memcpy(m_pData, str.c_str(), m_length);
			m_pData[m_length] = 0;
		}

		return *this;
	}

	/**
	 * Get a zero-terminated C string
	 *
	 * The buffer can be expected to be valid during the lifetime of this String instance but only
	 * until the next non-const method call.
	 *
	 * \return Zero-terminated C string
	 */
	const char* c_str() const
	{
		return m_pData ? m_pData : EMPTY_STRING_CONSTANT;
	}

	/// \copydoc compare(const char*, unsigned long)
	int compare(const stlcompat::String& other) const
	{
		return compare(other.c_str(), other.size());
	}

	/// \copydoc compare(const char*, unsigned long)
	int compare(const std::string& other) const
	{
		return compare(other.c_str(), other.size());
	}

	/// \copydoc compare(const char*, unsigned long)
	int compare(const char* other) const
	{
		return compare(other, strlen(other));
	}

	/**
	 * Check whether string is empty
	 * \sa size
	 * \return True if string is empty, otherwise false
	 */
	bool empty() const
	{
		return m_length == 0;
	}

	/**
	 * Determines the length of the string
	 *
	 * Alias for size().
	 *
	 * \sa size
	 * \return Length of the string
	 */
	unsigned long length() const
	{
		return m_length;
	}

	/**
	 * Determines the length of the string
	 * \return Length of the string
	 */
	unsigned long size() const
	{
		return m_length;
	}

	/**
	 * Get a substring
	 *
	 * \param startIndex Index from which the substring should begin
	 * \param length Maximum number of characters that the substring should contain
	 */
	String substr(unsigned long startIndex, unsigned long length = npos)
	{
		if (startIndex >= m_length)
			return EMPTY_STRING_CONSTANT;

		length = length < m_length - startIndex ? length : m_length - startIndex;
		return String(m_pData + startIndex, length);
	}

	/**
	 * Get the n-th character of the string
	 *
	 * \param pos Zero-based index
	 * \return Character at position pos (0 if pos == string length)
	 */
	const char& operator[](unsigned long pos) const
	{
		// Because m_pData might be NULL for empty string, always use empty string constant here
		if (pos == m_length)
			return EMPTY_STRING_CONSTANT[0];

		if (pos > m_length)
		{
			assert(pos <= m_length);
			return EMPTY_STRING_CONSTANT[0];
		}

		return m_pData[pos];
	}

	/// Convert to an std::string
	operator std::string() const
	{
		if (m_pData)
			return std::string(m_pData, m_length);
		else
			return std::string();
	}

	/// Compares two strings
	friend bool operator==(const String& lhs, const String& rhs)
	{
		if (!lhs.m_length)
			return !rhs.m_length;

		if (lhs.m_length != rhs.m_length)
			return false;

		return memcmp(lhs.m_pData, rhs.m_pData, lhs.m_length) == 0;
	}

	/// Compares string with a C string
	friend bool operator==(const String& lhs, const char* rhs)
	{
		if (!*rhs)
			return lhs.m_length == 0;

		if (!lhs.m_length)
			return false;

		for (unsigned long i = 0; i < lhs.m_length; ++i)
		{
			if (!*rhs || *rhs != lhs.m_pData[i])
				return false;

			++rhs;
		}

		return !*rhs;
	}

	/// Compares string with a C string
	friend bool operator==(const char* lhs, const String& rhs)
	{
		return rhs == lhs;
	}

	/// Checks inequality
	friend bool operator!=(const String& lhs, const String& rhs)
	{
		return !(lhs == rhs);
	}

	/// Checks inequality
	friend bool operator!=(const String& lhs, const char* rhs)
	{
		return !(lhs == rhs);
	}

	/// Checks inequality
	friend bool operator!=(const char* lhs, const String& rhs)
	{
		return !(lhs == rhs);
	}

	friend std::ostream& operator<<(std::ostream& stream, const String& s)
	{
		return stream << std::string(s);
	}

private:

	/**
	 * Compares with another string
	 *
	 * \param other String to compare with
	 * \param otherLength Number of characters in the other string
	 * \return 0 if both strings are equal, <0 if either the value of the first non-matching
	 *         character in the other string is larger or the other string is longer, >0 if either
	 *         the value of the first non-matching character in the other string is smaller or the
	 *         other string is shorter
	 */
	int compare(const char* other, unsigned long otherLength) const
	{
		if (m_length == otherLength)
		{
			if (!m_length)
				return 0;

			return memcmp(m_pData, other, m_length);
		}

		const unsigned long minLength = m_length < otherLength ? m_length : otherLength;

		const int cmp = memcmp(m_pData, other, minLength);
		if (cmp)
			return cmp;
		else
			return m_length < otherLength ? -1 : 1;
	}

	/// Data pointer, must always include zero terminator or be NULL
	char*			m_pData;

	/// Number of chars in m_pData, must always be updated when m_pData is modified
	unsigned long	m_length;
};



/**
 * Basic vector implementation that converts to std::vector
 *
 * Convert the instance to std::vector if you need advanced methods.
 */
template<typename T> class Vector
{
public:
	/// Constructor for empty vector
	Vector() :
		m_pElements(0),
		m_elementsSize(0),
		m_size(0)
	{
	}

	/// Destructor
	~Vector()
	{
		deleteAll();
	}

	/// Copy constructor
	Vector(const Vector& other) :
		m_pElements(0),
		m_elementsSize(0),
		m_size(0)
	{
		if (!other.m_pElements)
			return;

		m_pElements = new unsigned char[sizeof(T) * other.m_elementsSize];
		m_elementsSize = other.m_elementsSize;

		const T* const src = reinterpret_cast<const T*>(other.m_pElements);

		for (unsigned long i = 0; i < other.m_size; ++i)
			new (reinterpret_cast<T*>(m_pElements) + i) T(src[i]);

		m_size = other.m_size;
	}

	/// Assignment operator
	Vector& operator=(const Vector& other)
	{
		if (&other == this)
			return *this;

		deleteAll();

		if (!other.m_pElements || !other.m_size)
			return *this;

		m_pElements = new unsigned char[sizeof(T) * other.m_elementsSize];
		m_elementsSize = other.m_elementsSize;

		const T* const src = reinterpret_cast<const T*>(other.m_pElements);

		for (unsigned long i = 0; i < other.m_size; ++i)
			new (reinterpret_cast<T*>(m_pElements) + i) T(src[i]);

		m_size = other.m_size;

		return *this;
	}

	/// Copy constructor from std::vector
	Vector(const std::vector<T>& other) :
		m_pElements(0),
		m_elementsSize(0),
		m_size(0)
	{
		const typename std::vector<T>::size_type otherSize = other.size();
		if (!otherSize)
			return;

		m_pElements = new unsigned char[sizeof(T) * otherSize];
		m_elementsSize = otherSize;

		const T* const src = &other[0];

		for (unsigned long i = 0; i < otherSize; ++i)
			new (reinterpret_cast<T*>(m_pElements) + i) T(src[i]);

		m_size = otherSize;
	}

	/// Assignment operator from std::vector
	Vector& operator=(const std::vector<T>& other)
	{
		deleteAll();

		const typename std::vector<T>::size_type otherSize = other.size();
		if (!otherSize)
			return *this;

		m_pElements = new unsigned char[sizeof(T) * otherSize];
		m_elementsSize = otherSize;

		const T* const src = &other[0];

		for (unsigned long i = 0; i < otherSize; ++i)
			new (reinterpret_cast<T*>(m_pElements) + i) T(src[i]);

		m_size = otherSize;

		return *this;
	}

#if defined(METAIOSDK_COMPAT_HAVE_CPP11) && !defined(METAIOSDK_COMPAT_NO_CPP11_STL_FEATURES)

	/// Move constructor
	Vector(Vector&& other)
	{
		m_pElements = other.m_pElements;
		m_elementsSize = other.m_elementsSize;
		m_size = other.m_size;

		other.m_pElements = 0;
		other.m_elementsSize = 0;
		other.m_size = 0;
	}

	/// Move assignment operator
	Vector& operator=(Vector&& other)
	{
		if (&other == this)
			return *this;

		deleteAll();

		m_pElements = other.m_pElements;
		m_elementsSize = other.m_elementsSize;
		m_size = other.m_size;

		other.m_pElements = 0;
		other.m_elementsSize = 0;
		other.m_size = 0;

		return *this;
	}

#endif

	/// Removes all elements
	void clear()
	{
		deleteAll();
	}

	/// Checks if the vector is empty
	bool empty() const
	{
		return !m_size;
	}

	/// Adds an element to the vector
	void push_back(const T& copyMe)
	{
		ensureSize(m_size + 1);

		new (reinterpret_cast<T*>(m_pElements) + m_size) T(copyMe);

		++m_size;
	}

#if defined(METAIOSDK_COMPAT_HAVE_CPP11) && !defined(METAIOSDK_COMPAT_NO_CPP11_STL_FEATURES)

	/// Adds an element to the vector
	void push_back(T&& stealMe)
	{
		ensureSize(m_size + 1);

		new (reinterpret_cast<T*>(m_pElements) + m_size) T(std::move(stealMe));

		++m_size;
	}

#endif

	/// Converts to an std::vector
	operator std::vector<T>() const
	{
		if (!m_size)
			return std::vector<T>();

		return std::vector<T>(reinterpret_cast<T*>(m_pElements), reinterpret_cast<T*>(m_pElements) + m_size);
	}

	/**
	 * Get the n-th element of the vector
	 *
	 * \param index Zero-based index
	 * \return Element at position index (0 if index == number of elements)
	 */
	const T& operator[](unsigned long index) const
	{
		if (index >= m_size)
		{
			assert(index < m_size);
		}

		return reinterpret_cast<const T*>(m_pElements)[index];
	}

	/**
	 * Get the n-th element of the vector
	 *
	 * \param index Zero-based index
	 * \return Element at position index (0 if index == number of elements)
	 */
	T& operator[](unsigned long index)
	{
		if (index >= m_size)
		{
			assert(index < m_size);
		}

		return reinterpret_cast<T*>(m_pElements)[index];
	}

	/**
	 * Remove the n-th element of the vector
	 *
	 * \param index Zero-based index
	 */
	void remove(unsigned long index)
	{
		if (index >= m_size)
		{
			assert(index < m_size);
			return;
		}

		(reinterpret_cast<T*>(m_pElements) + index)->~T();

		if (index < m_size - 1)
		{
			memmove(m_pElements + sizeof(T) * index,
			        m_pElements + sizeof(T) * (index + 1),
			        sizeof(T) * (m_size - 1 - index));
		}
		else
		{
			// Set memory to 0xcc for debugging purposes
			memset(reinterpret_cast<T*>(m_pElements) + index, 0xcc, sizeof(T));
		}

		--m_size;
	}

	/**
	 * Determines the number of elements in the vector
	 * \return Number of elements
	 */
	unsigned long size() const
	{
		return m_size;
	}

private:
	void deleteAll()
	{
		if (!m_pElements)
			return;

		for (unsigned long i = 0; i < m_size; ++i)
		{
			(reinterpret_cast<T*>(m_pElements) + i)->~T();
		}

		delete[] m_pElements;
		m_pElements = 0;
		m_elementsSize = 0;
		m_size = 0;
	}

	void ensureSize(const unsigned long newElementsSize)
	{
		if (m_elementsSize >= newElementsSize || newElementsSize <= 0)
			return;

		const unsigned long actualNewElementsSize = (newElementsSize * 32) / 24;
		unsigned char* newBuffer = new unsigned char[sizeof(T) * actualNewElementsSize];

		if (m_size)
			memcpy(newBuffer, m_pElements, sizeof(T) * m_size);

		if (m_pElements)
			delete[] m_pElements;

		m_pElements = newBuffer;
		m_elementsSize = actualNewElementsSize;
	}

	unsigned char*	m_pElements; ///< buffer for elements
	unsigned long	m_elementsSize; ///< number of allocated T elements in m_pElements
	unsigned long	m_size; ///< actual number of elements
};

} // namespace stlcompat
} // namespace metaio

#endif //__AS_STLCOMPATIBILITY_H_INCLUDED__
