//
//  Affdex.h
//  Affdex.framework
//
//  Created by Boisy Pitre on 7/11/13.
//  Copyright (c) 2014 Affectiva, Inc.. All rights reserved.
//

#import <TargetConditionals.h>
#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
#endif
#import <AVFoundation/AVFoundation.h>

@protocol AFDXDetectorDelegate;

/**
 \mainpage
 Welcome to the Affdex SDK for iOS! With this SDK, your iOS app will be able to detect faces and their facial expressions using the built-in camera, or via a file on your iOS device.
 
 <b>Hardware Requirements</b>
 <br>
 <ul>
 <li>Any iPad, iPhone, or iPod Touch running iOS 8 or newer.</li>
 </ul>
 
 <b>Development Requirements</b>
 <br>
 <ul>
 <li> Xcode 6 with the iOS 8 SDK</li>
 </ul>
 
 <b>Getting Started</b>
 <br>
 To get started, visit https://github.com/Affectiva/affdex-ios and pull down the source for our demo app, FollowMe. Ensure that the Code Signing settings for the FollowMe target are setup correctly. The identity is setup for "iPhone Developer" which should match your identity automatically.
 ￼
 If you have any questions, comments or suggestions, please email them to sdk@affectiva.com.
 
 Enjoy the SDK!
 */

/**
 \brief
 This class encapsulates data about a single face
 */
@interface AFDXFace : NSObject <NSCoding>

/**
 \brief
 faceId is a unique identifier for a face in a frame.
 */
@property (assign) NSUInteger faceId;

/* Emotions */

/**
 \brief
 angerScore is the ranking of anger for the face (0 to 100).
 */
@property (assign) CGFloat angerScore;

/**
 \brief
 contemptScore is the ranking of contempt for the face (0 to 100).
 */
@property (assign) CGFloat contemptScore;

/**
 \brief
 disgustScore is the ranking of disgust for the face (0 to 100).
 */
@property (assign) CGFloat disgustScore;

/**
 \brief
 expressivenessScore is the ranking of expressiveness for the face (0 to 100).
 */
@property (assign) CGFloat expressivenessScore;

/**
 \brief
 fearScore is the ranking of fear for the face (0 to 100).
 */
@property (assign) CGFloat fearScore;

/**
 \brief
 joyScore is the ranking of joy for the face (0 to 100).
 */
@property (assign) CGFloat joyScore;

/**
 \brief
 sadnessScore is the ranking of sadness for the face (0 to 100).
 */
@property (assign) CGFloat sadnessScore;

/**
 \brief
 surpriseScore is the ranking of surprise for the face (0 to 100).
 */
@property (assign) CGFloat surpriseScore;

/**
 \brief
 valenceScore is the ranking of the valence for the face (-100 to 100).
 */
@property (assign) CGFloat  valenceScore;

/* Expressions */

/**
 \brief
 attentionScore is the ranking of the attention for the face (0 to 100).
 */
@property (assign) CGFloat attentionScore;

/**
 \brief
 browFurrowScore is the ranking of the brow furrow for the face (0 to 100).
 */
@property (assign) CGFloat browFurrowScore;

/**
 \brief
 browRaiseScore is the ranking of the brow raise for the face (0 to 100).
 */
@property (assign) CGFloat browRaiseScore;

/**
 \brief
 chinRaise is the ranking of the chin raise for the face (0 to 100).
 */
@property (assign) CGFloat  chinRaiseScore;

/**
 \brief
 eyeClosure is the ranking of the eye closure for the face (0 to 100).
 */
@property (assign) CGFloat  eyeClosureScore;

/**
 \brief
 innerBrowRaise is the ranking of the inner brow raise for the face (0 to 100).
 */
@property (assign) CGFloat  innerBrowRaiseScore;

/**
 \brief
 lipCornerDepressorScore is the ranking of the lip depression for the face (0 to 100).
 */
@property (assign) CGFloat lipCornerDepressorScore;

/**
 \brief
 lipPress is the ranking of the lip press for the face (0 to 100).
 */
@property (assign) CGFloat  lipPressScore;

