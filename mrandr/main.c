//
//  main.c
//  xrandr
//
//  Created by playerc on 11/21/14.
//  Copyright (c) 2014 playerc <playerc@msn.cn>. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ApplicationServices/ApplicationServices.h>

#define MAX_DISPLAYS 8

int askfor_display_id(CGDirectDisplayID *id);
CGDisplayModeRef askfor_display_mode(CGDirectDisplayID display_id);
int ask_is_retry();
void switch_to_mode(CGDirectDisplayID display, CGDisplayModeRef mode);
void print_display_mode_list(CGDisplayModeRef current_mode ,
			     CFArrayRef mode_list_ref
			     );
void print_display_id_list(CGDirectDisplayID ids[], uint32_t count);
int display_mode_compare(CGDisplayModeRef a, CGDisplayModeRef b);
void mflush();

int main(int argc, const char * argv[]){
	CGDirectDisplayID display_id;
	CGDisplayModeRef display_mode = NULL;

	printf("mrandr v0.1 \n"
	       "Copyright (c) 2014 playerc <playerc@msn.cn>\n"
	       "!!!This program only run on mac os x 10.6 and later."
	       );
	
	if (askfor_display_id(&display_id) != 0) {
		if ((display_mode = askfor_display_mode(display_id)) != NULL){
			switch_to_mode(display_id, display_mode);
		}
	}
	
	if (display_mode != NULL){
		CGDisplayModeRelease(display_mode);
	}
	printf("\nEnded....\n");
	return 0;
}

/**
 向用户询问显示器编号。
 @*id: 存储用户选择的显示器编号 
 返回值：
   0 : 失败
 其他 : 成功
 */
int askfor_display_id(CGDirectDisplayID *id){
	CGDirectDisplayID displays[ MAX_DISPLAYS ];
	uint32_t displays_count;
	int choose_index = 0;

	CGGetActiveDisplayList(MAX_DISPLAYS, displays, &displays_count);

	for (;;) {
		printf("\nDisplay List:");
		print_display_id_list(displays, displays_count);

		printf("\nChoose a display:");
		mflush();
		if (scanf("%d",&choose_index) == 0){
			choose_index = -1;
		}

		if (choose_index < 0 || choose_index >= displays_count){
			printf("\nPlease intput a Integer between %d and %d .",
			       0,
			       displays_count
			       );
			
			if (ask_is_retry() == 0) {
				return 0;
			}
		}
		else {
			break;
		}
	}

	*id = displays[choose_index];

	return 1;
}

int ask_is_retry(){
	printf("\nRetry? (y/n): ");

	mflush();
	if (getchar() != 'y') {
		return 0;
	}	
	return 1;
}

/**
 向用户询问指定显示器的显示模式.
 @display_id : 指定的显示器id
 返回值:
 用户选择的显示器模式。
 NULL : 获取失败
 注意：
 返回值需要调用 CGDisplayModeRelease() 方法进行释放。
 */
CGDisplayModeRef askfor_display_mode(CGDirectDisplayID display_id){
	CGDisplayModeRef mode;
	CGDisplayModeRef current_mode;
	CFArrayRef mode_list;
	int choose_index;

	mode_list = CGDisplayCopyAllDisplayModes(display_id, NULL);
	current_mode = CGDisplayCopyDisplayMode(display_id);

	for (;;){
		printf("\n Mode List:");
		print_display_mode_list(current_mode, mode_list);

		printf("\nchoose a mode :");
		mflush();
		if (scanf("%d",&choose_index) == 0) {
			choose_index  = -1;
		}

		if (choose_index < 0
		    || choose_index >= CFArrayGetCount(mode_list)) {
			mode = NULL;
			printf("\nPlease intput a Integer between %d and %zd .",
			       0,
			       CFArrayGetCount(mode_list)
			       );
			if (ask_is_retry() == 0) {
				break;
			}
		}
		else {
			mode = (CGDisplayModeRef) CFArrayGetValueAtIndex(
								mode_list,
								choose_index
								);
			CGDisplayModeRetain(mode);
			break;
		}
	}
	CFRelease(current_mode);
	CFRelease(mode_list);
	return mode;
}

void print_display_id_list(CGDirectDisplayID ids[], uint32_t count){
	uint32_t i ;

	for (i = 0; i < count; ++i) {
		printf("\n %4d : %d",i,CGDisplayVendorNumber(ids[i]));
	}
	return ;
}

void print_display_mode_list(CGDisplayModeRef current_mode ,CFArrayRef mode_list_ref){
	CGDisplayModeRef mode;
	CFIndex i,count;

	count = CFArrayGetCount(mode_list_ref);

	for (i = 0; i < count; ++i) {
		char c;
		mode = (CGDisplayModeRef) CFArrayGetValueAtIndex(
								 mode_list_ref,
								 i
								 );

		c =  display_mode_compare(current_mode, mode) == 0
		? '*' : ' ';
		printf("\n %c %4zd :%5zd*%5zd*%2d@%3zd",
		       c,
		       i,
		       CGDisplayModeGetWidth(mode),
		       CGDisplayModeGetHeight(mode),
		       CGDisplayModeGetIOFlags(mode),
		       (uint32_t) CGDisplayModeGetRefreshRate(mode)
		       );
	}

	return;
}

int display_mode_compare(CGDisplayModeRef a, CGDisplayModeRef b){
	int d_w = (int)CGDisplayModeGetWidth(a)
	- (int)CGDisplayModeGetWidth(b);
	int d_h = (int)CGDisplayModeGetHeight(a)
	- (int)CGDisplayModeGetHeight(b);
	int d_f = (int)CGDisplayModeGetIOFlags(a)
	- (int)CGDisplayModeGetIOFlags(b);
	int d_r = CGDisplayModeGetRefreshRate(a)
	- CGDisplayModeGetRefreshRate(b);

	if (d_w == 0 && d_h == 0 && d_f == 0 && d_r == 0){
		return 0;
	}
	else if (d_f > 0 && d_r > 0){
		if (d_w > 0 || d_h > 0){
			return 1;
		}
		else {
			return -1;
		}
	}
	else {
		return -1;
	}
}

void mflush(){
	fpurge(stdin);
}

void switch_to_mode(CGDirectDisplayID display, CGDisplayModeRef mode){
	CGDisplayConfigRef config_ref;

	CGBeginDisplayConfiguration(&config_ref);
	CGConfigureDisplayWithDisplayMode(config_ref, display, mode, NULL);
	CGCompleteDisplayConfiguration(config_ref, kCGConfigurePermanently);
}

