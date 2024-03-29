/******************************************************************************\
* Copyright (C) 2012-2017 Leap Motion, Inc. All rights reserved.               *
* Leap Motion proprietary and confidential. Not for distribution.              *
* Use subject to the terms of the Leap Motion SDK Agreement available at       *
* https://developer.leapmotion.com/sdk_agreement, or another agreement         *
* between Leap Motion and you, your company or other organization.             *
\******************************************************************************/

#undef __cplusplus

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LeapC.h"
#include "ExampleConnection.h"
#include "motion.h"

static LEAP_CONNECTION* connectionHandle;

Motion motion;

long timediff(clock_t t1, clock_t t2) {
	long elapsed;
	elapsed = ((double)t2 - t1) / CLOCKS_PER_SEC * 1000;
	return elapsed;
}
clock_t t1 = 0;

/** count timediff example
int main(void) {
	clock_t t1, t2;
	int i;
	float x = 2.7182;
	long elapsed;

	t1 = clock();
	for (i = 0; i < 1000000; i++) {
		x = x * 3.1415;
	}
	t2 = clock();

	elapsed = timediff(t1, t2);
	printf("elapsed: %ld ms\n", elapsed);


	return 0;
}
*/

/** Callback for when the connection opens. */
static void OnConnect(){
  printf("Connected.\n");
}

/** Callback for when a device is found. */
static void OnDevice(const LEAP_DEVICE_INFO *props){
  printf("Found device %s.\n", props->serial);
}

/** Callback for when a frame of tracking data is available. */
static void OnFrame(const LEAP_TRACKING_EVENT *frame){//10ms per frame
  //printf("Frame %lli with %i hands.\n", (long long int)frame->info.frame_id, frame->nHands);
  //printf("elapsed: %ld ms\n", timediff(t1, clock()));
  t1 = clock();
  Vector left(0, 0, 0);
  Vector right(0, 0, 0);
  Vector leftPinch(0, 100, 0);//x = strength(0-1) y = distance(0-100)
  Vector rightPinch(0, 100, 0);
  Vector leftPalmDirection;
  Vector rightPalmDirection;
  for(uint32_t h = 0; h < frame->nHands; h++){
    LEAP_HAND* hand = &frame->pHands[h];
	/*
    printf("    Hand id %i is a %s hand with position (%f, %f, %f).\n",
                hand->id,
                (hand->type == eLeapHandType_Left ? "left" : "right"),
                hand->palm.position.x,
                hand->palm.position.y,
                hand->palm.position.z);
	*/
	if (hand->type == eLeapHandType_Left) {
		//printf("left: strength: %f distance: %f\n", hand->pinch_strength, hand->pinch_distance);
		//printf("left palm direction: %f %f %f\n", hand->palm.normal.x, hand->palm.normal.y, hand->palm.normal.z);
		left.x = hand->palm.position.x;
		left.y = hand->palm.position.y;
		left.z = hand->palm.position.z;
		leftPinch.x = hand->pinch_strength;
		leftPinch.y = hand->pinch_distance;
		leftPalmDirection.x = hand->palm.normal.x;
		leftPalmDirection.y = hand->palm.normal.y;
		leftPalmDirection.z = hand->palm.normal.z;
	}
	else {
		//printf("right: strength: %f distance: %f\n", hand->pinch_strength, hand->pinch_distance);
		//printf("right palm direction: %f %f %f\n", hand->palm.normal.x, hand->palm.normal.y, hand->palm.normal.z);
		right.x = hand->palm.position.x;
		right.y = hand->palm.position.y;
		right.z = hand->palm.position.z;
		rightPinch.x = hand->pinch_strength;
		rightPinch.y = hand->pinch_distance;
		rightPalmDirection.x = hand->palm.normal.x;
		rightPalmDirection.y = hand->palm.normal.y;
		rightPalmDirection.z = hand->palm.normal.z;
	}
  }
  //printf("left.z: %f, right.z: %f\n", left.z, right.z);
  motion.insertNewFrame(left.x, left.y, left.z, right.x, right.y, right.z, leftPinch, rightPinch, leftPalmDirection, rightPalmDirection);
}

static void OnImage(const LEAP_IMAGE_EVENT *image){
	/*
  printf("Image %lli  => Left: %d x %d (bpp=%d), Right: %d x %d (bpp=%d)\n",
      (long long int)image->info.frame_id,
      image->image[0].properties.width,image->image[0].properties.height,image->image[0].properties.bpp*8,
      image->image[1].properties.width,image->image[1].properties.height,image->image[1].properties.bpp*8);
	  */
	printf("");
}

static void OnLogMessage(const eLeapLogSeverity severity, const int64_t timestamp,
                         const char* message) {
  const char* severity_str;
  switch(severity) {
    case eLeapLogSeverity_Critical:
      severity_str = "Critical";
      break;
    case eLeapLogSeverity_Warning:
      severity_str = "Warning";
      break;
    case eLeapLogSeverity_Information:
      severity_str = "Info";
      break;
    default:
      severity_str = "";
      break;
  }
  printf("[%s][%lli] %s\n", severity_str, (long long int)timestamp, message);
}

static void* allocate(uint32_t size, eLeapAllocatorType typeHint, void* state) {
  void* ptr = malloc(size);
  return ptr;
}

static void deallocate(void* ptr, void* state) {
  if (!ptr)
    return;
  free(ptr);
}

void OnPointMappingChange(const LEAP_POINT_MAPPING_CHANGE_EVENT *change){
  if (!connectionHandle)
    return;

  uint64_t size = 0;
  if (LeapGetPointMappingSize(*connectionHandle, &size) != eLeapRS_Success || !size)
    return;

  LEAP_POINT_MAPPING* pointMapping = (LEAP_POINT_MAPPING*)malloc(size);
  if (!pointMapping)
    return;

  if (LeapGetPointMapping(*connectionHandle, pointMapping, &size) == eLeapRS_Success &&
      pointMapping->nPoints > 0) {
    printf("Managing %u points as of frame %lld at %lld\n", pointMapping->nPoints, (long long int)pointMapping->frame_id, (long long int)pointMapping->timestamp);
  }
  free(pointMapping);
}

void OnHeadPose(const LEAP_HEAD_POSE_EVENT *event) {
  printf("Head pose:\n");
  printf("    Head position (%f, %f, %f).\n",
    event->head_position.x,
    event->head_position.y,
    event->head_position.z);
  printf("    Head orientation (%f, %f, %f, %f).\n",
    event->head_orientation.w,
    event->head_orientation.x,
    event->head_orientation.y,
    event->head_orientation.z);
 }

int main(int argc, char** argv) {
  //Set callback function pointers
  ConnectionCallbacks.on_connection          = &OnConnect;
  ConnectionCallbacks.on_device_found        = &OnDevice;
  ConnectionCallbacks.on_frame               = &OnFrame;
  ConnectionCallbacks.on_image               = &OnImage;
  ConnectionCallbacks.on_point_mapping_change = &OnPointMappingChange;
  ConnectionCallbacks.on_log_message         = &OnLogMessage;
  ConnectionCallbacks.on_head_pose           = &OnHeadPose;

  connectionHandle = OpenConnection();
  {
    LEAP_ALLOCATOR allocator = { allocate, deallocate, NULL };
    LeapSetAllocator(*connectionHandle, &allocator);
  }
  LeapSetPolicyFlags(*connectionHandle, eLeapPolicyFlag_Images | eLeapPolicyFlag_MapPoints, 0);

  printf("Press Enter to exit program.\n");
  getchar();

  DestroyConnection();

  return 0;
}
//End-of-Sample.c
