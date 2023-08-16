#pragma once
/* strconv2.h Slight Modded Ver. by Ho9tocraft */
/* Last Modified:             2023/08/15 23:40 */
#include <stdarg.h>
#include <windows.h>

#include <codecvt>
#include <iostream>
#include <locale>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

static inline wstring cp_to_wide(const string& s, UINT codepage)
{
    int in_length = (int)s.length();
    int out_length =
        MultiByteToWideChar(codepage, 0, s.c_str(), in_length, 0, 0);
    wstring result(out_length, L'\0');
    if (out_length)
        MultiByteToWideChar(codepage, 0, s.c_str(), in_length, &result[0],
                            out_length);
    return result;
}
static inline string wide_to_cp(const wstring& s, UINT codepage)
{
    int in_length = (int)s.length();
    int out_length =
        WideCharToMultiByte(codepage, 0, s.c_str(), in_length, 0, 0, 0, 0);
    string result(out_length, '\0');
    if (out_length)
        WideCharToMultiByte(codepage, 0, s.c_str(), in_length, &result[0],
                            out_length, 0, 0);
    return result;
}

static inline string cp_to_utf8(const string& s, UINT codepage)
{
    if (codepage == CP_UTF8) return s;
    wstring wide = cp_to_wide(s, codepage);
    return wide_to_cp(wide, CP_UTF8);
}
static inline string utf8_to_cp(const string& s, UINT codepage)
{
    if (codepage == CP_UTF8) return s;
    wstring wide = cp_to_wide(s, CP_UTF8);
    return wide_to_cp(wide, codepage);
}

static inline wstring ansi_to_wide(const string& s)
{
    return cp_to_wide(s, CP_ACP);
}
static inline string wide_to_ansi(const wstring& s)
{
    return wide_to_cp(s, CP_ACP);
}

static inline wstring sjis_to_wide(const string& s)
{
    return cp_to_wide(s, 932);
}
static inline string wide_to_sjis(const wstring& s)
{
    return wide_to_cp(s, 932);
}

static inline wstring utf8_to_wide(const string& s)
{
    return cp_to_wide(s, CP_UTF8);
}
static inline string wide_to_utf8(const wstring& s)
{
    return wide_to_cp(s, CP_UTF8);
}

static inline string ansi_to_utf8(const string& s)
{
    return cp_to_utf8(s, CP_ACP);
}
static inline string utf8_to_ansi(const string& s)
{
    return utf8_to_cp(s, CP_ACP);
}

static inline string sjis_to_utf8(const string& s)
{
    return cp_to_utf8(s, 932);
}
static inline string utf8_to_sjis(const string& s)
{
    return utf8_to_cp(s, 932);
}

#ifdef __cpp_char8_t
static inline u8string utf8_to_char8(const string& s)
{
    return u8string(s.begin(), s.end());
}
static inline string char8_to_utf8(const u8string& s)
{
    return string(s.begin(), s.end());
}

static inline wstring char8_to_wide(const u8string& s)
{
    return cp_to_wide(char8_to_utf8(s), CP_UTF8);
}
static inline u8string wide_to_char8(const wstring& s)
{
    return utf8_to_char8(wide_to_cp(s, CP_UTF8));
}

static inline u8string cp_to_char8(const string& s, UINT codepage)
{
    return utf8_to_char8(cp_to_utf8(s, codepage));
}
static inline string char8_to_cp(const u8string& s, UINT codepage)
{
    return utf8_to_cp(char8_to_utf8(s), codepage);
}

static inline u8string ansi_to_char8(const string& s)
{
    return cp_to_char8(s, CP_ACP);
}
static inline string char8_to_ansi(const u8string& s)
{
    return char8_to_cp(s, CP_ACP);
}

static inline u8string sjis_to_char8(const string& s)
{
    return cp_to_char8(s, 932);
}
static inline string char8_to_sjis(const u8string& s)
{
    return char8_to_cp(s, 932);
}
#endif

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4996)
#endif

static inline string char16_to_utf8(const u16string& s)
{
    try
    {
        wstring_convert<codecvt_utf8<char16_t>, char16_t> convert;
        return convert.to_bytes(s);
    }
    catch (...)
    {
        return "";
    }
}

