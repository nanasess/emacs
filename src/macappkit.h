/* Definitions and headers for AppKit framework on macOS.
   Copyright (C) 2008-2021  YAMAMOTO Mitsuharu

This file is part of GNU Emacs Mac port.

GNU Emacs Mac port is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

GNU Emacs Mac port is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Emacs Mac port.  If not, see <https://www.gnu.org/licenses/>.  */

#undef Z
#import <Cocoa/Cocoa.h>
#import <WebKit/WebKit.h>
#import <Quartz/Quartz.h>
#import <QuartzCore/QuartzCore.h>
#import <IOKit/graphics/IOGraphicsLib.h>
#import <OSAKit/OSAKit.h>
#if HAVE_MAC_METAL
#import <Metal/Metal.h>
#endif
#if HAVE_UNIFORM_TYPE_IDENTIFIERS
#import <UniformTypeIdentifiers/UniformTypeIdentifiers.h>
#endif
#define Z (current_buffer->text->z)

#ifndef NSFoundationVersionNumber10_8_3
#define NSFoundationVersionNumber10_8_3 945.16
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101300
typedef double NSAppKitVersion;
#ifndef NSAppKitVersionNumber10_6
static const NSAppKitVersion NSAppKitVersionNumber10_6 = 1038;
#endif
#ifndef NSAppKitVersionNumber10_7
static const NSAppKitVersion NSAppKitVersionNumber10_7 = 1138;
#endif
#ifndef NSAppKitVersionNumber10_8
static const NSAppKitVersion NSAppKitVersionNumber10_8 = 1187;
#endif
#ifndef NSAppKitVersionNumber10_9
static const NSAppKitVersion NSAppKitVersionNumber10_9 = 1265;
#endif
#ifndef NSAppKitVersionNumber10_10_Max
static const NSAppKitVersion NSAppKitVersionNumber10_10_Max = 1349;
#endif
#ifndef NSAppKitVersionNumber10_11
static const NSAppKitVersion NSAppKitVersionNumber10_11 = 1404;
#endif
#ifndef NSAppKitVersionNumber10_12
static const NSAppKitVersion NSAppKitVersionNumber10_12 = 1504;
#endif
#endif
#ifndef __MAC_10_14
static const NSAppKitVersion NSAppKitVersionNumber10_13 = 1561;
#endif
#ifndef __MAC_10_15
static const NSAppKitVersion NSAppKitVersionNumber10_14 = 1671;
#endif
#ifndef __MAC_11_0
static const NSAppKitVersion NSAppKitVersionNumber10_15 = 1894;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= 101500 || (WK_API_ENABLED && MAC_OS_X_VERSION_MIN_REQUIRED >= 101300)
#define USE_WK_API 1
#endif

#ifndef USE_ARC
#if defined (__clang__) && __has_feature (objc_arc)
#define USE_ARC 1
#endif
#endif

#if !USE_ARC
#ifndef __unsafe_unretained
#define __unsafe_unretained
#endif
#ifndef __autoreleasing
#define __autoreleasing
#endif
#endif

#if !__has_feature (objc_instancetype)
typedef id instancetype;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= 101100 && __has_feature (objc_generics)
#define NSArrayOf(ObjectType)		NSArray <ObjectType>
#define NSMutableArrayOf(ObjectType)	NSMutableArray <ObjectType>
#define NSSetOf(ObjectType)		NSSet <ObjectType>
#define NSMutableSetOf(ObjectType)	NSMutableSet <ObjectType>
#define NSDictionaryOf(KeyT, ObjectT)	NSDictionary <KeyT, ObjectT>
#define NSMutableDictionaryOf(KeyT, ObjectT) NSMutableDictionary <KeyT, ObjectT>
#define NSMapTableOf(KeyT, ObjectT)	NSMapTable <KeyT, ObjectT>
#else
#define NSArrayOf(ObjectType)		NSArray
#define NSMutableArrayOf(ObjectType)	NSMutableArray
#define NSSetOf(ObjectType)		NSSet
#define NSMutableSetOf(ObjectType)	NSMutableSet
#define NSDictionaryOf(KeyT, ObjectT)	NSDictionary
#define NSMutableDictionaryOf(KeyT, ObjectT) NSMutableDictionary
#define NSMapTableOf(KeyT, ObjectT)	NSMapTable
#define __kindof
#endif

#ifndef NS_NOESCAPE
#define NS_NOESCAPE CF_NOESCAPE
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101200
typedef NSString * NSKeyValueChangeKey;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101201
typedef NSString * NSTouchBarItemIdentifier;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101300
typedef NSString * NSAccessibilityAttributeName;
typedef NSString * NSAccessibilityActionName;
typedef NSString * NSAccessibilityNotificationName;
typedef NSString * NSAccessibilityParameterizedAttributeName;
typedef NSString * NSAppearanceName;
typedef NSString * NSAttributedStringDocumentAttributeKey;
typedef NSString * NSColorListName;
typedef NSString * NSColorName;
typedef NSString * NSPasteboardType;
typedef NSString * NSPasteboardName;
typedef NSString * NSToolbarIdentifier;
typedef NSString * NSToolbarItemIdentifier;
typedef NSString * NSWindowTabbingIdentifier;
#endif

/* Some methods that are not declared in older versions.  Should be
   used with some runtime check such as `respondsToSelector:'. */

#if MAC_OS_X_VERSION_MAX_ALLOWED < 1070
@interface NSColor (AvailableOn1070AndLater)
+ (NSColor *)colorWithSRGBRed:(CGFloat)red green:(CGFloat)green
			 blue:(CGFloat)blue alpha:(CGFloat)alpha;
@end
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 1080
@interface NSColor (AvailableOn1080AndLater)
+ (NSColor *)colorWithCGColor:(CGColorRef)cgColor;
- (CGColorRef)CGColor;
@end
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 1080
@interface NSFileManager (AvailableOn1080AndLater)
- (BOOL)trashItemAtURL:(NSURL *)url resultingItemURL:(NSURL **)outResultingURL
		 error:(NSError **)error;
@end
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 1070
enum {
  NSApplicationPresentationFullScreen			= 1 << 10,
  NSApplicationPresentationAutoHideToolbar		= 1 << 11
};
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101200
enum {
    NSWindowListOrderedFrontToBack = (1 << 0)
};
typedef NSInteger NSWindowListOptions;

@interface NSApplication (AvailableOn101200AndLater)
- (void)enumerateWindowsWithOptions:(NSWindowListOptions)options
			 usingBlock:(void (NS_NOESCAPE ^) (NSWindow *window,
							   BOOL *stop))block;
