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
 * @file        CFPP-Type.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ base abstract class for CF wrappers
 */

#include <CF++.hpp>

namespace CF
{
    Type::~Type()
    {}
    
    bool Type::operator == ( const Type & value ) const
    {
        if( this->GetCFObject() == nullptr )
        {
            return false;
        }
        
        if( value.GetCFObject() == nullptr )
        {
            return false;
        }
        
        return ( CFEqual( this->GetCFObject(), value.GetCFObject() ) ) ? true : false;
    }
    
    bool Type::operator != ( const Type & value ) const
    {
        return !( *( this ) == value );
    }
            
    Type::operator CFTypeRef () const
    {
        return this->GetCFObject();
    }
    
    Type::operator CFBooleanRef () const
    {
        return ( this->IsBoolean() ) ? static_cast< CFBooleanRef >( this->GetCFObject() ) : nullptr;
    }
    
    Type::operator CFNumberRef () const
    {
        return ( this->IsNumber() ) ? static_cast< CFNumberRef >( this->GetCFObject() ) : nullptr;
    }
    
    Type::operator CFDateRef () const
    {
        return ( this->IsDate() ) ? static_cast< CFDateRef >( this->GetCFObject() ) : nullptr;
    }
    
    Type::operator CFStringRef () const
    {
        return ( this->IsString() ) ? static_cast< CFStringRef >( this->GetCFObject() ) : nullptr;
    }
    
    Type::operator CFMutableStringRef () const
    {
        return ( this->IsString() ) ? static_cast< CFMutableStringRef >( const_cast< void * >( this->GetCFObject() ) ) : nullptr;
    }
    
    Type::operator CFURLRef () const
    {
        return ( this->IsURL() ) ? static_cast< CFURLRef >( this->GetCFObject() ) : nullptr;
    }
    
    Type::operator CFDataRef () const
    {
        return ( this->IsData() ) ? static_cast< CFDataRef >( this->GetCFObject() ) : nullptr;
    }
    
    Type::operator CFMutableDataRef () const
    {
        return ( this->IsData() ) ? static_cast< CFMutableDataRef >( const_cast< void * >( this->GetCFObject() ) ) : nullptr;
    }
    
    Type::operator CFArrayRef () const
    {
        return ( this->IsArray() ) ? static_cast< CFArrayRef >( this->GetCFObject() ) : nullptr;
    }
    
    Type::operator CFMutableArrayRef () const
    {
        return ( this->IsArray() ) ? static_cast< CFMutableArrayRef >( const_cast< void * >( this->GetCFObject() ) ) : nullptr;
    }
    
    Type::operator CFDictionaryRef () const
    {
        return ( this->IsDictionary() ) ? static_cast< CFDictionaryRef >( this->GetCFObject() ) : nullptr;
    }
    
    Type::operator CFMutableDictionaryRef () const
    {
        return ( this->IsDictionary() ) ? static_cast< CFMutableDictionaryRef >( const_cast< void * >( this->GetCFObject() ) ) : nullptr;
    }
    
    Type::operator CFUUIDRef () const
    {
        return ( this->IsUUID() ) ? static_cast< CFUUIDRef >( this->GetCFObject() ) : nullptr;
    }
    
    Type::operator CFErrorRef () const
    {
        return ( this->IsError() ) ? static_cast< CFErrorRef >( const_cast< void * >( this->GetCFObject() ) ) : nullptr;
    }
    
    Type::operator CFReadStreamRef () const
    {
        return ( this->IsReadStream() ) ? static_cast< CFReadStreamRef >( const_cast< void * >( this->GetCFObject() ) ) : nullptr;
    }
    
    Type::operator CFWriteStreamRef () const
    {
        return ( this->IsWriteStream() ) ? static_cast< CFWriteStreamRef >( const_cast< void * >( this->GetCFObject() ) ) : nullptr;
    }
    
