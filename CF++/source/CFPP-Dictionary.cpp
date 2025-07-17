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
 * @file        CFPP-Dictionary.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFDictionaryRef wrapper
 */

#include <CF++.hpp>

static bool __hasCallBacks = false;

static CFDictionaryKeyCallBacks   __keyCallbacks;
static CFDictionaryValueCallBacks __valueCallbacks;

#ifdef _WIN32

static const void *	__CFDictionaryRetainCallBack( CFAllocatorRef allocator, const void * value );
static const void *	__CFDictionaryRetainCallBack( CFAllocatorRef allocator, const void * value )
{
    ( void )allocator;
    
    if( value != nullptr )
    {
        value = CFRetain( value );
    }
    
    return value;
}

static void __CFDictionaryReleaseCallBack( CFAllocatorRef allocator, const void * value );
static void __CFDictionaryReleaseCallBack( CFAllocatorRef allocator, const void * value )
{
    ( void )allocator;
    
    if( value != nullptr )
    {
        CFRelease( value );
    }
}

static CFStringRef __CFDictionaryCopyDescriptionCallBack( const void * value );
static CFStringRef __CFDictionaryCopyDescriptionCallBack( const void * value )
{
    if( value == nullptr )
    {
        return CFStringCreateWithCString( ( CFAllocatorRef )nullptr, "(null)", kCFStringEncodingUTF8 );
    }
    
    return CFCopyDescription( value );
}

static Boolean __CFDictionaryEqualCallBack( const void * value1, const void * value2 );
static Boolean __CFDictionaryEqualCallBack( const void * value1, const void * value2 )
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

static CFHashCode __CFDictionaryHashCallBack( const void * value );
static CFHashCode __CFDictionaryHashCallBack( const void * value )
{
    if( value == nullptr )
    {
        return 0;
    }
    
    return CFHash( value );
}

static void __createCallbacks( void )
{
    if( __hasCallBacks == true  )
    {
        return;
    }
    
    __hasCallBacks = true;
    
    __keyCallbacks.version         = 0;
    __keyCallbacks.retain          = __CFDictionaryRetainCallBack;
    __keyCallbacks.release         = __CFDictionaryReleaseCallBack;
    __keyCallbacks.copyDescription = __CFDictionaryCopyDescriptionCallBack;
    __keyCallbacks.equal           = __CFDictionaryEqualCallBack;
    __keyCallbacks.hash            = __CFDictionaryHashCallBack;
    
    __valueCallbacks.version         = 0;
    __valueCallbacks.retain          = __CFDictionaryRetainCallBack;
    __valueCallbacks.release         = __CFDictionaryReleaseCallBack;
    __valueCallbacks.copyDescription = __CFDictionaryCopyDescriptionCallBack;
    __valueCallbacks.equal           = __CFDictionaryEqualCallBack;
}

#else

static void __createCallbacks( void )
{
    if( __hasCallBacks == true  )
    {
        return;
    }
    
    __hasCallBacks      = true;
    __keyCallbacks      = kCFTypeDictionaryKeyCallBacks;
    __valueCallbacks    = kCFTypeDictionaryValueCallBacks;
}

#endif

namespace CF
{
    Dictionary::Dictionary( void ): _cfObject( nullptr )
    {
        __createCallbacks();
        
        this->_cfObject = CFDictionaryCreateMutable
        (
            static_cast< CFAllocatorRef >( nullptr ),
            0,
            &__keyCallbacks,
            &__valueCallbacks
        );
    }
    
    Dictionary::Dictionary( CFIndex capacity ): _cfObject( nullptr )
    {
        __createCallbacks();
        
        this->_cfObject = CFDictionaryCreateMutable
        (
            static_cast< CFAllocatorRef >( nullptr ),
            capacity,
            &__keyCallbacks,
            &__valueCallbacks
        );
    }
    
    Dictionary::Dictionary( const Dictionary & value ): _cfObject( nullptr )
    {
        __createCallbacks();
        
        if( value._cfObject != nullptr )
        {
            this->_cfObject = CFDictionaryCreateMutableCopy
            (
                static_cast< CFAllocatorRef >( nullptr ),
                CFDictionaryGetCount( value._cfObject ),
                value._cfObject
            );
        }
    }
    
    Dictionary::Dictionary( const AutoPointer & value ): _cfObject( nullptr )
    {
        __createCallbacks();
        
        if( value.IsValid() && value.GetTypeID() == this->GetTypeID() )
        {
            this->_cfObject = CFDictionaryCreateMutableCopy
            (
                static_cast< CFAllocatorRef >( nullptr ),
                CFDictionaryGetCount( value ),
                value
            );
        }
    }
    