static inline u16string utf8_to_char16(const string& s)
{
    try
    {
        wstring_convert<codecvt_utf8<char16_t>, char16_t> convert;
        return convert.from_bytes(s);
    }
    catch (...)
    {
        return u"";
    }
}

static inline string char16_to_cp(const u16string& s,
                                       unsigned int codepage)
{
    return utf8_to_cp(char16_to_utf8(s), codepage);
}

static inline string char32_to_utf8(const u32string& s)
{
    try
    {
        wstring_convert<codecvt_utf8<char32_t>, char32_t> convert;
        return convert.to_bytes(s);
    }
    catch (...)
    {
        return "";
    }
}

static inline u32string utf8_to_char32(const string& s)
{
    try
    {
        wstring_convert<codecvt_utf8<char32_t>, char32_t> convert;
        return convert.from_bytes(s);
    }
    catch (...)
    {
        return U"";
    }
}

static inline string char32_to_cp(const u32string& s,
                                       unsigned int codepage)
{
    return utf8_to_cp(char32_to_utf8(s), codepage);
}

#ifdef __cpp_char8_t
static inline u8string char16_to_char8(const u16string& s)
{
    try
    {
        wstring_convert<codecvt_utf8<char16_t>, char16_t> convert;
        return utf8_to_char8(convert.to_bytes(s));
    }
    catch (...)
    {
        return u8"";
    }
}

static inline u16string char8_to_char16(const u8string& s)
{
    try
    {
        wstring_convert<codecvt_utf8<char16_t>, char16_t> convert;
        return convert.from_bytes(char8_to_utf8(s));
    }
    catch (...)
    {
        return u"";
    }
}

static inline u8string char32_to_char8(const u32string& s)
{
    try
    {
        wstring_convert<codecvt_utf8<char32_t>, char32_t> convert;
        return utf8_to_char8(convert.to_bytes(s));
    }
    catch (...)
    {
        return u8"";
    }
}

static inline u32string char8_to_char32(const u8string& s)
{
    try
    {
        wstring_convert<codecvt_utf8<char32_t>, char32_t> convert;
        return convert.from_bytes(char8_to_utf8(s));
    }
    catch (...)
    {
        return U"";
    }
}
#endif

static inline wstring vformat(const wchar_t* format, va_list args)
{
    int len = _vsnwprintf(0, 0, format, args);
    if (len < 0) return L"";
    vector<wchar_t> buffer(len + 1);
    len = _vsnwprintf(&buffer[0], len, format, args);
    if (len < 0) return L"";
    buffer[len] = L'\0';
    return &buffer[0];
}
static inline string vformat(const char* format, va_list args)
{
    int len = _vsnprintf(0, 0, format, args);
    if (len < 0) return "";
    vector<char> buffer(len + 1);
    len = _vsnprintf(&buffer[0], len, format, args);
    if (len < 0) return "";
    buffer[len] = '\0';
    return &buffer[0];
}
#ifdef __cpp_char8_t
static inline u8string vformat(const char8_t* format, va_list args)
{
    int len = _vsnprintf(0, 0, (const char*)format, args);
    if (len < 0) return u8"";
    vector<char> buffer(len + 1);
    len = _vsnprintf(&buffer[0], len, (const char*)format, args);
    if (len < 0) return u8"";
    buffer[len] = '\0';
    return (char8_t*)&buffer[0];
}
#endif

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

static inline wstring format(const wchar_t* format, ...)
{
    va_list args;
    va_start(args, format);
    wstring s = vformat(format, args);
    va_end(args);
    return s;
}
static inline string format(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    string s = vformat(format, args);
    va_end(args);
    return s;
}
#ifdef __cpp_char8_t
static inline u8string format(const char8_t* format, ...)
{
    va_list args;
    va_start(args, format);
    u8string s = vformat(format, args);
    va_end(args);
    return s;
}
#endif

static inline void format(ostream& ostrm, const wchar_t* format, ...)
{
    va_list args;
    va_start(args, format);
    wstring s = vformat(format, args);
    va_end(args);
    ostrm << wide_to_utf8(s) << flush;
}
static inline void format(ostream& ostrm, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    string s = vformat(format, args);
    va_end(args);
    ostrm << s << flush;
}
#ifdef __cpp_char8_t
static inline void format(ostream& ostrm, const char8_t* format, ...)
{
    va_list args;
    va_start(args, format);
    u8string s = vformat(format, args);
    va_end(args);
    ostrm << char8_to_utf8(s) << flush;
}
#endif

