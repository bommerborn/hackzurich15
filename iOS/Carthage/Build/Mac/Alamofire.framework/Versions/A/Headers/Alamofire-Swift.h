// Generated by Apple Swift version 2.1 (swiftlang-700.1.100.4 clang-700.1.75)
#pragma clang diagnostic push

#if defined(__has_include) && __has_include(<swift/objc-prologue.h>)
# include <swift/objc-prologue.h>
#endif

#pragma clang diagnostic ignored "-Wauto-import"
#include <objc/NSObject.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#if defined(__has_include) && __has_include(<uchar.h>)
# include <uchar.h>
#elif !defined(__cplusplus) || __cplusplus < 201103L
typedef uint_least16_t char16_t;
typedef uint_least32_t char32_t;
#endif

typedef struct _NSZone NSZone;

#if !defined(SWIFT_PASTE)
# define SWIFT_PASTE_HELPER(x, y) x##y
# define SWIFT_PASTE(x, y) SWIFT_PASTE_HELPER(x, y)
#endif
#if !defined(SWIFT_METATYPE)
# define SWIFT_METATYPE(X) Class
#endif

#if defined(__has_attribute) && __has_attribute(objc_runtime_name)
# define SWIFT_RUNTIME_NAME(X) __attribute__((objc_runtime_name(X)))
#else
# define SWIFT_RUNTIME_NAME(X)
#endif
#if defined(__has_attribute) && __has_attribute(swift_name)
# define SWIFT_COMPILE_NAME(X) __attribute__((swift_name(X)))
#else
# define SWIFT_COMPILE_NAME(X)
#endif
#if !defined(SWIFT_CLASS_EXTRA)
# define SWIFT_CLASS_EXTRA
#endif
#if !defined(SWIFT_PROTOCOL_EXTRA)
# define SWIFT_PROTOCOL_EXTRA
#endif
#if !defined(SWIFT_ENUM_EXTRA)
# define SWIFT_ENUM_EXTRA
#endif
#if !defined(SWIFT_CLASS)
# if defined(__has_attribute) && __has_attribute(objc_subclassing_restricted) 
#  define SWIFT_CLASS(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) __attribute__((objc_subclassing_restricted)) SWIFT_CLASS_EXTRA
#  define SWIFT_CLASS_NAMED(SWIFT_NAME) __attribute__((objc_subclassing_restricted)) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
# else
#  define SWIFT_CLASS(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
#  define SWIFT_CLASS_NAMED(SWIFT_NAME) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
# endif
#endif

#if !defined(SWIFT_PROTOCOL)
# define SWIFT_PROTOCOL(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) SWIFT_PROTOCOL_EXTRA
# define SWIFT_PROTOCOL_NAMED(SWIFT_NAME) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_PROTOCOL_EXTRA
#endif

#if !defined(SWIFT_EXTENSION)
# define SWIFT_EXTENSION(M) SWIFT_PASTE(M##_Swift_, __LINE__)
#endif

#if !defined(OBJC_DESIGNATED_INITIALIZER)
# if defined(__has_attribute) && __has_attribute(objc_designated_initializer)
#  define OBJC_DESIGNATED_INITIALIZER __attribute__((objc_designated_initializer))
# else
#  define OBJC_DESIGNATED_INITIALIZER
# endif
#endif
#if !defined(SWIFT_ENUM)
# define SWIFT_ENUM(_type, _name) enum _name : _type _name; enum SWIFT_ENUM_EXTRA _name : _type
#endif
typedef float swift_float2  __attribute__((__ext_vector_type__(2)));
typedef float swift_float3  __attribute__((__ext_vector_type__(3)));
typedef float swift_float4  __attribute__((__ext_vector_type__(4)));
typedef double swift_double2  __attribute__((__ext_vector_type__(2)));
typedef double swift_double3  __attribute__((__ext_vector_type__(3)));
typedef double swift_double4  __attribute__((__ext_vector_type__(4)));
typedef int swift_int2  __attribute__((__ext_vector_type__(2)));
typedef int swift_int3  __attribute__((__ext_vector_type__(3)));
typedef int swift_int4  __attribute__((__ext_vector_type__(4)));
#if defined(__has_feature) && __has_feature(modules)
@import Foundation;
@import Foundation.NSURLSession;
@import ObjectiveC;
#endif

#pragma clang diagnostic ignored "-Wproperty-attribute-mismatch"
#pragma clang diagnostic ignored "-Wduplicate-method-arg"

