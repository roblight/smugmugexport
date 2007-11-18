//
//  NSDataAdditions.h
//  SmugMugExport
//
//  Created by Aaron Evans on 10/11/06.
//  Copyright 2006 Aaron Evans. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface NSData (NSDataAdditions)
-(NSString *)md5HexString;
-(NSData *)md5Hash;
+(NSData *)dataFromModGzUrl:(NSURL *)url;
@end