@end
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101300
typedef NSInteger NSModalResponse;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 1090
static const NSModalResponse NSModalResponseAbort = NSRunAbortedResponse;
static const NSModalResponse NSModalResponseContinue = NSRunContinuesResponse;
static const NSModalResponse NSModalResponseOK = NSOKButton;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 1070
enum {
  NSWindowCollectionBehaviorFullScreenPrimary	= 1 << 7,
  NSWindowCollectionBehaviorFullScreenAuxiliary	= 1 << 8
};
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 1070
enum {
  NSWindowAnimationBehaviorDefault		= 0,
  NSWindowAnimationBehaviorNone			= 2,
  NSWindowAnimationBehaviorDocumentWindow	= 3,
  NSWindowAnimationBehaviorUtilityWindow	= 4,
  NSWindowAnimationBehaviorAlertPanel		= 5
};
typedef NSInteger NSWindowAnimationBehavior;

enum {
  NSFullScreenWindowMask = 1 << 14
};

@interface NSWindow (AvailableOn1070AndLater)
- (NSWindowAnimationBehavior)animationBehavior;
- (void)setAnimationBehavior:(NSWindowAnimationBehavior)newAnimationBehavior;
- (void)toggleFullScreen:(id)sender;
- (CGFloat)backingScaleFactor;
@end
#endif

#if MAC_OS_X_VERSION_MIN_REQUIRED < 101000
@interface NSWindow (Undocumented)
- (NSRect)_intersectBottomCornersWithRect:(NSRect)viewRect;
- (void)_maskRoundedBottomCorners:(NSRect)clipRect;
@end
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101300
@interface NSWindowTabGroup : NSObject
@property (readonly, copy) NSArrayOf (NSWindow *) *windows;
@property (getter=isOverviewVisible) BOOL overviewVisible;
@property (readonly, getter=isTabBarVisible) BOOL tabBarVisible;
@property (assign) NSWindow *selectedWindow;
@end

@interface NSWindow (AvailableOn101300AndLater)
@property (readonly, assign) NSWindowTabGroup *tabGroup;
- (void)toggleTabOverview:(id)sender;
@end
#endif

/* Undocumented NSWindowStackController class and NSWindow property to
   access it.  Only used as a fallback for NSWindowTabGroup on macOS
   10.12.  */
@interface NSWindowStackController : NSObject
@property (assign) NSWindow *selectedWindow;
@end

@interface NSWindow (UndocumentedOn101200)
@property (readonly, assign) NSWindowStackController *_windowStackController;
@end

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101200
enum {
  NSWindowStyleMaskBorderless		= NSBorderlessWindowMask,
  NSWindowStyleMaskTitled		= NSTitledWindowMask,
  NSWindowStyleMaskClosable		= NSClosableWindowMask,
  NSWindowStyleMaskMiniaturizable	= NSMiniaturizableWindowMask,
  NSWindowStyleMaskResizable		= NSResizableWindowMask,
  NSWindowStyleMaskFullScreen		= NSFullScreenWindowMask
};
typedef NSUInteger NSWindowStyleMask;

enum {
  NSWindowUserTabbingPreferenceManual,
  NSWindowUserTabbingPreferenceAlways,
  NSWindowUserTabbingPreferenceInFullScreen
};
typedef NSInteger NSWindowUserTabbingPreference;

enum {
  NSWindowTabbingModeAutomatic,
  NSWindowTabbingModePreferred,
  NSWindowTabbingModeDisallowed
};
typedef NSInteger NSWindowTabbingMode;

@interface NSWindow (AvailableOn101200AndLater)
+ (NSWindowUserTabbingPreference)userTabbingPreference;
- (void)addTabbedWindow:(NSWindow *)window
		ordered:(NSWindowOrderingMode)ordered;
@property NSWindowTabbingMode tabbingMode;
@property (copy) NSWindowTabbingIdentifier tabbingIdentifier;
@property (readonly, copy) NSArrayOf (NSWindow *) *tabbedWindows;
@end
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 1070
@interface NSScreen (AvailableOn1070AndLater)
- (CGFloat)backingScaleFactor;
@end
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 1090
@interface NSScreen (AvailableOn1090AndLater)
+ (BOOL)screensHaveSeparateSpaces;
@end
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101500
@interface NSScreen (AvailableOn101500AndLater)
@property (readonly, copy) NSString *localizedName;
@end
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 1090
@interface NSAppearance : NSObject
+ (NSAppearance *)appearanceNamed:(NSAppearanceName)name;
+ (NSAppearance *)currentAppearance;
+ (void)setCurrentAppearance:(NSAppearance *)appearance;
@end

@protocol NSAppearanceCustomization <NSObject>
@property (retain) NSAppearance *appearance;
@property (readonly, retain) NSAppearance *effectiveAppearance;
@end

@interface NSWindow (AppearanceCustomization) <NSAppearanceCustomization>
@end

@interface NSView (AppearanceCustomization) <NSAppearanceCustomization>
@end
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 110000
@interface NSAppearance (AvailableOn110000AndLater)
+ (NSAppearance *)currentDrawingAppearance;
- (void)performAsCurrentDrawingAppearance:(void (NS_NOESCAPE ^)(void))block;
@end
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101400
@interface NSApplication (AppearanceCustomization) <NSAppearanceCustomization>
@end
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101000
@interface NSAppearance (AvailableOn101000AndLater)
@property (readonly, copy) NSAppearanceName name;
@property (readonly) BOOL allowsVibrancy;
@end
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101300
typedef NSInteger NSWindowLevel;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101300
enum {
  NSFontPanelModeMaskFace = NSFontPanelFaceModeMask,
  NSFontPanelModeMaskSize = NSFontPanelSizeModeMask,
  NSFontPanelModeMaskCollection = NSFontPanelCollectionModeMask
};
typedef NSUInteger NSFontPanelModeMask;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101400
@protocol NSFontChanging <NSObject>
@optional
- (void)changeFont:(NSFontManager *)sender;
- (NSFontPanelModeMask)validModesForFontPanel:(NSFontPanel *)fontPanel;
@end

@protocol NSMenuItemValidation <NSObject>
- (BOOL)validateMenuItem:(NSMenuItem *)menuItem;
@end

@protocol NSToolbarItemValidation <NSObject>
- (BOOL)validateToolbarItem:(NSToolbarItem *)item;
@end
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101300
enum {
  NSProgressIndicatorStyleBar = NSProgressIndicatorBarStyle,
  NSProgressIndicatorStyleSpinning = NSProgressIndicatorSpinningStyle
};
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 1090
@interface NSSavePanel (AvailableOn1090AndLater)
@property BOOL showsTagField;
@end
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 1070
enum {
    NSEventPhaseNone        = 0,
    NSEventPhaseBegan       = 0x1 << 0,
    NSEventPhaseStationary  = 0x1 << 1,
    NSEventPhaseChanged     = 0x1 << 2,
    NSEventPhaseEnded       = 0x1 << 3,
    NSEventPhaseCancelled   = 0x1 << 4,
};
typedef NSUInteger NSEventPhase;

