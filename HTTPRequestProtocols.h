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

#ifndef __has_extension
#define __has_extension(x) 0
#endif

#if __has_extension(attribute_unavailable_with_message)
#define UNAVAILABLE __attribute__((unavailable))
#else
#define UNAVAILABLE
#endif


#pragma mark - Basic request protocol (Level 1)
@protocol HTTPRequestLevel1Protocol;
@protocol HTTPRequestLevel1DelegateProtocol;

typedef id<HTTPRequestLevel1Protocol> HTTPRequestLevel1;
typedef id<HTTPRequestLevel1DelegateProtocol> HTTPRequestLevel1Delegate;

@protocol HTTPRequestLevel1DelegateProtocol <NSObject>

@optional
- (void)requestDidFinishLoading:(HTTPRequestLevel1)request;
- (void)request:(HTTPRequestLevel1)request didFailWithError:(NSError *)error;
- (void)request:(HTTPRequestLevel1)request didReceiveResponseHeaders:(NSDictionary *)responseHeaders;
- (void)request:(HTTPRequestLevel1) didReceiveData:(NSData *)data;
@end

@protocol HTTPRequestLevel1Protocol <NSObject>
@required
+ (id)requestWithURL:(NSURL *)url;
- (id)initWithURL:(NSURL *)url;
- (void)setURL:(NSURL *)url;
- (NSURL *)URL;

- (void)setDelegate:(HTTPRequestLevel1Delegate)delegate;
- (HTTPRequestLevel1Delegate)delegate;

- (void)setHTTPMethod:(NSString *)method;
- (NSString *)HTTPMethod;

- (void)setHTTPBody:(NSData *)body;
- (NSData *)HTTPBody;

- (void)setHTTPBodyStream:(NSInputStream*)bodyStream;
- (NSInputStream *)HTTPBodyStream;

- (void)appendBodyData:(NSData *)data;

- (void)setValue:(NSString *)value forHTTPHeaderField:(NSString *)field;
- (void)setAllHTTPHeaderFields:(NSDictionary *)headerFields;
- (NSString *)valueForHTTPHeaderField:(NSString *)field;
- (NSDictionary *)allHTTPHeaderFields;

- (NSData *)responseData;
- (NSString *)responseString;
- (NSDictionary *)responseHeaders;

- (NSError *)error;

- (id)internalRequest;

- (BOOL)startAsynchronous;
- (BOOL)startSynchronous;
- (void)cancel;


- (void)setCachePolicy:(NSURLRequestCachePolicy)cachePolicy;
- (NSURLRequestCachePolicy)cachePolicy;

@end

#pragma mark - Level2 request protocol for POST method

@protocol HTTPRequestLevel2Protocol;
typedef id<HTTPRequestLevel2Protocol> HTTPRequestLevel2;
@protocol HTTPRequestLevel2DelegateProtocol <HTTPRequestLevel1DelegateProtocol>
@optional
- (void)requestDidFinishLoading:(HTTPRequestLevel2)request;
- (void)request:(HTTPRequestLevel2)request didFailWithError:(NSError *)error;
- (void)request:(HTTPRequestLevel2)request didReceiveResponseHeaders:(NSDictionary *)responseHeaders;
- (void)request:(HTTPRequestLevel2) didReceiveData:(NSData *)data;
@end
typedef id<HTTPRequestLevel2DelegateProtocol> HTTPRequestLevel2Delegate;

@protocol HTTPRequestLevel2Protocol <HTTPRequestLevel1Protocol>

@required
- (void)setDelegate:(HTTPRequestLevel2Delegate)delegate;
- (HTTPRequestLevel2Delegate)delegate;

- (void)addPostValue:(id<NSObject>)value forKey:(NSString *)key;
- (void)setPostValue:(id<NSObject>)value forKey:(NSString *)key;

- (void)addData:(NSData *)data forKey:(NSString *)key;
- (void)addData:(id)data withFileName:(NSString *)fileName andContentType:(NSString *)contentType forKey:(NSString *)key;
- (void)setData:(NSData * )data forKey:(NSString *)key;
- (void)setData:(NSData * )data withFilename:(NSString*)name contentType:(NSString *)contentType forKey:(NSString *)key;

@end


typedef HTTPRequestLevel1 HTTPRequest;
typedef HTTPRequestLevel1Delegate HTTPRequestDelegate;

typedef HTTPRequestLevel2 HTTPRequest2;
typedef HTTPRequestLevel2Delegate HTTPRequest2Delegate;

#ifdef __cplusplus
extern "C"
#else
extern
#endif
id requestLevel1ForURL(NSURL *url);
id requestLevel2ForURL(NSURL *url);
