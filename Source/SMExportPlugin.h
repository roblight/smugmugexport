//
//  SMExportPlugin.h
//  SMExportPlugin
//
//  Created by Aaron Evans on 10/7/06.
//  Copyright 2006 Aaron Evans. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "ExportPluginProtocol.h"
#import "SMAccess.h"

@class SMAccess, ExportMgr, SMAccountManager;
@protocol ExportPluginProtocol, SMAccessDelegate;

@interface SMExportPlugin : NSObject <ExportPluginProtocol, SMAccessDelegate> {

	IBOutlet id firstView;
	IBOutlet id lastView;
	IBOutlet NSBox *settingsBox;
	IBOutlet NSPanel *uploadPanel;
	IBOutlet NSPanel *loginPanel;
	IBOutlet NSPopUpButton *acccountPopupButton;
	IBOutlet NSArrayController *albumsArrayController;
	IBOutlet NSPanel *newAlbumSheet;
	IBOutlet NSPanel *preferencesPanel;
	IBOutlet NSArrayController *categoriesArrayController;
	IBOutlet NSArrayController *subCategoriesArrayController;
	
	NSString *username;  // this is the username bound to the textfield, account manager holds the real username
	NSString *password; // same goes for password..
	NSString *sessionUploadStatusText;
	NSString *statusText;
	NSNumber *fileUploadProgress;
	NSNumber *sessionUploadProgress;
	NSString *loginSheetStatusMessage;
	NSImage *currentThumbnail;
	NSString *imageUploadProgressText; // below the thumbnail..
	NSURL *uploadSiteUrl;
	NSMutableDictionary *newAlbumPreferences;
	
	NSInvocation *postLogoutInvocation; // do this after a logout is complete
	
	BOOL isUploading;
	BOOL loginSheetIsBusy;
	BOOL isBusy;
	BOOL loginAttempted;
	BOOL uploadCancelled;
	BOOL errorAlertSheetIsVisisble;
	BOOL siteUrlHasBeenFetched;
	BOOL browserOpenedInGallery;
	BOOL isDeletingAlbum;
	BOOL isCreatingAlbum;
	BOOL isUpdateInProgress;
	int uploadRetryCount;
	int imagesUploaded;
	int albumUrlFetchAttemptCount;

	ExportMgr *exportManager;
	SMAccess *smAccess;
	SMAccountManager *accountManager;
}

#pragma mark Upload Actions
-(IBAction)cancelUpload:(id)sender;

#pragma mark Login Actions
-(IBAction)cancelLoginSheet:(id)sender;
-(IBAction)showLoginSheet:(id)sender;
-(IBAction)performLoginFromSheet:(id)sender;

#pragma mark Misc
-(IBAction)donate:(id)sender;

#pragma mark Preferences
-(IBAction)showPreferences:(id)sender;
-(IBAction)closePreferencesSheet:(id)sender;

#pragma mark Album Creation Actions
-(IBAction)addNewAlbum:(id)sender;
-(IBAction)removeAlbum:(id)sender;
-(IBAction)cancelNewAlbumSheet:(id)sender;
-(IBAction)createAlbum:(id)sender;

#pragma mark Update
-(IBAction)checkForUpdates:(id)sender;

@end