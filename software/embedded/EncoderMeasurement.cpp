#include "EncoderMeasurement.h"

#include "encoders.h"
#include "constants.h"
#include "Arduino.h"

//Encoder Measurement Class function implementation
void EncoderMeasurement::initialize() {
  initEncoders();       Serial.println("Encoders Initialized..."); //initialize Encoders
  clearEncoderCount();  Serial.println("Encoders Cleared..."); //clear Encoder Counts

  encoderRCount = 0;
  encoderLCount = 0;
  dEncoderR = 0;
  dEncoderL = 0;
  dThetaR = 0.0;
  dThetaL = 0.0;
  dWheelR = 0.0;
  dWheelL= 0.0;
  totalWheelR = 0.0;
  totalWheelL = 0.0;
  mVR = 0.0;
  mVL = 0.0;
}

void EncoderMeasurement::update() {
  float encoderRCountPrev = encoderRCount;
  float encoderLCountPrev = encoderLCount;

  encoderRCount = readEncoder(1);
  encoderLCount = -1 * readEncoder(2);

  // unsigned overflow works in our favor here
  dEncoderR = encoderRCount - encoderRCountPrev;
  dEncoderL = encoderLCount - encoderLCountPrev;

  //update the angle incremet in radians
  dThetaR = (dEncoderR * enc2Theta);
  dThetaL = (dEncoderL * enc2Theta);

  // update the wheel distance travelled in meters
  dWheelR = dEncoderR * enc2Wheel;
  dWheelL = dEncoderL * enc2Wheel;

  // we need to convert to signed values here
  totalWheelR = static_cast<int32_t>(encoderRCount) * enc2Wheel;
  totalWheelL = static_cast<int32_t>(encoderLCount) * enc2Wheel;

  //motor velocity (Left is 2, Right is 1)
  mVR = dWheelR / PERIOD;
  mVL = dWheelL / PERIOD;
}