/**
 \brief
 chinRaise is the ranking of the lip pucker for the face (0 to 100).
 */
@property (assign) CGFloat  lipPuckerScore;

/**
 \brief
 lipSuck is the ranking of the lip suck for the face (0 to 100).
 */
@property (assign) CGFloat  lipSuckScore;

/**
 \brief
 mouthOpen is the ranking of the mouth open for the face (0 to 100).
 */
@property (assign) CGFloat  mouthOpenScore;

/**
 \brief
 noseWrinkle is the ranking of the nose wrinkle for the face (0 to 100).
 */
@property (assign) CGFloat  noseWrinkleScore;

/**
 \brief
 smileScore is the ranking of the smile for the face (0 to 100).
 */
@property (assign) CGFloat smileScore;

/**
 \brief
 smirk is the ranking of the smirk for the face (0 to 100).
 */
@property (assign) CGFloat  smirkScore;

/**
 \brief
 upperLipRaise is the ranking of the upper lip raise for the face (0 to 100).
 */
@property (assign) CGFloat  upperLipRaiseScore;

/* Measurements */

/**
 \brief
 interOcularDistance is the distance in pixels between the outer corners of the eyes.
 */
@property (assign) CGFloat  interOcularDistanceScore;

/**
 \brief
 headAngleLeftRight is the ranking of the left/right head angle (yaw) for the face (-30 degrees to 30 degrees).
 */
@property (assign) CGFloat  headAngleLeftRightScore;

/**
 \brief
 headAngleRoll is the ranking of the roll of the head angle for the face (-60 degrees to 60 degrees).
 */
@property (assign) CGFloat  headAngleRollScore;

/**
 \brief
 headAngleUpDown is the ranking of the up/down head angle (pitch) for the face (-30 degrees to 30 degrees).
 */
@property (assign) CGFloat  headAngleUpDownScore;

/* Appearance */

/**
 \brief
 faceBounds contains the bounding box of the face in the frame.
 */
@property (assign) CGRect     faceBounds;

/**
 \brief
 facePoints contains an array of CGPoints representing points on the face.
 */
@property (strong) NSArray    *facePoints;

/**
 \brief
 userInfo private user data that can be associated with this face.
 */
@property (strong) id          userInfo;

@end

/**
 \brief
 This class utilizes Affdex's facial expression detection capabilities by analyzing video frames and returning information about the faces in each frame.
 
 The AFDXDetector class analyzes successive video frames in order to measure the number and degree of facial expressions of the subjects.
 Depending upon the initialization method used, the video frames may come from either the built-in camera of the device, via a file on
 the device, or pushed to the engine through a method.
 */
@interface AFDXDetector : NSObject <AVCaptureVideoDataOutputSampleBufferDelegate>

/**
 \enum AFDXCameraType
 This enumeration is used to specify the camera to use during recording.
 */
typedef enum
{
    /// The front camera specifier
    AFDX_CAMERA_FRONT = 0,
    /// The back camera specifier
    AFDX_CAMERA_BACK  = 1
} AFDXCameraType;

/**
 This contains the path to the license file provided by Affectiva.
 */
@property (nonatomic, strong) NSString *licensePath;

/**
 This property returns the state of the detector.
 */
@property (readonly) BOOL isRunning;

/**
 The queue used to call the delegate's adopted AFDXDetectorDelegate methods.
 */
@property dispatch_queue_t delegateQueue;

/**
 A boolean value that turns on or off the Anger classifier.
 */
@property (nonatomic, assign) BOOL anger;

/**
 A boolean value that turns on or off the Contempt classifier.
 */
@property (nonatomic, assign) BOOL contempt;

/**
 A boolean value that turns on or off the Disgust classifier.
 */
@property (nonatomic, assign) BOOL disgust;

/**
 A boolean value that turns on or off the Expressiveness classifier.
 */
@property (nonatomic, assign) BOOL expressiveness;

/**
 A boolean value that turns on or off the Fear classifier.
 */
@property (nonatomic, assign) BOOL fear;

/**
 A boolean value that turns on or off the Joy classifier.
 */
@property (nonatomic, assign) BOOL joy;

