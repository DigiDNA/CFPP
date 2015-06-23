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
 * @file        CFPP-Boolean.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Unit tests for CF::Boolean
 */

#include <CF++.h>
#include <GoogleMock/GoogleMock.h>

using namespace testing;

TEST( CFPP_Boolean, CTOR )
{
    CF::Boolean b1;
    CF::Boolean b2( true );
    
    ASSERT_FALSE( b1.GetValue() );
    ASSERT_TRUE(  b2.GetValue() );
}

TEST( CFPP_Boolean, CTOR_CFType )
{
    CFBooleanRef b;
    CFStringRef  s;
    
    b = kCFBooleanTrue;
    s = CFStringCreateWithCString( NULL, "hello, world", kCFStringEncodingASCII );
    
    {
        CF::Boolean b1( static_cast< CFTypeRef >( b ) );
        CF::Boolean b2( static_cast< CFTypeRef >( s ) );
        CF::Boolean b3( static_cast< CFTypeRef >( NULL ) );
        
        ASSERT_TRUE(  b1.GetValue() );
        ASSERT_FALSE( b2.GetValue() );
        ASSERT_FALSE( b3.GetValue() );
    }
    
    CFRelease( s );
}

TEST( CFPP_Boolean, CTOR_CFBoolean )
{
    CF::Boolean b1( kCFBooleanTrue );
    CF::Boolean b2( kCFBooleanFalse );
    CF::Boolean b3( static_cast< CFBooleanRef >( NULL ) );
    
    ASSERT_TRUE(  b1.GetValue() );
    ASSERT_FALSE( b2.GetValue() );
    ASSERT_FALSE( b3.GetValue() );
}

TEST( CFPP_Boolean, CTOR_CFType_WithDefaultValue )
{
    CFBooleanRef b;
    CFStringRef  s;
    
    b = kCFBooleanTrue;
    s = CFStringCreateWithCString( NULL, "hello, world", kCFStringEncodingASCII );
    
    {
        CF::Boolean b1( static_cast< CFTypeRef >( b ), false );
        CF::Boolean b2( static_cast< CFTypeRef >( s ), true );
        CF::Boolean b3( static_cast< CFTypeRef >( NULL ), true );
        
        ASSERT_TRUE( b1.GetValue() );
        ASSERT_TRUE( b2.GetValue() );
        ASSERT_TRUE( b3.GetValue() );
    }
    
    CFRelease( s );
}

TEST( CFPP_Boolean, CTOR_CFBoolean_WithDefaultValue )
{
    CF::Boolean b1( kCFBooleanTrue, false );
    CF::Boolean b2( kCFBooleanFalse, true );
    CF::Boolean b3( static_cast< CFBooleanRef >( NULL ), true );
    
    ASSERT_TRUE(  b1.GetValue() );
    ASSERT_FALSE( b2.GetValue() );
    ASSERT_TRUE(  b3.GetValue() );
}

TEST( CFPP_Boolean, CCTOR )
{
    CF::Boolean b1( true );
    CF::Boolean b2( false );
    CF::Boolean b3( b1 );
    CF::Boolean b4( b2 );
    
    ASSERT_TRUE(  b3.GetValue() );
    ASSERT_FALSE( b4.GetValue() );
}

TEST( CFPP_Boolean, MCTOR )
{
    CF::Boolean b1( true );
    CF::Boolean b2( std::move( b1 ) );
    
    ASSERT_FALSE( b1.GetValue() );
    ASSERT_FALSE( b1.IsValid() );
    ASSERT_TRUE(  b2.GetValue() );
}

TEST( CFPP_Boolean, OperatorAssignBoolean )
{
    CF::Boolean b1;
    CF::Boolean b2( true );
    CF::Boolean b3( false );
    
    ASSERT_FALSE( b1.GetValue() );
    
    b1 = b2;
    
    ASSERT_TRUE( b1.GetValue() );
    
    b1 = b3;
    
    ASSERT_FALSE( b1.GetValue() );
}

