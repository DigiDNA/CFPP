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
 * @file        CFPP-ReadStream.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFReadStreamRef wrapper
 */

#include <CF++.hpp>

namespace CF
{
    ReadStream::ReadStream(): _cfObject( nullptr )
    {}
    
    ReadStream::ReadStream( URL url ): _cfObject( nullptr )
    {
        this->_cfObject = CFReadStreamCreateWithFile( static_cast< CFAllocatorRef >( nullptr ), url );
    }
    
    ReadStream::ReadStream( const  std::string & path ): _cfObject( nullptr )
    {
        URL url;
        
        url = URL::FileSystemURL( path );
        
        this->_cfObject = CFReadStreamCreateWithFile( static_cast< CFAllocatorRef >( nullptr ), url );
    }
    
    ReadStream::ReadStream( const char * path ): _cfObject( nullptr )
    {
        URL url;
        
        url = URL::FileSystemURL( path );
        
        this->_cfObject = CFReadStreamCreateWithFile( static_cast< CFAllocatorRef >( nullptr ), url );
    }
    
    ReadStream::ReadStream( const ReadStream & value ): _cfObject( nullptr )
    {
        if( value._cfObject != nullptr )
        {
            this->_cfObject = static_cast< CFReadStreamRef >( const_cast< void * >( CFRetain( value._cfObject ) ) );
        }
    }
    
    ReadStream::ReadStream( const AutoPointer & value ): _cfObject( nullptr )
    {
        if( value.IsValid() && value.GetTypeID() == this->GetTypeID() )
        {
            this->_cfObject = static_cast< CFReadStreamRef >( const_cast< void * >( CFRetain( value ) ) );
        }
    }
    
    ReadStream::ReadStream( CFTypeRef value ): _cfObject( nullptr )
    {
        if( value != nullptr && CFGetTypeID( value ) == this->GetTypeID() )
        {
            this->_cfObject = static_cast< CFReadStreamRef >( const_cast< void * >( CFRetain( value ) ) );
        }
    }
    
    ReadStream::ReadStream( CFReadStreamRef value ): _cfObject( nullptr )
    {
        if( value != nullptr && CFGetTypeID( value ) == this->GetTypeID() )
        {
            this->_cfObject = static_cast< CFReadStreamRef >( const_cast< void * >( CFRetain( value ) ) );
        }
    }
    
    ReadStream::ReadStream( std::nullptr_t ): ReadStream( static_cast< CFTypeRef >( nullptr ) )
    {}
    
    ReadStream::ReadStream( ReadStream && value ) noexcept
    {
        this->_cfObject = value._cfObject;
        value._cfObject = nullptr;
    }
    
    ReadStream::~ReadStream()
    {
        if( this->_cfObject != nullptr )
        {
            CFRelease( this->_cfObject );
            
            this->_cfObject = nullptr;
        }
    }
    
    ReadStream & ReadStream::operator =( ReadStream value )
    {
        swap( *( this ), value );
        
        return *( this );
    }
    
    ReadStream & ReadStream::operator =( const AutoPointer & value )
    {
        return operator =( ReadStream( value ) );
    }
    
    ReadStream & ReadStream::operator =( CFTypeRef value )
    {
        return operator =( ReadStream( value ) );
    }
    
    ReadStream & ReadStream::operator =( CFReadStreamRef value )
    {
        return operator =( ReadStream( value ) );
    }
    
    ReadStream & ReadStream::operator =( std::nullptr_t )
    {
        return operator =( ReadStream( nullptr ) );
    }
    
    CFTypeID ReadStream::GetTypeID() const
    {
        return CFReadStreamGetTypeID();
    }
    
    CFTypeRef ReadStream::GetCFObject() const
    {
        return this->_cfObject;
    }
    
    bool ReadStream::Open()
    {
        if( this->_cfObject == nullptr )
        {
            return false;
        }
        
        return ( CFReadStreamOpen( this->_cfObject ) ) ? true : false;
    }
    
    bool ReadStream::Open( const std::string & path )
    {
        return this->Open( URL::FileSystemURL( path ) );
    }
    
    bool ReadStream::Open( const char * path )
    {
        return this->Open( URL::FileSystemURL( path ) );
    }
    
    bool ReadStream::Open( const URL & url )
    {
        if( this->_cfObject != nullptr )
        {
            this->Close();
            
            CFRelease( this->_cfObject );
        }
        
        this->_cfObject = CFReadStreamCreateWithFile( static_cast< CFAllocatorRef >( nullptr ), url );
        
        return this->Open();
    }
    