@interface NSEvent (AvailableOn1070AndLater)
- (BOOL)hasPreciseScrollingDeltas;
- (CGFloat)scrollingDeltaX;
- (CGFloat)scrollingDeltaY;
- (NSEventPhase)momentumPhase;
- (BOOL)isDirectionInvertedFromDevice;
- (NSEventPhase)phase;
+ (BOOL)isSwipeTrackingFromScrollEventsEnabled;
@end
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 1080
enum {
    NSEventTypeSmartMagnify = 32
};

enum {
    NSEventPhaseMayBegin    = 0x1 << 5
};
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101000
typedef NSUInteger NSEventModifierFlags;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101100
@interface NSEvent (AvailableOn101003AndLater)
- (NSInteger)stage;
@end
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101200
enum {
  NSEventTypeLeftMouseDown	= NSLeftMouseDown,
  NSEventTypeLeftMouseUp	= NSLeftMouseUp,
  NSEventTypeMouseMoved		= NSMouseMoved,
  NSEventTypeLeftMouseDragged	= NSLeftMouseDragged,
  NSEventTypeKeyDown		= NSKeyDown,
  NSEventTypeKeyUp		= NSKeyUp,
  NSEventTypeApplicationDefined	= NSApplicationDefined,
  NSEventTypeScrollWheel	= NSScrollWheel
};

enum {
  NSEventMaskLeftMouseDown	= NSLeftMouseDownMask,
  NSEventMaskLeftMouseUp	= NSLeftMouseUpMask,
  NSEventMaskRightMouseDown	= NSRightMouseDownMask,
  NSEventMaskRightMouseUp	= NSRightMouseUpMask,
  NSEventMaskMouseMoved		= NSMouseMovedMask,
  NSEventMaskLeftMouseDragged	= NSLeftMouseDraggedMask,
  NSEventMaskRightMouseDragged	= NSRightMouseDraggedMask,
  NSEventMaskMouseEntered	= NSMouseEnteredMask,
  NSEventMaskMouseExited	= NSMouseExitedMask,
  NSEventMaskKeyDown		= NSKeyDownMask,
  NSEventMaskKeyUp		= NSKeyUpMask,
  NSEventMaskScrollWheel	= NSScrollWheelMask,
  NSEventMaskOtherMouseDown	= NSOtherMouseDownMask,
  NSEventMaskOtherMouseUp	= NSOtherMouseUpMask,
  NSEventMaskOtherMouseDragged	= NSOtherMouseDraggedMask,
  NSEventMaskAny		= NSAnyEventMask
};

enum {
  NSEventModifierFlagCapsLock	= NSAlphaShiftKeyMask,
  NSEventModifierFlagShift	= NSShiftKeyMask,
  NSEventModifierFlagControl	= NSControlKeyMask,
  NSEventModifierFlagOption	= NSAlternateKeyMask,
  NSEventModifierFlagCommand	= NSCommandKeyMask,
  NSEventModifierFlagNumericPad	= NSNumericPadKeyMask,
  NSEventModifierFlagHelp	= NSHelpKeyMask,
  NSEventModifierFlagFunction	= NSFunctionKeyMask,
  NSEventModifierFlagDeviceIndependentFlagsMask
				= NSDeviceIndependentModifierFlagsMask
};
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 1070
@interface NSAnimationContext (AvailableOn1070AndLater)
+ (void)runAnimationGroup:(void (^)(NSAnimationContext *context))changes
        completionHandler:(void (^)(void))completionHandler;
- (void)setTimingFunction:(CAMediaTimingFunction *)newTimingFunction;
@end

@interface CALayer (AvailableOn1070AndLater)
@property CGFloat contentsScale;
@end
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101200
static const NSBezelStyle NSBezelStyleRounded = NSRoundedBezelStyle;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 1090
enum {
  NSPaperOrientationPortrait	= NSPortraitOrientation,
  NSPaperOrientationLandscape	= NSLandscapeOrientation
};
typedef NSInteger NSPaperOrientation;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101000
@interface NSWorkspace (AvailableOn101000AndLater)
- (BOOL)accessibilityDisplayShouldIncreaseContrast;
- (BOOL)accessibilityDisplayShouldDifferentiateWithoutColor;
- (BOOL)accessibilityDisplayShouldReduceTransparency;
@end
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 1080
@interface NSView (AvailableOn1080AndLater)
@property (readonly) BOOL wantsUpdateLayer;
@end
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 1090
@interface NSView (AvailableOn1090AndLater)
- (void)setLayerUsesCoreImageFilters:(BOOL)usesFilters;
@end
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101000
typedef NSUInteger NSAutoresizingMaskOptions;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101200
enum {
  NSCompositingOperationSourceOver = NSCompositeSourceOver
};
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101200
enum {
  NSControlSizeRegular	= NSRegularControlSize,
  NSControlSizeSmall	= NSSmallControlSize
};
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101300
typedef NSInteger NSControlStateValue;
static const NSControlStateValue NSControlStateValueOff = NSOffState;
static const NSControlStateValue NSControlStateValueOn = NSOnState;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 110000
@interface NSImage (AvailableOn110000AndLater)
+ (instancetype)imageWithSystemSymbolName:(NSString *)symbolName
		 accessibilityDescription:(NSString *)description;
@end
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101201
@protocol NSTouchBarDelegate @end

@interface NSTouchBarItem : NSObject <NSCoding>
- (instancetype)initWithIdentifier:(NSTouchBarItemIdentifier)identifier;
@end

@interface NSCustomTouchBarItem : NSTouchBarItem
@property (retain) __kindof NSView *view;
@end

@interface NSCandidateListTouchBarItem : NSTouchBarItem
@end

@interface NSTouchBar : NSObject <NSCoding>
@property (assign) id <NSTouchBarDelegate> delegate;
@property (copy) NSArrayOf (NSTouchBarItemIdentifier) *defaultItemIdentifiers;
@property (copy) NSTouchBarItemIdentifier principalItemIdentifier;
@end
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 1070
@interface NSView (AvailableOn1070AndLater)
@property BOOL translatesAutoresizingMaskIntoConstraints;
@end

@interface NSLayoutConstraint : NSObject <NSAnimatablePropertyContainer>
@end
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101000
@interface NSLayoutConstraint (AvailableOn101000AndLater)
@property (getter=isActive) BOOL active;
@end
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101100
@interface NSLayoutAnchor : NSObject <NSCopying, NSCoding>
- (NSLayoutConstraint *)constraintEqualToAnchor:(NSLayoutAnchor *)anchor;
- (NSLayoutConstraint *)constraintGreaterThanOrEqualToAnchor:(NSLayoutAnchor *)anchor;
- (NSLayoutConstraint *)constraintLessThanOrEqualToAnchor:(NSLayoutAnchor *)anchor;
- (NSLayoutConstraint *)constraintEqualToAnchor:(NSLayoutAnchor *)anchor constant:(CGFloat)c;
- (NSLayoutConstraint *)constraintGreaterThanOrEqualToAnchor:(NSLayoutAnchor *)anchor constant:(CGFloat)c;
- (NSLayoutConstraint *)constraintLessThanOrEqualToAnchor:(NSLayoutAnchor *)anchor constant:(CGFloat)c;
@end

