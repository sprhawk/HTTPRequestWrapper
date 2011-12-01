//
//Copyright (c) 2011, Hongbo Yang (hongbo@yang.me)
//All rights reserved.
//
//1. Redistribution and use in source and binary forms, with or without modification, are permitted 
//provided that the following conditions are met:
//
//2. Redistributions of source code must retain the above copyright notice, this list of conditions 
//and 
//the following disclaimer.
//
//3. Redistributions in binary form must reproduce the above copyright notice, this list of conditions
//and the following disclaimer in the documentation and/or other materials provided with the 
//distribution.
//
//Neither the name of the Hongbo Yang nor the names of its contributors may be used to endorse or 
//promote products derived from this software without specific prior written permission.
//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
//IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
//FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
//CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
//DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
//DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER 
//IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
//OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#import <Foundation/Foundation.h>
#import "HTTPRequestProtocols.h"
#import "ASIFormDataRequest.h"

@interface ASIHTTPRequestWrapper : NSObject <HTTPRequestLevel1Protocol, ASIHTTPRequestDelegate>

@property (atomic, assign, readwrite) HTTPRequestLevel1Delegate delegate;
@property (atomic, retain, readonly) ASIHTTPRequest * request;

- (void)setHTTPBodyStream:(NSInputStream *)bodyStream UNAVAILABLE;
- (NSInputStream *)HTTPBodyStream UNAVAILABLE;
- (void)setCachePolicy:(NSURLRequestCachePolicy)cachePolicy UNAVAILABLE;
- (NSURLRequestCachePolicy)cachePolicy UNAVAILABLE;
@end

@interface ASIFormDataRequestWrapper : ASIHTTPRequestWrapper <HTTPRequestLevel2Protocol, ASIHTTPRequestDelegate>
@property (atomic, retain, readonly) ASIFormDataRequest * request;
@property (atomic, assign, readwrite) HTTPRequestLevel2Delegate delegate;

@end