static inline string formatA(const wchar_t* format, ...)
{
    va_list args;
    va_start(args, format);
    wstring s = vformat(format, args);
    va_end(args);
    return wide_to_ansi(s);
}
static inline string formatA(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    string s = vformat(format, args);
    va_end(args);
    return utf8_to_ansi(s);
}
#ifdef __cpp_char8_t
static inline string formatA(const char8_t* format, ...)
{
    va_list args;
    va_start(args, format);
    u8string s = vformat(format, args);
    va_end(args);
    return char8_to_ansi(s);
}
#endif

static inline void formatA(ostream& ostrm, const wchar_t* format, ...)
{
    va_list args;
    va_start(args, format);
    wstring s = vformat(format, args);
    va_end(args);
    ostrm << wide_to_ansi(s) << flush;
}
static inline void formatA(ostream& ostrm, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    string s = vformat(format, args);
    va_end(args);
    ostrm << utf8_to_ansi(s) << flush;
}
#ifdef __cpp_char8_t
static inline void formatA(ostream& ostrm, const char8_t* format, ...)
{
    va_list args;
    va_start(args, format);
    u8string s = vformat(format, args);
    va_end(args);
    ostrm << char8_to_ansi(s) << flush;
}
#endif

static inline void dbgmsg(const wchar_t* title, const wchar_t* format, ...)
{
    va_list args;
    va_start(args, format);
    wstring s = vformat(format, args);
    va_end(args);
    MessageBoxW(0, s.c_str(), title, MB_OK);
}
static inline void dbgmsg(const char* title, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    string s = vformat(format, args);
    va_end(args);
    MessageBoxW(0, utf8_to_wide(s).c_str(), utf8_to_wide(title).c_str(), MB_OK);
}
#ifdef __cpp_char8_t
static inline void dbgmsg(const char8_t* title, const char8_t* format, ...)
{
    va_list args;
    va_start(args, format);
    u8string s = vformat(format, args);
    va_end(args);
    MessageBoxW(0, char8_to_wide(s).c_str(), char8_to_wide(title).c_str(),
                MB_OK);
}
#endif

static inline HANDLE handle_for_ostream(ostream& ostrm)
{
    if (&ostrm == &cout)
    {
        return GetStdHandle(STD_OUTPUT_HANDLE);
    }
    else if (&ostrm == &cerr)
    {
        return GetStdHandle(STD_ERROR_HANDLE);
    }
    return INVALID_HANDLE_VALUE;
}
static inline void dbgout(ostream& ostrm, const wchar_t* format, ...)
{
    va_list args;
    va_start(args, format);
    wstring ws = vformat(format, args);
    va_end(args);
    HANDLE h = handle_for_ostream(ostrm);
    if (h == INVALID_HANDLE_VALUE)
    {
        return;
    }
    DWORD dwNumberOfCharsWrite;
    if (GetFileType(h) != FILE_TYPE_CHAR)
    {
        string s = wide_to_cp(ws, GetConsoleOutputCP());
        WriteFile(h, s.c_str(), (DWORD)s.size(), &dwNumberOfCharsWrite, NULL);
    }
    else
    {
        WriteConsoleW(h, ws.c_str(), (DWORD)ws.size(), &dwNumberOfCharsWrite,
                      NULL);
    }
}
static inline void dbgout(ostream& ostrm, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    string s = vformat(format, args);
    va_end(args);
    HANDLE h = handle_for_ostream(ostrm);
    if (h == INVALID_HANDLE_VALUE)
    {
        return;
    }
    DWORD dwNumberOfCharsWrite;
    if (GetFileType(h) != FILE_TYPE_CHAR)
    {
        s = utf8_to_cp(s, GetConsoleOutputCP());
        WriteFile(h, s.c_str(), (DWORD)s.size(), &dwNumberOfCharsWrite, NULL);
    }
    else
    {
        wstring ws = utf8_to_wide(s);
        WriteConsoleW(h, ws.c_str(), (DWORD)ws.size(), &dwNumberOfCharsWrite,
                      NULL);
    }
}
#ifdef __cpp_char8_t
static inline void dbgout(ostream& ostrm, const char8_t* format, ...)
{
    va_list args;
    va_start(args, format);
    u8string s = vformat(format, args);
    va_end(args);
    HANDLE h = handle_for_ostream(ostrm);
    if (h == INVALID_HANDLE_VALUE)
    {
        return;
    }
    DWORD dwNumberOfCharsWrite;
    if (GetFileType(h) != FILE_TYPE_CHAR)
    {
        string str = char8_to_cp(s, GetConsoleOutputCP());
        WriteFile(h, (const char*)str.c_str(), (DWORD)str.size(),
                  &dwNumberOfCharsWrite, NULL);
    }
    else
    {
        wstring ws = char8_to_wide(s);
        WriteConsoleW(h, ws.c_str(), (DWORD)ws.size(), &dwNumberOfCharsWrite,
                      NULL);
    }
}
#endif