@interface NSLayoutXAxisAnchor : NSLayoutAnchor
@end
@interface NSLayoutYAxisAnchor : NSLayoutAnchor
@end

@interface NSLayoutDimension : NSLayoutAnchor
- (NSLayoutConstraint *)constraintEqualToConstant:(CGFloat)c;
- (NSLayoutConstraint *)constraintGreaterThanOrEqualToConstant:(CGFloat)c;
- (NSLayoutConstraint *)constraintLessThanOrEqualToConstant:(CGFloat)c;
- (NSLayoutConstraint *)constraintEqualToAnchor:(NSLayoutDimension *)anchor multiplier:(CGFloat)m;
- (NSLayoutConstraint *)constraintGreaterThanOrEqualToAnchor:(NSLayoutDimension *)anchor multiplier:(CGFloat)m;
- (NSLayoutConstraint *)constraintLessThanOrEqualToAnchor:(NSLayoutDimension *)anchor multiplier:(CGFloat)m;
- (NSLayoutConstraint *)constraintEqualToAnchor:(NSLayoutDimension *)anchor multiplier:(CGFloat)m constant:(CGFloat)c;
- (NSLayoutConstraint *)constraintGreaterThanOrEqualToAnchor:(NSLayoutDimension *)anchor multiplier:(CGFloat)m constant:(CGFloat)c;
- (NSLayoutConstraint *)constraintLessThanOrEqualToAnchor:(NSLayoutDimension *)anchor multiplier:(CGFloat)m constant:(CGFloat)c;
@end

@interface NSView (AvailableOn101100AndLater)
@property (readonly, retain) NSLayoutXAxisAnchor *leadingAnchor;
@property (readonly, retain) NSLayoutXAxisAnchor *trailingAnchor;
@property (readonly, retain) NSLayoutXAxisAnchor *leftAnchor;
@property (readonly, retain) NSLayoutXAxisAnchor *rightAnchor;
@property (readonly, retain) NSLayoutYAxisAnchor *topAnchor;
@property (readonly, retain) NSLayoutYAxisAnchor *bottomAnchor;
@property (readonly, retain) NSLayoutDimension *widthAnchor;
@property (readonly, retain) NSLayoutDimension *heightAnchor;
@property (readonly, retain) NSLayoutXAxisAnchor *centerXAnchor;
@property (readonly, retain) NSLayoutYAxisAnchor *centerYAnchor;
@property (readonly, retain) NSLayoutYAxisAnchor *firstBaselineAnchor;
@property (readonly, retain) NSLayoutYAxisAnchor *lastBaselineAnchor;
@end
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 1090
@interface NSStackView : NSView
+ (instancetype)stackViewWithViews:(NSArrayOf (NSView *) *)views;
@end
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101200
@interface NSButton (AvailableOn101200AndLater)
+ (instancetype)buttonWithTitle:(NSString *)title image:(NSImage *)image
			 target:(id)target action:(SEL)action;
+ (instancetype)buttonWithTitle:(NSString *)title
			 target:(id)target action:(SEL)action;
+ (instancetype)buttonWithImage:(NSImage *)image
			 target:(id)target action:(SEL)action;
+ (instancetype)checkboxWithTitle:(NSString *)title
			   target:(id)target action:(SEL)action;
+ (instancetype)radioButtonWithTitle:(NSString *)title
			      target:(id)target action:(SEL)action;
@end
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101200
static const NSBitmapImageFileType NSBitmapImageFileTypePNG = NSPNGFileType;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101200
@interface PDFPage (AvailableOn101200AndLater)
- (void) drawWithBox: (PDFDisplayBox) box toContext:(CGContextRef)context;
@end
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED < 101100
typedef NSInteger NSGlyphProperty;

@interface NSLayoutManager (AvailableOn101100AndLater)
- (NSUInteger)getGlyphsInRange:(NSRange)glyphRange glyphs:(CGGlyph *)glyphBuffer
		    properties:(NSGlyphProperty *)props
	      characterIndexes:(NSUInteger *)charIndexBuffer
		    bidiLevels:(unsigned char *)bidiLevelBuffer;
@end
#endif

/* Categories for existing classes.  */

@interface NSData (Emacs)
- (Lisp_Object)lispString;
@end

@interface NSString (Emacs)
+ (instancetype)stringWithLispString:(Lisp_Object)lispString;
+ (instancetype)stringWithUTF8LispString:(Lisp_Object)lispString;
+ (instancetype)stringWithUTF8String:(const char *)bytes fallback:(BOOL)flag;
- (Lisp_Object)lispString;
- (Lisp_Object)UTF8LispString;
- (Lisp_Object)UTF16LispString;
- (NSArrayOf (NSString *) *)componentsSeparatedByCamelCasingWithCharactersInSet:(NSCharacterSet *)separator;
@end

@interface NSMutableArray (Emacs)
- (void)enqueue:(id)obj;
- (id)dequeue;
@end

@interface NSFont (Emacs)
+ (NSFont *)fontWithFace:(struct face *)face;
@end

@interface NSEvent (Emacs)
- (NSEvent *)mouseEventByChangingType:(NSEventType)type
		          andLocation:(NSPoint)location;
- (CGEventRef)coreGraphicsEvent;
@end

@interface NSAttributedString (Emacs)
- (Lisp_Object)UTF16LispString;
@end

@interface NSColor (Emacs)
+ (NSColor *)colorWithEmacsColorPixel:(unsigned long)pixel;
- (CGColorRef)copyCGColor;
- (BOOL)getSRGBComponents:(CGFloat *)components;
+ (NSColor *)colorWithCoreGraphicsColor:(CGColorRef)cgColor;
@end

@interface NSImage (Emacs)
+ (NSImage *)imageWithCGImage:(CGImageRef)cgImage exclusive:(BOOL)flag;
@end

@interface NSApplication (Emacs)
- (void)postDummyEvent;
- (void)runTemporarilyWithBlock:(void (^)(void))block;
@end

@interface NSScreen (Emacs)
+ (NSScreen *)screenContainingPoint:(NSPoint)aPoint;
+ (NSScreen *)closestScreenForRect:(NSRect)aRect;
- (BOOL)containsDock;
- (BOOL)canShowMenuBar;
@end

@interface NSWindow (Emacs)
- (Lisp_Object)lispFrame;
- (NSWindow *)topLevelWindow;
- (void)enumerateChildWindowsUsingBlock:(NS_NOESCAPE void
					 (^)(NSWindow *child, BOOL *stop))block;
@end

@interface NSCursor (Emacs)
+ (NSCursor *)cursorWithThemeCursor:(ThemeCursor)shape;
@end

