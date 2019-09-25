//
//  MainVC.m
//  DemoiOS
//
//  Created by Faizan on 18/09/2019.
//  Copyright © 2019 Fizz. All rights reserved.
//

#import "MainVC.h"
#import <MQTTClient/MQTTLog.h>
#import <FizzClient/FizzClient.h>

#define HistoryPageSize     10
#define CellHeight          60
#define ConnectText         @"Connect"
#define DisconnectText      @"Disconnect"
#define TableCellId         @"Message Cell"
#define GlobalChannel       @"global-sample"
#define AppId               @"751326fc-305b-4aef-950a-074c9a21d461"
#define AppSecret           @"5c963d03-64e6-439a-b2a9-31db60dd0b34"

@interface MainVC()<UITextFieldDelegate, KPDropMenuDelegate, UITableViewDelegate, UITableViewDataSource, FizzChannelMessageListener> {
    BOOL _initSuccess;
    
    NSString *_userId;
    NSNumber *_locale;
    NSMutableArray<FizzChannelMessage *> *_messages;
}

@end

@implementation MainVC

#pragma mark - UIViewController - life cycle methods
-(void)dealloc {
    [_messages removeAllObjects];
}

-(void)viewDidLoad {
    [super viewDidLoad];
    
    // view setup
    [self trimButton];
    [self setupTextField];
    [self setupDropdowns];
    [self setupMessagesTable];
    
    // fizz setup
    [self initializeFizz];
    
    // log settings for MQTT
    [MQTTLog setLogLevel:DDLogLevelOff];
}

-(void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [self registerForKeyboardNotifications];
}

-(void)viewWillDisappear:(BOOL)animated {
    [self deregisterFromKeyboardNotifications];
    [super viewWillDisappear:animated];
}

-(instancetype)initWithCoder:(NSCoder *)coder {
    self = [super initWithCoder:coder];
    
    _messages = [NSMutableArray array];
    
    return self;
}

#pragma mark - private helper methods - view related
-(void)trimButton {
    _toggleBtn.layer.cornerRadius = 10;
    _toggleBtn.clipsToBounds = YES;
}

-(void)setupTextField {
    _messageInput.delegate = self;
    
    UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(dismissKeyboard)];
    [tap setCancelsTouchesInView:NO];
    [self.view addGestureRecognizer:tap];
}

-(void)setupDropdowns {
    // userDropdown
    _userDropdown.items = @[@"User A", @"User B", @"User C", @"User D"];
    _userDropdown.itemIds = @[@"UserA", @"UserB", @"UserC", @"UserD"];
    _userDropdown.delegate = self;
    
    // localeDropdown
    _localeDropdown.items = @[@"English", @"French", @"Spanish"];
    _localeDropdown.itemIds = @[@(English), @(French), @(Spanish)];
    _localeDropdown.delegate = self;
}

-(void)reloadTableView {
    __weak MainVC *wself = self;
    NSUInteger totalMessages = _messages.count;
    dispatch_async(dispatch_get_main_queue(), ^{
        [wself.messagesTable reloadData];
        if(totalMessages > wself.messagesTable.visibleCells.count) {
            [wself.messagesTable scrollToRowAtIndexPath:[NSIndexPath indexPathForRow:totalMessages-1 inSection:0]
                                       atScrollPosition:UITableViewScrollPositionBottom animated:YES];
        }
    });
}

-(void)clearMessagesTable {
    [_messages removeAllObjects];
    [self reloadTableView];
}

-(void)setupMessagesTable {
    _messagesTable.delegate = self;
    _messagesTable.dataSource = self;
    [_messagesTable setCanCancelContentTouches:NO];
}

