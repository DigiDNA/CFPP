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
 * @header      CFPP-Type.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ base abstract class for CF wrappers
 */

#ifndef CFPP_TYPE_HPP
#define CFPP_TYPE_HPP

namespace CF
{
    typedef enum
    {
        PropertyListFormatXML       = 0x00,
        PropertyListFormatBinary    = 0x01
    }
    PropertyListFormat;
    
    class CFPP_EXPORT Type
    {
        public:
            
            virtual ~Type();
            
            virtual CFTypeID  GetTypeID() const = 0;
            virtual CFTypeRef GetCFObject() const = 0;
            
            bool operator == ( const Type & value ) const;
            bool operator != ( const Type & value ) const;
            
            operator CFTypeRef              () const;
            operator CFBooleanRef           () const;
            operator CFNumberRef            () const;
            operator CFDateRef              () const;
            operator CFStringRef            () const;
            operator CFMutableStringRef     () const;
            operator CFURLRef               () const;
            operator CFDataRef              () const;
            operator CFMutableDataRef       () const;
            operator CFArrayRef             () const;
            operator CFMutableArrayRef      () const;
            operator CFDictionaryRef        () const;
            operator CFMutableDictionaryRef () const;
            operator CFUUIDRef              () const;
            operator CFErrorRef             () const;
            operator CFReadStreamRef        () const;
            operator CFWriteStreamRef       () const;
            
            std::string Description()    const;
            CFHashCode  Hash()           const;
            void        Show()           const;
            CFIndex     GetRetainCount() const;
            
            bool IsValid()                                        const;
            bool IsValidPropertyList( PropertyListFormat format ) const;
            
            bool IsBoolean()     const;
            bool IsNumber()      const;
            bool IsDate()        const;
            bool IsString()      const;
            bool IsURL()         const;
            bool IsData()        const;
            bool IsArray()       const;
            bool IsDictionary()  const;
            bool IsUUID()        const;
            bool IsError()       const;
            bool IsReadStream()  const;
            bool IsWriteStream() const;
            
            friend std::ostream & operator << ( std::ostream & os, const Type & obj );
    };
}

#endif /* CFPP_TYPE_HPP */