@interface NSCursor (UndocumentedOn1070AndLater)
+ (NSCursor *)_windowResizeNorthWestSouthEastCursor;
+ (NSCursor *)_windowResizeNorthEastSouthWestCursor;
+ (NSCursor *)_windowResizeNorthSouthCursor;
+ (NSCursor *)_windowResizeNorthCursor;
+ (NSCursor *)_windowResizeSouthCursor;
+ (NSCursor *)_windowResizeEastWestCursor;
+ (NSCursor *)_windowResizeEastCursor;
+ (NSCursor *)_windowResizeWestCursor;
+ (NSCursor *)_windowResizeNorthWestCursor;
+ (NSCursor *)_windowResizeNorthEastCursor;
+ (NSCursor *)_windowResizeSouthWestCursor;
+ (NSCursor *)_windowResizeSouthEastCursor;
@end

#if MAC_OS_X_VERSION_MIN_REQUIRED < 101000
/* Workarounds for memory leaks on OS X 10.9.  */
@interface NSApplication (Undocumented)
- (void)_installMemoryPressureDispatchSources;
- (void)_installMemoryStatusDispatchSources;
@end
#endif

@interface EmacsApplication : NSApplication
@end

@interface EmacsPosingWindow : NSWindow
+ (void)setup;
@end

/* Class for delegate for NSApplication.  It also becomes the target
   of several actions such as those from EmacsMainView, menus,
   dialogs, and actions/services bound in the mac-apple-event
   keymap.  */

@interface EmacsController : NSObject <NSApplicationDelegate, NSUserInterfaceValidations>
{
  /* Points to HOLD_QUIT arg passed to read_socket_hook.  */
  struct input_event *hold_quit;

  /* Number of events stored during a
     handleQueuedEventsWithHoldingQuitIn: call.  */
  int count;

  /* Whether to generate a HELP_EVENT at the end of handleOneNSEvent:
     call.  */
  int do_help;

  /* Non-zero means that a HELP_EVENT has been generated since Emacs
   start.  */
  bool any_help_event_p;

  /* The frame on which a HELP_EVENT occurs.  */
  struct frame *emacsHelpFrame;

  /* The item selected in the popup menu.  */
  int menuItemSelection;

  /* Non-nil means left mouse tracking has been suspended and will be
     resumed when this block is called.  */
  void (^trackingResumeBlock)(void);

  /* Whether a service provider for Emacs is registered as of
     applicationWillFinishLaunching: or not.  */
  BOOL serviceProviderRegistered;

  /* Whether the application should update its presentation options
     when it becomes active next time.  */
  BOOL needsUpdatePresentationOptionsOnBecomingActive;

  /* Whether conflicting Cocoa's text system key bindings (e.g., C-q)
     are disabled or not.  */
  BOOL conflictingKeyBindingsDisabled;

  /* Saved key bindings with or without conflicts (currently, those
     for writing direction commands on Mac OS X 10.6).  */
  NSDictionaryOf (NSString *, NSString *)
    *keyBindingsWithConflicts, *keyBindingsWithoutConflicts;

  /* Help topic that the user selected using Help menu search.  */
  id selectedHelpTopic;

  /* Search string for which the user selected "Show All Help
     Topics".  */
  NSString *searchStringForAllHelpTopics;

#if MAC_OS_X_VERSION_MIN_REQUIRED < 101100
  /* Date of last flushWindow call.  */
  NSDate *lastFlushDate;

  /* Timer for deferring flushWindow call.  */
  NSTimer *flushTimer;

  /* Set of windows whose flush is deferred.  */
  NSMutableSetOf (NSWindow *) *deferredFlushWindows;
#endif

  /* Set of key paths for which NSApp is observed via the
     `application-kvo' subkeymap in mac-apple-event-map.  */
  NSSetOf (NSString *) *observedKeyPaths;
}
- (void)updateObservedKeyPaths;
- (int)getAndClearMenuItemSelection;
- (void)storeInputEvent:(id)sender;
- (void)setMenuItemSelectionToTag:(id)sender;
- (void)storeEvent:(struct input_event *)bufp;
- (void)setTrackingResumeBlock:(void (^)(void))block;
- (NSTimeInterval)minimumIntervalForReadSocket;
- (int)handleQueuedNSEventsWithHoldingQuitIn:(struct input_event *)bufp;
- (void)cancelHelpEchoForEmacsFrame:(struct frame *)f;
- (BOOL)conflictingKeyBindingsDisabled;
- (void)setConflictingKeyBindingsDisabled:(BOOL)flag;
#if MAC_OS_X_VERSION_MIN_REQUIRED < 101400
- (void)flushWindow:(NSWindow *)window force:(BOOL)flag;
#endif
- (void)updatePresentationOptions;
- (void)showMenuBar;
@end

/* Like NSWindow, but allows suspend/resume resize control tracking.
   It also provides the delegate methods windowWillEnterTabOverview
   and windowDidExitTabOverview.  */

@interface EmacsWindow : NSWindow <NSMenuItemValidation>
{
  /* Left mouse up event used for suspending resize control
     tracking.  */
  NSEvent *mouseUpEvent;

  /* Pointer location of the left mouse down event that initiated the
     current resize control tracking session.  The value is in the
     base coordinate system of the window.  */
  NSPoint resizeTrackingStartLocation;

  /* Window size when the current resize control tracking session was
     started.  */
  NSSize resizeTrackingStartWindowSize;

  /* Whether the call to setupResizeTracking: is suspended for the
     next left mouse down event.  */
  BOOL setupResizeTrackingSuspended;

  /* Whether the window should be made visible when the application
     gets unhidden next time.  */
  BOOL needsOrderFrontOnUnhide;

  /* Positive values mean the usual -constrainFrameRect:toScreen:
     behavior is suspended.  */
  char constrainingToScreenSuspensionCount;

  /* Tab group object that is showing its overview invoked from the
     EmacsWindow object.  */
  NSWindowTabGroup *observedTabGroup;
}
- (void)suspendResizeTracking:(NSEvent *)event
	   positionAdjustment:(NSPoint)adjustment;
- (void)resumeResizeTracking;
- (BOOL)needsOrderFrontOnUnhide;
- (void)setNeedsOrderFrontOnUnhide:(BOOL)flag;
- (void)suspendConstrainingToScreen:(BOOL)flag;
- (void)exitTabGroupOverview;
@end

@interface NSObject (EmacsWindowDelegate)
- (BOOL)window:(NSWindow *)sender shouldForwardAction:(SEL)action to:(id)target;
- (NSRect)window:(NSWindow *)sender willConstrainFrame:(NSRect)frameRect
	toScreen:(NSScreen *)screen;
- (void)windowWillEnterTabOverview;
- (void)windowDidExitTabOverview;
@end

@class EmacsView;
@class EmacsOverlayView;

