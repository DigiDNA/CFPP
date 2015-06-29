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
 * @file        CFPP-Type.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Unit tests for CF::Type
 */

#include <CF++.h>
#include <GoogleMock/GoogleMock.h>

using namespace testing;

TEST( CFPP_Type, OperatorEqual )
{
    CF::Number o1 = 1;
    CF::Number o2 = 1;
    CF::Type & t1 = o1;
    CF::Type & t2 = o2;
    
    ASSERT_TRUE( t1 == t2 );
    
    o1 = static_cast< CFNumberRef >( NULL );
    
    ASSERT_FALSE( t1.IsValid() );
    ASSERT_FALSE( t1 == t2 );
    
    o1 = 1;
    o2 = static_cast< CFNumberRef >( NULL );
    
    ASSERT_TRUE(  t1.IsValid() );
    ASSERT_FALSE( t2.IsValid() );
    ASSERT_FALSE( t1 == t2 );
    
    o1 = static_cast< CFNumberRef >( NULL );
    o2 = static_cast< CFNumberRef >( NULL );
    
    ASSERT_FALSE( t1.IsValid() );
    ASSERT_FALSE( t2.IsValid() );
    ASSERT_FALSE( t1 == t2 );
}

TEST( CFPP_Type, OperatorNotEqual )
{
    CF::Number o1 = 0;
    CF::Number o2 = 1;
    CF::Type & t1 = o1;
    CF::Type & t2 = o2;
        
    ASSERT_TRUE( t1 != t2 );
    
    o1 = static_cast< CFNumberRef >( NULL );
    
    ASSERT_FALSE( t1.IsValid() );
    ASSERT_TRUE(  t1 != t2 );
    
    o1 = 1;
    o2 = static_cast< CFNumberRef >( NULL );
    
    ASSERT_TRUE(  t1.IsValid() );
    ASSERT_FALSE( t2.IsValid() );
    ASSERT_TRUE(  t1 != t2 );
    
    o1 = static_cast< CFNumberRef >( NULL );
    o2 = static_cast< CFNumberRef >( NULL );
    
    ASSERT_FALSE( t1.IsValid() );
    ASSERT_FALSE( t2.IsValid() );
    ASSERT_TRUE(  t1 != t2 );
}

TEST( CFPP_Type, CastToCFTypeRef )
{
    CF::Number o;
    CF::Type & t = o;
    
    ASSERT_TRUE( static_cast< CFTypeRef >( t ) != NULL );
}

TEST( CFPP_Type, CastToCFBooleanRef )
{
    CF::Boolean o1;
    CF::Number  o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFBooleanRef >( t1 ) != NULL );
    ASSERT_TRUE( static_cast< CFBooleanRef >( t2 ) == NULL );
}

TEST( CFPP_Type, CastToCFNumberRef )
{
    CF::Number  o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFNumberRef >( t1 ) != NULL );
    ASSERT_TRUE( static_cast< CFNumberRef >( t2 ) == NULL );
}

TEST( CFPP_Type, CastToCFDateRef )
{
    CF::Date    o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFDateRef >( t1 ) != NULL );
    ASSERT_TRUE( static_cast< CFDateRef >( t2 ) == NULL );
}

TEST( CFPP_Type, CastToCFStringRef )
{
    CF::String  o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFStringRef >( t1 ) != NULL );
    ASSERT_TRUE( static_cast< CFStringRef >( t2 ) == NULL );
}

TEST( CFPP_Type, CastToCFMutableStringRef )
{
    CF::String  o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFMutableStringRef >( t1 ) != NULL );
    ASSERT_TRUE( static_cast< CFMutableStringRef >( t2 ) == NULL );
}

TEST( CFPP_Type, CastToCFURLRef )
{
    CF::URL     o1( std::string( "http://www.xs-labs.com/" ) );
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFURLRef >( t1 ) != NULL );
    ASSERT_TRUE( static_cast< CFURLRef >( t2 ) == NULL );
}

TEST( CFPP_Type, CastToCFDataRef )
{
    CF::Data    o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFDataRef >( t1 ) != NULL );
    ASSERT_TRUE( static_cast< CFDataRef >( t2 ) == NULL );
}

TEST( CFPP_Type, CastToCFMutableDataRef )
{
    CF::Data    o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFMutableDataRef >( t1 ) != NULL );
    ASSERT_TRUE( static_cast< CFMutableDataRef >( t2 ) == NULL );
}