    void ReadStream::Close()
    {
        if( this->_cfObject == nullptr )
        {
            return;
        }
        
        CFReadStreamClose( this->_cfObject );
    }
    
    bool ReadStream::HasBytesAvailable() const
    {
        if( this->_cfObject == nullptr )
        {
            return false;
        }
        
        return ( CFReadStreamHasBytesAvailable( this->_cfObject ) ) ? true : false;
    }
    
    CFStreamStatus ReadStream::GetStatus() const
    {
        if( this->_cfObject == nullptr )
        {
            return kCFStreamStatusError;
        }
        
        return CFReadStreamGetStatus( this->_cfObject );
    }
    
    Error ReadStream::GetError() const
    {
        AutoPointer e;
        
        if( this->_cfObject == nullptr )
        {
            return e.As< CFErrorRef >();
        }
        
        e = CFReadStreamCopyError( this->_cfObject );
        
        return e.As< CFErrorRef >();
    }
        
    CFIndex ReadStream::Read( Data::Byte * buffer, CFIndex length )
    {
        if( this->_cfObject == nullptr )
        {
            return -1;
        }
        
        if( buffer == nullptr || length <= 0 )
        {
            return -1;
        }
        
        return CFReadStreamRead( this->_cfObject, buffer, length );
    }
    
    Data ReadStream::Read( CFIndex length )
    {
        Data                          data;
        std::shared_ptr< Data::Byte > bytes;
        CFIndex                       read;
        
        if( this->_cfObject == nullptr )
        {
            return data;
        }
        
        if( length > 0 )
        {
            bytes = std::shared_ptr< Data::Byte >( new Data::Byte[ static_cast< size_t >( length ) ], std::default_delete< Data::Byte[] >() );
            
            do
            {
                read    = this->Read( bytes.get(), length );
                length -= read;
                
                if( read == -1 || length < 0 )
                {
                    return {};
                }
                else if( read > 0 )
                {
                    data.AppendBytes( bytes.get(), read );
                }
            }
            while( length > 0 );
        }
        else
        {
            bytes = std::shared_ptr< Data::Byte >( new Data::Byte[ 4096 ], std::default_delete< Data::Byte[] >() );
            
            do
            {
                read = this->Read( bytes.get(), 4096 );
                
                if( read == -1 )
                {
                    return {};
                }
                else if( read > 0 )
                {
                    data.AppendBytes( bytes.get(), read );
                }
            }
            while( read > 0 );
        }
        
        return data;
    }
    
    const Data::Byte * ReadStream::GetBuffer( CFIndex maxBytesToRead, CFIndex * numBytesRead )
    {
        if( this->_cfObject == nullptr )
        {
            return nullptr;
        }
        
        return CFReadStreamGetBuffer( this->_cfObject, maxBytesToRead, numBytesRead );
    }
    
    AutoPointer ReadStream::GetProperty( const String & name ) const
    {
        if( this->_cfObject == nullptr )
        {
            return nullptr;
        }
        
        return CFReadStreamCopyProperty( this->_cfObject, name );
    }
    
    bool ReadStream::SetProperty( const String & name, CFTypeRef value )
    {
        if( this->_cfObject == nullptr )
        {
            return false;
        }
        
        return ( CFReadStreamSetProperty( this->_cfObject, name, value ) ) ? true : false;
    }
    
    bool ReadStream::SetClient( CFOptionFlags events, CFReadStreamClientCallBack callback, CFStreamClientContext * context )
    {
        if( this->_cfObject == nullptr )
        {
            return false;
        }
        
        return ( CFReadStreamSetClient( this->_cfObject, events, callback, context ) ) ? true : false;
    }
    
    void ReadStream::ScheduleWithRunLoop( CFRunLoopRef runLoop, CF::String mode )
    {
        if( this->_cfObject == nullptr )
        {
            return;
        }
        
        CFReadStreamScheduleWithRunLoop( this->_cfObject, runLoop, mode );
    }
    
    void ReadStream::UnscheduleFromRunLoop( CFRunLoopRef runLoop, CF::String mode )
    {
        if( this->_cfObject == nullptr )
        {
            return;
        }
        
        CFReadStreamUnscheduleFromRunLoop( this->_cfObject, runLoop, mode );
    }
    
    ReadStream::Iterator ReadStream::begin( CFIndex bytesToRead ) const
    {
        return Iterator( this->_cfObject, bytesToRead, false );
    }
    
    ReadStream::Iterator ReadStream::end() const
    {
        return Iterator( this->_cfObject, 0, true );
    }
    
    void swap( ReadStream & v1, ReadStream & v2 ) noexcept
    {
        using std::swap;
        
        swap( v1._cfObject, v2._cfObject );
    }
}
