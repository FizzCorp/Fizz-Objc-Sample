//
//  MainVC.h
//  DemoiOS
//
//  Created by Faizan on 18/09/2019.
//  Copyright © 2019 Fizz. All rights reserved.
//

#import "KPDropMenu.h"
#import <UIKit/UIKit.h>

@interface MainVC : UIViewController

@property (nonatomic, weak) IBOutlet UIButton *toggleBtn;
@property (nonatomic, weak) IBOutlet UITextField *messageInput;
@property (nonatomic, weak) IBOutlet UITableView *messagesTable;
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *messageInputBottom;

@property (nonatomic, weak) IBOutlet KPDropMenu *userDropdown;
@property (nonatomic, weak) IBOutlet KPDropMenu *localeDropdown;

@end
