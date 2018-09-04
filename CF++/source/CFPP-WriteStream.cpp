/*******************************************************************************
 * Copyright (c) 2014, Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * Distributed under the Boost Software License, Version 1.0.
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************/

/*!
 * @file        CFPP-WriteStream.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFWriteStreamRef wrapper
 */

#include <CF++.hpp>

namespace CF
{
    WriteStream::WriteStream( void ): _cfObject( NULL )
    {}
    
    WriteStream::WriteStream( URL url ): _cfObject( NULL )
    {
        this->_cfObject = CFWriteStreamCreateWithFile( static_cast< CFAllocatorRef >( NULL ), url );
    }
    
    WriteStream::WriteStream( const std::string & path ): _cfObject( NULL )
    {
        URL url;
        
        url = URL::FileSystemURL( path );
        
        this->_cfObject = CFWriteStreamCreateWithFile( static_cast< CFAllocatorRef >( NULL ), url );
    }
    
    WriteStream::WriteStream( const char * path ): _cfObject( NULL )
    {
        URL url;
        
        url = URL::FileSystemURL( path );
        
        this->_cfObject = CFWriteStreamCreateWithFile( static_cast< CFAllocatorRef >( NULL ), url );
    }
    
    WriteStream::WriteStream( const WriteStream & value ): _cfObject( NULL )
    {
        if( value._cfObject != NULL )
        {
            this->_cfObject = static_cast< CFWriteStreamRef >( const_cast< void * >( CFRetain( value._cfObject ) ) );
        }
    }
    
    WriteStream::WriteStream( const AutoPointer & value ): _cfObject( NULL )
    {
        if( value.IsValid() && value.GetTypeID() == this->GetTypeID() )
        {
            this->_cfObject = static_cast< CFWriteStreamRef >( const_cast< void * >( CFRetain( value ) ) );
        }
    }
    
    WriteStream::WriteStream( CFTypeRef value ): _cfObject( NULL )
    {
        if( value != NULL && CFGetTypeID( value ) == this->GetTypeID() )
        {
            this->_cfObject = static_cast< CFWriteStreamRef >( const_cast< void * >( CFRetain( value ) ) );
        }
    }
    
    WriteStream::WriteStream( CFWriteStreamRef value ): _cfObject( NULL )
    {
        if( value != NULL && CFGetTypeID( value ) == this->GetTypeID() )
        {
            this->_cfObject = static_cast< CFWriteStreamRef >( const_cast< void * >( CFRetain( value ) ) );
        }
    }
    
    #ifdef CFPP_HAS_CPP11
    WriteStream::WriteStream( WriteStream && value ) noexcept
    {
        this->_cfObject = value._cfObject;
        value._cfObject = nullptr;
    }
    #endif
    
    WriteStream::~WriteStream( void )
    {
        if( this->_cfObject != NULL )
        {
            CFRelease( this->_cfObject );
            
            this->_cfObject = NULL;
        }
    }
    
    WriteStream & WriteStream::operator = ( WriteStream value )
    {
        swap( *( this ), value );
        
        return *( this );
    }
    
    WriteStream & WriteStream::operator = ( const AutoPointer & value )
    {
        return operator =( WriteStream( value ) );
    }
    
    WriteStream & WriteStream::operator = ( CFTypeRef value )
    {
        return operator =( WriteStream( value ) );
    }
    
    WriteStream & WriteStream::operator = ( CFWriteStreamRef value )
    {
        return operator =( WriteStream( value ) );
    }
    
    CFTypeID WriteStream::GetTypeID( void ) const
    {
        return CFWriteStreamGetTypeID();
    }
    
    CFTypeRef WriteStream::GetCFObject( void ) const
    {
        return this->_cfObject;
    }
    
    bool WriteStream::Open( void ) const
    {
        if( this->_cfObject == NULL )
        {
            return false;
        }
        
        return ( CFWriteStreamOpen( this->_cfObject ) ) ? true : false;
    }
    
    bool WriteStream::Open( const std::string & path )
    {
        return this->Open( URL::FileSystemURL( path ) );
    }
    
    bool WriteStream::Open( const char * path )
    {
        return this->Open( URL::FileSystemURL( path ) );
    }
    