TEST( CFPP_Boolean, OperatorAssignCFType )
{
    CF::Boolean b1;
    CF::String  s( "hello, world" );
    
    ASSERT_FALSE( b1.GetValue() );
    
    b1 = static_cast< CFTypeRef >( kCFBooleanTrue );
    
    ASSERT_TRUE( b1.GetValue() );
    
    b1 = static_cast< CFTypeRef >( kCFBooleanFalse );
    
    ASSERT_FALSE( b1.GetValue() );
    
    b1 = kCFBooleanTrue;
    
    ASSERT_TRUE( b1.GetValue() );
    
    b1 = static_cast< CFTypeRef >( s.GetCFObject() );
    
    ASSERT_FALSE( b1.GetValue() );
}

TEST( CFPP_Boolean, OperatorAssignCFBoolean )
{
    CF::Boolean b1;
    CF::String  s( "hello, world" );
    
    ASSERT_FALSE( b1.GetValue() );
    
    b1 = kCFBooleanTrue;
    
    ASSERT_TRUE( b1.GetValue() );
    
    b1 = kCFBooleanFalse;
    
    ASSERT_FALSE( b1.GetValue() );
    
    b1 = kCFBooleanTrue;
    
    ASSERT_TRUE( b1.GetValue() );
    
    b1 = static_cast< CFBooleanRef >( s.GetCFObject() );
    
    ASSERT_FALSE( b1.GetValue() );
}

TEST( CFPP_Boolean, OperatorAssignBool )
{
    CF::Boolean b1;
    
    ASSERT_FALSE( b1.GetValue() );
    
    b1 = true;
    
    ASSERT_TRUE( b1.GetValue() );
    
    b1 = false;
    
    ASSERT_FALSE( b1.GetValue() );
}

TEST( CFPP_Boolean, OperatorEqualBoolean )
{
    CF::Boolean b1( true );
    CF::Boolean b2( false );
    
    ASSERT_TRUE(  b1 == b1 );
    ASSERT_FALSE( b1 == b2 );
    ASSERT_TRUE(  b2 == b2 );
    ASSERT_FALSE( b2 == b1 );
}

TEST( CFPP_Boolean, OperatorEqualCFType )
{
    CF::Boolean b1( true );
    CF::Boolean b2( false );
    CF::String  s( "hello, world" );
    
    ASSERT_TRUE(  b1 == static_cast< CFTypeRef >( kCFBooleanTrue ) );
    ASSERT_FALSE( b1 == static_cast< CFTypeRef >( kCFBooleanFalse ) );
    ASSERT_FALSE( b1 == static_cast< CFTypeRef >( s.GetCFObject() ) );
    ASSERT_TRUE(  b2 == static_cast< CFTypeRef >( kCFBooleanFalse ) );
    ASSERT_FALSE( b2 == static_cast< CFTypeRef >( kCFBooleanTrue ) );
    ASSERT_FALSE( b2 == static_cast< CFTypeRef >( s.GetCFObject() ) );
}

TEST( CFPP_Boolean, OperatorEqualCFBoolean )
{
    CF::Boolean b1( true );
    CF::Boolean b2( false );
    CF::String  s( "hello, world" );
    
    ASSERT_TRUE(  b1 == kCFBooleanTrue );
    ASSERT_FALSE( b1 == kCFBooleanFalse );
    ASSERT_FALSE( b1 == static_cast< CFBooleanRef >( s.GetCFObject() ) );
    ASSERT_TRUE(  b2 == kCFBooleanFalse );
    ASSERT_FALSE( b2 == kCFBooleanTrue );
    ASSERT_FALSE( b2 == static_cast< CFBooleanRef >( s.GetCFObject() ) );
}

TEST( CFPP_Boolean, OperatorEqualBool )
{
    CF::Boolean b1( true );
    CF::Boolean b2( false );
    
    ASSERT_TRUE(  b1 == true );
    ASSERT_FALSE( b1 == false );
    ASSERT_TRUE(  b2 == false );
    ASSERT_FALSE( b2 == true );
}

