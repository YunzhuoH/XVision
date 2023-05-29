/*****************************************************************************
 * HString.h
 *****************************************************************************
 *
 * Project:     HALCON/C++
 * Description: String class for automatic memory management
 *
 * (c) 2010-2019 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************
 *
 *
 *****************************************************************************/


#ifndef HCPP_STRING_H
#define HCPP_STRING_H


namespace HalconCpp
{

class HStringData;
class HTupleElement;


class LIntExport HString
{

public:

  // Create an empty string
  HString();

  // Create from C string
  HString(const char* text);

#if _WIN32
  // Create from wide character string
  HString(const wchar_t* text);
#endif

  // Copy constructor
  HString(const HString& string);

  // Destroy string
  virtual ~HString();

  // Assignment operator
  HString& operator=(const HString& string);

  // String equality
  bool operator==(const HString& string) const;
  bool operator!=(const HString& string) const;
  bool operator==(const char* string) const;
  bool operator!=(const char* string) const;
#if _WIN32
  bool operator==(const wchar_t* string) const;
  bool operator!=(const wchar_t* string) const;
#endif

  // Concatenation
  HString  operator+(const HString& string);
  HTuple   operator+(const HTuple& tuple);
  HTuple   operator+(const HTupleElement& te);
  HString& operator+=(const HString& string);
  HString& operator+=(const char * c);
#if _WIN32
  HString& operator+=(const wchar_t * c);
#endif

  /* Methods */

  // Clear contents of string
  void Clear();

  // Test for empty string
  bool IsEmpty() const;

  // ANSI implementations of the Length and Text method

  // Length of the char* string in bytes
  // note that the returned length of a string with non-ASCII characters
  // depends on the encoding and can be greater than the number of characters
  size_t      LengthA() const;

  // Pointer to string data (internal char* representation with
  // the selected interface encoding)
  // the pointer is valid as long as the HString is not modified
  const char* TextA() const;

  // implicit cast operator to char* C string
  operator const char* (void) const
  {
    return TextA();
  }

#ifdef _WIN32
  // wide char implementations of the Length and Text method (Windows only)

  // Length of the wchar_t* string in wchar_t words
  // note that the length of a string which contains Unicode characters which
  // are not part of the Basic Multilingual Plane (BMP, code points > 0xffff)
  // is greater than the number of characters
  size_t         LengthW() const;

#ifdef _NATIVE_WCHAR_T_DEFINED
  // pointer to wide string data (internal wchar_t* representation with
  // UTF-16 encoding)
  // and implicit cast operator to wchar_t* C string
  // the pointer is valid as long as the HString is not modified
  const wchar_t* TextW() const;
  operator const wchar_t* (void) const;
#else
  const wchar_t* TextW() const
  {
    return TextUS();
  }
#endif
  // the following methods are for being compatible with applications which
  // are compiled with /Zc:wchar_t-
  const unsigned short* TextUS() const;
  operator const unsigned short* (void) const;
#endif

  // For compatibility reasons the functions Text and Length are defined
  // with the char* semantics.
  // Please note the encoding of the returned strings now depends on the
  // interface encoding and can be set via SetHcppInterfaceStringEncodingIsUtf8

  // Length of (char*) string (in the current interface encoding, in bytes)
  size_t Length() const
  {
    return LengthA();
  }

  // Pointer to string data (internal char* representation with
  // the selected interface encoding)
  // the pointer is valid as long as the HString is not modified
  const char* Text() const
  {
    return TextA();
  }


  // transcoding functions
  //
  // these functions return a pointer to memory owned by this HString instance
  // the pointer becomes invalid, when the string is changed.
  const char* ToLocal8bit() const;
  const char* ToUtf8() const;
  //
  static HString FromLocal8bit(const char* str);
  static HString FromUtf8(const char* str);

protected:

  // Internal constructor
  HString(const HStringData& text);

  // Data container
  HStringData& mText;
};


}

#endif
