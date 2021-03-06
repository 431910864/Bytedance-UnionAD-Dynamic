//
//  BUInterstitialAd.h
//  BUAdSDK
//
//  Copyright © 2017年 bytedance. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BUAdSDKDefines.h"
#import "BUMaterialMeta.h"

NS_ASSUME_NONNULL_BEGIN

@class BUSize;
@protocol BUInterstitialAdDelegate;

@interface BUInterstitialAd : NSObject
@property (nonatomic, weak, nullable) id<BUInterstitialAdDelegate> delegate;
@property (nonatomic, getter=isAdValid, readonly) BOOL adValid;

/// media configuration parameters.
@property (nonatomic, copy, readonly) NSDictionary *mediaExt;

/**
 Initializes interstitial ad.
 @param slotID : The unique identifier of interstitial ad.
 @param expectSize : custom size, default 600px * 400px
 @return BUInterstitialAd
 */
- (instancetype)initWithSlotID:(NSString *)slotID size:(BUSize *)expectSize ;

/**
adload_seq：（针对聚合广告位）传递本次请求是为“自然日内某设备某广告位置第N次展示机会”发出的广告请求，同物理位置在自然日从1开始计数，不同物理位置独立计数；example：某原生广告位置，当天第5次产生展示机会，这次展示机向穿山甲发送了4次广告请求，则这4次广告请求的"adload_seq"的值应为5。第二天重新开始计数。

prime_rit：（针对聚合广告位）广告物理位置对应的固定穿山甲广告位id，可以使用第一层的广告位id也可以为某一层的广告位id，但要求同一物理位置在该字段固定上报同一广告位id，不频繁更换；example：某原生广告位，当天共发出了1000个请求，这1000个请求中使用了5个不同target的穿山甲rit，用某X rit来作为该位置的标记rit，则这1000次请求的prime_rit都需要上报X rit的rit id。
*/

- (instancetype)initWithSlotID:(NSString *)slotID adloadSeq:(NSInteger)adloadSeq primeRit:(NSString * __nullable)primeRit size:(BUSize *)expectSize ;
/**
 Load interstitial ad datas.
 */
- (void)loadAdData;
/**
 Display interstitial ad.
 @param rootViewController : root view controller for displaying ad.
 @return : whether it is successfully displayed.
 */
- (BOOL)showAdFromRootViewController:(UIViewController *)rootViewController;

@end

@protocol BUInterstitialAdDelegate <NSObject>

@optional
/**
 This method is called when interstitial ad material loaded successfully.
 */
- (void)interstitialAdDidLoad:(BUInterstitialAd *)interstitialAd;

/**
 This method is called when interstitial ad material failed to load.
 @param error : the reason of error
 */
- (void)interstitialAd:(BUInterstitialAd *)interstitialAd didFailWithError:(NSError * _Nullable)error;

/**
 This method is called when interstitial ad slot will be showing.
 */
- (void)interstitialAdWillVisible:(BUInterstitialAd *)interstitialAd;

/**
 This method is called when interstitial ad is clicked.
 */
- (void)interstitialAdDidClick:(BUInterstitialAd *)interstitialAd;

/**
 This method is called when interstitial ad is about to close.
 */
- (void)interstitialAdWillClose:(BUInterstitialAd *)interstitialAd;

/**
 This method is called when interstitial ad is closed.
 */
- (void)interstitialAdDidClose:(BUInterstitialAd *)interstitialAd;

/**
 This method is called when another controller has been closed.
 @param interactionType : open appstore in app or open the webpage or view video ad details page.
 */
- (void)interstitialAdDidCloseOtherController:(BUInterstitialAd *)interstitialAd interactionType:(BUInteractionType)interactionType;
@end

NS_ASSUME_NONNULL_END