@interface NSURL (SWIFT_EXTENSION(Alamofire))
@property (nonatomic, readonly, copy) NSString * __nonnull URLString;
@end


@interface NSURLComponents (SWIFT_EXTENSION(Alamofire))
@property (nonatomic, readonly, copy) NSString * __nonnull URLString;
@end

@class NSMutableURLRequest;

@interface NSURLRequest (SWIFT_EXTENSION(Alamofire))
@property (nonatomic, readonly, strong) NSMutableURLRequest * __nonnull URLRequest;
@end


@interface NSURLRequest (SWIFT_EXTENSION(Alamofire))
@property (nonatomic, readonly, copy) NSString * __nonnull URLString;
@end


@interface NSURLSession (SWIFT_EXTENSION(Alamofire))
@end

@class NSURLSessionTask;
@class TaskDelegate;
@class NSError;
@class NSURLAuthenticationChallenge;
@class NSURLCredential;
@class NSHTTPURLResponse;
@class NSInputStream;
@class NSURLSessionDataTask;
@class NSURLResponse;
@class NSURLSessionDownloadTask;
@class NSData;
@class NSCachedURLResponse;


/// Responsible for handling all delegate callbacks for the underlying session.
SWIFT_CLASS("_TtCC9Alamofire7Manager15SessionDelegate")
@interface SessionDelegate : NSObject <NSURLSessionDelegate, NSURLSessionTaskDelegate, NSURLSessionDataDelegate, NSURLSessionDownloadDelegate>
- (TaskDelegate * __nullable)objectForKeyedSubscript:(NSURLSessionTask * __nonnull)task;
- (void)setObject:(TaskDelegate * __nullable)newValue forKeyedSubscript:(NSURLSessionTask * __nonnull)task;

/// Overrides default behavior for NSURLSessionDelegate method URLSession:didBecomeInvalidWithError:.
@property (nonatomic, copy) void (^ __nullable sessionDidBecomeInvalidWithError)(NSURLSession * __nonnull, NSError * __nullable);

/// Overrides default behavior for NSURLSessionDelegate method URLSessionDidFinishEventsForBackgroundURLSession:.
@property (nonatomic, copy) void (^ __nullable sessionDidFinishEventsForBackgroundURLSession)(NSURLSession * __nonnull);

/// Tells the delegate that the session has been invalidated.
///
/// \param session The session object that was invalidated.
///
/// \param error The error that caused invalidation, or nil if the invalidation was explicit.
- (void)URLSession:(NSURLSession * __nonnull)session didBecomeInvalidWithError:(NSError * __nullable)error;

/// Requests credentials from the delegate in response to a session-level authentication request from the remote server.
///
/// \param session The session containing the task that requested authentication.
///
/// \param challenge An object that contains the request for authentication.
///
/// \param completionHandler A handler that your delegate method must call providing the disposition and credential.
- (void)URLSession:(NSURLSession * __nonnull)session didReceiveChallenge:(NSURLAuthenticationChallenge * __nonnull)challenge completionHandler:(void (^ __nonnull)(NSURLSessionAuthChallengeDisposition, NSURLCredential * __nullable))completionHandler;

/// Tells the delegate that all messages enqueued for a session have been delivered.
///
/// \param session The session that no longer has any outstanding requests.
- (void)URLSessionDidFinishEventsForBackgroundURLSession:(NSURLSession * __nonnull)session;

/// Overrides default behavior for NSURLSessionTaskDelegate method URLSession:task:willPerformHTTPRedirection:newRequest:completionHandler:.
@property (nonatomic, copy) NSURLRequest * __nullable (^ __nullable taskWillPerformHTTPRedirection)(NSURLSession * __nonnull, NSURLSessionTask * __nonnull, NSHTTPURLResponse * __nonnull, NSURLRequest * __nonnull);

/// Overrides default behavior for NSURLSessionTaskDelegate method URLSession:session:task:needNewBodyStream:.
@property (nonatomic, copy) NSInputStream * __null_unspecified (^ __nullable taskNeedNewBodyStream)(NSURLSession * __nonnull, NSURLSessionTask * __nonnull);

/// Overrides default behavior for NSURLSessionTaskDelegate method URLSession:task:didSendBodyData:totalBytesSent:totalBytesExpectedToSend:.
@property (nonatomic, copy) void (^ __nullable taskDidSendBodyData)(NSURLSession * __nonnull, NSURLSessionTask * __nonnull, int64_t, int64_t, int64_t);