    Dictionary::Dictionary( CFTypeRef cfObject ): _cfObject( nullptr )
    {
        __createCallbacks();
        
        if( cfObject != nullptr && CFGetTypeID( cfObject ) == this->GetTypeID() )
        {
            this->_cfObject = CFDictionaryCreateMutableCopy
            (
                static_cast< CFAllocatorRef >( nullptr ),
                CFDictionaryGetCount( static_cast< CFDictionaryRef >( cfObject ) ),
                static_cast< CFDictionaryRef >( cfObject )
            );
        }
    }
    
    Dictionary::Dictionary( CFDictionaryRef cfObject ): _cfObject( nullptr )
    {
        __createCallbacks();
        
        if( cfObject != nullptr && CFGetTypeID( cfObject ) == this->GetTypeID() )
        {
            this->_cfObject = CFDictionaryCreateMutableCopy
            (
                static_cast< CFAllocatorRef >( nullptr ),
                CFDictionaryGetCount( cfObject ),
                cfObject
            );
        }
    }
    
    Dictionary::Dictionary( std::nullptr_t ): Dictionary( static_cast< CFTypeRef >( nullptr ) )
    {}
    
    Dictionary::Dictionary( std::initializer_list< Pair > value ): Dictionary( static_cast< CFIndex >( value.size() ) )
    {
        for( Pair p: value )
        {
            if( p.GetKey() == nullptr || p.GetValue() == nullptr )
            {
                continue;
            }
            
            CFDictionarySetValue( this->_cfObject, p.GetKey(), p.GetValue() );
        }
    }
    
    Dictionary::Dictionary( Dictionary && value ) noexcept
    {
        this->_cfObject = value._cfObject;
        value._cfObject = nullptr;
    }
    
    Dictionary::~Dictionary( void )
    {
        if( this->_cfObject != nullptr )
        {
            CFRelease( this->_cfObject );
            
            this->_cfObject = nullptr;
        }
    }
    
    Dictionary & Dictionary::operator = ( Dictionary value )
    {
        swap( *( this ), value );
        
        return *( this );
    }
    
    Dictionary & Dictionary::operator = ( const AutoPointer & value )
    {
        return operator =( Dictionary( value ) );
    }
    
    Dictionary & Dictionary::operator = ( CFTypeRef value )
    {
        return operator =( Dictionary( value ) );
    }
    
    Dictionary & Dictionary::operator = ( CFDictionaryRef value )
    {
        return operator =( Dictionary( value ) );
    }
    
    Dictionary & Dictionary::operator = ( std::nullptr_t )
    {
        return operator =( Dictionary( nullptr ) );
    }
    
    Dictionary & Dictionary::operator += ( const Pair & pair )
    {
        this->AddValue( pair.GetKey(), pair.GetValue() );
        
        return *( this );
    }
    
    Dictionary & Dictionary::operator << ( const Pair & pair )
    {
        this->SetValue( pair.GetKey(), pair.GetValue() );
        
        return *( this );
    }
    
    CFTypeRef Dictionary::operator [] ( CFTypeRef key ) const
    {
        return this->GetValue( key );
    }
    
    CFTypeRef Dictionary::operator [] ( const char * key ) const
    {
        return operator []( String( key ) );
    }
    
    CFTypeRef Dictionary::operator [] ( const String & key ) const
    {
        return this->GetValue( key );
    }
    
    CFTypeID Dictionary::GetTypeID( void ) const
    {
        return CFDictionaryGetTypeID();
    }
    
    CFTypeRef Dictionary::GetCFObject( void ) const
    {
        return this->_cfObject;
    }
    
    bool Dictionary::ContainsKey( CFTypeRef key ) const
    {
        if( this->_cfObject == nullptr || key == nullptr )
        {
            return false;
        }
        
        return ( CFDictionaryContainsKey( this->_cfObject, key ) ) ? true : false;
    }
    
    bool Dictionary::ContainsKey( const char * key ) const
    {
        return this->ContainsKey( String( key ) );
    }
    
    bool Dictionary::ContainsKey( const String & key ) const
    {
        return this->ContainsKey( key.GetCFObject() );
    }
    
    bool Dictionary::ContainsValue( CFTypeRef value ) const
    {
        if( this->_cfObject == nullptr || value == nullptr )
        {
            return false;
        }
        
        return ( CFDictionaryContainsValue( this->_cfObject, value ) ) ? true : false;
    }
    
    void Dictionary::RemoveAllValues( void ) const
    {
        if( this->_cfObject == nullptr )
        {
            return;
        }
        
        CFDictionaryRemoveAllValues( this->_cfObject );
    }
    
