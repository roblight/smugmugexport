//
//  SMEAccountManager.m
//  SmugMugExport
//
//  Created by Aaron Evans on 10/29/06.
//  Copyright 2006 Aaron Evans. All rights reserved.
//

#import "SMEAccountManager.h"
#import "SMEKeychainManager.h"
#import "SMEGlobals.h"
#import "SMEUserDefaultsAdditions.h"

NSString *KeychainItemName = @"SmugMug Exporter";
NSString *KeychainItemKind = @"application password";

@interface SMEAccountManager (Private)
-(void)populateAccounts;
-(NSString *)keychainItemNameForAccount:(NSString *)accountId;
-(BOOL)passwordExistsInKeychainForAccount:(NSString *)account;
-(void)addAccountToKeychain:(NSString *)account password:(NSString *)password;
-(void)addAccount:(NSString *)username withPassword:(NSString *)password;
-(NSString *)passwordForUsername:(NSString *)user;
-(void)setAccounts:(NSArray *)a;
-(void)addAccount:(NSString *)account;
-(void)removeAccountFromKeychain:(NSString *)account;
-(void)modifyAccountInKeychain:(NSString *)account newPassword:(NSString *)newPassword;
-(NSString *)selectedAccount;
-(void)setSelectedAccount:(NSString *)anAccount;
-(BOOL)rememberPasswordInKeychain;
@end

@implementation SMEAccountManager

+(SMEAccountManager *)accountManager {
	return [[[[self class] alloc] init] autorelease];
}

-(void)dealloc {
	[super dealloc];
}

-(NSString *)keychainItemNameForAccount:(NSString *)accountId {
	return [NSString stringWithFormat:@"%@: %@", KeychainItemName, accountId];
}

-(BOOL)passwordExistsInKeychainForAccount:(NSString *)account {
	return [[SMEKeychainManager sharedKeychainManager] checkForExistanceOfKeychainItem:[self keychainItemNameForAccount:account] withItemKind:KeychainItemKind forUsername:account];
}

-(void)addAccountToKeychain:(NSString *)account password:(NSString *)password {
	if([self passwordExistsInKeychainForAccount:account])
		return;

	[[SMEKeychainManager sharedKeychainManager] addKeychainItem:[self keychainItemNameForAccount:account] withItemKind:KeychainItemKind forUsername:account withPassword:password];
}

-(void)removeAccountFromKeychain:(NSString *)account {
	[[SMEKeychainManager sharedKeychainManager] deleteKeychainItem:[self keychainItemNameForAccount:account] withItemKind:KeychainItemKind forUsername:KeychainItemKind];
}

-(void)modifyAccountInKeychain:(NSString *)account newPassword:(NSString *)newPassword {
	if([self passwordForAccount:account] != nil)
		[[SMEKeychainManager sharedKeychainManager] modifyKeychainItem:[self keychainItemNameForAccount:account] withItemKind:KeychainItemKind forUsername:account withNewPassword:newPassword];
	else
		[self addAccountToKeychain:account password:newPassword];
}

-(void)addAccount:(NSString *)account withPassword:(NSString *)password {
	if([[self accounts] containsObject:account] && [self rememberPasswordInKeychain]) {
		[self modifyAccountInKeychain:account newPassword:password];
	} else {
		if([self rememberPasswordInKeychain])
			[self addAccountToKeychain:account password:password];
		[self addAccount:account];		
	}
	
	[self setSelectedAccount:account];
}

-(NSString *)passwordForAccount:(NSString *)account {
	return [[SMEKeychainManager sharedKeychainManager] passwordFromKeychainItem:[self keychainItemNameForAccount:account] withItemKind:KeychainItemKind forUsername:account];
}

-(void)addAccount:(NSString *)account {
	if(![[self accounts] containsObject:account])
		[self setAccounts:[[self accounts] arrayByAddingObject:account]];

	[self setSelectedAccount:account];
}

-(NSArray *)accounts {
	return [[NSUserDefaults smugMugUserDefaults] objectForKey:SMEAccountsDefaultsKey];
}

-(void)setAccounts:(NSArray *)a {
	[[NSUserDefaults smugMugUserDefaults] setObject:a forKey:SMEAccountsDefaultsKey];
}

-(NSString *)selectedAccount {

	NSString *anAccount = [[NSUserDefaults smugMugUserDefaults] objectForKey:SMESelectedAccountDefaultsKey];

	if([[self accounts] containsObject:anAccount])
		return anAccount;
	
	if([[self accounts] count] == 0)
		return nil;
	
	return [[self accounts] objectAtIndex:0];
}

-(void)setSelectedAccount:(NSString *)anAccount {
	[self willChangeValueForKey:@"selectedAccount"];
	[[NSUserDefaults smugMugUserDefaults] setObject:anAccount forKey:SMESelectedAccountDefaultsKey];
	[self didChangeValueForKey:@"selectedAccount"];
}

-(BOOL)canAttemptAutoLogin {
	return [[self accounts] count] > 0 &&
		[self selectedAccount] != nil &&
		[self passwordForAccount:[self selectedAccount]] != nil;
}

-(BOOL)rememberPasswordInKeychain {
	if([[NSUserDefaults smugMugUserDefaults] objectForKey:SMStorePasswordInKeychain] == nil)
		return NO;
	
	return [[[NSUserDefaults smugMugUserDefaults] objectForKey:SMStorePasswordInKeychain] boolValue];
}

@end
