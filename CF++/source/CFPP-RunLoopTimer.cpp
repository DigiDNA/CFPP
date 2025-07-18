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
 * @file        CFPP-RunLoopTimer.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFRunLoopTimerRef wrapper
 */

#include <CF++.hpp>

namespace CF
{
    RunLoopTimer::RunLoopTimer( const RunLoopTimer & value ): _cfObject( nullptr )
    {
        if( value._cfObject != nullptr )
        {
            this->_cfObject = static_cast< CFRunLoopTimerRef >( const_cast< void * >( CFRetain( value._cfObject ) ) );
        }
    }
    
    RunLoopTimer::RunLoopTimer( const AutoPointer & value ): _cfObject( nullptr )
    {
        if( value.IsValid() && value.GetTypeID() == this->GetTypeID() )
        {
            this->_cfObject = static_cast< CFRunLoopTimerRef >( const_cast< void * >( CFRetain( value ) ) );
        }
    }
    
    RunLoopTimer::RunLoopTimer( CFTypeRef value ): _cfObject( nullptr )
    {
        if( value != nullptr && CFGetTypeID( value ) == this->GetTypeID() )
        {
            this->_cfObject = static_cast< CFRunLoopTimerRef >( const_cast< void * >( CFRetain( value ) ) );
        }
    }
    
    RunLoopTimer::RunLoopTimer( CFRunLoopTimerRef value ): _cfObject( nullptr )
    {
        if( value != nullptr && CFGetTypeID( value ) == this->GetTypeID() )
        {
            this->_cfObject = static_cast< CFRunLoopTimerRef >( const_cast< void * >( CFRetain( value ) ) );
        }
    }
    
    RunLoopTimer::RunLoopTimer( RunLoopTimer && value ) noexcept
    {
        this->_cfObject = value._cfObject;
        value._cfObject = nullptr;
    }
    
    RunLoopTimer::~RunLoopTimer()
    {
        if( this->_cfObject != nullptr )
        {
            CFRelease( this->_cfObject );
            
            this->_cfObject = nullptr;
        }
    }
    
    RunLoopTimer & RunLoopTimer::operator =( RunLoopTimer value )
    {
        swap( *( this ), value );
        
        return *( this );
    }
    
    RunLoopTimer & RunLoopTimer::operator =( const AutoPointer & value )
    {
        return operator =( RunLoopTimer( value ) );
    }
    
    RunLoopTimer & RunLoopTimer::operator =( CFTypeRef value )
    {
        return operator =( RunLoopTimer( value ) );
    }
    
    RunLoopTimer & RunLoopTimer::operator =( CFRunLoopTimerRef value )
    {
        return operator =( RunLoopTimer( value ) );
    }
    
    CFTypeID RunLoopTimer::GetTypeID() const
    {
        return CFRunLoopTimerGetTypeID();
    }
    
    CFTypeRef RunLoopTimer::GetCFObject() const
    {
        return static_cast< CFTypeRef >( this->_cfObject );
    }
    
    void swap( RunLoopTimer & v1, RunLoopTimer & v2 ) noexcept
    {
        using std::swap;
        
        swap( v1._cfObject, v2._cfObject );
    }
}
