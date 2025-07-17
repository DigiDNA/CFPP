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
 * @file        CFPP-Array.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFArrayRef wrapper
 */

#include <CF++.hpp>

static bool __hasCallBacks = false;

static CFArrayCallBacks __callbacks;

#ifdef _WIN32

static const void *    __CFArrayRetainCallBack( CFAllocatorRef allocator, const void * value );
static const void *    __CFArrayRetainCallBack( CFAllocatorRef allocator, const void * value )
{
    ( void )allocator;
    
    if( value != nullptr )
    {
        value = CFRetain( value );
    }
    
    return value;
}

static void __CFArrayReleaseCallBack( CFAllocatorRef allocator, const void * value );
static void __CFArrayReleaseCallBack( CFAllocatorRef allocator, const void * value )
{
    ( void )allocator;
    
    if( value != nullptr )
    {
        CFRelease( value );
    }
}

static CFStringRef __CFArrayCopyDescriptionCallBack( const void * value );
static CFStringRef __CFArrayCopyDescriptionCallBack( const void * value )
{
    if( value == nullptr )
    {
        return CFStringCreateWithCString( ( CFAllocatorRef )nullptr, "(null)", kCFStringEncodingUTF8 );
    }
    
    return CFCopyDescription( value );
}

static Boolean __CFArrayEqualCallBack( const void * value1, const void * value2 );
static Boolean __CFArrayEqualCallBack( const void * value1, const void * value2 )
{
    if( value1 == value2 )
    {
        return true;
    }
    
    if( value1 == nullptr || value2 == nullptr )
    {
        return false;
    }
    
    return CFEqual( value1, value2 );
}

static void __createCallbacks()
{
    if( __hasCallBacks == true  )
    {
        return;
    }
    
    __hasCallBacks = true;
    
    __callbacks.version         = 0;
    __callbacks.retain          = __CFArrayRetainCallBack;
    __callbacks.release         = __CFArrayReleaseCallBack;
    __callbacks.copyDescription = __CFArrayCopyDescriptionCallBack;
    __callbacks.equal           = __CFArrayEqualCallBack;
}

#else

static void __createCallbacks()
{
    if( __hasCallBacks == true  )
    {
        return;
    }
    
    __hasCallBacks = true;
    __callbacks    = kCFTypeArrayCallBacks;
}

#endif

namespace CF
{
    Array::Array(): _cfObject( nullptr )
    {
        __createCallbacks();
        
        this->_cfObject = CFArrayCreateMutable
        (
            static_cast< CFAllocatorRef >( nullptr ),
            0,
            &__callbacks
        );
    }
    
    Array::Array( CFIndex capacity ): _cfObject( nullptr )
    {
        __createCallbacks();
        
        this->_cfObject = CFArrayCreateMutable
        (
            static_cast< CFAllocatorRef >( nullptr ),
            capacity,
            &__callbacks
        );
    }
    
    Array::Array( const Array & value ): _cfObject( nullptr )
    {
        __createCallbacks();
        
        if( value._cfObject != nullptr )
        {
            this->_cfObject = CFArrayCreateMutableCopy
            (
                static_cast< CFAllocatorRef >( nullptr ),
                CFArrayGetCount( value._cfObject ),
                value._cfObject
            );
        }
    }
    
    Array::Array( const AutoPointer & value ): _cfObject( nullptr )
    {
        __createCallbacks();
        
        if( value.IsValid() && value.GetTypeID() == this->GetTypeID() )
        {
            this->_cfObject = CFArrayCreateMutableCopy
            (
                static_cast< CFAllocatorRef >( nullptr ),
                CFArrayGetCount( value ),
                value
            );
        }
    }
    
    Array::Array( CFTypeRef value ): _cfObject( nullptr )
    {
        __createCallbacks();
        
        if( value != nullptr && CFGetTypeID( value ) == this->GetTypeID() )
        {
            this->_cfObject = CFArrayCreateMutableCopy
            (
                static_cast< CFAllocatorRef >( nullptr ),
                CFArrayGetCount( static_cast< CFArrayRef >( value ) ),
                static_cast< CFArrayRef >( value )
            );
        }
    }
    
    Array::Array( CFArrayRef value ): _cfObject( nullptr )
    {
        __createCallbacks();
        
        if( value != nullptr && CFGetTypeID( value ) == this->GetTypeID() )
        {
            this->_cfObject = CFArrayCreateMutableCopy
            (
                static_cast< CFAllocatorRef >( nullptr ),
                CFArrayGetCount( value ),
                value
            );
        }
    }
    
    Array::Array( std::nullptr_t ): Array( static_cast< CFTypeRef >( nullptr ) )
    {}
    
    Array::Array( std::initializer_list< CFTypeRef > value ): Array( static_cast< CFIndex >( value.size() ) )
    {
        for( CFTypeRef o: value )
        {
            if( o != nullptr )
            {
                CFArrayAppendValue( this->_cfObject, o );
            }
        }
    }
    
    Array::Array( Array && value ) noexcept
    {
        this->_cfObject = value._cfObject;
        value._cfObject = nullptr;
    }
    
