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
 * @header      CFPP-RunLoopSourceInfo.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Convenience for CF::RunLoopSouce context's info
 */

#ifndef CFPP_RUN_LOOP_SOURCE_INFO_HPP
#define CFPP_RUN_LOOP_SOURCE_INFO_HPP

namespace CF
{
    class RunLoop;
    
    class RunLoopSourceInfo
    {
        public:
            
            static CFRunLoopSourceContext CreateContext( const std::function< void() > & perform, const std::function< void( RunLoop &, CFRunLoopMode ) > & schedule, const std::function< void( RunLoop &, CFRunLoopMode ) > & cancel );
            
            RunLoopSourceInfo( const RunLoopSourceInfo & )              = delete;
            RunLoopSourceInfo & operator =( const RunLoopSourceInfo & ) = delete;
            
        private:
            
            RunLoopSourceInfo( const std::function< void() > & perform, const std::function< void( RunLoop &, CFRunLoopMode ) > & schedule, const std::function< void( RunLoop &, CFRunLoopMode ) > & cancel );
            
            virtual ~RunLoopSourceInfo();
            
            static void _Perform(  void * info );
            static void _Schedule( void * info, CFRunLoopRef rl, CFRunLoopMode mode );
            static void _Cancel(   void * info, CFRunLoopRef rl, CFRunLoopMode mode );
            
            static const void * _Retain( const void * info );
            static void         _Release( const void * info );
            
            size_t                                            _rc;
            std::function< void() >                           _perform;
            std::function< void( RunLoop &, CFRunLoopMode ) > _schedule;
            std::function< void( RunLoop &, CFRunLoopMode ) > _cancel;
    };
}

#endif /* CFPP_RUN_LOOP_SOURCE_INFO_HPP */
