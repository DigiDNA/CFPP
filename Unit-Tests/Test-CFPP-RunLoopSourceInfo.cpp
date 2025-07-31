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
 * @file        Test-CFPP-RunLoopSourceInfo.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Unit tests for CF::RunLoopSourceInfo
 */

#include <CF++.hpp>

#define XSTEST_GTEST_COMPAT
#include <XSTest/XSTest.hpp>

TEST( CFPP_RunLoopSourceInfo, CreateContext )
{
    CFRunLoopSourceContext context = CF::RunLoopSourceInfo::CreateContext( nullptr, nullptr, nullptr );
    
    ASSERT_NE( context.perform,  nullptr );
    ASSERT_NE( context.schedule, nullptr );
    ASSERT_NE( context.cancel,   nullptr );
    ASSERT_NE( context.retain,   nullptr );
    ASSERT_NE( context.release,  nullptr );
}

TEST( CFPP_RunLoopSourceInfo, Perform )
{
    int                    x  = 0;
    CFRunLoopSourceContext c1 = CF::RunLoopSourceInfo::CreateContext( nullptr, nullptr, nullptr );
    CFRunLoopSourceContext c2 = CF::RunLoopSourceInfo::CreateContext
    (
        [ & ]
        {
            x += 1;
        },
        nullptr,
        nullptr
    );
    
    ASSERT_NE( c1.perform, nullptr );
    ASSERT_NE( c2.perform, nullptr );
    
    ASSERT_NO_THROW(         c1.perform( c1.info ) );
    ASSERT_NO_FATAL_FAILURE( c1.perform( c1.info ) );
    ASSERT_NO_THROW(         c2.perform( c2.info ) );
    ASSERT_NO_FATAL_FAILURE( c2.perform( c2.info ) );
    
    ASSERT_EQ( x, 2 );
}

TEST( CFPP_RunLoopSourceInfo, Schedule )
{
    int                    x  = 0;
    CFRunLoopSourceContext c1 = CF::RunLoopSourceInfo::CreateContext( nullptr, nullptr, nullptr );
    CFRunLoopSourceContext c2 = CF::RunLoopSourceInfo::CreateContext
    (
        nullptr,
        [ & ]( CF::RunLoop &, CFStringRef )
        {
            x += 1;
        },
        nullptr
    );
    
    ASSERT_NE( c1.perform, nullptr );
    ASSERT_NE( c2.perform, nullptr );
    
    ASSERT_NO_THROW(         c1.schedule( c1.info, nullptr, kCFRunLoopDefaultMode ) );
    ASSERT_NO_FATAL_FAILURE( c1.schedule( c1.info, nullptr, kCFRunLoopDefaultMode ) );
    ASSERT_NO_THROW(         c2.schedule( c2.info, nullptr, kCFRunLoopDefaultMode ) );
    ASSERT_NO_FATAL_FAILURE( c2.schedule( c2.info, nullptr, kCFRunLoopDefaultMode ) );
    
    ASSERT_EQ( x, 2 );
}

TEST( CFPP_RunLoopSourceInfo, Cancel )
{
    int                    x  = 0;
    CFRunLoopSourceContext c1 = CF::RunLoopSourceInfo::CreateContext( nullptr, nullptr, nullptr );
    CFRunLoopSourceContext c2 = CF::RunLoopSourceInfo::CreateContext
    (
        nullptr,
        nullptr,
        [ & ]( CF::RunLoop &, CFStringRef )
        {
            x += 1;
        }
    );
    
    ASSERT_NE( c1.perform, nullptr );
    ASSERT_NE( c2.perform, nullptr );
    
    ASSERT_NO_THROW(         c1.cancel( c1.info, nullptr, kCFRunLoopDefaultMode ) );
    ASSERT_NO_FATAL_FAILURE( c1.cancel( c1.info, nullptr, kCFRunLoopDefaultMode ) );
    ASSERT_NO_THROW(         c2.cancel( c2.info, nullptr, kCFRunLoopDefaultMode ) );
    ASSERT_NO_FATAL_FAILURE( c2.cancel( c2.info, nullptr, kCFRunLoopDefaultMode ) );
    
    ASSERT_EQ( x, 2 );
}