    CFIndex Dictionary::GetCount( void ) const
    {
        return ( this->_cfObject == nullptr ) ? 0 : CFDictionaryGetCount( this->_cfObject );
    }
    
    CFTypeRef Dictionary::GetValue( CFTypeRef key ) const
    {
        if( this->_cfObject == nullptr || key == nullptr )
        {
            return nullptr;
        }
        
        return CFDictionaryGetValue( this->_cfObject, key );
    }
    
    CFTypeRef Dictionary::GetValue( const char * key ) const
    {
        return this->GetValue( String( key ) );
    }
    
    CFTypeRef Dictionary::GetValue( const String & key ) const
    {
        return this->GetValue( key.GetCFObject() );
    }
    
    void Dictionary::AddValue( CFTypeRef key, CFTypeRef value ) const
    {
        if( this->_cfObject == nullptr || key == nullptr || value == nullptr )
        {
            return;
        }
        
        CFDictionaryAddValue( this->_cfObject, key, value );
    }
    
    void Dictionary::AddValue( const char * key, CFTypeRef value ) const
    {
        this->AddValue( String( key ), value );
    }
    
    void Dictionary::AddValue( const String & key, CFTypeRef value ) const
    {
        this->AddValue( key.GetCFObject(), value );
    }
    
    void Dictionary::RemoveValue( CFTypeRef key ) const
    {
        if( this->_cfObject == nullptr || key == nullptr )
        {
            return;
        }
        
        CFDictionaryRemoveValue( this->_cfObject, key );
    }
    
    void Dictionary::RemoveValue( const char * key ) const
    {
        this->RemoveValue( String( key ) );
    }
    
    void Dictionary::RemoveValue( const String & key ) const
    {
        this->RemoveValue( key.GetCFObject() );
    }
    
    void Dictionary::ReplaceValue( CFTypeRef key, CFTypeRef value ) const
    {
        if( this->_cfObject == nullptr || key == nullptr || value == nullptr )
        {
            return;
        }
        
        CFDictionaryReplaceValue( this->_cfObject, key, value );
    }
    
    void Dictionary::ReplaceValue( const char * key, CFTypeRef value ) const
    {
        this->ReplaceValue( String( key ), value );
    }
    
    void Dictionary::ReplaceValue( const String & key, CFTypeRef value ) const
    {
        this->ReplaceValue( key.GetCFObject(), value );
    }
    
    void Dictionary::SetValue( CFTypeRef key, CFTypeRef value ) const
    {
        if( this->_cfObject == nullptr || key == nullptr || value == nullptr )
        {
            return;
        }
        
        CFDictionarySetValue( this->_cfObject, key, value );
    }
    
    void Dictionary::SetValue( const char * key, CFTypeRef value ) const
    {
        this->SetValue( String( key ), value );
    }
    
    void Dictionary::SetValue( const String & key, CFTypeRef value ) const
    {
        this->SetValue( key.GetCFObject(), value );
    }
    
    void Dictionary::AddValue( CFTypeRef key, const char * value ) const
    {
        this->AddValue( key, String( value ) );
    }
    
    void Dictionary::AddValue( const char * key, const char * value ) const
    {
        this->AddValue( key, String( value ) );
    }
    
    void Dictionary::AddValue( const String & key, const char * value ) const
    {
        this->AddValue( key, String( value ) );
    }
    
    void Dictionary::ReplaceValue( CFTypeRef key, const char * value ) const
    {
        this->ReplaceValue( key, String( value ) );
    }
    
    void Dictionary::ReplaceValue( const char * key, const char * value ) const
    {
        this->ReplaceValue( key, String( value ) );
    }
    
    void Dictionary::ReplaceValue( const String & key, const char * value ) const
    {
        this->ReplaceValue( key, String( value ) );
    }
    
    void Dictionary::SetValue( CFTypeRef key, const char * value ) const
    {
        this->SetValue( key, String( value ) );
    }
    
    void Dictionary::SetValue( const char * key, const char * value ) const
    {
        this->SetValue( key, String( value ) );
    }
    
    void Dictionary::SetValue( const String & key, const char * value ) const
    {
        this->SetValue( key, String( value ) );
    }
    
    Dictionary::Iterator Dictionary::begin( void ) const
    {
        return Iterator( this->_cfObject, this->GetCount() );
    }
    
    Dictionary::Iterator Dictionary::end( void ) const
    {
        return Iterator( this->_cfObject, this->GetCount(), this->GetCount() );
    }
    
    void swap( Dictionary & v1, Dictionary & v2 ) noexcept
    {
        using std::swap;
        
        swap( v1._cfObject, v2._cfObject );
    }
}