TEST( CFPP_Type, CastToCFArrayRef )
{
    CF::Array   o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFArrayRef >( t1 ) != NULL );
    ASSERT_TRUE( static_cast< CFArrayRef >( t2 ) == NULL );
}

TEST( CFPP_Type, CastToCFMutableArrayRef )
{
    CF::Array   o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFMutableArrayRef >( t1 ) != NULL );
    ASSERT_TRUE( static_cast< CFMutableArrayRef >( t2 ) == NULL );
}

TEST( CFPP_Type, CastToCFDictionaryRef )
{
    CF::Dictionary o1;
    CF::Boolean    o2;
    CF::Type     & t1 = o1;
    CF::Type     & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFDictionaryRef >( t1 ) != NULL );
    ASSERT_TRUE( static_cast< CFDictionaryRef >( t2 ) == NULL );
}

TEST( CFPP_Type, CastToCFMutableDictionaryRef )
{
    CF::Dictionary o1;
    CF::Boolean    o2;
    CF::Type     & t1 = o1;
    CF::Type     & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFMutableDictionaryRef >( t1 ) != NULL );
    ASSERT_TRUE( static_cast< CFMutableDictionaryRef >( t2 ) == NULL );
}

TEST( CFPP_Type, CastToCFUUIDRef )
{
    CF::UUID    o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFUUIDRef >( t1 ) != NULL );
    ASSERT_TRUE( static_cast< CFUUIDRef >( t2 ) == NULL );
}

TEST( CFPP_Type, CastToCFErrorRef )
{
    CF::Error   o1( std::string( "Unknown error" ), 0 );
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFErrorRef >( t1 ) != NULL );
    ASSERT_TRUE( static_cast< CFErrorRef >( t2 ) == NULL );
}

TEST( CFPP_Type, CastToCFReadStreamRef )
{
    CF::ReadStream o1( std::string( "/tmp/cf++.txt" ) );
    CF::Boolean    o2;
    CF::Type     & t1 = o1;
    CF::Type     & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFReadStreamRef >( t1 ) != NULL );
    ASSERT_TRUE( static_cast< CFReadStreamRef >( t2 ) == NULL );
}

TEST( CFPP_Type, CastToCFWriteStreamRef )
{
    CF::WriteStream o1( std::string( "/tmp/cf++.txt" ) );
    CF::Boolean     o2;
    CF::Type      & t1 = o1;
    CF::Type      & t2 = o2;
    
    ASSERT_TRUE( static_cast< CFWriteStreamRef >( t1 ) != NULL );
    ASSERT_TRUE( static_cast< CFWriteStreamRef >( t2 ) == NULL );
}

TEST( CFPP_Type, Description )
{
    CF::Array      o;
    CF::Type & t = o;
    
    ASSERT_TRUE( t.Description().length() > 0 );
    ASSERT_TRUE( t.Description().find( "<CFArray 0x" ) == 0 );
}

TEST( CFPP_Type, Hash )
{
    CF::Number o;
    CF::Type & t = o;
    
    ASSERT_TRUE( t.Hash() == CFHash( t.GetCFObject() ) );
    
    o = static_cast< CFNumberRef >( NULL );
    
    ASSERT_FALSE( t.IsValid() );
    ASSERT_EQ( t.Hash(), static_cast< CFHashCode >( 0 ) );
}

TEST( CFPP_Type, Show )
{
    ASSERT_NO_THROW( CF::Array().Show() );
    ASSERT_NO_FATAL_FAILURE( CF::Array().Show() );
    
    ASSERT_NO_THROW( CF::Boolean().Show() );
    ASSERT_NO_FATAL_FAILURE( CF::Boolean().Show() );
    
    ASSERT_NO_THROW( CF::Data().Show() );
    ASSERT_NO_FATAL_FAILURE( CF::Data().Show() );
    
    ASSERT_NO_THROW( CF::Date().Show() );
    ASSERT_NO_FATAL_FAILURE( CF::Date().Show() );
    
    ASSERT_NO_THROW( CF::Dictionary().Show() );
    ASSERT_NO_FATAL_FAILURE( CF::Dictionary().Show() );
    
    ASSERT_NO_THROW( CF::Error().Show() );
    ASSERT_NO_FATAL_FAILURE( CF::Error().Show() );
    
    ASSERT_NO_THROW( CF::Number().Show() );
    ASSERT_NO_FATAL_FAILURE( CF::Number().Show() );
    
    ASSERT_NO_THROW( CF::ReadStream().Show() );
    ASSERT_NO_FATAL_FAILURE( CF::ReadStream().Show() );
    
    ASSERT_NO_THROW( CF::String().Show() );
    ASSERT_NO_FATAL_FAILURE( CF::String().Show() );
    
    ASSERT_NO_THROW( CF::URL().Show() );
    ASSERT_NO_FATAL_FAILURE( CF::URL().Show() );
    
    ASSERT_NO_THROW( CF::UUID().Show() );
    ASSERT_NO_FATAL_FAILURE( CF::UUID().Show() );
    
    ASSERT_NO_THROW( CF::WriteStream().Show() );
    ASSERT_NO_FATAL_FAILURE( CF::WriteStream().Show() );
}

