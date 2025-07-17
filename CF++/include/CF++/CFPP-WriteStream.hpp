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
 * @header      CFPP-WriteStream.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFWriteStreamRef wrapper
 */

#ifndef CFPP_WRITE_STREAM_HPP
#define CFPP_WRITE_STREAM_HPP

namespace CF
{
    class CFPP_EXPORT WriteStream: public Type
    {
        public:
            
            WriteStream();
            WriteStream( const std::string & path );
            WriteStream( const char * path );
            WriteStream( URL url );
            WriteStream( const WriteStream & value );
            WriteStream( const AutoPointer & value );
            WriteStream( CFTypeRef value );
            WriteStream( CFWriteStreamRef value );
            WriteStream( std::nullptr_t );
            WriteStream( WriteStream && value ) noexcept;
            
            ~WriteStream() override;
            
            WriteStream & operator = ( WriteStream value );
            WriteStream & operator = ( const AutoPointer & value );
            WriteStream & operator = ( CFTypeRef value );
            WriteStream & operator = ( CFWriteStreamRef value );
            WriteStream & operator = ( std::nullptr_t );
            
            CFTypeID  GetTypeID() const override;
            CFTypeRef GetCFObject() const override;
            
            bool Open();
            bool Open( const std::string & path );
            bool Open( const char * path );
            bool Open( const URL & url );
            void Close();
            
            bool           CanAcceptBytes() const;
            CFStreamStatus GetStatus() const;
            Error          GetError() const;
            AutoPointer    GetProperty( const String & name ) const;
            
            CFIndex Write( const Data::Byte * buffer, CFIndex length );
            CFIndex Write( const Data & data );
            bool    WriteAll( const Data::Byte * buffer, CFIndex length );
            bool    WriteAll( const Data & data );
            bool    SetProperty( const String & name, CFTypeRef value );
            bool    SetClient( CFOptionFlags events, CFWriteStreamClientCallBack callback, CFStreamClientContext * context );
            void    ScheduleWithRunLoop( CFRunLoopRef runLoop, CF::String mode );
            void    UnscheduleFromRunLoop( CFRunLoopRef runLoop, CF::String mode );
            
            friend void swap( WriteStream & v1, WriteStream & v2 ) noexcept;
            
        private:
            
            CFWriteStreamRef _cfObject;
    };
}

#endif /* CFPP_WRITE_STREAM_HPP */