    std::string Type::Description() const
    {
        CFStringRef  cfDescription;
        std::string  description;
        char       * cStr;
        size_t       length;
        
        if( this->GetCFObject() == nullptr )
        {
            return "(null)";
        }
        
        cfDescription = CFCopyDescription( this->GetCFObject() );
        
        if( cfDescription == nullptr )
        {
            return "(null)";
        }
        
        length = static_cast< size_t >( CFStringGetMaximumSizeForEncoding( CFStringGetLength( cfDescription ), CFStringGetSystemEncoding() ) );
        cStr   = new char [ length + 1 ];
        
        if( cStr == nullptr )
        {
            CFRelease( cfDescription );
            
            return "(null)";
        }
        
        memset( cStr, 0, length + 1 );
        CFStringGetCString( cfDescription, cStr, static_cast< CFIndex >( length + 1 ), CFStringGetSystemEncoding() );
        
        description = std::string( cStr );
        
        delete [] cStr;
        
        CFRelease( cfDescription );
        
        return description;
    }
    
    CFHashCode Type::Hash() const
    {
        if( this->GetCFObject() == nullptr )
        {
            return static_cast< CFHashCode >( 0 );
        }
        
        return CFHash( this->GetCFObject() );
    }
    
    CFIndex Type::GetRetainCount() const
    {
        if( this->GetCFObject() == nullptr )
        {
            return 0;
        }
        
        return CFGetRetainCount( this->GetCFObject() );
    }
    
    bool Type::IsValid() const
    {
        return ( this->GetCFObject() != nullptr ) ? true : false;
    }
    
    bool Type::IsValidPropertyList( PropertyListFormat format ) const
    {
        CFPropertyListFormat cfFormat;
        
        cfFormat = kCFPropertyListXMLFormat_v1_0;
        
        if( format == PropertyListFormatBinary )
        {
            cfFormat = kCFPropertyListBinaryFormat_v1_0;
        }
        
        return this->IsValid() && CFPropertyListIsValid( this->GetCFObject(), cfFormat );
    }
    
    bool Type::IsBoolean() const
    {
        return this->GetTypeID() == CFBooleanGetTypeID();
    }
    
    bool Type::IsNumber() const
    {
        return this->GetTypeID() == CFNumberGetTypeID();
    }
    
    bool Type::IsDate() const
    {
        return this->GetTypeID() == CFDateGetTypeID();
    }
    
    bool Type::IsString() const
    {
        return this->GetTypeID() == CFStringGetTypeID();
    }
    
    bool Type::IsURL() const
    {
        return this->GetTypeID() == CFURLGetTypeID();
    }
    
    bool Type::IsData() const
    {
        return this->GetTypeID() == CFDataGetTypeID();
    }
    
    bool Type::IsArray() const
    {
        return this->GetTypeID() == CFArrayGetTypeID();
    }
    
    bool Type::IsDictionary() const
    {
        return this->GetTypeID() == CFDictionaryGetTypeID();
    }
    
    bool Type::IsUUID() const
    {
        return this->GetTypeID() == CFUUIDGetTypeID();
    }
    
    bool Type::IsError() const
    {
        return this->GetTypeID() == CFErrorGetTypeID();
    }
    
    bool Type::IsReadStream() const
    {
        return this->GetTypeID() == CFReadStreamGetTypeID();
    }
    
    bool Type::IsWriteStream() const
    {
        return this->GetTypeID() == CFWriteStreamGetTypeID();
    }
    
    void Type::Show() const
    {
        std::string className;
        
        className = "CF::Type";
        
        if( this->IsBoolean() )
        {
            className = "CF::Boolean";
        }
        else if( this->IsNumber() )
        {
            className = "CF::Number";
        }
        else if( this->IsDate() )
        {
            className = "CF::Date";
        }
        else if( this->IsString() )
        {
            className = "CF::String";
        }
        else if( this->IsURL() )
        {
            className = "CF::URL";
        }
        else if( this->IsData() )
        {
            className = "CF::Data";
        }
        else if( this->IsArray() )
        {
            className = "CF::Array";
        }
        else if( this->IsDictionary() )
        {
            className = "CF::Dictionary";
        }
        else if( this->IsUUID() )
        {
            className = "CF::UUID";
        }
        else if( this->IsError() )
        {
            className = "CF::Error";
        }
        else if( this->IsReadStream() )
        {
            className = "CF::ReadStream";
        }
        else if( this->IsWriteStream() )
        {
            className = "CF::WriteStream";
        }
        
        std::cout << className << " - " << this->Description() << std::endl;
    }
    
    std::ostream & operator << ( std::ostream & os, const Type & obj )
    {
        os << obj.Description();
        
        return os;
    }
}
