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
 * @file        Test-CFPP-Null.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Unit tests for CF::Null
 */

#include <CF++.hpp>

#define XSTEST_GTEST_COMPAT
#include <XSTest/XSTest.hpp>

TEST( CFPP_Null, CTOR )
{
    CF::Null n;
    
    ASSERT_TRUE( n.IsValid() );
    
    #ifndef _WIN32
    ASSERT_EQ( n.GetCFObject(), kCFNull );
    #endif
}

TEST( CFPP_Null, CCTOR )
{
    CF::Null n1;
    CF::Null n2( n1 );
    CF::Null n3( CF::Null( static_cast< CFNullRef >( NULL ) ) );
    
    ASSERT_TRUE(  n1.IsValid() );
    ASSERT_TRUE(  n2.IsValid() );
    ASSERT_FALSE( n3.IsValid() );
}

TEST( CFPP_Null, CTOR_CFTypeRef )
{
    CF::Null n1( kCFNull );
    CF::Null n2( static_cast< CFTypeRef >( NULL ) );
    CF::Null n3( static_cast< CFTypeRef >( CF::Array() ) );
    
    ASSERT_TRUE(  n1.IsValid() );
    ASSERT_FALSE( n2.IsValid() );
    ASSERT_FALSE( n3.IsValid() );
}

TEST( CFPP_Null, MCTOR )
{
    CF::Null n1;
    CF::Null n2( std::move( n1 ) );
    
    ASSERT_TRUE( n2.IsValid() );
}

TEST( CFPP_Null, OperatorAssign )
{
    CF::Null n1;
    CF::Null n2( CF::Null( static_cast< CFNullRef >( NULL ) ) );
    
    ASSERT_TRUE(  n1.IsValid() );
    ASSERT_FALSE( n2.IsValid() );
    
    n2 = n1;
    
    ASSERT_TRUE( n1.IsValid() );
    ASSERT_TRUE( n2.IsValid() );
}

TEST( CFPP_Null, OperatorAssign_CFTypeRef )
{
    CF::Null n( static_cast< CFTypeRef >( NULL ) );
    
    ASSERT_FALSE( n.IsValid() );
    
    n = static_cast< CFTypeRef >( kCFNull );
    
    ASSERT_TRUE( n.IsValid() );
    
    n = static_cast< CFTypeRef >( NULL );
    
    ASSERT_FALSE( n.IsValid() );
}

TEST( CFPP_Null, GetTypeID )
{
    CF::Null n;
    
    ASSERT_EQ( n.GetTypeID(), CFNullGetTypeID() );
}

TEST( CFPP_Null, GetCFObject )
{
    CF::Null n1;
    CF::Null n2( static_cast< CFTypeRef >( NULL ) );
    
    ASSERT_TRUE( n1.GetCFObject() != NULL );
    ASSERT_TRUE( n2.GetCFObject() == NULL );
}

TEST( CFPP_Null, Swap )
{
    CF::Null n1;
    CF::Null n2( static_cast< CFTypeRef >( NULL ) );
    
    ASSERT_TRUE(  n1.IsValid() );
    ASSERT_FALSE( n2.IsValid() );
    
    swap( n1, n2 );
    
    ASSERT_TRUE(  n2.IsValid() );
    ASSERT_FALSE( n1.IsValid() );
}