/// Overrides default behavior for NSURLSessionTaskDelegate method URLSession:task:didCompleteWithError:.
@property (nonatomic, copy) void (^ __nullable taskDidComplete)(NSURLSession * __nonnull, NSURLSessionTask * __nonnull, NSError * __nullable);

/// Tells the delegate that the remote server requested an HTTP redirect.
///
/// \param session The session containing the task whose request resulted in a redirect.
///
/// \param task The task whose request resulted in a redirect.
///
/// \param response An object containing the server’s response to the original request.
///
/// \param request A URL request object filled out with the new location.
///
/// \param completionHandler A closure that your handler should call with either the value of the request
/// parameter, a modified URL request object, or NULL to refuse the redirect and
/// return the body of the redirect response.
- (void)URLSession:(NSURLSession * __nonnull)session task:(NSURLSessionTask * __nonnull)task willPerformHTTPRedirection:(NSHTTPURLResponse * __nonnull)response newRequest:(NSURLRequest * __nonnull)request completionHandler:(void (^ __nonnull)(NSURLRequest * __nullable))completionHandler;

/// Requests credentials from the delegate in response to an authentication request from the remote server.
///
/// \param session The session containing the task whose request requires authentication.
///
/// \param task The task whose request requires authentication.
///
/// \param challenge An object that contains the request for authentication.
///
/// \param completionHandler A handler that your delegate method must call providing the disposition and credential.
- (void)URLSession:(NSURLSession * __nonnull)session task:(NSURLSessionTask * __nonnull)task didReceiveChallenge:(NSURLAuthenticationChallenge * __nonnull)challenge completionHandler:(void (^ __nonnull)(NSURLSessionAuthChallengeDisposition, NSURLCredential * __nullable))completionHandler;

/// Tells the delegate when a task requires a new request body stream to send to the remote server.
///
/// \param session The session containing the task that needs a new body stream.
///
/// \param task The task that needs a new body stream.
///
/// \param completionHandler A completion handler that your delegate method should call with the new body stream.
- (void)URLSession:(NSURLSession * __nonnull)session task:(NSURLSessionTask * __nonnull)task needNewBodyStream:(void (^ __nonnull)(NSInputStream * __nullable))completionHandler;

/// Periodically informs the delegate of the progress of sending body content to the server.
///
/// \param session The session containing the data task.
///
/// \param task The data task.
///
/// \param bytesSent The number of bytes sent since the last time this delegate method was called.
///
/// \param totalBytesSent The total number of bytes sent so far.
///
/// \param totalBytesExpectedToSend The expected length of the body data.
- (void)URLSession:(NSURLSession * __nonnull)session task:(NSURLSessionTask * __nonnull)task didSendBodyData:(int64_t)bytesSent totalBytesSent:(int64_t)totalBytesSent totalBytesExpectedToSend:(int64_t)totalBytesExpectedToSend;

/// Tells the delegate that the task finished transferring data.
///
/// \param session The session containing the task whose request finished transferring data.
///
/// \param task The task whose request finished transferring data.
///
/// \param error If an error occurred, an error object indicating how the transfer failed, otherwise nil.
- (void)URLSession:(NSURLSession * __nonnull)session task:(NSURLSessionTask * __nonnull)task didCompleteWithError:(NSError * __nullable)error;

/// Overrides default behavior for NSURLSessionDataDelegate method URLSession:dataTask:didReceiveResponse:completionHandler:.
@property (nonatomic, copy) NSURLSessionResponseDisposition (^ __nullable dataTaskDidReceiveResponse)(NSURLSession * __nonnull, NSURLSessionDataTask * __nonnull, NSURLResponse * __nonnull);

/// Overrides default behavior for NSURLSessionDataDelegate method URLSession:dataTask:didBecomeDownloadTask:.
@property (nonatomic, copy) void (^ __nullable dataTaskDidBecomeDownloadTask)(NSURLSession * __nonnull, NSURLSessionDataTask * __nonnull, NSURLSessionDownloadTask * __nonnull);

/// Overrides default behavior for NSURLSessionDataDelegate method URLSession:dataTask:didReceiveData:.
@property (nonatomic, copy) void (^ __nullable dataTaskDidReceiveData)(NSURLSession * __nonnull, NSURLSessionDataTask * __nonnull, NSData * __nonnull);

