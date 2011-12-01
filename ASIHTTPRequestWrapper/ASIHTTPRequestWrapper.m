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

#import "ASIHTTPRequestWrapper.h"

id requestLevel1ForURL(NSURL *url)
{
    return [ASIHTTPRequestWrapper requestWithURL:url];
}

id requestLevel2ForURL(NSURL *url)
{
    return [ASIFormDataRequest requestWithURL:url];
}

@interface ASIHTTPRequestWrapper ()
@property (atomic, assign, readwrite) BOOL isSelfRetained;
@property (atomic, retain, readwrite) ASIHTTPRequest * request;
@end

@implementation ASIHTTPRequestWrapper

@synthesize isSelfRetained = _isSelfRetained;
@synthesize request = _request;
@synthesize delegate = _delegate;

+ (id)requestWithURL:(NSURL *)url
{
    return [[[[self class] alloc] initWithURL:url] autorelease];
}
- (id)initWithURL:(NSURL *)url
{
    if (url && (self = [super init])) {
        self.request = [ASIHTTPRequest requestWithURL:url];
        self.request.delegate = self;
    }
    return self;
}

- (void)dealloc
{
    self.request = nil;
    [super dealloc];
}

- (void)setURL:(NSURL *)url
{
    self.request.url = url;
}
- (NSURL *)URL
{
    return self.request.url;
}


- (void)setHTTPMethod:(NSString *)method
{
    [self.request setRequestMethod:method];
}
- (NSString *)HTTPMethod
{
    return [self.request requestMethod];
}

- (void)setHTTPBody:(NSData *)body
{
    NSMutableData * data = nil;
    if (![body isKindOfClass:[NSMutableData class]]) {
        data = [[body mutableCopy] autorelease];
    }
    else {
        data = (NSMutableData *)body;
    }
    [self.request setPostBody:data];
}

- (NSData *)HTTPBody
{
    return [self.request postBody];
}

- (void)appendBodyData:(NSData *)data 
{
    [self.request appendPostData:data];
}

- (NSInputStream *)HTTPBodyStream
{
    return nil;
}

- (void)setHTTPBodyStream:(NSInputStream*)bodyStream
{
    return;
}

- (void)setValue:(NSString *)value forHTTPHeaderField:(NSString *)field
{
    [self.request addRequestHeader:field value:value];
}
- (void)setAllHTTPHeaderFields:(NSDictionary *)headerFields
{
    NSMutableDictionary * headers = nil;
    if (![headerFields isKindOfClass:[NSMutableDictionary class]]) {
        headers = [[headerFields mutableCopy] autorelease];
    }
    else {
        headers = (NSMutableDictionary *)headerFields;
    }
    self.request.requestHeaders = headers;
}

- (NSString *)valueForHTTPHeaderField:(NSString *)field
{
    return [self.request.requestHeaders objectForKey:field];
}
- (NSDictionary *)allHTTPHeaderFields
{
    return self.request.requestHeaders;
}

- (NSData *)responseData
{
    return self.request.responseData;
}
- (NSString *)responseString
{
    return self.request.responseString;
}
- (NSDictionary *)responseHeaders
{
    return self.request.responseHeaders;
}

- (NSError *)error 
{
    return self.request.error;
}

- (id)internalRequest
{
    return self.request;
}

- (void)setIsSelfRetained:(BOOL)isSelfRetained
{
    @synchronized(self) {
        if (isSelfRetained != _isSelfRetained) {
            _isSelfRetained = isSelfRetained;
            if (_isSelfRetained) {
                [self retain];
            }
            else {
                [self release];
            }
        }
    }
}

- (BOOL)isSelfRetained {
    @synchronized(self) {
        return _isSelfRetained;
    }
}

- (BOOL)startAsynchronous
{
    self.isSelfRetained = YES;
    [self.request startAsynchronous];
    return TRUE;
}
- (BOOL)startSynchronous
{
    [self.request startSynchronous];
    return TRUE;
}

- (void)cancel
{
    self.isSelfRetained = NO;
}


- (void)setCachePolicy:(NSURLRequestCachePolicy)cachePolicy
{
    
}

- (NSURLRequestCachePolicy)cachePolicy {
    return NSURLRequestUseProtocolCachePolicy;
}
#pragma marm - handle ASIHTTPRequestDelegate
- (void)requestFailed:(ASIHTTPRequest *)request
{
    if ([self.delegate respondsToSelector:@selector(request:didFailWithError:)]) 
    {
        [self.delegate request:self didFailWithError:request.error];
    }
    self.isSelfRetained = NO;
}

- (void)requestFinished:(ASIHTTPRequest *)request
{
    if ([self.delegate respondsToSelector:@selector(request:didFailWithError:)]) 
    {
        [self.delegate requestDidFinishLoading:self];
    }
    self.isSelfRetained = NO;
}

@end

@interface ASIFormDataRequestWrapper ()
@property (atomic, assign, readwrite) BOOL isSelfRetained;
@property (atomic, retain, readwrite) ASIHTTPRequest * request;
@end

@implementation ASIFormDataRequestWrapper

@dynamic isSelfRetained;
@dynamic request;
@dynamic delegate;

- (id)initWithURL:(NSURL *)url
{
    if (url && (self = [super init])) {
        self.request = [ASIFormDataRequest requestWithURL:url];
        self.request.delegate = self;
    }
    return self;
}

#pragma mark - implement HTTPRequestLevel2Protocol
- (void)appendBodyData:(NSData *)data
{
    [self.request appendPostData:data];
}

- (void)addPostValue:(id<NSObject>)value forKey:(NSString *)key
{
    [self.request addPostValue:value forKey:key];
}
- (void)setPostValue:(id<NSObject>)value forKey:(NSString *)key
{
    [self.request setPostValue:value forKey:key];
}


- (void)addData:(NSData *)data forKey:(NSString *)key
{
    [self.request addData:data forKey:key];
}
- (void)addData:(id)data withFileName:(NSString *)fileName andContentType:(NSString *)contentType forKey:(NSString *)key
{
    [self.request addData:data withFileName:fileName andContentType:contentType forKey:key];
}
- (void)setData:(NSData * )data forKey:(NSString *)key
{
    [self.request setData:data forKey:key];
}
- (void)setData:(NSData * )data withFilename:(NSString*)name contentType:(NSString *)contentType forKey:(NSString *)key
{
    [self.request setData:data withFileName:name andContentType:contentType forKey:key];
}

@end
