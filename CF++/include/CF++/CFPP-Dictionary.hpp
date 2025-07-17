/*******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2014 Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/

/*!
 * @header      CFPP-Dictionary.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFDictionaryRef wrapper
 */

#ifndef CFPP_DICTIONARY_HPP
#define CFPP_DICTIONARY_HPP

#include <map>

namespace CF
{
    class CFPP_EXPORT Dictionary: public PropertyListType< Dictionary >
    {
        public:
            
            Dictionary();
            Dictionary( CFIndex capacity );
            Dictionary( const Dictionary & value );
            Dictionary( const AutoPointer & value );
            Dictionary( CFTypeRef cfObject );
            Dictionary( CFDictionaryRef cfObject );
            Dictionary( std::nullptr_t );
            Dictionary( std::initializer_list< Pair > value );
            Dictionary( Dictionary && value ) noexcept;
            
            ~Dictionary() override;
            
            Dictionary & operator = ( Dictionary value );
            Dictionary & operator = ( const AutoPointer & value );
            Dictionary & operator = ( CFTypeRef value );
            Dictionary & operator = ( CFDictionaryRef value );
            Dictionary & operator = ( std::nullptr_t );
            
            Dictionary & operator += ( const Pair & pair );
            Dictionary & operator << ( const Pair & pair );
            
            CFTypeRef operator [] ( CFTypeRef key )      const;
            CFTypeRef operator [] ( const char * key )   const;
            CFTypeRef operator [] ( const String & key ) const;
            
            CFTypeID  GetTypeID()   const override;
            CFTypeRef GetCFObject() const override;
            
            bool      ContainsKey( CFTypeRef key )      const;
            bool      ContainsKey( const char * key )   const;
            bool      ContainsKey( const String & key ) const;
            bool      ContainsValue( CFTypeRef value )  const;
            CFIndex   GetCount()                        const;
            CFTypeRef GetValue( CFTypeRef key )         const;
            CFTypeRef GetValue( const char * key )      const;
            CFTypeRef GetValue( const String & key )    const;
            
            void RemoveAllValues();
            void AddValue( CFTypeRef key, CFTypeRef value );
            void AddValue( const char * key, CFTypeRef value );
            void AddValue( const String & key, CFTypeRef value );
            void RemoveValue( CFTypeRef key );
            void RemoveValue( const char * key );
            void RemoveValue( const String & key );
            void ReplaceValue( CFTypeRef key, CFTypeRef value );
            void ReplaceValue( const char * key, CFTypeRef value );
            void ReplaceValue( const String & key, CFTypeRef value );
            void SetValue( CFTypeRef key, CFTypeRef value );
            void SetValue( const char * key, CFTypeRef value );
            void SetValue( const String & key, CFTypeRef value );
            
            /*
             * To avoid implicit conversion from const char * to CFTypeRef - const void *
             */
            void AddValue( CFTypeRef key, const char * value );
            void AddValue( const char * key, const char * value );
            void AddValue( const String & key, const char * value );
            void ReplaceValue( CFTypeRef key, const char * value );
            void ReplaceValue( const char * key, const char * value );
            void ReplaceValue( const String & key, const char * value );
            void SetValue( CFTypeRef key, const char * value );
            void SetValue( const char * key, const char * value );
            void SetValue( const String & key, const char * value );
            
            friend void swap( Dictionary & v1, Dictionary & v2 ) noexcept;
            
            #if __cplusplus >= 201703L
            class CFPP_EXPORT Iterator
            #else
            class CFPP_EXPORT Iterator: public std::iterator< std::bidirectional_iterator_tag, CF::Pair >
            #endif
            {
                public:
                
                    #if __cplusplus >= 201703L
                    using iterator_category = std::bidirectional_iterator_tag;
                    using value_type        = CF::Pair;
                    using difference_type   = ptrdiff_t;
                    using pointer           = CF::Pair *;
                    using reference         = CF::Pair &;
                    #endif
                    
                    Iterator();
                    Iterator( const Iterator & value );
                    Iterator( Iterator && value ) noexcept;
                    
                    virtual ~Iterator();
                    
                    Iterator & operator = ( Iterator value );
                    Iterator & operator ++();
                    Iterator   operator ++( int );
                    Iterator & operator --();
                    Iterator   operator --( int );
                    
                    Iterator & operator += ( CFIndex value );
                    Iterator & operator -= ( CFIndex value );
                    
                    Iterator operator + ( CFIndex value );
                    Iterator operator - ( CFIndex value );
                    
                    bool operator == ( const Iterator & value ) const;
                    bool operator != ( const Iterator & value ) const;
                    
                    CF::Pair operator * () const;
                    
                    CFTypeRef GetKey()   const;
                    CFTypeRef GetValue() const;
                    
                    friend void swap( Iterator & v1, Iterator & v2 ) noexcept;
                    
                private:
                    
                    friend class Dictionary;
                    
                    Iterator( CFDictionaryRef dictionary, CFIndex count, CFIndex pos = 0 );
                    
                    CFDictionaryRef _cfObject;
                    CF::Array       _keys;
                    CFIndex         _count;
                    CFIndex         _pos;
            };
            
            Iterator begin() const;
            Iterator end()   const;
            
        private:
            
            CFMutableDictionaryRef _cfObject;
    };
}

#endif /* CFPP_DICTIONARY_HPP */