-(void)showAlert:(NSString *)message {
    UIAlertAction *dismissAction = [UIAlertAction actionWithTitle:@"Dismiss" style:UIAlertActionStyleDefault handler:nil];
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:@"Fizz" message:message preferredStyle:UIAlertControllerStyleAlert];
    
    __weak MainVC *wself = self;
    [alertController addAction:dismissAction];
    dispatch_async(dispatch_get_main_queue(), ^{
        [wself presentViewController:alertController animated:YES completion:nil];
    });
}

-(void)animateMessageField:(float)bottomMargin {
    __weak MainVC *wself = self;
    [UIView animateWithDuration:0 delay:0 options:UIViewAnimationOptionCurveEaseInOut animations:^{
        wself.messageInputBottom.constant = bottomMargin;
        [wself.view setNeedsUpdateConstraints];
        [wself.view layoutIfNeeded];
    } completion:nil];
}

-(void)loadMessages:(NSArray<FizzChannelMessage *> *)messages {
    [_messages addObjectsFromArray:messages];
    [self reloadTableView];
}

#pragma mark - private helper methods - keyboard related
-(void)dismissKeyboard {
    [_messageInput resignFirstResponder];
}

-(void)registerForKeyboardNotifications {
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(keyboardWasShown:)
                                                 name:UIKeyboardDidShowNotification
                                               object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(keyboardWillBeHidden:)
                                                 name:UIKeyboardWillHideNotification
                                               object:nil];
}

-(void)deregisterFromKeyboardNotifications {
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:UIKeyboardDidHideNotification
                                                  object:nil];
    
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:UIKeyboardWillHideNotification
                                                  object:nil];
}

-(void)keyboardWasShown:(NSNotification *)notification {
    NSDictionary *info = [notification userInfo];
    CGSize keyboardSize = [[info objectForKey:UIKeyboardFrameBeginUserInfoKey] CGRectValue].size;
    
    CGFloat botMargin = keyboardSize.height + _messageInput.frame.size.height;
    [self animateMessageField:(-1 * botMargin)];
}

-(void)keyboardWillBeHidden:(NSNotification *)notification {
    [self animateMessageField:0];
}

#pragma mark - private helper methods - fizz lifecycle
-(void)openFizz {
    __weak MainVC *wself = self;
    [[FizzClient instance] openWithUser:_userId locale:_locale.intValue services:All andErrorAck:^(FizzError *openError) {
        if(openError) {
            NSLog(@"fizz:: openError: %@", openError.errorDescription);
            [wself showAlert:@"Unable to open connection!!!"];
        }
    }];
}

-(void)closeFizz {
    __weak MainVC *wself = self;
    [[FizzClient instance] close:^(FizzError *closeError) {
        if(closeError) {
            NSLog(@"fizz:: closeError: %@", closeError.errorDescription);
            [wself showAlert:@"Unable to close connection!!!"];
        }
    }];
}

-(void)initializeFizz {
    FizzClient *fizzClient = [FizzClient instance];
    
    // initialize fizz
    FizzError *initError = [fizzClient initializeWithAppId:AppId andSecret:AppSecret];
    BOOL initSuccess = _initSuccess = !initError;
    if(initSuccess) {
        __weak MainVC *wself = self;// add listener
        [fizzClient.chat addListener:wself forKey:@"FizzDemoListener"];
    }
    else {
        NSLog(@"fizz:: initError: %@", initError.errorDescription);
        [self showAlert:@"Unable to initialize!!!"];
    }
}

#pragma mark - private helper methods - fizz operations
-(void)joinChannel {
    __weak MainVC *wself = self;
    [[FizzClient instance].chat subscribeChannel:GlobalChannel withErrorAck:^(FizzError *joinError) {
        if(joinError) {
            NSLog(@"fizz:: joinError: %@", joinError.errorDescription);
            [wself showAlert:@"Unable to join channel!!!"];
        }
    }];
}

