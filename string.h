//
//  string.h
//

#ifndef string_h
#define string_h

#include <string.h>

class String
{
public:
    String(const char* str="", size_t size=SIZE_T_MAX)
    {
        size = size == SIZE_T_MAX ? strlen(str) : size;
        if (size >= kSSO) {
            size_ = size;
            data_ = new char[size + 1];
            assert(!sso_);
            memcpy(data_, str, size);
            data_[size+1] = '\0';
        } else {
            ssize_ = size;
            sso_ = true;
            memcpy(str_, str, size);
            str_[size+1] = '\0';
        }
    }
    
    String(const String& rhs)
    : String(rhs.c_str(), rhs.size())
    {
    }
    
    ~String()
    {
        if (!sso_) {
            delete[] data_;
        }
    }
    
    String(String&& rhs): String()
    {
        swap(rhs);
    }
    
    String& operator=(String&& rhs)
    {
        swap(rhs);
        return *this;
    }
    
    String& operator=(const String& rhs)
    {
        *this = String(rhs);
        return *this;
    }
    
    size_t size() const
    {
        return sso_ ? ssize_ : size_;
    }
    
    const char* c_str() const
    {
        return sso_ ? str_ : data_;
    }
private:
    static constexpr size_t kSSO = sizeof(char*) + sizeof(size_t) - 1;

    void swap(String& rhs)
    {
        std::swap(size_, rhs.size_);
        std::swap(data_, rhs.data_);
    }
    union {
        struct {
            char* data_;
            size_t size_;
        };
        struct {
            bool sso_ : 1;
            size_t ssize_ : 7;
            char str_[kSSO];
        };
    };
};


#endif /* string_h */