    bool WriteStream::Open( const URL & url )
    {
        if( this->_cfObject != NULL )
        {
            this->Close();
            
            CFRelease( this->_cfObject );
        }
        
        this->_cfObject = CFWriteStreamCreateWithFile( static_cast< CFAllocatorRef >( NULL ), url );
        
        return this->Open();
    }
    
    void WriteStream::Close( void ) const
    {
        if( this->_cfObject == NULL )
        {
            return;
        }
        
        CFWriteStreamClose( this->_cfObject );
    }
    
    bool WriteStream::CanAcceptBytes( void ) const
    {
        if( this->_cfObject == NULL )
        {
            return false;
        }
        
        return ( CFWriteStreamCanAcceptBytes( this->_cfObject ) ) ? true : false;
    }
    
    CFStreamStatus WriteStream::GetStatus( void ) const
    {
        if( this->_cfObject == NULL )
        {
            return kCFStreamStatusError;
        }
        
        return CFWriteStreamGetStatus( this->_cfObject );
    }
    
    Error WriteStream::GetError( void ) const
    {
        AutoPointer e;
        
        if( this->_cfObject == NULL )
        {
            return e.As< CFErrorRef >();
        }
        
        e = CFWriteStreamCopyError( this->_cfObject );
        
        return e.As< CFErrorRef >();
    }
    
    CFIndex WriteStream::Write( const Data::Byte * buffer, CFIndex length ) const
    {
        if( this->_cfObject == NULL )
        {
            return -1;
        }
        
        if( buffer == NULL || length <= 0 )
        {
            return -1;
        }
        
        return CFWriteStreamWrite( this->_cfObject, buffer, length );
    }
    
    CFIndex WriteStream::Write( const Data & data ) const
    {
        return this->Write( data.GetBytePtr(), data.GetLength() );
    }
    
    bool WriteStream::WriteAll( const Data::Byte * buffer, CFIndex length ) const
    {
        CFIndex written;
        
        if( this->_cfObject == NULL )
        {
            return false;
        }
        
        if( buffer == NULL || length <= 0 )
        {
            return false;
        }
        
        while( 1 )
        {
            written = CFWriteStreamWrite( this->_cfObject, buffer, length );
            
            if( written < 0 )
            {
                return false;
            }
            else if( written == 0 )
            {
                return this->GetStatus() == kCFStreamStatusAtEnd;
            }
            else if( written == length )
            {
                return true;
            }
            
            length -= written;
            buffer += written;
            
            if( length < 0 )
            {
                return false;
            }
        }
    }
    
    bool WriteStream::WriteAll( const Data & data ) const
    {
        return this->WriteAll( data.GetBytePtr(), data.GetLength() );
    }
    
    AutoPointer WriteStream::GetProperty( const String & name )
    {
        if( this->_cfObject == NULL )
        {
            return NULL;
        }
        
        return CFWriteStreamCopyProperty( this->_cfObject, name );
    }
    
    bool WriteStream::SetProperty( const String & name, CFTypeRef value )
    {
        if( this->_cfObject == NULL )
        {
            return false;
        }
        
        return ( CFWriteStreamSetProperty( this->_cfObject, name, value ) ) ? true : false;
    }
    
    bool WriteStream::SetClient( CFOptionFlags events, CFWriteStreamClientCallBack callback, CFStreamClientContext * context )
    {
        if( this->_cfObject == NULL )
        {
            return false;
        }
        
        return ( CFWriteStreamSetClient( this->_cfObject, events, callback, context ) ) ? true : false;
    }
    
    void WriteStream::ScheduleWithRunLoop( CFRunLoopRef runLoop, CF::String mode )
    {
        if( this->_cfObject == NULL )
        {
            return;
        }
        
        CFWriteStreamScheduleWithRunLoop( this->_cfObject, runLoop, mode );
    }
    
    void WriteStream::UnscheduleFromRunLoop( CFRunLoopRef runLoop, CF::String mode )
    {
        if( this->_cfObject == NULL )
        {
            return;
        }
        
        CFWriteStreamUnscheduleFromRunLoop( this->_cfObject, runLoop, mode );
    }
    
    void swap( WriteStream & v1, WriteStream & v2 ) noexcept
    {
        using std::swap;
        
        swap( v1._cfObject, v2._cfObject );
    }
}
