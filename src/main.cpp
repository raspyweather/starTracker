
#include <AccelStepper.h>

#define STEPPER_DIR_PIN D1
#define STEPPER_STEP_PIN D2
#define STEPPER_SLEEP_PIN D3
#define STEPPER_RESET_PIN D4
#define STEPPER_ENABLE_PIN D0

AccelStepper stepper(AccelStepper::DRIVER, STEPPER_STEP_PIN, STEPPER_DIR_PIN);

const float STEP_DIRECTION = -1.0;

const float STEPS_PER_STEP = 16.0;
const float STEPS_PER_TURN = 200.0 * STEPS_PER_STEP;

const float GEARHEAD_RATIO = 51.0;
const float WORMDRIVE_RATIO = 120.0;

const float STEPS_PER_DAY = (GEARHEAD_RATIO * WORMDRIVE_RATIO * STEPS_PER_TURN);
const float STEPS_PER_SEC = (STEPS_PER_DAY / (24 * 3600.0));

void setup()
{
    Serial.begin(9600);
    pinMode(STEPPER_SLEEP_PIN, OUTPUT);
    digitalWrite(STEPPER_SLEEP_PIN, HIGH);
    pinMode(STEPPER_RESET_PIN, OUTPUT);
    digitalWrite(STEPPER_RESET_PIN, HIGH);

    stepper.setEnablePin(STEPPER_ENABLE_PIN);
    stepper.setPinsInverted(false, false, true);
    stepper.enableOutputs();
    stepper.setMaxSpeed(STEPS_PER_SEC * 2);
    stepper.setAcceleration(0.1);
    stepper.setSpeed(STEPS_PER_SEC * STEP_DIRECTION);
    delay(3000);
}

void loop()
{
    stepper.runSpeed();
    ESP.wdtFeed();
}