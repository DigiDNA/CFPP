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
 * @header      CFPP-AnyPropertyListType.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ generic wrapper for CF property list types
 */

#ifndef CFPP_ANY_PROPERTY_LIST_TYPE_H
#define CFPP_ANY_PROPERTY_LIST_TYPE_H

namespace CF
{
    class Data;
    
    class CFPP_EXPORT AnyPropertyListType: public PropertyListBase
    {
        public:
            
            static AnyPropertyListType FromPropertyList( const std::string & path );
            static AnyPropertyListType FromPropertyListString( const std::string & plist );
            static AnyPropertyListType FromPropertyListData( const Data & plist );
            
            AnyPropertyListType( PropertyListFormat format );
            AnyPropertyListType( const AnyPropertyListType & value );
            AnyPropertyListType( const AutoPointer & value, PropertyListFormat format );
            AnyPropertyListType( CFTypeRef value, PropertyListFormat format );
            AnyPropertyListType( std::nullptr_t, PropertyListFormat format );
            AnyPropertyListType( AnyPropertyListType && value ) noexcept;
            
            virtual ~AnyPropertyListType( void );
            
            AnyPropertyListType & operator = ( AnyPropertyListType value );
            AnyPropertyListType & operator = ( const AutoPointer & value );
            AnyPropertyListType & operator = ( CFTypeRef value );
            AnyPropertyListType & operator = ( std::nullptr_t value );
            
            bool IsValidPropertyList( void ) const;
            
            virtual CFTypeID  GetTypeID( void ) const;
            virtual CFTypeRef GetCFObject( void ) const;
            
            PropertyListFormat GetFormat( void ) const;
            
            friend void swap( AnyPropertyListType & v1, AnyPropertyListType & v2 ) noexcept;
            
        protected:
            
            CFTypeRef          _cfObject;
            PropertyListFormat _format;
    };
}

#endif /* CFPP_ANY_PROPERTY_LIST_TYPE_H */