/* Class for delegate of NSWindow and NSToolbar (see its Toolbar
   category declared later).  It also becomes that target of
   frame-dependent actions such as those from font panels.  */

@interface EmacsFrameController : NSObject <NSWindowDelegate>
{
  /* The Emacs frame corresponding to the NSWindow that
     EmacsFrameController object is associated with as delegate.  */
  struct frame *emacsFrame;

  /* Window and view for the Emacs frame.  */
  EmacsWindow *emacsWindow;
  EmacsView *emacsView;

  /* View overlaid on the Emacs frame window.  */
  EmacsOverlayView *overlayView;

  /* Window for the spinning progress indicator (corresponding to
     hourglass) shown at the upper-right corner of the window.  */
  NSWindow *hourglassWindow;

  /* The current window manager state.  */
  WMState windowManagerState;

  /* The last window frame before maximize/fullscreen.  The position
     is relative to the top left corner of the screen.  */
  NSRect savedFrame;

  /* The root Core Animation layer for mac-start-animation.  */
  CALayer *animationLayer;

  /* The block called when the window ends live resize.  */
  void (^liveResizeCompletionHandler) (void);

  /* Whether transition effect should be set up when the window will
     start live resize.  */
  BOOL shouldLiveResizeTriggerTransition;

  /* Boolean to cache [emacsView isHiddenOrHasHiddenAncestor].  */
  BOOL emacsViewIsHiddenOrHasHiddenAncestor;

  /* Window manager state after the full screen transition.  */
  WMState fullScreenTargetState;

  /* Enum value determining the symbol that is set as `fullscreen'
     frame parameter after the full screen transition.  */
  enum {
    FULLSCREEN_PARAM_NONE, FULLSCREEN_PARAM_NIL,
    FULLSCREEN_PARAM_FULLBOTH, FULLSCREEN_PARAM_FULLSCREEN
  } fullscreenFrameParameterAfterTransition;

  /* Array of blocks called when the window completes full screen
     transition.  Each block is called with the window object and a
     boolean value meaning whether the transition has succeeded.  */
  NSMutableArrayOf (void (^)(EmacsWindow *, BOOL))
    *fullScreenTransitionCompletionHandlers;

  /* Map from child windows to alpha values that are saved while they
     are made completely transparent temporarily.  */
  NSMapTableOf (NSWindow *, NSNumber *) *savedChildWindowAlphaMap;
}
- (instancetype)initWithEmacsFrame:(struct frame *)emacsFrame;
- (void)setupEmacsView;
- (void)setupWindow;
- (void)closeWindow;
- (struct frame *)emacsFrame;
- (EmacsWindow *)emacsWindow;
- (BOOL)acceptsFocus;
- (WMState)windowManagerState;
- (void)setWindowManagerState:(WMState)newState;
- (void)updateBackingScaleFactor;
- (BOOL)emacsViewIsHiddenOrHasHiddenAncestor;
- (void)updateEmacsViewIsHiddenOrHasHiddenAncestor;
- (void)displayEmacsViewIfNeeded;
- (void)lockFocusOnEmacsView;
- (void)unlockFocusOnEmacsView;
- (void)scrollEmacsViewRect:(NSRect)aRect by:(NSSize)offset;
#if HAVE_MAC_METAL
- (void)updateEmacsViewMTLObjects;
#endif
- (NSPoint)convertEmacsViewPointToScreen:(NSPoint)point;
- (NSPoint)convertEmacsViewPointFromScreen:(NSPoint)point;
- (NSRect)convertEmacsViewRectToScreen:(NSRect)rect;
- (NSRect)convertEmacsViewRectFromScreen:(NSRect)rect;
- (NSRect)centerScanEmacsViewRect:(NSRect)rect;
- (void)invalidateCursorRectsForEmacsView;
#if MAC_OS_X_VERSION_MIN_REQUIRED < 101000
- (void)maskRoundedBottomCorners:(NSRect)clipRect directly:(BOOL)flag;
#endif
- (NSBitmapImageRep *)bitmapImageRepInEmacsViewRect:(NSRect)rect;
- (NSBitmapImageRep *)bitmapImageRep;
- (void)storeModifyFrameParametersEvent:(Lisp_Object)alist;
- (BOOL)isWindowFrontmost;
- (void)setupLiveResizeTransition;
- (void)setShouldLiveResizeTriggerTransition:(BOOL)flag;
- (void)setLiveResizeCompletionHandler:(void (^)(void))block;
- (BOOL)shouldBeTitled;
- (BOOL)shouldHaveShadow;
- (void)updateWindowStyle;
@end


/* Class for applicaion-side double buffering.  */

@interface EmacsBacking : NSObject
{
  /* Backing bitmaps used in application-side double buffering.  If
     backSurface below is NULL, then frontBitmap should also be NULL,
     and CALayer contents is a CGImage generated from backBitmap.
     Otherwise, CALayer contents is of IOSurface and updated by
     swapping.  */
  CGContextRef backBitmap, frontBitmap;

  /* Hardware-accelerated buffer data for backing bitmap and CALayer
     contents.  NULL for backSurface means the backing bitmap uses the
     ordinary main memory as its data, and frontSurface should also be
     NULL in this case.  */
  IOSurfaceRef backSurface, frontSurface;

  /* Semaphore used for synchronizing completion of asynchronous copy
     from CALayer contents to backing bitmap after swapping.  */
  dispatch_semaphore_t copyFromFrontToBackSemaphore;

#if HAVE_MAC_METAL
  /* GPU-accessible image data for backing bitmap and CALayer
     contents.  Both should be nil if backSurface is NULL, and both
     should be non-nil otherwise.  */
  id <MTLTexture> backTexture, frontTexture;

  /* Command queue of the optimal GPU device for the display in which
     the view appears, or nil if the GPU does not support Metal.  */
  id <MTLCommandQueue> mtlCommandQueue;
#endif

  CGFloat scaleFactor;

  /* Lock count for backing bitmap.  */
  char lockCount;
}
- (instancetype)initWithView:(NSView *)view;
- (char)lockCount;
- (NSSize)size;
#if HAVE_MAC_METAL
- (void)updateMTLObjectsForView:(NSView *)view;
#endif
- (void)setContentsForLayer:(CALayer *)layer;
- (void)lockFocus;
- (void)unlockFocus;
- (void)scrollRect:(NSRect)rect by:(NSSize)delta;
- (NSData *)imageBuffersDataForRectanglesData:(NSData *)rectanglesData;
- (void)restoreImageBuffersData:(NSData *)imageBuffersData
	      forRectanglesData:(NSData *)rectanglesData;
@end

/* Class for Emacs view that handles drawing events only.  It is used
   directly by tooltip frames, and indirectly by ordinary frames via
   inheritance.  */

@interface EmacsView : NSView
{
  /* Backing resources for applicaion-side double buffering.  */
  EmacsBacking *backing;

