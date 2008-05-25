//
//  SMAlbumInfo.h
//  SmugMugExport
//
//  Created by Aaron Evans on 3/23/08.
//  Copyright 2008 Aaron Evans. All rights reserved.
//

#import <Cocoa/Cocoa.h>
@class SMAlbum, SMAlbumRef;

/*
 * http://smugmug.jot.com/WikiHome/1.2.0/smugmug.albums.getInfo
 *
 */
@interface SMAlbumInfo : NSObject {
	NSString *albumId;
	NSString *albumKey;
	NSDictionary *category;
	NSDictionary *subCategory;
	NSString *title;
	NSString *description;
	NSString *keywords;
	
	BOOL isPublic;
	BOOL isPrintable;
	BOOL showsFilenames;
	BOOL isSharingEnabled;
	BOOL allowsComments;
	BOOL allowsExternalLinking;
	BOOL showsOriginals;
	BOOL allowsFriendsToEdit;
	BOOL allowsFamilyToEdit;
	BOOL displaysEXIFInfo;
	
/* 	
 support later if at all:
	unsigned int position;
	NSString *sortMethod;
	BOOL sortDirection;
	unsigned int imageCount;
	NSDate *lastUpdated; // ? string?
	unsigned int CommunityId;
	NSString *password;
 	BOOL hidesOwner;
	BOOL share; // what's this?
	BOOL isSmugMugSearchable;
	BOOL isWorldSearchable;
	// other pro options here
*/
}

-(id)init;
-(id)initWithAlbum:(SMAlbum *)album;

+(SMAlbumInfo *)albumInfo;
+(SMAlbumInfo *)albumInfoWithSMResponse:(NSDictionary *)response 
							 categories:(NSArray *)categories 
						  subcategories:(NSArray *)subcatgegories;
-(NSString *)albumId;
-(void)setAlbumId:(NSString *)anId;
-(NSString *)albumKey;
-(void)setAlbumKey:(NSString *)albumKey;

-(SMAlbumRef *)ref;
-(NSDictionary *)category;
-(void)setCategory:(NSDictionary *)anId;
-(NSDictionary *)subCategory;
-(void)setSubCategory:(NSDictionary *)subCategoryId;

-(NSString *)title;
-(void)setTitle:(NSString *)title;
-(NSString *)description;
-(void)setDescription:(NSString *)description;
-(NSString *)keywords; // TODO make the UI specify a collection of keywords
-(void)setKeywords:(NSString *)keywords;
-(BOOL)isPublic;
-(void)setIsPublic:(BOOL)v;
-(BOOL)isSharingEnabled;
-(void)setIsSharingEnabled:(BOOL)v;
-(BOOL)isPrintable;
-(void)setIsPrintable:(BOOL)v;
-(BOOL)showsFilenames;
-(void)setShowsFilenames:(BOOL)v;
-(BOOL)allowsComments;
-(void)setAllowsComments:(BOOL)v;
-(BOOL)allowsExternalLinking;
-(void)setAllowsExternalLinking:(BOOL)v;
-(BOOL)showsOriginals;
-(void)setShowsOriginals:(BOOL)v;
-(BOOL)allowsFriendsToEdit;
-(void)setAllowsFriendsToEdit:(BOOL)v;
-(BOOL)displaysEXIFInfo;
-(void)setDisplaysEXIFInfo:(BOOL)v;
-(BOOL)allowsFamilyToEdit;
-(void)setAllowsFamilyToEdit:(BOOL)v;

-(NSDictionary *)toDictionary;
@end