TEST( CFPP_Boolean, OperatorNotEqualBoolean )
{
    CF::Boolean b1( true );
    CF::Boolean b2( false );
    
    ASSERT_TRUE(  b1 != b2 );
    ASSERT_FALSE( b1 != b1 );
    ASSERT_TRUE(  b2 != b1 );
    ASSERT_FALSE( b2 != b2 );
}

TEST( CFPP_Boolean, OperatorNotEqualCFType )
{
    CF::Boolean b1( true );
    CF::Boolean b2( false );
    CF::String  s( "hello, world" );
    
    ASSERT_TRUE(  b1 != static_cast< CFTypeRef >( kCFBooleanFalse ) );
    ASSERT_FALSE( b1 != static_cast< CFTypeRef >( kCFBooleanTrue ) );
    ASSERT_TRUE(  b1 != static_cast< CFTypeRef >( s.GetCFObject() ) );
    ASSERT_TRUE(  b2 != static_cast< CFTypeRef >( kCFBooleanTrue ) );
    ASSERT_FALSE( b2 != static_cast< CFTypeRef >( kCFBooleanFalse ) );
    ASSERT_TRUE(  b2 != static_cast< CFTypeRef >( s.GetCFObject() ) );
}

TEST( CFPP_Boolean, OperatorNotEqualCFBoolean )
{
    CF::Boolean b1( true );
    CF::Boolean b2( false );
    CF::String  s( "hello, world" );
    
    ASSERT_TRUE(  b1 != kCFBooleanFalse );
    ASSERT_FALSE( b1 != kCFBooleanTrue );
    ASSERT_TRUE(  b1 != static_cast< CFBooleanRef >( s.GetCFObject() ) );
    ASSERT_TRUE(  b2 != kCFBooleanTrue );
    ASSERT_FALSE( b2 != kCFBooleanFalse );
    ASSERT_TRUE(  b2 != static_cast< CFBooleanRef >( s.GetCFObject() ) );
}

TEST( CFPP_Boolean, OperatorNotEqualBool )
{
    CF::Boolean b1( true );
    CF::Boolean b2( false );
    
    ASSERT_TRUE(  b1 != false );
    ASSERT_FALSE( b1 != true );
    ASSERT_TRUE(  b2 != true );
    ASSERT_FALSE( b2 != false );
}

TEST( CFPP_Boolean, CastToBool )
{
    CF::Boolean b1( true );
    CF::Boolean b2( false );
    
    ASSERT_TRUE(  static_cast< bool >( b1 ) );
    ASSERT_FALSE( static_cast< bool >( b2 ) );
}

TEST( CFPP_Boolean, GetTypeID )
{
    CF::Boolean b;
    
    ASSERT_EQ( b.GetTypeID(), CFBooleanGetTypeID() );
}

TEST( CFPP_Boolean, GetCFObject )
{
    CF::Boolean b1( true );
    CF::Boolean b2( false );
    
    ASSERT_NE( b1.GetCFObject(), static_cast< CFTypeRef >( NULL ) );
    ASSERT_NE( b2.GetCFObject(), static_cast< CFTypeRef >( NULL ) );
    ASSERT_EQ( b1.GetCFObject(), kCFBooleanTrue );
    ASSERT_EQ( b2.GetCFObject(), kCFBooleanFalse );
}

TEST( CFPP_Boolean, GetValue )
{
    CF::Boolean b1( true );
    CF::Boolean b2( false );
    
    ASSERT_EQ( b1.GetValue(), true );
    ASSERT_EQ( b2.GetValue(), false );
}

TEST( CFPP_Boolean, SetValue )
{
    CF::Boolean b( true );
    
    ASSERT_EQ( b.GetValue(), true );
    
    b.SetValue( false );
    
    ASSERT_EQ( b.GetValue(), false );
}

TEST( CFPP_Boolean, Swap )
{
    CF::Boolean b1( true );
    CF::Boolean b2( false );
    
    swap( b1, b2 );
    
    ASSERT_EQ( b1.GetValue(), false );
    ASSERT_EQ( b2.GetValue(), true );
}