-(void)fetchHistoricMessages {
    __weak MainVC *wself = self;
    [[FizzClient instance].chat queryLatestMessagesInChannel:GlobalChannel withCount:HistoryPageSize andQueryAck:^(NSArray<FizzChannelMessage *> *messages, FizzError *fetchError) {
        if(fetchError) {
            NSLog(@"fizz:: fetchError: %@", fetchError.errorDescription);
            [wself showAlert:@"Unable to fetch channel history!!!"];
        }
        else {
            [wself loadMessages:messages];
            dispatch_async(dispatch_get_main_queue(), ^{
                // subscribing channel after fetching history to avoid conflict with latest messages
                // to keep track of real time messages, subscribe first and sort the messages array by messageId
                [wself joinChannel];
            });
        }
    }];
}

-(void)publishMessage:(NSString *)messageText {
    __weak MainVC *wself = self;
    [[FizzClient instance].chat publishMessageToChannel:GlobalChannel withNick:_userId body:messageText data:@{} translate:YES persist:YES filter:YES andErrorAck:^(FizzError *publishError) {
        if(publishError) {
            NSLog(@"fizz:: publishError: %@", publishError.errorDescription);
            [wself showAlert:@"Unable to publish message in channel!!!"];
        }
    }];
}

#pragma mark - IBAction methods
-(IBAction)handleStateToggle:(id)sender {
    [_toggleBtn setEnabled:NO];
    enum FizzClientState clientState = [[FizzClient instance] state];
    if(clientState == Closed) {
        [self openFizz];
    }
    else {
        [self closeFizz];
    }
}

#pragma mark - delegate methods - UITextFieldDelegate
-(BOOL)textFieldShouldReturn:(UITextField *)textField {
    NSString *messageText = [textField.text stringByTrimmingCharactersInSet:
                             [NSCharacterSet whitespaceAndNewlineCharacterSet]];
    textField.text = @"";
    if(messageText.length > 0) {
        [self publishMessage:messageText];
    }
    
    return YES;
}

#pragma mark - delegate methods - KPDropMenu
-(void)didSelectItem:(KPDropMenu *)dropMenu atIndex:(int)index {
    if(dropMenu == _userDropdown) {
        _userId = dropMenu.itemIds[index];
    }
    else {
        _locale = dropMenu.itemIds[index];
    }
    
    if(_toggleBtn.enabled) { return; }
    BOOL enableControls = _initSuccess && _userId && _locale;
    if(enableControls) {// disabled byDefault
        [_toggleBtn setEnabled:YES];
        [_messageInput setEnabled:YES];
    }
}

#pragma mark - delegate methods - UITableViewDelegate
-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return CellHeight;
}

#pragma mark - delegate methods - UITableViewDataSource
-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return _messages.count;
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UILabel *textLabel = nil;
    UITableViewCell *messageCell = [tableView dequeueReusableCellWithIdentifier:TableCellId];
    
    if(!messageCell) {
        messageCell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:TableCellId];
        textLabel = messageCell.textLabel;
        
        [textLabel setNumberOfLines:0];
        [textLabel setClipsToBounds:NO];
        [textLabel setFont:[UIFont fontWithName:@"Times New Roman" size:12]];
    }
    
    textLabel = messageCell.textLabel;
    FizzChannelMessage *message = [_messages objectAtIndex:indexPath.row];
    textLabel.text = @"";
    textLabel.text = [message description];
    
    return messageCell;
}

#pragma mark - delegate methods - FizzChannelMessageListener
-(void)onDisconnectedEventReceived {
    [_toggleBtn setEnabled:YES];
    [_toggleBtn setTitle:ConnectText forState:UIControlStateNormal];
    
    [self clearMessagesTable];
}

-(void)onMessagePublishedEventReceived:(FizzChannelMessage *)message {
    [self loadMessages:@[message]];
}

-(void)onConnectedEventReceived:(BOOL)status syncRequired:(BOOL)syncRequired {
    [_toggleBtn setEnabled:YES];
    [_toggleBtn setTitle:DisconnectText forState:UIControlStateNormal];
    
    [self fetchHistoricMessages];
}

@end
