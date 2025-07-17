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
 * @header      CFPP-Date.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFDateRef wrapper
 */

#ifndef CFPP_DATE_HPP
#define CFPP_DATE_HPP

namespace CF
{
    class CFPP_EXPORT Date: public PropertyListType< Date >
    {
        public:
            
            static Date CurrentDate();
            
            Date();
            Date( const Date & value );
            Date( const AutoPointer & value );
            Date( CFTypeRef value );
            Date( CFDateRef value );
            Date( std::nullptr_t );
            Date( CFAbsoluteTime value );
            Date( Date && value ) noexcept;
            
            ~Date() override;
            
            Date & operator =( Date value );
            Date & operator =( const AutoPointer & value );
            Date & operator =( CFTypeRef value );
            Date & operator =( CFDateRef value );
            Date & operator =( std::nullptr_t );
            Date & operator =( CFAbsoluteTime value );
            
            bool operator == ( const Date & value )   const;
            bool operator == ( CFTypeRef value )      const;
            bool operator == ( CFDateRef value )      const;
            bool operator == ( CFAbsoluteTime value ) const;
            
            bool operator != ( const Date & value )   const;
            bool operator != ( CFTypeRef value )      const;
            bool operator != ( CFDateRef value )      const;
            bool operator != ( CFAbsoluteTime value ) const;
            
            bool operator >= ( const Date & value )   const;
            bool operator >= ( CFDateRef value )      const;
            bool operator >= ( CFAbsoluteTime value ) const;
            
            bool operator <= ( const Date & value )   const;
            bool operator <= ( CFDateRef value )      const;
            bool operator <= ( CFAbsoluteTime value ) const;
            
            bool operator >( const Date & value )   const;
            bool operator >( CFDateRef value )      const;
            bool operator >( CFAbsoluteTime value ) const;
            
            bool operator <( const Date & value )   const;
            bool operator <( CFDateRef value )      const;
            bool operator <( CFAbsoluteTime value ) const;
            
            Date & operator += ( const Date & value );
            Date & operator += ( CFDateRef value );
            Date & operator += ( CFAbsoluteTime value );
            
            Date & operator -= ( const Date & value );
            Date & operator -= ( CFDateRef value );
            Date & operator -= ( CFAbsoluteTime value );
            
            Date operator +( const Date & value );
            Date operator +( CFDateRef value );
            Date operator +( CFAbsoluteTime value );
            
            Date operator -( const Date & value );
            Date operator -( CFDateRef value );
            Date operator -( CFAbsoluteTime value );
            
            Date & operator ++ ();
            Date   operator ++ ( int );
            Date & operator -- ();
            Date   operator -- ( int );
            
            operator CFAbsoluteTime () const;
            
            CFTypeID  GetTypeID()   const override;
            CFTypeRef GetCFObject() const override;
            
            CFAbsoluteTime GetValue() const;
            void           SetValue( CFAbsoluteTime value );
            
            friend void swap( Date & v1, Date & v2 ) noexcept;
            
        protected:
            
            CFDateRef _cfObject;
    };
}

#endif /* CFPP_DATE_HPP */