/// Overrides default behavior for NSURLSessionDataDelegate method URLSession:dataTask:willCacheResponse:completionHandler:.
@property (nonatomic, copy) NSCachedURLResponse * __null_unspecified (^ __nullable dataTaskWillCacheResponse)(NSURLSession * __nonnull, NSURLSessionDataTask * __nonnull, NSCachedURLResponse * __nonnull);

/// Tells the delegate that the data task received the initial reply (headers) from the server.
///
/// \param session The session containing the data task that received an initial reply.
///
/// \param dataTask The data task that received an initial reply.
///
/// \param response A URL response object populated with headers.
///
/// \param completionHandler A completion handler that your code calls to continue the transfer, passing a
/// constant to indicate whether the transfer should continue as a data task or
/// should become a download task.
- (void)URLSession:(NSURLSession * __nonnull)session dataTask:(NSURLSessionDataTask * __nonnull)dataTask didReceiveResponse:(NSURLResponse * __nonnull)response completionHandler:(void (^ __nonnull)(NSURLSessionResponseDisposition))completionHandler;

/// Tells the delegate that the data task was changed to a download task.
///
/// \param session The session containing the task that was replaced by a download task.
///
/// \param dataTask The data task that was replaced by a download task.
///
/// \param downloadTask The new download task that replaced the data task.
- (void)URLSession:(NSURLSession * __nonnull)session dataTask:(NSURLSessionDataTask * __nonnull)dataTask didBecomeDownloadTask:(NSURLSessionDownloadTask * __nonnull)downloadTask;

/// Tells the delegate that the data task has received some of the expected data.
///
/// \param session The session containing the data task that provided data.
///
/// \param dataTask The data task that provided data.
///
/// \param data A data object containing the transferred data.
- (void)URLSession:(NSURLSession * __nonnull)session dataTask:(NSURLSessionDataTask * __nonnull)dataTask didReceiveData:(NSData * __nonnull)data;

/// Asks the delegate whether the data (or upload) task should store the response in the cache.
///
/// \param session The session containing the data (or upload) task.
///
/// \param dataTask The data (or upload) task.
///
/// \param proposedResponse The default caching behavior. This behavior is determined based on the current
/// caching policy and the values of certain received headers, such as the Pragma
/// and Cache-Control headers.
///
/// \param completionHandler A block that your handler must call, providing either the original proposed
/// response, a modified version of that response, or NULL to prevent caching the
/// response. If your delegate implements this method, it must call this completion
/// handler; otherwise, your app leaks memory.
- (void)URLSession:(NSURLSession * __nonnull)session dataTask:(NSURLSessionDataTask * __nonnull)dataTask willCacheResponse:(NSCachedURLResponse * __nonnull)proposedResponse completionHandler:(void (^ __nonnull)(NSCachedURLResponse * __nullable))completionHandler;

/// Overrides default behavior for NSURLSessionDownloadDelegate method URLSession:downloadTask:didFinishDownloadingToURL:.
@property (nonatomic, copy) void (^ __nullable downloadTaskDidFinishDownloadingToURL)(NSURLSession * __nonnull, NSURLSessionDownloadTask * __nonnull, NSURL * __nonnull);

/// Overrides default behavior for NSURLSessionDownloadDelegate method URLSession:downloadTask:didWriteData:totalBytesWritten:totalBytesExpectedToWrite:.
@property (nonatomic, copy) void (^ __nullable downloadTaskDidWriteData)(NSURLSession * __nonnull, NSURLSessionDownloadTask * __nonnull, int64_t, int64_t, int64_t);

/// Overrides default behavior for NSURLSessionDownloadDelegate method URLSession:downloadTask:didResumeAtOffset:expectedTotalBytes:.
@property (nonatomic, copy) void (^ __nullable downloadTaskDidResumeAtOffset)(NSURLSession * __nonnull, NSURLSessionDownloadTask * __nonnull, int64_t, int64_t);

/// Tells the delegate that a download task has finished downloading.
///
/// \param session The session containing the download task that finished.
///
/// \param downloadTask The download task that finished.
///
/// \param location A file URL for the temporary file. Because the file is temporary, you must either
/// open the file for reading or move it to a permanent location in your app’s sandbox
/// container directory before returning from this delegate method.
- (void)URLSession:(NSURLSession * __nonnull)session downloadTask:(NSURLSessionDownloadTask * __nonnull)downloadTask didFinishDownloadingToURL:(NSURL * __nonnull)location;