  /* Whether backing synchronization is suspended.  */
  BOOL synchronizeBackingSuspended;
}
- (struct frame *)emacsFrame;
+ (void)globallyDisableUpdateLayer:(BOOL)flag;
- (void)suspendSynchronizingBackingBitmap:(BOOL)flag;
- (void)synchronizeBacking;
- (void)lockFocusOnBacking;
- (void)unlockFocusOnBacking;
- (void)scrollBackingRect:(NSRect)rect by:(NSSize)delta;
#if HAVE_MAC_METAL
- (void)updateMTLObjects;
#endif
@end

/* Class for Emacs view that also handles input events.  Used by
   ordinary frames.  */

@interface EmacsMainView : EmacsView <NSTextInputClient, NSTouchBarDelegate>
{
  /* Target object to which the EmacsMainView object sends
     actions.  */
  id __unsafe_unretained target;

  /* Message selector of the action the EmacsMainView object
     sends.  */
  SEL action;

  /* Stores the Emacs input event that the action method is expected
     to process.  */
  struct input_event inputEvent;

  /* Whether key events were interpreted by intepretKeyEvents:.  */
  BOOL keyEventsInterpreted;

#if MAC_OS_X_VERSION_MIN_REQUIRED < 101000
  /* Whether scrollRect:by: has copied rounded bottom corner area.  */
  BOOL roundedBottomCornersCopied;
#endif

  /* Whether the raw key event below has mapped any of CGEvent flags.
     It is precalculated in keyDown: so as to avoid regeneration of a
     CGEvent object.  */
  BOOL rawKeyEventHasMappedFlags;

  /* Raw key event that is interpreted by intepretKeyEvents:.  */
  NSEvent *rawKeyEvent;

  /* Saved marked text passed by setMarkedText:selectedRange:.  */
  id markedText;

  /* Position in the last normal (non-momentum) wheel event.  */
  NSPoint savedWheelPoint;

  /* Modifiers in the last normal (non-momentum) wheel event.  */
  int savedWheelModifiers;

  /* Stage of the last gesture event of type NSEventTypePressure.  */
  NSInteger pressureEventStage;

  /* Touch bar item used for the candidate list.  Currently, only
     candidates from input methods are displayed.  */
  NSCandidateListTouchBarItem *candidateListTouchBarItem;
}
- (id)target;
- (SEL)action;
- (void)setTarget:(id)anObject;
- (void)setAction:(SEL)aSelector;
- (BOOL)sendAction:(SEL)theAction to:(id)theTarget;
- (struct input_event *)inputEvent;
- (NSString *)string;
- (void)synchronizeChildFrameOrigins;
@end

/* Class for overlay view of an Emacs frame window.  */

@interface EmacsOverlayView : NSView
{
  /* Whether to highlight the area corresponding to the content of the
     Emacs frame window.  */
  BOOL highlighted;
}
- (void)setHighlighted:(BOOL)flag;
#if MAC_OS_X_VERSION_MIN_REQUIRED < 1070
- (void)setShowsResizeIndicator:(BOOL)flag;
#endif
@end

/* Class for scroller that doesn't do modal mouse tracking.  */

@interface NonmodalScroller : NSScroller
{
  /* Timer used for posting events periodically during mouse
     tracking.  */
  NSTimer *timer;

  /* Code for the scroller part that the user hit.  */
  NSScrollerPart hitPart;

  /* Whether the hitPart area should be highlighted.  */
  BOOL hilightsHitPart;

  /* Whether the scroller is created as horizontal.  */
  BOOL isHorizontal;

  /* If the scroller knob is currently being dragged by the user, this
     is the number of pixels from the top of the knob to the place
     where the user grabbed it.  If the knob is pressed but not
     dragged yet, this is a negative number whose absolute value is
     the number of pixels plus 1.  */
  CGFloat knobGrabOffset;

  /* The position of the top (for vertical scroller) or left (for
     horizontal, respectively) of the scroller knob in pixels,
     relative to the knob slot.  */
  CGFloat knobMinEdgeInSlot;
}
+ (void)updateBehavioralParameters;
- (BOOL)dragUpdatesFloatValue;
- (NSTimeInterval)buttonDelay;
- (NSTimeInterval)buttonPeriod;
- (BOOL)pagingBehavior;
@end

/* Just for avoiding warnings about undocumented methods in NSScroller.  */

@interface NSScroller (Undocumented)
- (void)drawArrow:(NSUInteger)position highlightPart:(NSInteger)part;
@end

/* Class for Scroller used for an Emacs window.  */

@interface EmacsScroller : NonmodalScroller
{
  /* Emacs scroll bar for the scroller.  */
  struct scroll_bar *emacsScrollBar;

  /* The size of the scroller knob track area in pixels.  */
  CGFloat knobSlotSpan;

  /* Minimum size of the scroller knob, in pixels.  */
  CGFloat minKnobSpan;

  /* The size of the whole scroller area in pixels.  */
  CGFloat frameSpan;

  /* The position the user clicked in pixels, relative to the whole
     scroller area.  */
  CGFloat clickPositionInFrame;

  /* This is used for saving the `code' and `modifiers' members of an
     input event for a scroller click with the control modifier.  */
  struct input_event inputEvent;

  /* Values in the last mac_set_scroll_bar_thumb call.  */
  int whole, portion;
}
- (void)setEmacsScrollBar:(struct scroll_bar *)bar;
- (struct scroll_bar *)emacsScrollBar;
- (CGFloat)knobSlotSpan;
- (CGFloat)minKnobSpan;
- (CGFloat)knobMinEdgeInSlot;
- (CGFloat)frameSpan;
- (CGFloat)clickPositionInFrame;
- (ptrdiff_t)inputEventCode;
- (int)inputEventModifiers;
- (int)whole;
- (void)setWhole:(int)theWhole;
- (int)portion;
- (void)setPortion:(int)thePortion;
@end

@interface EmacsFrameController (ScrollBar)
- (void)addScrollerWithScrollBar:(struct scroll_bar *)bar;
- (void)setVibrantScrollersHidden:(BOOL)flag;
@end

@interface EmacsToolbarItem : NSToolbarItem
{
  /* Array of CoreGraphics images of the item.  */
  NSArrayOf (id) *coreGraphicsImages;
}
- (void)setCoreGraphicsImage:(CGImageRef)cgImage;
- (void)setCoreGraphicsImages:(NSArrayOf (id) *)cgImages;
@end

/* Dummy protocol for specifying the return type of the selector
   `item' that has multiple possibilities if unspecified.  */
@protocol EmacsToolbarItemViewer
- (NSToolbarItem *)item;
@end

@interface EmacsFrameController (Toolbar) <NSToolbarDelegate, NSToolbarItemValidation>
- (void)setupToolBarWithVisibility:(BOOL)visible;
- (void)updateToolbarDisplayMode;
- (void)storeToolBarEvent:(id)sender;
- (void)noteToolBarMouseMovement:(NSEvent *)event;
@end

