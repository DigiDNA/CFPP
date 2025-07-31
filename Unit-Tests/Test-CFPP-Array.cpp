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
 * @file        Test-CFPP-Array.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Unit tests for CF::Array
 */

#include <CF++.hpp>

#define XSTEST_GTEST_COMPAT
#include <XSTest/XSTest.hpp>

TEST( CFPP_Array, CTOR )
{
    CF::Array a;
    
    ASSERT_TRUE( a.IsValid() );
    ASSERT_EQ( a.GetCount(), 0 );
}

TEST( CFPP_Array, CTOR_CFIndex )
{
    CF::Array a( 100 );
    
    ASSERT_TRUE( a.IsValid() );
    ASSERT_EQ( a.GetCount(), 0 );
}

TEST( CFPP_Array, CTOR_AutoPointer )
{
    CF::Array a1( CF::AutoPointer( CFArrayCreateMutable( nullptr, 10, nullptr ) ) );
    CF::Array a2( CF::AutoPointer( CFUUIDCreate( nullptr ) ) );
    CF::Array a3( CF::AutoPointer( nullptr ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_FALSE( a3.IsValid() );
}

TEST( CFPP_Array, CTOR_CFType )
{
    CF::Array a1( static_cast< CFTypeRef >( CF::Array().GetCFObject() ) );
    CF::Array a2( static_cast< CFTypeRef >( nullptr ) );
    CF::Array a3( static_cast< CFTypeRef >( CF::Boolean().GetCFObject() ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_FALSE( a3.IsValid() );
}

TEST( CFPP_Array, CTOR_CFArray )
{
    CF::Array a1( static_cast< CFArrayRef >( CF::Array().GetCFObject() ) );
    CF::Array a2( static_cast< CFArrayRef >( nullptr ) );
    CF::Array a3( static_cast< CFArrayRef >( CF::Boolean().GetCFObject() ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_FALSE( a3.IsValid() );
}

TEST( CFPP_Array, CTOR_NullPointer )
{
    CF::Array a( nullptr );
    
    ASSERT_FALSE( a.IsValid() );
}

TEST( CFPP_Array, CTOR_STDInitializerList )
{
    CF::Array a
    (
        {
            CF::String( "hello" ),
            CF::String( "world" ),
            CF::Number( 42 ),
            CF::AutoPointer( CFStringCreateWithCString( nullptr, "hello, universe", kCFStringEncodingASCII ) )
        }
    );
    
    ASSERT_TRUE( a.IsValid() );
    ASSERT_EQ( a.GetCount(), 4 );
    
    ASSERT_TRUE( CF::String( a[ 0 ] ).IsValid() );
    ASSERT_TRUE( CF::String( a[ 1 ] ).IsValid() );
    ASSERT_TRUE( CF::Number( a[ 2 ] ).IsValid() );
    ASSERT_TRUE( CF::String( a[ 3 ] ).IsValid() );
    
    ASSERT_TRUE( CF::String( a[ 0 ] ) == "hello" );
    ASSERT_TRUE( CF::String( a[ 1 ] ) == "world" );
    ASSERT_TRUE( CF::Number( a[ 2 ] ) == 42 );
    ASSERT_TRUE( CF::String( a[ 3 ] ) == "hello, universe" );
}

TEST( CFPP_Array, CCTOR )
{
    CF::Array a1;
    
    a1 << "hello";
    a1 << "world";
    
    ASSERT_TRUE( a1.IsValid() );
    ASSERT_EQ( a1.GetCount(), 2 );
    
    {
        CF::Array a2( a1 );
        
        ASSERT_TRUE( a1.IsValid() );
        ASSERT_TRUE( a2.IsValid() );
        ASSERT_EQ( a1.GetCount(), 2 );
        ASSERT_EQ( a2.GetCount(), 2 );
    }
}

TEST( CFPP_Array, MCTOR )
{
    CF::Array a1;
    
    a1 << "hello";
    a1 << "world";
    
    ASSERT_TRUE( a1.IsValid() );
    ASSERT_EQ( a1.GetCount(), 2 );
    
    {
        CF::Array a2( std::move( a1 ) );
        
        ASSERT_FALSE( a1.IsValid() );
        ASSERT_TRUE(  a2.IsValid() );
        ASSERT_EQ( a2.GetCount(), 2 );
    }
}

TEST( CFPP_Array, OperatorAssignArray )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( nullptr ) );
    CF::Array a3( static_cast< CFArrayRef >( nullptr ) );
    CF::Array a4;
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_FALSE( a3.IsValid() );
    ASSERT_TRUE(  a4.IsValid() );
    
    a3 = a1;
    a4 = a2;
    
    ASSERT_TRUE(  a3.IsValid() );
    ASSERT_FALSE( a4.IsValid() );
}

TEST( CFPP_Array, OperatorAssignAutoPointer )
{
    CF::Array a1( static_cast< CFTypeRef >( nullptr ) );
    CF::Array a2;
    CF::Array a3;
    
    ASSERT_FALSE( a1.IsValid() );
    ASSERT_TRUE(  a2.IsValid() );
    ASSERT_TRUE(  a3.IsValid() );
    
    a1 = CF::AutoPointer( CFArrayCreateMutable( nullptr, 0, nullptr ) );
    a2 = CF::AutoPointer( CFUUIDCreate( nullptr ) );
    a3 = CF::AutoPointer( nullptr );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_FALSE( a3.IsValid() );
}

TEST( CFPP_Array, OperatorAssignCFType )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( nullptr ) );
    CF::Array a3( static_cast< CFArrayRef >( nullptr ) );
    CF::Array a4;
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_FALSE( a3.IsValid() );
    ASSERT_TRUE(  a4.IsValid() );
    
    a3 = static_cast< CFTypeRef >( a1 );
    a4 = static_cast< CFTypeRef >( a2 );
    
    ASSERT_TRUE(  a3.IsValid() );
    ASSERT_FALSE( a4.IsValid() );
}

TEST( CFPP_Array, OperatorAssignCFArray )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( nullptr ) );
    CF::Array a3( static_cast< CFArrayRef >( nullptr ) );
    CF::Array a4;
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_FALSE( a3.IsValid() );
    ASSERT_TRUE(  a4.IsValid() );
    
    a3 = static_cast< CFArrayRef >( a1 );
    a4 = static_cast< CFArrayRef >( a2 );
    
    ASSERT_TRUE(  a3.IsValid() );
    ASSERT_FALSE( a4.IsValid() );
}