/**
 A boolean value that turns on or off the Sadness classifier.
 */
@property (nonatomic, assign) BOOL sadness;

/**
 A boolean value that turns on or off the Surprise classifier.
 */
@property (nonatomic, assign) BOOL surprise;

/**
 A boolean value that turns on or off the Valence classifier.
 */
@property (nonatomic, assign) BOOL valence;

/**
 A boolean value that turns on or off the Attention classifier.
 */
@property (nonatomic, assign) BOOL attention;

/**
 A boolean value that turns on or off the Brow Furrow classifier.
 */
@property (nonatomic, assign) BOOL browFurrow;

/**
 A boolean value that turns on or off the Brow Raise classifier.
 */
@property (nonatomic, assign) BOOL browRaise;

/**
 A boolean value that turns on or off the Chin Raise classifier.
 */
@property (nonatomic, assign) BOOL chinRaise;

/**
 A boolean value that turns on or off the Eye Closure classifier.
 */
@property (nonatomic, assign) BOOL eyeClosure;

/**
 A boolean value that turns on or off the Inner Brow Raise classifier.
 */
@property (nonatomic, assign) BOOL innerBrowRaise;

/**
 A boolean value that turns on or off the Lip Depressor classifier.
 */
@property (nonatomic, assign) BOOL lipCornerDepressor;

/**
 A boolean value that turns on or off the Lip Press classifier.
 */
@property (nonatomic, assign) BOOL lipPress;

/**
 A boolean value that turns on or off the Lip Pucker classifier.
 */
@property (nonatomic, assign) BOOL lipPucker;

/**
 A boolean value that turns on or off the Lip Suck classifier.
 */
@property (nonatomic, assign) BOOL lipSuck;

/**
 A boolean value that turns on or off the Mouth Open classifier.
 */
@property (nonatomic, assign) BOOL mouthOpen;

/**
 A boolean value that turns on or off the Nose Wrinkle classifier.
 */
@property (nonatomic, assign) BOOL noseWrinkle;

/**
 A boolean value that turns on or off the Smile classifier.
 */
@property (nonatomic, assign) BOOL smile;

/**
 A boolean value that turns on or off the Smirk classifier.
 */
@property (nonatomic, assign) BOOL smirk;

/**
 A boolean value that turns on or off the Upper Lip Raise classifier.
 */
@property (nonatomic, assign) BOOL upperLipRaise;

/**
 A boolean value that turns on or off the Inter Ocular Distance classifier.
 */
@property (nonatomic, assign) BOOL interOcularDistance;

/**
 A boolean value that turns on or off the Head Angle Left Right classifier.
 */
@property (nonatomic, assign) BOOL headAngleLeftRight;

/**
 A boolean value that turns on or off the Head Angle Roll classifier.
 */
@property (nonatomic, assign) BOOL headAngleRoll;

/**
 A boolean value that turns on or off the Head Angle Up Down classifier.
 */
@property (nonatomic, assign) BOOL headAngleUpDown;

/**
 The percentage of time a face was detected (reset at every start/stop)
 */
@property (readonly) float percentFaceDetected;

/**
 The maximum process rate to operate in [FPS]
 */
@property (nonatomic, assign) float maxProcessRate;

/**
 \brief
 userInfo user-defined optional data that is carried with the detector object and useful in blocks
 */
@property (strong) id          userInfo;

/**
 \brief
 delegate The object destined to receive messages of the AFDXDetectorDelegate protocol.
 */
@property (weak)   id          delegate;

/**
 \brief
 Turns on or off all emotion classifiers at once.
 \param
 value        TRUE = turn on all emotion classifiers; FALSE = turn off all emotion classifiers
 */
- (void)setDetectAllEmotions:(BOOL)value;

/**
 \brief
 Turns on or off all expression classifiers at once.
 \param
 value        TRUE = turn on all expression classifiers; FALSE = turn off all expression classifiers
 */
- (void)setDetectAllExpressions:(BOOL)value;


