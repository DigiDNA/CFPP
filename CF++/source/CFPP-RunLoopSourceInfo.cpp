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
 * @file        CFPP-RunLoopSource.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFRunLoopSourceRef wrapper
 */

#include <CF++.hpp>

namespace CF
{
    CFRunLoopSourceContext RunLoopSourceInfo::CreateContext( const std::function< void() > & perform, const std::function< void( RunLoop &, CFRunLoopMode ) > & schedule, const std::function< void( RunLoop &, CFRunLoopMode ) > & cancel )
    {
        CFRunLoopSourceContext context;
        
        memset( &context, 0, sizeof( CFRunLoopSourceContext ) );
        
        context.info     = new RunLoopSourceInfo( perform, schedule, cancel );
        context.perform  = &RunLoopSourceInfo::_Perform;
        context.schedule = &RunLoopSourceInfo::_Schedule;
        context.cancel   = &RunLoopSourceInfo::_Cancel;
        context.retain   = &RunLoopSourceInfo::_Retain;
        context.release  = &RunLoopSourceInfo::_Release;
        
        return context;
    }
    
    RunLoopSourceInfo::RunLoopSourceInfo( const std::function< void() > & perform, const std::function< void( RunLoop &, CFRunLoopMode ) > & schedule, const std::function< void( RunLoop &, CFRunLoopMode ) > & cancel ):
        _rc(       0 ),
        _perform(  perform ),
        _schedule( schedule ),
        _cancel(   cancel )
    {}
    
    RunLoopSourceInfo::~RunLoopSourceInfo()
    {}
    
    void RunLoopSourceInfo::_Perform( void * info )
    {
        if( info == nullptr )
        {
            return;
        }
        
        RunLoopSourceInfo * self = static_cast< RunLoopSourceInfo * >( const_cast< void * >( info ) );
        
        if( self->_perform != nullptr )
        {
            self->_perform();
        }
    }
    
    void RunLoopSourceInfo::_Schedule( void * info, CFRunLoopRef rl, CFRunLoopMode mode )
    {
        if( info == nullptr )
        {
            return;
        }
        
        RunLoopSourceInfo * self    = static_cast< RunLoopSourceInfo * >( const_cast< void * >( info ) );
        RunLoop             runLoop = rl;
        
        if( self->_schedule != nullptr )
        {
            self->_schedule( runLoop, mode );
        }
    }
    
    void RunLoopSourceInfo::_Cancel( void * info, CFRunLoopRef rl, CFRunLoopMode mode )
    {
        if( info == nullptr )
        {
            return;
        }
        
        RunLoopSourceInfo * self    = static_cast< RunLoopSourceInfo * >( const_cast< void * >( info ) );
        RunLoop             runLoop = rl;
        
        if( self->_cancel != nullptr )
        {
            self->_cancel( runLoop, mode );
        }
    }
    
    const void * RunLoopSourceInfo::_Retain( const void * info )
    {
        if( info == nullptr )
        {
            return info;
        }
        
        RunLoopSourceInfo * self = static_cast< RunLoopSourceInfo * >( const_cast< void * >( info ) );
        self->_rc               += 1;
        
        return info;
    }
    
    void RunLoopSourceInfo::_Release( const void * info )
    {
        if( info == nullptr )
        {
            return;
        }
        
        RunLoopSourceInfo * self = static_cast< RunLoopSourceInfo * >( const_cast< void * >( info ) );
        
        if( self->_rc == 0 )
        {
            delete self;
        }
        else
        {
            self->_rc -= 1;
        }
    }
}
