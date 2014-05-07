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
 
/* $Id$ */

/*!
 * @file        CFPP-Boolean.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFBooleanRef wrapper
 */

#include <CF++.h>

#ifdef _WIN32

#include <Windows.h>

static bool         __hasCFBoolean   = false;
static CFBooleanRef __cfBooleanTrue  = NULL;
static CFBooleanRef __cfBooleanFalse = NULL;

static void __loadCFBoolean( void )
{
    HMODULE cfModule;

    if( __hasCFBoolean == true )
    {
        return;
    }

    cfModule = GetModuleHandle( L"CoreFoundation.dll" );

    if( cfModule != NULL )
    {
        __hasCFBoolean   = true;
        __cfBooleanTrue  = *( ( CFBooleanRef * )GetProcAddress( cfModule, "kCFBooleanTrue" ) );
        __cfBooleanFalse = *( ( CFBooleanRef * )GetProcAddress( cfModule, "kCFBooleanFalse" ) );
    }
}

#endif

namespace CF
{
    Boolean::Boolean( CFTypeRef cfObject )
    {
        bool b;

        this->_cfObject = NULL;
        
        if( cfObject != NULL && CFGetTypeID( cfObject ) == this->GetTypeID()  )
        {
            b = ( CFBooleanGetValue( ( CFBooleanRef )cfObject ) ) ? true : false;
        }
        else
        {
            b = false;
        }

        this->SetValue( b );
    }
    
    Boolean::Boolean( CFBooleanRef cfObject )
    {
        bool b;

        this->_cfObject = NULL;
        
        if( cfObject != NULL && CFGetTypeID( cfObject ) == this->GetTypeID() )
        {
            b = ( CFBooleanGetValue( cfObject ) ) ? true : false;
        }
        else
        {
            b = false;
        }

        this->SetValue( b );
    }
    
    Boolean::Boolean( bool value )
    {
        this->_cfObject = NULL;
        
        this->SetValue( value );
    }
    
    Boolean::Boolean( const Boolean & value )
    {
        this->_cfObject = NULL;
        
        this->SetValue( value.GetValue() );
    }
    
    Boolean::~Boolean( void )
    {
        if( this->_cfObject != NULL )
        {
            CFRelease( this->_cfObject );
            
            this->_cfObject = NULL;
        }
    }
    
    Boolean & Boolean::operator = ( const Boolean & value )
    {
        this->SetValue( value.GetValue() );
        
        return *( this );
    }
    
    Boolean & Boolean::operator = ( CFTypeRef value )
    {
        bool b;

        if( value != NULL && CFGetTypeID( value ) == this->GetTypeID() )
        {
            b = ( CFBooleanGetValue( ( CFBooleanRef )value ) ) ? true : false;
        }
        else
        {
            b = false;
        }

        this->SetValue( b );
        
        return *( this );
    }
    
    Boolean & Boolean::operator = ( CFBooleanRef value )
    {
        bool b;

        if( value != NULL && CFGetTypeID( value ) == this->GetTypeID() )
        {
            b = ( CFBooleanGetValue( value ) ) ? true : false;
        }
        else
        {
            b = false;
        }

        this->SetValue( b );

        return *( this );
    }
    
    Boolean & Boolean::operator = ( bool value )
    {
        this->SetValue( value );
        
        return *( this );
    }
    
    bool Boolean::operator == ( const Boolean & value ) const
    {
        return this->GetValue() == value.GetValue();
    }
    
    bool Boolean::operator == ( bool value ) const
    {
        return this->GetValue() == value;
    }
    
    bool Boolean::operator == ( CFTypeRef value ) const
    {
        bool b;

        if( value == NULL || CFGetTypeID( value ) != this->GetTypeID() )
        {
            return false;
        }
        
        b = ( CFBooleanGetValue( ( CFBooleanRef )value ) ) ? true : false;

        return this->GetValue() == b;
    }
    
    bool Boolean::operator == ( CFBooleanRef value ) const
    {
        bool b;

        if( value == NULL || CFGetTypeID( value ) != this->GetTypeID() )
        {
            return false;
        }

        b = ( CFBooleanGetValue( value ) ) ? true : false;
        
        return this->GetValue() == b;
    }
            
    bool Boolean::operator != ( const Boolean & value ) const
    {
        return !( *( this ) == value );
    }
    
    bool Boolean::operator != ( bool value ) const
    {
        return !( *( this ) == value );
    }
    
    bool Boolean::operator != ( CFTypeRef value ) const
    {
        return !( *( this ) == value );
    }
    
    bool Boolean::operator != ( CFBooleanRef value ) const
    {
        return !( *( this ) == value );
    }
    
    Boolean::operator bool ()
    {
        return this->GetValue();
    }
    
    CFTypeID Boolean::GetTypeID( void ) const
    {
        return CFBooleanGetTypeID();
    }
    
    CFTypeRef Boolean::GetCFObject( void ) const
    {
        return ( CFTypeRef )( this->_cfObject );
    }
            
    bool Boolean::GetValue( void ) const
    {
        if( this->_cfObject == NULL )
        {
            return false;
        }
        
        return ( CFBooleanGetValue( this->_cfObject ) ) ? true : false;
    }
    
    void Boolean::SetValue( bool value )
    {
        if( this->_cfObject != NULL )
        {
            CFRelease( this->_cfObject );
        }
        
        #ifdef _WIN32

        __loadCFBoolean();

        this->_cfObject = ( CFBooleanRef )CFRetain( ( value == true ) ? __cfBooleanTrue : __cfBooleanFalse );

        #else
        
        this->_cfObject = ( CFBooleanRef )CFRetain( ( value == true ) ? kCFBooleanTrue : kCFBooleanFalse );
        
        #endif
    }
}