class unicode_ostream
{
private:
    ostream* m_ostrm;
    UINT m_target_cp;
    bool is_ascii(const string& s)
    {
        for (size_t i = 0; i < s.size(); i++)
        {
            unsigned char c = (unsigned char)s[i];
            if (c > 0x7f) return false;
        }
        return true;
    }

public:
    unicode_ostream(ostream& ostrm, UINT target_cp = CP_ACP)
        : m_ostrm(&ostrm), m_target_cp(target_cp)
    {
    }
    ostream& stream() { return *m_ostrm; }
    void stream(ostream& ostrm) { m_ostrm = &ostrm; }
    UINT target_cp() { return m_target_cp; }
    void target_cp(UINT cp) { m_target_cp = cp; }
    template <typename T>
    unicode_ostream& operator<<(const T& x)
    {
        ostringstream oss;
        oss << x;
        string output = oss.str();
        if (is_ascii(output))
        {
            (*m_ostrm) << x;
        }
        else
        {
            (*m_ostrm) << utf8_to_cp(output, m_target_cp);
        }
        return *this;
    }
    unicode_ostream& operator<<(const wstring& x)
    {
        (*m_ostrm) << wide_to_cp(x, m_target_cp);
        return *this;
    }
    unicode_ostream& operator<<(const wchar_t* x)
    {
        (*m_ostrm) << wide_to_cp(x, m_target_cp);
        return *this;
    }
    unicode_ostream& operator<<(const string& x)
    {
        (*m_ostrm) << utf8_to_cp(x, m_target_cp);
        return *this;
    }
    unicode_ostream& operator<<(const char* x)
    {
        (*m_ostrm) << utf8_to_cp(x, m_target_cp);
        return *this;
    }
#ifdef __cpp_char8_t
    unicode_ostream& operator<<(const u8string& x)
    {
        (*m_ostrm) << char8_to_cp(x, m_target_cp);
        return *this;
    }
    unicode_ostream& operator<<(const char8_t* x)
    {
        (*m_ostrm) << char8_to_cp(x, m_target_cp);
        return *this;
    }
#endif
    unicode_ostream& operator<<(const u16string& x)
    {
        (*m_ostrm) << char16_to_cp(x, m_target_cp);
        return *this;
    }
    unicode_ostream& operator<<(const char16_t* x)
    {
        (*m_ostrm) << char16_to_cp(x, m_target_cp);
        return *this;
    }
    unicode_ostream& operator<<(const u32string& x)
    {
        (*m_ostrm) << char32_to_cp(x, m_target_cp);
        return *this;
    }
    unicode_ostream& operator<<(const char32_t* x)
    {
        (*m_ostrm) << char32_to_cp(x, m_target_cp);
        return *this;
    }
    unicode_ostream& operator<<(
        ostream& (*pf)(ostream&))  // For manipulators...
    {
        (*m_ostrm) << pf;
        return *this;
    }
    unicode_ostream& operator<<(basic_ios<char>& (*pf)(
        basic_ios<char>&))  // For manipulators...
    {
        (*m_ostrm) << pf;
        return *this;
    }
};

#define U8(X) ((const char *)u8##X)
#define U16(X) (u##X)
#define U32(X) (U##X)
#define WIDE(X) (L##X)