    Array::~Array()
    {
        if( this->_cfObject != nullptr )
        {
            CFRelease( this->_cfObject );
            
            this->_cfObject = nullptr;
        }
    }
    
    Array & Array::operator = ( Array value )
    {
        swap( *( this ), value );
        
        return *( this );
    }
    
    Array & Array::operator = ( const AutoPointer & value )
    {
        return operator =( Array( value ) );
    }
    
    Array & Array::operator = ( CFTypeRef value )
    {
        return operator =( Array( value ) );
    }
    
    Array & Array::operator = ( CFArrayRef value )
    {
        return operator =( Array( value ) );
    }
    
    Array & Array::operator = ( std::nullptr_t )
    {
        return operator =( Array( nullptr ) );
    }
    
    Array & Array::operator += ( const Array & value )
    {
        this->AppendArray( value._cfObject );
        
        return *( this );
    }
    
    Array & Array::operator += ( CFTypeRef value )
    {
        return operator +=( Array( value ) );
    }
    
    Array & Array::operator += ( CFArrayRef value )
    {
        return operator +=( Array( value ) );
    }
    
    Array & Array::operator << ( CFTypeRef value )
    {
        this->AppendValue( value );
        
        return *( this );
    }
    
    Array & Array::operator << ( const char * value )
    {
        return operator <<( String( value ) );
    }
    
    Array & Array::operator << ( const String & value )
    {
        return operator <<( value.GetCFObject() );
    }
    
    Array & Array::operator << ( const Number & value )
    {
        return operator <<( value.GetCFObject() );
    }
            
    CFTypeRef Array::operator [] ( int index ) const
    {
        return this->GetValueAtIndex( static_cast< CFIndex >( index ) );
    }
    
    CFTypeID Array::GetTypeID() const
    {
        return CFArrayGetTypeID();
    }
    
    CFTypeRef Array::GetCFObject() const
    {
        return this->_cfObject;
    }
    
    CFIndex Array::GetCount() const
    {
        return ( this->_cfObject == nullptr ) ? 0 : CFArrayGetCount( this->_cfObject );
    }
    
    bool Array::ContainsValue( CFTypeRef value ) const
    {
        if( this->_cfObject == nullptr || value == nullptr )
        {
            return false;
        }
        
        return ( CFArrayContainsValue
        (
            this->_cfObject,
            CFRangeMake( 0, this->GetCount() ),
            value
        ) ) ? true : false;
    }
    
    void Array::RemoveAllValues() const
    {
        if( this->_cfObject != nullptr )
        {
            CFArrayRemoveAllValues( this->_cfObject );
        }
    }
    
    CFTypeRef Array::GetValueAtIndex( CFIndex index ) const
    {
        if( this->_cfObject == nullptr || index >= this->GetCount() )
        {
            return nullptr;
        }
        
        return CFArrayGetValueAtIndex( this->_cfObject, index );
    }
    
    void Array::SetValueAtIndex( CFTypeRef value, CFIndex index ) const
    {
        if( this->_cfObject == nullptr || index > this->GetCount() || value == nullptr )
        {
            return;
        }
        
        CFArraySetValueAtIndex( this->_cfObject, index, value );
    }
    
    void Array::InsertValueAtIndex( CFTypeRef value, CFIndex index ) const
    {
        if( this->_cfObject == nullptr || index > this->GetCount() || value == nullptr )
        {
            return;
        }
        
        CFArrayInsertValueAtIndex( this->_cfObject, index, value );
    }
    
    void Array::AppendValue( CFTypeRef value ) const
    {
        if( this->_cfObject == nullptr || value == nullptr )
        {
            return;
        }
        
        CFArrayAppendValue( this->_cfObject, value );
    }
    
    void Array::RemoveValueAtIndex( CFIndex index ) const
    {
        if( this->_cfObject == nullptr || index >= this->GetCount() )
        {
            return;
        }
        
        CFArrayRemoveValueAtIndex( this->_cfObject, index );
    }
    
    void Array::AppendArray( CFArrayRef array ) const
    {
        if( array == nullptr || CFGetTypeID( array ) != this->GetTypeID() )
        {
            return;
        }
        
        if( this->_cfObject != nullptr )
        {
            CFArrayAppendArray
            (
                this->_cfObject,
                array,
                CFRangeMake( 0, CFArrayGetCount( array ) )
            );
        }
    }
    
    void Array::ExchangeValuesAtIndices( CFIndex index1, CFIndex index2 ) const
    {
        if( this->_cfObject == nullptr || index1 >= this->GetCount() || index2 >= this->GetCount() )
        {
            return;
        }
        
        CFArrayExchangeValuesAtIndices( this->_cfObject, index1, index2 );
    }
    
    Array::Iterator Array::begin() const
    {
        return Iterator( this->_cfObject, this->GetCount() );
    }
    
    Array::Iterator Array::end() const
    {
        return Iterator( this->_cfObject, this->GetCount(), this->GetCount() );
    }
        
    void swap( Array & v1, Array & v2 ) noexcept
    {
        using std::swap;
        
        swap( v1._cfObject, v2._cfObject );
    }
}