/**
 \brief
 Initializes the ADFXDetector for processing video from a camera.
 
 This method initializes the Affdex facial expression engine and prepares it to receive video frames from the camera
 on the device. The caller specifices which camera (front or back) will be used to capture the frames.
 
 Note that the object "owns" the camera device and will not reqlinuish it until the object is deallocated.
 
 \param
 delegate     The object which will receive emotion messages.
 \param
 camera       An enumerated value indicating which camera (AFDX_CAMERA_FRONT or AFDX_CAMERA_BACK)
 \param
 maximumFaces The maximum number of faces that will be detected by the detector.
 
 @result
 The newly created object.
 */
- (id)initWithDelegate:(id <AFDXDetectorDelegate>)delegate usingCamera:(AFDXCameraType)camera maximumFaces:(NSUInteger)maximumFaces;

/**
 \brief
 Initializes the ADFXDetector for processing video from a file.
 
 This method initializes the Affdex facial expression engine and prepares it to receive video frames from a file
 on the device. The caller specifices the name of the movie file that contains the video to be processed.
 
 \param
 delegate     The object which will receive emotion messages.
 \param
 path         The path to the file containing the video.
 \param
 maximumFaces The maximum number of faces that will be detected by the detector.
 
 \result
 The newly created object.
 */
- (id)initWithDelegate:(id <AFDXDetectorDelegate>)delegate usingFile:(NSString *)path maximumFaces:(NSUInteger)maximumFaces;

/**
 \brief
 Initializes the ADFXDetector for processing video frames pushed by the caller.
 
 This method initializes the Affdex facial expression engine and prepares it to receive video frames pushed from the caller.
 
 \param
 delegate     The object which will receive emotion messages.
 \param
 discrete     If TRUE, then images passed to processImage: are expected to be unrelated.
 \param
 maximumFaces The maximum number of faces that will be detected by the detector.
 
 \result
 The newly created object.
 */
- (id)initWithDelegate:(id <AFDXDetectorDelegate>)delegate discreteImages:(BOOL)discrete maximumFaces:(NSUInteger)maximumFaces;

/**
 \brief
 Starts the AFDXDetector's detection process.
 
 When an AFDXDetector receives this message, it will begin processing frames from the built-in camera or file (assuming the related initialization methods were used), looking for faces.

 \result
 If nil, no error; otherwise an NSError object.
*/
- (NSError *)start;

/**
 \brief
 Stops the AFDXDetector's detection process.
 
 When an AFDXDetector receives this message, it will stop processing frames.
 
 \result
 If nil, no error; otherwise an NSError object.
 */
- (NSError *)stop;

/**
 \brief
 Asks the AFDXDetector to process the passed image as a discrete image.
 
 This method is used when the initWithDelegate:discreteImages:maximumFaces: method is used to create the AFDXDetector.
 Callers may pass frames to this method at any rate that is suitable for them.
 The detector expects subsequent frames to be unrelated to previous frames (e.g. a series of still photos).
 
 \param
 facePicture A reference to an image object to process.
 */
#if TARGET_OS_IPHONE
- (void)processImage:(UIImage *)facePicture;
#else
- (void)processImage:(NSImage *)facePicture;
#endif

/**
 \brief
 Asks the AFDXDetector to process the passed UIImage.
 
 This method is used when the initWithDelegate:discreteImages:maximumFaces: method is used to create the AFDXDetector.
 Callers may pass frames to this method at any rate that is suitable for them.
 The detector expects subsequent frames to be related to previous frames (e.g. a video stream).
 
 \param
 facePicture A reference to a UIImage object to process.
 \param
 time        The time into the stream associated with the facePicture to process.
 */
#if TARGET_OS_IPHONE
- (void)processImage:(UIImage *)facePicture atTime:(NSTimeInterval)time;
#else
- (void)processImage:(NSImage *)facePicture atTime:(NSTimeInterval)time;
#endif

#if TARGET_OS_IPHONE
/**
 \brief
 Rotate a UIImage by the specified number of degrees.
 
 This method is useful for rotating UIImage objects.
 
 \param
 src          The source image to rotate.
 \param
 angleDegrees The angle (in degrees) to rotate the image.
 
 \result
 The rotated UIImage is returned.
 */
- (UIImage *)rotateUIImage:(const UIImage *)src degrees:(float)angleDegrees;
#endif

