//
//  KPDropMenu.m
//  KPDropMenu
//
//  Created by Krishna Patel on 22/03/17.
//  Copyright © 2017 Krishna. All rights reserved.
//

#import "KPDropMenu.h"

@interface KPDropMenu () <UITableViewDelegate, UITableViewDataSource> {
    BOOL isCollapsed;
    int selectedIndex;
    
    UILabel *label;
    UITableView *tblView;
    UIFont *selectedFont, *font, *itemFont;
    UITapGestureRecognizer *tapGestureBackground;
}
@end

@implementation KPDropMenu

-(instancetype)init {
    if (self = [super init]) {
        [self initLayer];
    }
    return self;
}

-(instancetype)initWithCoder:(NSCoder *)aDecoder {
    if (self = [super initWithCoder:aDecoder]) {
        [self initLayer];
    }
    return self;
}

-(instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        [self initLayer];
    }
    return self;
}

-(void)initLayer {
    isCollapsed = YES;
    _directionDown = YES;
    
    _itemHeight = 40.0;
    selectedIndex = -1;
    _itemFontSize = 14.0;
    _titleFontSize = 14.0;
    _titleColor = [UIColor blackColor];
    _itemTextColor = [UIColor blackColor];
    _itemBackground = [UIColor whiteColor];
    _itemsFont = [UIFont systemFontOfSize:14.0];
    
    _itemTextAlignment = _titleTextAlignment = NSTextAlignmentCenter;
}

#pragma mark - Setter
-(void)setEnabled:(BOOL)enabled {
    [label setEnabled:enabled];
    [self setUserInteractionEnabled:enabled];
}

-(void)setTitle:(NSString *)title {
    _title = title;
}

-(void)setTitleTextAlignment:(NSTextAlignment)titleTextAlignment {
    if(titleTextAlignment) {
        _titleTextAlignment = titleTextAlignment;
    }
}

-(void)setItemTextAlignment:(NSTextAlignment)itemTextAlignment {
    if(itemTextAlignment) {
        _itemTextAlignment = itemTextAlignment;
    }
}

-(void)setTitleColor:(UIColor *)titleColor {
    if(titleColor) {
        _titleColor = titleColor;
    }
}

-(void)setTitleFontSize:(CGFloat)titleFontSize {
    if(titleFontSize) {
        _titleFontSize = titleFontSize;
    }
    
}

-(void)setItemHeight:(double)itemHeight {
    if(itemHeight) {
        _itemHeight = itemHeight;
    }
}

-(void)setItemBackground:(UIColor *)itemBackground {
    if(itemBackground) {
        _itemBackground = itemBackground;
    }
}

-(void)setItemTextColor:(UIColor *)itemTextColor {
    if(itemTextColor) {
        _itemTextColor = itemTextColor;
    }
}

-(void)setItemFontSize:(CGFloat)itemFontSize {
    if(itemFontSize) {
        _itemFontSize = itemFontSize;
    }
}

-(void)setItemsFont:(UIFont *)itemFont1 {
    if(itemFont1) {
        _itemsFont = itemFont1;
    }
}

-(void)setDirectionDown:(BOOL)directionDown {
    _directionDown = directionDown;
}

#pragma mark - Setups
-(void)layoutSubviews {
    [super layoutSubviews];
    
    self.layer.cornerRadius = 4;
    self.layer.borderColor = [[UIColor grayColor] CGColor];
    self.layer.borderWidth = 1;
    
    if(label == nil) {
        label = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, self.frame.size.width, self.frame.size.height)];
        label.textColor = _titleColor;
        label.text = _title;
        label.textAlignment = _titleTextAlignment;
        label.font = font;
        [self addSubview:label];
    }
    
    UITapGestureRecognizer *tapGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(didTap:)];
    [self addGestureRecognizer:tapGesture];
    
    tblView = [[UITableView alloc] initWithFrame:CGRectMake(self.frame.origin.x, self.frame.origin.y, self.frame.size.width, self.frame.size.height)] ;
    [tblView registerClass:[UITableViewCell class] forCellReuseIdentifier:@"cell"];
    tblView.delegate = self;
    tblView.dataSource = self;
    tblView.backgroundColor = _itemBackground;
}

-(void)didTap:(UIGestureRecognizer *)gesture {
    isCollapsed = !isCollapsed;
    if(!isCollapsed) {
        CGFloat height = (CGFloat)(_items.count > 5 ? _itemHeight*5 : _itemHeight * (double)(_items.count));
        
        tblView.layer.zPosition = 1;
        [tblView removeFromSuperview];
        tblView.layer.borderColor = [[UIColor lightGrayColor] CGColor];
        tblView.layer.borderWidth = 1;
        tblView.layer.cornerRadius = 4;
        [self.superview addSubview:tblView];
        [tblView reloadData];
        
        [UIView animateWithDuration:0.25 animations:^ {
            if(self.directionDown) {
                self->tblView.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y + self.frame.size.height+5, self.frame.size.width, height);
            }
            else {
                self->tblView.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y - 5 - height, self.frame.size.width, height);
            }
        }];
        
        if(_delegate != nil) {
            if([_delegate respondsToSelector:@selector(didShow:)])
                [_delegate didShow:self];
        }
        
        UIView *view = [[UIView alloc] initWithFrame:[UIScreen mainScreen].bounds];
        view.tag = 99121;
        [self.superview insertSubview:view belowSubview:tblView];
        
        tapGestureBackground = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(didTapBackground:)];
        [view addGestureRecognizer:tapGestureBackground];
        
    }
    else {
        [self collapseTableView];
    }
}

-(void)didTapBackground:(UIGestureRecognizer *)gesture {
    isCollapsed = TRUE;
    [self collapseTableView];
}

-(void)collapseTableView {
    if(isCollapsed) {
        [UIView animateWithDuration:0.25 animations:^ {
            if(self.directionDown) {
                self->tblView.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y + self.frame.size.height+5, self.frame.size.width, 0);
            }
            else {
                self->tblView.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, self.frame.size.width, 0);
            }
        }];
        
        [[self.superview viewWithTag:99121] removeFromSuperview];
        if(_delegate != nil) {
            if([_delegate respondsToSelector:@selector(didHide:)]) {
                [_delegate didHide:self];
            }
        }
    }
}

#pragma mark - UITableView's Delegate and Datasource Methods
-(NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return _items.count;
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"cell"];
    if(cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"cell"];
    }
    
    cell.textLabel.textAlignment = _itemTextAlignment;
    cell.textLabel.text = _items[indexPath.row];
    
    cell.textLabel.font = _itemsFont;
    cell.textLabel.textColor = _itemTextColor;
    
    if (indexPath.row == selectedIndex) {
        cell.accessoryType = UITableViewCellAccessoryCheckmark;
    }
    else {
        cell.accessoryType = UITableViewCellAccessoryNone;
    }
    
    cell.backgroundColor = _itemBackground;
    cell.tintColor = self.tintColor;
    return cell;
}

-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return _itemHeight;
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    selectedIndex = (int)indexPath.row;
    label.text = _items[selectedIndex];
    
    if(_itemIds.count > 0) {
        self.tag = [_itemIds[selectedIndex] integerValue];
    }
    
    isCollapsed = TRUE;
    [self collapseTableView];
    if(_delegate != nil) {
        if([_delegate respondsToSelector:@selector(didSelectItem:atIndex:)]) {
            [_delegate didSelectItem:self atIndex:selectedIndex];
        }
    }
}

@end