TEST( CFPP_Array, OperatorAssignNullPointer )
{
    CF::Array a;
    
    ASSERT_TRUE( a.IsValid() );
    
    a = nullptr;
    
    ASSERT_FALSE( a.IsValid() );
}

TEST( CFPP_Array, Referencing )
{
    CF::Array a1;
    
    {
        CF::Array a2 = CF::Array::Referencing( a1 );
        
        ASSERT_EQ( a1.GetCFObject(), a2.GetCFObject() );
        
        a1 << CF::String( "foo" );
        
        ASSERT_EQ( a1.GetCFObject(), a2.GetCFObject() );
    }
    
    ASSERT_EQ( CF::String( a1[ 0 ] ), "foo" );
}

TEST( CFPP_Array, OperatorPlusEqualArray )
{
    CF::Array a1;
    CF::Array a2;
    CF::Array a3( static_cast< CFArrayRef >( nullptr ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_TRUE(  a2.IsValid() );
    ASSERT_FALSE( a3.IsValid() );
    
    a1 << CF::String( "hello, world" );
    
    ASSERT_TRUE( a1.GetCount() == 1 );
    ASSERT_TRUE( a2.GetCount() == 0 );
    
    a1 += a2;
    
    ASSERT_TRUE( a1.GetCount() == 1 );
    ASSERT_TRUE( a2.GetCount() == 0 );
    
    a1 += a1;
    
    ASSERT_TRUE( a1.GetCount() == 2 );
    
    a1 += a3;
    
    ASSERT_TRUE( a1.GetCount() == 2 );
    
    a3 += a1;
    
    ASSERT_FALSE( a3.IsValid() );
}

TEST( CFPP_Array, OperatorPlusEqualCFType )
{
    CF::Array a1;
    CF::Array a2;
    CF::Array a3( static_cast< CFArrayRef >( nullptr ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_TRUE(  a2.IsValid() );
    ASSERT_FALSE( a3.IsValid() );
    
    a1 << CF::String( "hello, world" );
    
    ASSERT_TRUE( a1.GetCount() == 1 );
    ASSERT_TRUE( a2.GetCount() == 0 );
    
    a1 += static_cast< CFTypeRef >( a2.GetCFObject() );
    
    ASSERT_TRUE( a1.GetCount() == 1 );
    ASSERT_TRUE( a2.GetCount() == 0 );
    
    a1 += static_cast< CFTypeRef >( a1.GetCFObject() );
    
    ASSERT_TRUE( a1.GetCount() == 2 );
    
    a1 += static_cast< CFTypeRef >( a3.GetCFObject() );
    
    ASSERT_TRUE( a1.GetCount() == 2 );
    
    a3 += static_cast< CFTypeRef >( a1.GetCFObject() );
    
    ASSERT_FALSE( a3.IsValid() );
}

TEST( CFPP_Array, OperatorPlusEqualCFArray )
{
    CF::Array a1;
    CF::Array a2;
    CF::Array a3( static_cast< CFArrayRef >( nullptr ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_TRUE(  a2.IsValid() );
    ASSERT_FALSE( a3.IsValid() );
    
    a1 << CF::String( "hello, world" );
    
    ASSERT_TRUE( a1.GetCount() == 1 );
    ASSERT_TRUE( a2.GetCount() == 0 );
    
    a1 += static_cast< CFArrayRef >( a2.GetCFObject() );
    
    ASSERT_TRUE( a1.GetCount() == 1 );
    ASSERT_TRUE( a2.GetCount() == 0 );
    
    a1 += static_cast< CFArrayRef >( a1.GetCFObject() );
    
    ASSERT_TRUE( a1.GetCount() == 2 );
    
    a1 += static_cast< CFArrayRef >( a3.GetCFObject() );
    
    ASSERT_TRUE( a1.GetCount() == 2 );
    
    a3 += static_cast< CFArrayRef >( a1.GetCFObject() );
    
    ASSERT_FALSE( a3.IsValid() );
}

TEST( CFPP_Array, OperatorLeftShiftCFType )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( nullptr ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_TRUE(  a1.GetCount() == 0 );
    
    a1 << static_cast< CFTypeRef >( CF::String( "hello, world" ).GetCFObject() );
    a2 << static_cast< CFTypeRef >( CF::String( "hello, world" ).GetCFObject() );
    
    ASSERT_TRUE(  a1.GetCount() == 1 );
    ASSERT_FALSE( a2.IsValid() );
}

TEST( CFPP_Array, OperatorLeftShiftCChar )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( nullptr ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_TRUE(  a1.GetCount() == 0 );
    
    a1 << "hello, world";
    a2 << "hello, world";
    
    ASSERT_TRUE(  a1.GetCount() == 1 );
    ASSERT_FALSE( a2.IsValid() );
}

TEST( CFPP_Array, OperatorLeftShiftString )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( nullptr ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_TRUE(  a1.GetCount() == 0 );
    
    a1 << CF::String( "hello, world" );
    a2 << CF::String( "hello, world" );
    
    ASSERT_TRUE(  a1.GetCount() == 1 );
    ASSERT_FALSE( a2.IsValid() );
}

TEST( CFPP_Array, OperatorLeftShiftNumber )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( nullptr ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_TRUE(  a1.GetCount() == 0 );
    
    a1 << CF::Number( 42 );
    a2 << CF::Number( 42 );
    
    ASSERT_TRUE(  a1.GetCount() == 1 );
    ASSERT_FALSE( a2.IsValid() );
}

TEST( CFPP_Array, OperatorSubscript )
{
    CF::Array a1;
    CF::Array a2;
    CF::Array a3( static_cast< CFArrayRef >( nullptr ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_TRUE(  a2.IsValid() );
    ASSERT_FALSE( a3.IsValid() );
    
    a1 << CF::String( "hello, world" );
    
    ASSERT_TRUE( a1.GetCount() == 1 );
    ASSERT_TRUE( a2.GetCount() == 0 );
    
    ASSERT_NO_FATAL_FAILURE( a2[ 0 ] );
    ASSERT_NO_FATAL_FAILURE( a3[ 0 ] );
    ASSERT_NO_THROW( a2[ 0 ] );
    ASSERT_NO_THROW( a3[ 0 ] );
    
    ASSERT_TRUE( a1[ 0 ] != nullptr );
    ASSERT_TRUE( a1[ 1 ] == nullptr );
    ASSERT_TRUE( a2[ 0 ] == nullptr );
    ASSERT_TRUE( a3[ 0 ] == nullptr );
    
    ASSERT_EQ( CFGetTypeID( a1[ 0 ] ), CFStringGetTypeID() );
}

TEST( CFPP_Array, GetTypeID )
{
    CF::Array a;
    
    ASSERT_EQ( a.GetTypeID(), CFArrayGetTypeID() );
}

TEST( CFPP_Array, GetCFObject )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( nullptr ) );
    
    ASSERT_TRUE( a1.GetCFObject() != nullptr );
    ASSERT_TRUE( a2.GetCFObject() == nullptr );
    ASSERT_EQ( CFGetTypeID( a1.GetCFObject() ), CFArrayGetTypeID() );
}

TEST( CFPP_Array, GetCount )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( nullptr ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    
    ASSERT_TRUE( a1.GetCount() == 0 );
    ASSERT_TRUE( a2.GetCount() == 0 );
    
    a1 << CF::String( "hello, world" );
    a2 << CF::String( "hello, world" );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    
    ASSERT_TRUE( a1.GetCount() == 1 );
    ASSERT_TRUE( a2.GetCount() == 0 );
    
    a1.RemoveAllValues();
    a2.RemoveAllValues();
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    
    ASSERT_TRUE( a1.GetCount() == 0 );
    ASSERT_TRUE( a2.GetCount() == 0 );
}

TEST( CFPP_Array, ContainsValue )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( nullptr ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    
    a1 << CF::String( "hello, world" );
    a1 << CF::Number( 42 );
    
    ASSERT_TRUE(  a1.ContainsValue( CF::String( "hello, world" ) ) );
    ASSERT_TRUE(  a1.ContainsValue( CF::Number( 42 ) ) );
    ASSERT_FALSE( a2.ContainsValue( CF::String( "hello, world" ) ) );
    ASSERT_FALSE( a2.ContainsValue( CF::Number( 42 ) ) );
    ASSERT_FALSE( a1.ContainsValue( CF::String( "hello, universe" ) ) );
    ASSERT_FALSE( a1.ContainsValue( CF::Number( 43 ) ) );
}

TEST( CFPP_Array, RemoveAllValues )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( nullptr ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    
    a1 << CF::String( "hello, world" );
    a1 << CF::Number( 42 );
    a1 << CF::String( "hello, universe" );
    
    a2 << CF::String( "hello, world" );
    a2 << CF::Number( 42 );
    a2 << CF::String( "hello, universe" );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_TRUE(  a1.GetCount() == 3 );
    
    a1.RemoveAllValues();
    a2.RemoveAllValues();
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_TRUE(  a1.GetCount() == 0 );
    
    a1.RemoveAllValues();
    a2.RemoveAllValues();
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_TRUE(  a1.GetCount() == 0 );
}

TEST( CFPP_Array, GetValueAtIndex )
{
    CF::Array a1;
    CF::Array a2;
    CF::Array a3( static_cast< CFArrayRef >( nullptr ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_TRUE(  a2.IsValid() );
    ASSERT_FALSE( a3.IsValid() );
    
    a1 << CF::String( "hello, world" );
    
    ASSERT_TRUE(  a1.GetCount() == 1 );
    ASSERT_TRUE(  a2.GetCount() == 0 );
    
    ASSERT_NO_FATAL_FAILURE( a2.GetValueAtIndex( 0 ) );
    ASSERT_NO_FATAL_FAILURE( a3.GetValueAtIndex( 0 ) );
    ASSERT_NO_THROW( a2.GetValueAtIndex( 0 ) );
    ASSERT_NO_THROW( a3.GetValueAtIndex( 0 ) );
    
    ASSERT_TRUE( a1.GetValueAtIndex( 0 ) != nullptr );
    ASSERT_TRUE( a1.GetValueAtIndex( 1 ) == nullptr );
    ASSERT_TRUE( a2.GetValueAtIndex( 0 ) == nullptr );
    ASSERT_TRUE( a3.GetValueAtIndex( 0 ) == nullptr );
    
    ASSERT_EQ( CFGetTypeID( a1.GetValueAtIndex( 0 ) ), CFStringGetTypeID() );
}

TEST( CFPP_Array, SetValueAtIndex )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( nullptr ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_TRUE(  a1.GetCount() == 0 );
    
    ASSERT_NO_FATAL_FAILURE( a1.SetValueAtIndex( CF::String( "hello, world" ), 1 ) );
    ASSERT_NO_FATAL_FAILURE( a2.SetValueAtIndex( CF::String( "hello, world" ), 0 ) );
    ASSERT_NO_THROW( a1.SetValueAtIndex( CF::String( "hello, world" ), 1 ) );
    ASSERT_NO_THROW( a2.SetValueAtIndex( CF::String( "hello, world" ), 0 ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_TRUE(  a1.GetCount() == 0 );
    
    a1.SetValueAtIndex( CF::String( "hello, world" ), 0 );
    
    ASSERT_TRUE( a1.GetCount() == 1 );
    
    a1.SetValueAtIndex( CF::String( "hello, universe" ), 0 );
    a1.SetValueAtIndex( CF::String( "hello, world" ), 1 );
    
    ASSERT_TRUE( a1.GetCount() == 2 );
    
    ASSERT_TRUE( CF::String( a1[ 0 ] ) == "hello, universe" );
    ASSERT_TRUE( CF::String( a1[ 1 ] ) == "hello, world" );
}

TEST( CFPP_Array, InsertValueAtIndex )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( nullptr ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_TRUE(  a1.GetCount() == 0 );
    
    ASSERT_NO_FATAL_FAILURE( a1.InsertValueAtIndex( CF::String( "hello, world" ), 1 ) );
    ASSERT_NO_FATAL_FAILURE( a2.InsertValueAtIndex( CF::String( "hello, world" ), 0 ) );
    ASSERT_NO_THROW( a1.InsertValueAtIndex( CF::String( "hello, world" ), 1 ) );
    ASSERT_NO_THROW( a2.InsertValueAtIndex( CF::String( "hello, world" ), 0 ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_TRUE(  a1.GetCount() == 0 );
    
    a1.InsertValueAtIndex( CF::String( "hello, world" ), 0 );
    
    ASSERT_TRUE( a1.GetCount() == 1 );
    
    a1.InsertValueAtIndex( CF::String( "hello, universe" ), 0 );
    
    ASSERT_TRUE( a1.GetCount() == 2 );
    
    ASSERT_TRUE( CF::String( a1[ 0 ] ) == "hello, universe" );
    ASSERT_TRUE( CF::String( a1[ 1 ] ) == "hello, world" );
}

TEST( CFPP_Array, AppendValue )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( nullptr ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_TRUE(  a1.GetCount() == 0 );
    
    a1.AppendValue( static_cast< CFTypeRef >( CF::String( "hello, world" ).GetCFObject() ) );
    a2.AppendValue( static_cast< CFTypeRef >( CF::String( "hello, world" ).GetCFObject() ) );
    
    ASSERT_TRUE(  a1.GetCount() == 1 );
    ASSERT_FALSE( a2.IsValid() );
}

TEST( CFPP_Array, RemoveValueAtIndex )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( nullptr ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_TRUE(  a1.GetCount() == 0 );
    
    a1 << "hello, world";
    a1 << "hello, universe";
    
    ASSERT_TRUE( a1.GetCount() == 2 );
    
    ASSERT_NO_FATAL_FAILURE( a1.RemoveValueAtIndex( 42 ) );
    ASSERT_NO_FATAL_FAILURE( a2.RemoveValueAtIndex( 0 ) );
    ASSERT_NO_THROW( a1.RemoveValueAtIndex( 42 ) );
    ASSERT_NO_THROW( a2.RemoveValueAtIndex( 0 ) );
    
    ASSERT_TRUE( a1.GetCount() == 2 );
    
    a1.RemoveValueAtIndex( 1 );
    
    ASSERT_TRUE( a1.GetCount() == 1 );
    
    a1.RemoveValueAtIndex( 0 );
    
    ASSERT_TRUE( a1.GetCount() == 0 );
    
    ASSERT_NO_FATAL_FAILURE( a1.RemoveValueAtIndex( 0 ) );
    ASSERT_NO_THROW( a1.RemoveValueAtIndex( 0 ) );
    
    ASSERT_TRUE( a1.GetCount() == 0 );
}

TEST( CFPP_Array, AppendArray )
{
    CF::Array a1;
    CF::Array a2;
    CF::Array a3( static_cast< CFArrayRef >( nullptr ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_TRUE(  a2.IsValid() );
    ASSERT_FALSE( a3.IsValid() );
    
    a1 << CF::String( "hello, world" );
    
    ASSERT_TRUE( a1.GetCount() == 1 );
    ASSERT_TRUE( a2.GetCount() == 0 );
    
    a1.AppendArray( a2 );
    
    ASSERT_TRUE( a1.GetCount() == 1 );
    ASSERT_TRUE( a2.GetCount() == 0 );
    
    a1.AppendArray( a1 );
    
    ASSERT_TRUE( a1.GetCount() == 2 );
    
    a1.AppendArray( a3 );
    
    ASSERT_TRUE( a1.GetCount() == 2 );
    
    a3.AppendArray( a1 );
    
    ASSERT_FALSE( a3.IsValid() );
}

TEST( CFPP_Array, ExchangeValuesAtIndices )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( nullptr ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_TRUE(  a1.GetCount() == 0 );
    
    a1 << "hello, world";
    a1 << "hello, universe";
    
    ASSERT_TRUE( a1.GetCount() == 2 );
    
    ASSERT_TRUE( CF::String( a1[ 0 ] ) == "hello, world" );
    ASSERT_TRUE( CF::String( a1[ 1 ] ) == "hello, universe" );
    
    a1.ExchangeValuesAtIndices( 0, 1 );
    
    ASSERT_TRUE( CF::String( a1[ 0 ] ) == "hello, universe" );
    ASSERT_TRUE( CF::String( a1[ 1 ] ) == "hello, world" );
    
    ASSERT_NO_FATAL_FAILURE( a1.ExchangeValuesAtIndices( 42, 43 ) );
    ASSERT_NO_FATAL_FAILURE( a1.ExchangeValuesAtIndices(  0,  2 ) );
    ASSERT_NO_FATAL_FAILURE( a2.ExchangeValuesAtIndices(  0,  1 ) );
    ASSERT_NO_THROW( a1.ExchangeValuesAtIndices( 42, 43 ) );
    ASSERT_NO_THROW( a1.ExchangeValuesAtIndices(  0,  2 ) );
    ASSERT_NO_THROW( a2.ExchangeValuesAtIndices(  0,  1 ) );
    
    ASSERT_TRUE( CF::String( a1[ 0 ] ) == "hello, universe" );
    ASSERT_TRUE( CF::String( a1[ 1 ] ) == "hello, world" );
}

TEST( CFPP_Array, Swap )
{
    CF::Array a1;
    CF::Array a2;
    
    a1 << "hello";
    a1 << "world";
    
    ASSERT_EQ( a1.GetCount(), 2 );
    ASSERT_EQ( a2.GetCount(), 0 );
    
    swap( a1, a2 );
    
    ASSERT_EQ( a1.GetCount(), 0 );
    ASSERT_EQ( a2.GetCount(), 2 );
}
