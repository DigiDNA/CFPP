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
 * @header      CFPP-RunLoopObserver.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFRunLoopObserverRef wrapper
 */

#ifndef CFPP_RUN_LOOP_OBSERVER_HPP
#define CFPP_RUN_LOOP_OBSERVER_HPP

namespace CF
{
    class CFPP_EXPORT RunLoopObserver: public Type
    {
        public:
            
            RunLoopObserver( const RunLoopObserver & value );
            RunLoopObserver( const AutoPointer & value );
            RunLoopObserver( CFTypeRef cfObject );
            RunLoopObserver( CFRunLoopObserverRef cfObject );
            RunLoopObserver( RunLoopObserver && value ) noexcept;
            
            ~RunLoopObserver() override;
            
            RunLoopObserver & operator =( RunLoopObserver value );
            RunLoopObserver & operator =( const AutoPointer & value );
            RunLoopObserver & operator =( CFTypeRef value );
            RunLoopObserver & operator =( CFRunLoopObserverRef value );
            
            CFTypeID  GetTypeID()   const override;
            CFTypeRef GetCFObject() const override;
            
            friend void swap( RunLoopObserver & v1, RunLoopObserver & v2 ) noexcept;
            
        private:
            
            CFRunLoopObserverRef _cfObject;
    };
}

#endif /* CFPP_RUN_LOOP_OBSERVER_HPP */
