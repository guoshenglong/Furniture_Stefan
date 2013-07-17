//
//  BaseService.m
//  Furniture0701
//
//  Created by li yajin on 13-7-17.
//  Copyright (c) 2013年 郭胜龙. All rights reserved.
//

#import "BaseService.h"

@interface BaseService ()

@end

@implementation BaseService
@synthesize connection,connectionData;
- (void)dealloc
{
    // [super dealloc];
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    // [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle


// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad
{
    // [super viewDidLoad];
    NSLog(@"viewDidLoad");
    //文件地址
    NSString *urlAsString = @"http://192.168.2.8:8080/Vertra/background/furniture/2-1.png";
    NSURL    *url = [NSURL URLWithString:urlAsString];
    NSURLRequest *request = [NSURLRequest requestWithURL:url];
    NSMutableData *data = [[NSMutableData alloc] init];
    self.connectionData = data;
    // [data release];
    NSURLConnection *newConnection = [[NSURLConnection alloc]
                                      initWithRequest:request
                                      delegate:self
                                      startImmediately:YES];
    self.connection = newConnection;
    // [newConnection release];
    if (self.connection != nil){
        NSLog(@"Successfully created the connection");
    } else {
        NSLog(@"Could not create the connection");
    }
}


// 测试模型下载的函数
- (BOOL)downloadModelTest
{
    NSLog(@"测试模型下载的函数");
    //文件地址
    NSString *urlAsString = @"http://192.168.2.8:8080/Vertra/background/furniture/2-1.png";
    NSURL    *url = [NSURL URLWithString:urlAsString];
    NSURLRequest *request = [NSURLRequest requestWithURL:url];
    NSMutableData *data = [[NSMutableData alloc] init];
    self.connectionData = data;
    // [data release];
    NSURLConnection *newConnection = [[NSURLConnection alloc]
                                      initWithRequest:request
                                      delegate:self
                                      startImmediately:YES];
    self.connection = newConnection;
    // [newConnection release];
    if (self.connection != nil){
        NSLog(@"Successfully created the connection");
    } else {
        NSLog(@"Could not create the connection");
    }
    return YES;
}

// 测试图片下载的函数
- (BOOL)downloadImageTest
{
    NSLog(@"测试模型下载的函数");
    //文件地址
    NSString *urlAsString = @"http://192.168.2.8:8080/Vertra/background/furniture/2-1.png";
    NSURL    *url = [NSURL URLWithString:urlAsString];
    NSURLRequest *request = [NSURLRequest requestWithURL:url];
    NSMutableData *data = [[NSMutableData alloc] init];
    self.connectionData = data;
    // [data release];
    NSURLConnection *newConnection = [[NSURLConnection alloc]
                                      initWithRequest:request
                                      delegate:self
                                      startImmediately:YES];
    self.connection = newConnection;
    // [newConnection release];
    if (self.connection != nil){
        NSLog(@"Successfully created the connection");
    } else {
        NSLog(@"Could not create the connection");
    }
    return YES;
}

// 测试数据加载的函数
- (BOOL)dataTest
{
    NSLog(@"测试模型下载的函数");
    //文件地址
    NSString *urlAsString = @"http://192.168.2.8:8080/Vertra/background/furniture/2-1.png";
    NSURL    *url = [NSURL URLWithString:urlAsString];
    NSURLRequest *request = [NSURLRequest requestWithURL:url];
    NSMutableData *data = [[NSMutableData alloc] init];
    self.connectionData = data;
    // [data release];
    NSURLConnection *newConnection = [[NSURLConnection alloc]
                                      initWithRequest:request
                                      delegate:self
                                      startImmediately:YES];
    self.connection = newConnection;
    // [newConnection release];
    if (self.connection != nil){
        NSLog(@"Successfully created the connection");
    } else {
        NSLog(@"Could not create the connection");
    }
    return YES;
}

// 加载链接出错
- (void) connection:(NSURLConnection *)connection
   didFailWithError:(NSError *)error{
    NSLog(@"An error happened");
    NSLog(@"%@", error);
}

// 接收数据
- (void) connection:(NSURLConnection *)connection
     didReceiveData:(NSData *)data{
    NSLog(@"Received data");
    [self.connectionData appendData:data];
}

// 链接完成，下载数据，保存文件
- (void) connectionDidFinishLoading
:(NSURLConnection *)connection{
    /* 下载的数据 */
    
    NSLog(@"文件长度： %d", self.connectionData.length);
    NSLog(@"文件长度： %@", self.connectionData);
    NSLog(@"下载成功");
    
    UIImage * result;
    
    result = [UIImage imageWithData:connectionData];
    
    [UIImagePNGRepresentation(result) writeToFile:[@"pic" stringByAppendingPathComponent:[NSString stringWithFormat:@"%@.%@", @"1-1", @"png"]] options:NSAtomicWrite error:nil];
    
    if ([self.connectionData writeToFile:@"213.png" atomically:YES]) {
        NSLog(@"保存成功.");
    }
    else
    {
        NSLog(@"保存失败.");
    }
    
    /* do something with the data here */
    
    [self.connection cancel];
    self.connection = nil;
    self.connectionData = nil;
}

// 断链重连， 应该重新下载文件
- (void) connection:(NSURLConnection *)connection
 didReceiveResponse:(NSURLResponse *)response{
    [self.connectionData setLength:0];
}

- (void) viewDidUnload{
    // [super viewDidUnload];
    [self.connection cancel];
    self.connection = nil;
    self.connectionData = nil;
}


@end
