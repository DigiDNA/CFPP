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
 * @header      CFPP-RunLoopSource.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFRunLoopSourceRef wrapper
 */

#ifndef CFPP_RUN_LOOP_SOURCE_HPP
#define CFPP_RUN_LOOP_SOURCE_HPP

namespace CF
{
    class RunLoop;
    
    class CFPP_EXPORT RunLoopSource: public Type
    {
        public:
            
            RunLoopSource( CFIndex order, const std::function< void() > & perform, const std::function< void( RunLoop &, CFRunLoopMode ) > & schedule = nullptr, const std::function< void( RunLoop &, CFRunLoopMode ) > & cancel = nullptr );
            RunLoopSource( CFIndex order, CFRunLoopSourceContext * context );
            RunLoopSource( const RunLoopSource & value );
            RunLoopSource( const AutoPointer & value );
            RunLoopSource( CFTypeRef cfObject );
            RunLoopSource( CFRunLoopSourceRef cfObject );
            RunLoopSource( RunLoopSource && value ) noexcept;
            
            ~RunLoopSource() override;
            
            RunLoopSource & operator =( RunLoopSource value );
            RunLoopSource & operator =( const AutoPointer & value );
            RunLoopSource & operator =( CFTypeRef value );
            RunLoopSource & operator =( CFRunLoopSourceRef value );
            
            CFTypeID  GetTypeID()   const override;
            CFTypeRef GetCFObject() const override;
            
            bool    IsSourceValid()                                const;
            CFIndex GetOrder()                                     const;
            void    GetContext( CFRunLoopSourceContext * context ) const;
            
            void Invalidate();
            void Signal();
            
            friend void swap( RunLoopSource & v1, RunLoopSource & v2 ) noexcept;
            
        private:
            
            CFRunLoopSourceRef _cfObject;
    };
}

#endif /* CFPP_RUN_LOOP_SOURCE_HPP */
