//
//  MQTTInMemoryPersistence.m
//  MQTTClient
//
//  Created by Christoph Krey on 22.03.15.
//  Copyright © 2015-2016 Christoph Krey. All rights reserved.
//

#import "MQTTInMemoryPersistence.h"

#ifdef LUMBERJACK
#define LOG_LEVEL_DEF ddLogLevel
#import <CocoaLumberjack/CocoaLumberjack.h>
#ifdef DEBUG
static const DDLogLevel ddLogLevel = DDLogLevelVerbose;
#else
static const DDLogLevel ddLogLevel = DDLogLevelWarning;
#endif
#else
#define DDLogVerbose NSLog
#define DDLogWarn NSLog
#define DDLogInfo NSLog
#define DDLogError NSLog
#endif

@implementation MQTTInMemoryFlow
@synthesize clientId;
@synthesize incomingFlag;
@synthesize retainedFlag;
@synthesize commandType;
@synthesize qosLevel;
@synthesize messageId;
@synthesize topic;
@synthesize data;
@synthesize deadline;

@end

@interface MQTTInMemoryPersistence()
@end

static NSMutableDictionary *clientIds;

@implementation MQTTInMemoryPersistence
@synthesize maxSize;
@synthesize persistent;
@synthesize maxMessages;
@synthesize maxWindowSize;

- (MQTTInMemoryPersistence *)init {
    self = [super init];
    self.maxMessages = MQTT_MAX_MESSAGES;
    self.maxWindowSize = MQTT_MAX_WINDOW_SIZE;
    if (!clientIds) {
        clientIds = [[NSMutableDictionary alloc] init];
    }
    return self;
}

- (NSUInteger)windowSize:(NSString *)clientId {
    NSUInteger windowSize = 0;
    NSArray *flows = [self allFlowsforClientId:clientId
                                  incomingFlag:NO];
    for (MQTTInMemoryFlow *flow in flows) {
        if ([flow.commandType intValue] != MQTT_None) {
            windowSize++;
        }
    }
    return windowSize;
}

- (MQTTInMemoryFlow *)storeMessageForClientId:(NSString *)clientId
                                        topic:(NSString *)topic
                                         data:(NSData *)data
                                   retainFlag:(BOOL)retainFlag
                                          qos:(MQTTQosLevel)qos
                                        msgId:(UInt16)msgId
                                 incomingFlag:(BOOL)incomingFlag
                                  commandType:(UInt8)commandType
                                     deadline:(NSDate *)deadline {
    if (([self allFlowsforClientId:clientId incomingFlag:incomingFlag].count <= self.maxMessages)) {
        MQTTInMemoryFlow *flow = (MQTTInMemoryFlow *)[self createFlowforClientId:clientId
                                                                    incomingFlag:incomingFlag
                                                                       messageId:msgId];
        flow.topic = topic;
        flow.data = data;
        flow.retainedFlag = [NSNumber numberWithBool:retainFlag];
        flow.qosLevel = [NSNumber numberWithUnsignedInteger:qos];
        flow.commandType = [NSNumber numberWithUnsignedInteger:commandType];
        flow.deadline = deadline;
        return flow;
    } else {
        return nil;
    }
}

- (void)deleteFlow:(MQTTInMemoryFlow *)flow {
    NSMutableDictionary *clientIdFlows = [clientIds objectForKey:flow.clientId];
    if (clientIdFlows) {
        NSMutableDictionary *clientIdDirectedFlow = [clientIdFlows objectForKey:flow.incomingFlag];
        if (clientIdDirectedFlow) {
            [clientIdDirectedFlow removeObjectForKey:flow.messageId];
        }
    }
}

- (void)deleteAllFlowsForClientId:(NSString *)clientId {
    DDLogInfo(@"[MQTTInMemoryPersistence] deleteAllFlowsForClientId %@", clientId);
    [clientIds removeObjectForKey:clientId];
}

- (void)sync {
    //
}

- (NSArray *)allFlowsforClientId:(NSString *)clientId
                    incomingFlag:(BOOL)incomingFlag {
    NSArray *flows = nil;
    NSMutableDictionary *clientIdFlows = [clientIds objectForKey:clientId];
    if (clientIdFlows) {
        NSMutableDictionary *clientIdDirectedFlow = [clientIdFlows objectForKey:[NSNumber numberWithBool:incomingFlag]];
        if (clientIdDirectedFlow) {
            flows = clientIdDirectedFlow.allValues;
        }
    }
    return flows;
}

- (MQTTInMemoryFlow *)flowforClientId:(NSString *)clientId
                         incomingFlag:(BOOL)incomingFlag
                            messageId:(UInt16)messageId {
    MQTTInMemoryFlow *flow = nil;
    
    NSMutableDictionary *clientIdFlows = [clientIds objectForKey:clientId];
    if (clientIdFlows) {
        NSMutableDictionary *clientIdDirectedFlow = [clientIdFlows objectForKey:[NSNumber numberWithBool:incomingFlag]];
        if (clientIdDirectedFlow) {
            flow = [clientIdDirectedFlow objectForKey:[NSNumber numberWithUnsignedInteger:messageId]];
        }
    }
    
    return flow;
}

- (MQTTInMemoryFlow *)createFlowforClientId:(NSString *)clientId
                               incomingFlag:(BOOL)incomingFlag
                                  messageId:(UInt16)messageId {
    
    NSMutableDictionary *clientIdFlows = [clientIds objectForKey:clientId];
    if (!clientIdFlows) {
        clientIdFlows = [[NSMutableDictionary alloc] init];
        [clientIds setObject:clientIdFlows forKey:clientId];
    }
    
    NSMutableDictionary *clientIdDirectedFlow = [clientIdFlows objectForKey:[NSNumber numberWithBool:incomingFlag]];
    if (!clientIdDirectedFlow) {
        clientIdDirectedFlow = [[NSMutableDictionary alloc] init];
        [clientIdFlows setObject:clientIdDirectedFlow forKey:[NSNumber numberWithBool:incomingFlag]];
    }
    
    MQTTInMemoryFlow *flow = [[MQTTInMemoryFlow alloc] init];
    flow.clientId = clientId;
    flow.incomingFlag = [NSNumber numberWithBool:incomingFlag];
    flow.messageId = [NSNumber numberWithUnsignedInteger:messageId];
    
    [clientIdDirectedFlow setObject:flow forKey:[NSNumber numberWithUnsignedInteger:messageId]];
    
    return flow;
}

@end