/**
 \brief
 A convenience method for drawing points and rectangles on an image
 
 This method can be used to draw points and rectangles associated with faces on an image.
 
 \param
 points An array of CGPoints to draw
 \param
 rectangles An array of CGRects to draw
 \param
 radius The radius of the points to draw
 \param
 pointColor  The color to use when drawing points
 \param
 rectangleColor The color to use when drawing rectangles
 \param
 image The image to draw on.
 
 \result
 A new image that contains the drawn elements
 */
#if TARGET_OS_IPHONE
- (UIImage *)imageByDrawingPoints:(NSArray *)points
                    andRectangles:(NSArray *)rectangles
                       withRadius:(float)radius
                  usingPointColor:(UIColor *)pointColor
                  usingRectangleColor:(UIColor *)rectangleColor
                          onImage:(UIImage *)image;
#else
- (NSImage *)imageByDrawingPoints:(NSArray *)points
                    andRectangles:(NSArray *)rectangles
                       withRadius:(float)radius
                  usingPointColor:(NSColor *)pointColor
              usingRectangleColor:(NSColor *)rectangleColor
                          onImage:(NSImage *)image;
#endif
@end

/**
 \protocol        AFDXDetectorDelegate
 
 \brief
 This protocol provides methods that the AFDXDetector uses to communicate to users of the class.
 */
@protocol AFDXDetectorDelegate

/**
 \brief
 Indicates that the face detector has processed the video.
 
 When the face tracker completes processing of the last frame, this method is called.
 (Applies only to processing of video files).
 
 \param
 detector    A pointer to the AFDXDetector object.
 */
@optional
- (void)detectorDidFinishProcessing:(AFDXDetector *)detector;

/**
 \brief
 Indicates that the face detector has started tracking a face.
 
 When the face tracker detects a face, this method is called. The receiver should expect that tracking continues until
 a call to detectorDidStop: occurs.
 
 \param
 detector    A pointer to the AFDXDetector object.
 \param
 face        A pointer to the AFDXFace object which has entered the frame.
 */
@optional
- (void)detector:(AFDXDetector *)detector didStartDetectingFace:(AFDXFace *)face;

/**
 \brief
 Indicates that the face detector has stopped tracking a face.
 
 When the face tracker no longer detects a face, this method is called. The receiver should expect that there is no
 face tracking until a call to detectorDidStart: occurs.
 
 \param
 detector    A pointer to the AFDXDetector object.
 \param
 face        A pointer to the AFDXFace object which has exited the frame.
 */
@optional
- (void)detector:(AFDXDetector *)detector didStopDetectingFace:(AFDXFace *)face;

/**
 \brief
 Called for all frames captured. Contains information for facial expressions detected for a particular time.
 
 When an facial expression has been detected at a specific point in the video stream, this method will be called with an
 array of AFDXMetric objects. The number of objects passed equals to the number of facial expressions requested when
 the detector was initialized.
 
 A reference to the actual image that was analyzed is passed as well. This can be useful for displaying in a view
 or doing other relevant processing.
 
 The time into the stream that the facial expression occurred is also available.  This is a relative time composed indicating
 the number of seconds into the processing stream that the frame occurred.
 
 This method will also be called if captured frame did not result in the detection of any facial expressions. This may happen for when no face is detected. In this case the array of AFDXMetric objects will be nil.
 
 \param
 detector    A pointer to the AFDXDetector object.
 \param
 faces       A dictionary of AFDXFace objects, indexed by face Id, which represents the faces that were present. Nil if none were detected for a particular frame.
 \param
 image       A reference to the image which was analyzed.
 \param
 time        The time into the stream that the facial expression was expressed.
 */
@required
#if TARGET_OS_IPHONE
- (void)detector:(AFDXDetector *)detector hasResults:(NSMutableDictionary *)faces forImage:(UIImage *)image atTime:(NSTimeInterval)time;
#else
- (void)detector:(AFDXDetector *)detector hasResults:(NSMutableDictionary *)faces forImage:(NSImage *)image atTime:(NSTimeInterval)time;
#endif

@end