TEST( CFPP_Type, GetRetainCount )
{
    CF::Array  o;
    CF::Type & t = o;
    
    ASSERT_TRUE( t.GetRetainCount() == CFGetRetainCount( t.GetCFObject() ) );
    ASSERT_TRUE( t.GetRetainCount() == 1 );
    
    o = static_cast< CFArrayRef >( NULL );
    
    ASSERT_FALSE( t.IsValid() );
    ASSERT_TRUE(  t.GetRetainCount() == 0 );
}

TEST( CFPP_Type, IsValid )
{
    CF::Data   o1;
    CF::Data   o2( static_cast< CFDataRef >( NULL ) );
    CF::Type & t1 = o1;
    CF::Type & t2 = o2;
    
    ASSERT_TRUE(  t1.IsValid() );
    ASSERT_FALSE( t2.IsValid() );
}

TEST( CFPP_Type, IsBoolean )
{
    CF::Boolean o1;
    CF::Number  o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE(  t1.IsBoolean() );
    ASSERT_FALSE( t2.IsBoolean() );
}

TEST( CFPP_Type, IsNumber )
{
    CF::Number  o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE(  t1.IsNumber() );
    ASSERT_FALSE( t2.IsNumber() );
}

TEST( CFPP_Type, IsDate )
{
    CF::Date    o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE(  t1.IsDate() );
    ASSERT_FALSE( t2.IsDate() );
}

TEST( CFPP_Type, IsString )
{
    CF::String  o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE(  t1.IsString() );
    ASSERT_FALSE( t2.IsString() );
}

TEST( CFPP_Type, IsURL )
{
    CF::URL     o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE(  t1.IsURL() );
    ASSERT_FALSE( t2.IsURL() );
}

TEST( CFPP_Type, IsData )
{
    CF::Data    o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE(  t1.IsData() );
    ASSERT_FALSE( t2.IsData() );
}

TEST( CFPP_Type, IsArray )
{
    CF::Array   o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE(  t1.IsArray() );
    ASSERT_FALSE( t2.IsArray() );
}

TEST( CFPP_Type, IsDictionary )
{
    CF::Dictionary o1;
    CF::Boolean    o2;
    CF::Type     & t1 = o1;
    CF::Type     & t2 = o2;
    
    ASSERT_TRUE(  t1.IsDictionary() );
    ASSERT_FALSE( t2.IsDictionary() );
}

TEST( CFPP_Type, IsUUID )
{
    CF::UUID    o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE(  t1.IsUUID() );
    ASSERT_FALSE( t2.IsUUID() );
}

TEST( CFPP_Type, IsError )
{
    CF::Error   o1;
    CF::Boolean o2;
    CF::Type  & t1 = o1;
    CF::Type  & t2 = o2;
    
    ASSERT_TRUE(  t1.IsError() );
    ASSERT_FALSE( t2.IsError() );
}

TEST( CFPP_Type, IsReadStream )
{
    CF::ReadStream o1;
    CF::Boolean    o2;
    CF::Type     & t1 = o1;
    CF::Type     & t2 = o2;
    
    ASSERT_TRUE(  t1.IsReadStream() );
    ASSERT_FALSE( t2.IsReadStream() );
}

TEST( CFPP_Type, IsWriteStream )
{
    CF::WriteStream o1;
    CF::Boolean     o2;
    CF::Type      & t1 = o1;
    CF::Type      & t2 = o2;
    
    ASSERT_TRUE(  t1.IsWriteStream() );
    ASSERT_FALSE( t2.IsWriteStream() );
}

TEST( CFPP_Type, STDOstreamFriend )
{
    CF::Array         o;
    std::stringstream ss;
    
    ss << o;
    
    ASSERT_TRUE( ss.str().length() > 0 );
    ASSERT_TRUE( ss.str().find( "<CFArray 0x" ) == 0 );
}
