//
//  SGG_Spine.h
//  SpineTesting
//
//  Created by Michael Redig on 2/10/14.
//  Copyright (c) 2014 Secret Game Group LLC. All rights reserved.
//

#import <SpriteKit/SpriteKit.h>
#import "SpineImport.h"
#import "SGG_SpineBone.h"

typedef enum {
	kSGG_SpineAnimationTypeBone,
	kSGG_SpineAnimationTypeDrawOrder,
	kSGG_SpineAnimationTypeSlots
} kSGG_SpineAnimationType;

@interface SGG_Spine : SKNode

@property (nonatomic, assign) BOOL debugMode;


@property (nonatomic, readonly) BOOL isRunningAnimation;
@property (nonatomic, strong, readonly) NSMutableArray* currentAnimationSequence;
@property (nonatomic, readonly) NSString* currentAnimation;
@property (nonatomic, readonly) NSInteger animationCount;

@property (nonatomic, assign) NSString* queuedAnimation;
@property (nonatomic, assign) CGFloat queueIntro;
@property (nonatomic) bool useQueue;
@property (nonatomic) CGFloat timeResolution; //defaults to 1/120 for smooth playback at 60 fps. If you are planning to have slower motion or ramp, you should increase the resolution (lower values are higher resolution). At 1/120, you will start noticing stutters at speeds lower than 0.5x.
@property (nonatomic) CGFloat playbackSpeed;


@property (nonatomic, strong) NSMutableDictionary* swappedTextures;
@property (nonatomic, strong) NSMutableArray* colorizedNodes;

@property (nonatomic, assign) CGFloat skeletonWidth; //got from spine json
@property (nonatomic, assign) CGFloat skeletonHeight; //got from spine json

@property (nonatomic, strong) NSArray* bones;
@property (nonatomic, strong) NSArray* skinSlots; //active slots in animation
@property (nonatomic, assign) NSString* currentSkin; //name of current skin
@property (nonatomic, readonly) NSInteger currentFrame;


@property (nonatomic, strong) NSArray* slotsArray; //raw array from json
@property (nonatomic, strong) NSDictionary* rawAnimationDictionary; //raw information from JSON

/*!
 * @discussion Sets this object to load an spine with an atlas and a skin preset
 * @attention this overload is for pre-made (compile-time) atlases
 * @param name : NSString. Name of spine json.
 * @param atlasName : NSString Name of atlas in the xcode atlas format
 * @param skinName : NSString with name of the skin to load
 * @param returns: nothing
 */
-(void)skeletonFromFileNamed:(NSString*)name andAtlasNamed:(NSString*)atlasName andUseSkinNamed:(NSString*)skinName;

/*!
  * @discussion Sets this object to load an spine with an atlas and a skin preset
  * @attention  this overload is for runtime generated atlases
  * @param name : NSString. Name of spine json.
  * @param atlas : SKTextureAtlas Object that represents the Atlas
  * @param skinName : NSString with name of the skin to load
  * @param returns: nothing
 */
-(void)skeletonFromFileNamed:(NSString*)name andAtlas:(SKTextureAtlas*)atlas andUseSkinNamed:(NSString*)skinName; //MW Edit

/*!
 * @discussion Method to set the animation to run.
 * @param animationName NSString with the name of animation
 * @param count number of times to repeat animation.
 * @param withIntroPeriodOf time to wait before set animation to run
 * @return Nothing
 */
-(void)runAnimation:(NSString*)animationName andCount:(NSInteger)count withIntroPeriodOf:(const CGFloat)introPeriod andUseQueue:(BOOL)useQueue;
/*!
 * @discussion Method to set the animation to run.
 * @param animationName NSString with the name of animation
 * @param count number of times to repeat animation.
 * @return Nothing
 */
-(void)runAnimation:(NSString*)animationName andCount:(NSInteger)count;
/*!
 * @discussion Method to set a Sequence of Animations to run.
 * @param animationName NSString with the name of animation
 * @param count number of times to repeat animation.
 * @return Nothing
 */
-(void)runAnimationSequence:(NSArray *)animationNames andUseQueue:(BOOL)useQueue;
-(void)stopAnimation;
-(void)jumpToFrame:(NSInteger)frame;
-(void)jumpToNextFrame;
-(void)jumpToPreviousFrame;
/*!
 * @description This method has to be called at every SpriteKit update - name should be changed to UpdateAnimation
 * @return Void
 */
-(void)activateAnimations;
/*!
 * @description Reset all bones to original
 * @return Void
 */

-(void)endOfAnimation;

-(void)resetSkeleton;
/*!
 * @description Changes current skin to given skin
 * @param skin The skin to replace
 * @return Void
 */
-(void)changeSkinTo:(NSString*)skin;
/*!
 * @description Changes skin to an array of selected skins
 * @param slotsToReplace Array of skins to replace
 * @return Void
 */
-(void)changeSkinPartial:(NSDictionary *)slotsToReplace;
/*!
 * @description Resets skins to original
 * @return Void
 */
-(void)resetSkinPartial;
/*!
 * @description Changes texture to an array of selected textures
 * @param attachmentsToReplace Array of textures to replace
 * @return Void
 */
-(void)changeTexturePartial:(NSDictionary *)attachmentsToReplace;
/*!
 * @description Resets swapped textures to the original skin
 * @return Void
 */
-(void)resetTexturePartial;
/*!
 * @description Colorizes all slots with the defined color and blend factor
 * @param color Desired color
 * @param blendFactor Desired intensity
 * @return Void
 */
-(void)colorizeAllSlotsWithColor:(SKColor *)color andIntensity:(CGFloat)blendFactor;
/*!
 * @description Colorizes an array of slots with the defined color and blend factor
 * @param slotsToColorize Selected slots
 * @param color Desired color
 * @param blendFactor Desired intensity
 * @return Void
 */
-(void)colorizeSlots:(NSArray *)slotsToColorize withColor:(SKColor *)color andIntensity:(CGFloat)blendFactor;

/*!
 * @description Resets all colorized slots to white and removes all the colorized nodes
 * @return Void
 */
-(void)resetColorizedSlots;

-(SGG_SpineBone*)findBoneNamed:(NSString*)boneName;




@end