/* Like NSFontPanel, but allows suspend/resume slider tracking.  */

@interface EmacsFontPanel : NSFontPanel
{
  /* Left mouse up event used for suspending slider tracking.  */
  NSEvent *mouseUpEvent;

  /* Slider being tracked.  */
  NSSlider * __unsafe_unretained trackedSlider;
}
- (void)suspendSliderTracking:(NSEvent *)event;
- (void)resumeSliderTracking;
@end

@interface EmacsController (FontPanel)
- (void)fontPanelWillClose:(NSNotification *)notification;
@end

@interface EmacsFrameController (FontPanel) <NSFontChanging>
- (NSFont *)fontForFace:(int)faceId character:(int)c
	       position:(int)pos object:(Lisp_Object)object;
- (void)changeFont:(id)sender;
@end

@interface EmacsFrameController (EventHandling)
- (void)noteEnterEmacsView;
- (void)noteLeaveEmacsView;
- (BOOL)noteMouseMovement:(NSPoint)point;
- (BOOL)clearMouseFace:(Mouse_HLInfo *)hlinfo;
- (void)noteMouseHighlightAtX:(int)x y:(int)y;
@end

@interface EmacsFrameController (Hourglass)
- (void)showHourglass:(id)sender;
- (void)hideHourglass:(id)sender;
- (void)updateHourglassWindowOrigin;
@end

@interface EmacsSavePanel : NSSavePanel
@end

@interface EmacsFontDialogController : NSObject <NSWindowDelegate, NSFontChanging>
@end

@interface NSMenu (Emacs)
- (NSMenuItem *)addItemWithWidgetValue:(widget_value *)wv;
- (void)fillWithWidgetValue:(widget_value *)first_wv;
@end

@interface EmacsMenu : NSMenu
@end

@interface NSEvent (Undocumented)
- (BOOL)_continuousScroll;
- (NSInteger)_scrollPhase;
- (CGFloat)deviceDeltaX;
- (CGFloat)deviceDeltaY;
- (CGFloat)deviceDeltaZ;
@end

@interface EmacsController (Menu) <NSMenuDelegate, NSUserInterfaceItemSearching>
- (void)trackMenuBar;
@end

@interface EmacsFrameController (Menu)
- (void)popUpMenu:(NSMenu *)menu atLocationInEmacsView:(NSPoint)location;
@end

@interface EmacsDialogView : NSView <NSTouchBarDelegate>
- (instancetype)initWithWidgetValue:(widget_value *)wv;
@end

@interface EmacsPrintProxyView : NSView
{
  NSArrayOf (NSView *) *views;
}
- (instancetype)initWithViews:(NSArrayOf (NSView *) *)theViews;
@end

@interface NSAppleEventDescriptor (Emacs)
- (OSErr)copyDescTo:(AEDesc *)desc;
@end

@interface EmacsFrameController (DragAndDrop)
- (void)registerEmacsViewForDraggedTypes:(NSArrayOf (NSPasteboardType) *)pboardTypes;
- (void)setOverlayViewHighlighted:(BOOL)flag;
@end

@interface EmacsOSAScript : OSAScript
@end

#ifdef USE_WK_API
@interface WKWebView (Undocumented)
-(void)_setOverrideDeviceScaleFactor:(CGFloat)deviceScaleFactor;
@end
#endif

@interface NSView (Emacs)
- (Emacs_Pix_Container)createXImageFromRect:(NSRect)rect
			    backgroundColor:(NSColor *)color
				scaleFactor:(CGFloat)scaleFactor;
@end

/* Protocol for document rasterization.  */

@protocol EmacsDocumentRasterizer <NSObject>
- (instancetype)initWithURL:(NSURL *)url
		    options:(NSDictionaryOf (NSString *, id) *)options;
- (instancetype)initWithData:(NSData *)data
		     options:(NSDictionaryOf (NSString *, id) *)options;
+ (BOOL)shouldInitializeInMainThread;
- (BOOL)shouldNotCache;
+ (NSArrayOf (NSString *) *)supportedTypes;
- (NSUInteger)pageCount;
- (NSSize)integralSizeOfPageAtIndex:(NSUInteger)index;
- (CGColorRef)copyBackgroundCGColorOfPageAtIndex:(NSUInteger)index;
- (NSDictionaryOf (NSString *, id) *)documentAttributesOfPageAtIndex:(NSUInteger)index;
- (void)drawPageAtIndex:(NSUInteger)index inRect:(NSRect)rect
	      inContext:(CGContextRef)ctx
		options:(NSDictionaryOf (NSString *, id) *)options;
@end

/* Class for PDF rasterization.  */

@interface EmacsPDFDocument : PDFDocument <EmacsDocumentRasterizer>
@end

/* Class for SVG rasterization.  It also works as a WKWebView
   navigation delegate or a WebView frame load delegate.  */

@interface EmacsSVGDocument : NSObject <EmacsDocumentRasterizer
#if MAC_OS_X_VERSION_MAX_ALLOWED >= 101100
#ifdef USE_WK_API
					, WKNavigationDelegate
#else
					, WebFrameLoadDelegate
#endif
#endif
				       >
{
  /* View to render the SVG image.  */
#ifdef USE_WK_API
  WKWebView *webView;
#else
  WebView *webView;
#endif

  /* Rectangle shown as the SVG image within webView.  */
  NSRect viewRect;

  /* Whether a page load has completed.  */
  BOOL isLoaded;
}
@end

/* Class for document rasterization other than PDF.  It also works as
   the layout manager delegate when rasterizing a multi-page
   document.  */

@interface EmacsDocumentRasterizer : NSObject <EmacsDocumentRasterizer, NSLayoutManagerDelegate>
{
  /* The text storage and document attributes for the document to be
     rasterized.  */
  NSTextStorage *textStorage;
  NSDictionaryOf (NSAttributedStringDocumentAttributeKey, id)
    *documentAttributes;
}
- (instancetype)initWithAttributedString:(NSAttributedString *)anAttributedString
		      documentAttributes:(NSDictionaryOf (NSString *, id) *)docAttributes;
@end

@interface EmacsFrameController (Accessibility)
- (void)postAccessibilityNotificationsToEmacsView;
@end

@interface EmacsFrameController (Animation)
- (void)setupAnimationLayer;
- (CALayer *)layerForRect:(NSRect)rect;
- (void)addLayer:(CALayer *)layer;
- (CIFilter *)transitionFilterFromProperties:(Lisp_Object)properties;
- (void)adjustTransitionFilter:(CIFilter *)filter forLayer:(CALayer *)layer;
@end

@interface NSLayoutManager (Emacs)
- (NSRect)enclosingRectForGlyphRange:(NSRange)glyphRange
		     inTextContainer:(NSTextContainer *)textContainer;
@end

@interface EmacsController (Sound) <NSSoundDelegate>
@end