/// Periodically informs the delegate about the download’s progress.
///
/// \param session The session containing the download task.
///
/// \param downloadTask The download task.
///
/// \param bytesWritten The number of bytes transferred since the last time this delegate
/// method was called.
///
/// \param totalBytesWritten The total number of bytes transferred so far.
///
/// \param totalBytesExpectedToWrite The expected length of the file, as provided by the Content-Length
/// header. If this header was not provided, the value is
/// <code>NSURLSessionTransferSizeUnknown
/// </code>.
- (void)URLSession:(NSURLSession * __nonnull)session downloadTask:(NSURLSessionDownloadTask * __nonnull)downloadTask didWriteData:(int64_t)bytesWritten totalBytesWritten:(int64_t)totalBytesWritten totalBytesExpectedToWrite:(int64_t)totalBytesExpectedToWrite;

/// Tells the delegate that the download task has resumed downloading.
///
/// \param session The session containing the download task that finished.
///
/// \param downloadTask The download task that resumed. See explanation in the discussion.
///
/// \param fileOffset If the file's cache policy or last modified date prevents reuse of the
/// existing content, then this value is zero. Otherwise, this value is an
/// integer representing the number of bytes on disk that do not need to be
/// retrieved again.
///
/// \param expectedTotalBytes The expected length of the file, as provided by the Content-Length header.
/// If this header was not provided, the value is NSURLSessionTransferSizeUnknown.
- (void)URLSession:(NSURLSession * __nonnull)session downloadTask:(NSURLSessionDownloadTask * __nonnull)downloadTask didResumeAtOffset:(int64_t)fileOffset expectedTotalBytes:(int64_t)expectedTotalBytes;
- (BOOL)respondsToSelector:(SEL __null_unspecified)selector;
- (nonnull instancetype)init OBJC_DESIGNATED_INITIALIZER;
@end

@class NSURLSessionStreamTask;
@class NSOutputStream;

@interface SessionDelegate (SWIFT_EXTENSION(Alamofire)) <NSURLSessionStreamDelegate>

/// Overrides default behavior for NSURLSessionStreamDelegate method URLSession:readClosedForStreamTask:.
@property (nonatomic, copy) void (^ __nullable streamTaskReadClosed)(NSURLSession * __nonnull, NSURLSessionStreamTask * __nonnull);

/// Overrides default behavior for NSURLSessionStreamDelegate method URLSession:writeClosedForStreamTask:.
@property (nonatomic, copy) void (^ __nullable streamTaskWriteClosed)(NSURLSession * __nonnull, NSURLSessionStreamTask * __nonnull);

/// Overrides default behavior for NSURLSessionStreamDelegate method URLSession:betterRouteDiscoveredForStreamTask:.
@property (nonatomic, copy) void (^ __nullable streamTaskBetterRouteDiscovered)(NSURLSession * __nonnull, NSURLSessionStreamTask * __nonnull);

/// Overrides default behavior for NSURLSessionStreamDelegate method URLSession:streamTask:didBecomeInputStream:outputStream:.
@property (nonatomic, copy) void (^ __nullable streamTaskDidBecomeInputStream)(NSURLSession * __nonnull, NSURLSessionStreamTask * __nonnull, NSInputStream * __nonnull, NSOutputStream * __nonnull);

/// Tells the delegate that the read side of the connection has been closed.
///
/// \param session The session.
///
/// \param streamTask The stream task.
- (void)URLSession:(NSURLSession * __nonnull)session readClosedForStreamTask:(NSURLSessionStreamTask * __nonnull)streamTask;

/// Tells the delegate that the write side of the connection has been closed.
///
/// \param session The session.
///
/// \param streamTask The stream task.
- (void)URLSession:(NSURLSession * __nonnull)session writeClosedForStreamTask:(NSURLSessionStreamTask * __nonnull)streamTask;

/// Tells the delegate that the system has determined that a better route to the host is available.
///
/// \param session The session.
///
/// \param streamTask The stream task.
- (void)URLSession:(NSURLSession * __nonnull)session betterRouteDiscoveredForStreamTask:(NSURLSessionStreamTask * __nonnull)streamTask;

/// Tells the delegate that the stream task has been completed and provides the unopened stream objects.
///
/// \param session The session.
///
/// \param streamTask The stream task.
///
/// \param inputStream The new input stream.
///
/// \param outputStream The new output stream.
- (void)URLSession:(NSURLSession * __nonnull)session streamTask:(NSURLSessionStreamTask * __nonnull)streamTask didBecomeInputStream:(NSInputStream * __nonnull)inputStream outputStream:(NSOutputStream * __nonnull)outputStream;
@end

#pragma clang diagnostic pop
