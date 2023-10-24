/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Tyni2                                                     */
/*    Created:      9/26/2023, 5:40:18 PM                                     */
/*    Description:  Code for vroom vroom                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include <stdlib.h>
#include <time.h>

using namespace vex;

// Setup
competition Competition; // Competition
brain Brain; // Brain
controller Controller1 = controller(); // Controller
motor TopLeft = motor(PORT1, ratio18_1, true); // Top Left Drive Motor
motor BottomLeft = motor(PORT9, ratio6_1, true); // Bottom Left Drive Motor
motor TopRight = motor(PORT2, ratio18_1, false); // Top Right Drive Motor
motor BottomRight = motor(PORT10, ratio6_1, false); // Bottom Right Drive Motor
motor Arm = motor(PORT7, ratio36_1, true); // Catapult Motor

// Variables
int meth = 1; // Determines which saying to print
int lsd = 500; // Timer using variable
bool armMoving = false;

const char* sayings[] = {"Stop ordering Marinara, I beg of you...", "Commiting various warcrimes...", "That's right, it goes in the square hole!",
                        "Loading chicken noises mucka blucka...", "Ok, hear me out officer...", "Jesus Screw Part 2: Electric Boogaloo",
                        "Wuh-oh, looks like the [REDACTED] is kicking in! qowijdqoiwjdoiqwj", "Thank you for coming to our TED Talk", 
                        "Geneva Convention? I thought it was a checklist!", "popcat.mp3", "Evading taxes and law enforcement since 2020!",
                        "RIP Famine", "YOU, ME, GAS STATION!", "We eat PlayDoh. Cry about it.", "STRIKE ME DOWN ZEUS! YOU DON'T HAVE THE- *boom*",
                        "No Maidens?", "Crazy? I was crazy once!", "chicken_noises.mp3", "... --- ...", ":O", "Just ziptie it! It'll be fine! *crash*",
                        "I was bored, ok?", "Yo momma", "AROUND THE WORLD AROUND THE WORLD", "i ate plastic once. did not taste good.",
                        "Don't toucha mah spageht", "*pretending to work*", "Kilometers? I use calories per Big Mac", "Tyler has 16 hats. Why?",
                        "Jack has magic hands. Be afraid.", "Navya keeps trying to draw on my tape", "Alexavier, I don't want the mower...",
                        "Hannah didn't let me play Payday 2 :(", "Seriously, who killed Heavy?", "vine_boom.mp3", "The ducks at the park are free. I have 432.",
                        "Triballs give you points when scored.", "Elevation is worth points.", "This is a robot :)", "i really need to get a job...",
                        "They locked me in here :(", "MAKE WAY FOR THE DOZER!", "FIGHT THE PAIN! FIGHT THE CLOWNS!", "It's juuuuuust a little blood!",
                        "I found the source of the ticking! A pipebomb!", "Alright ramblers, let's get rambling!", "I NEED A MEDIC BAG!",
                        "5 BULLETS LEFT!"
                        };

// Driving Commands
void ArmUp() {
  if (armMoving == false) {
    Arm.spin(forward);
    armMoving = true;
  } else {
    Arm.stop();
    armMoving = false;
  }
}

void ArmDown() {
  if (armMoving == false) {
    Arm.spin(reverse);
    armMoving = true;
  } else {
    Arm.stop();
    armMoving = false;
  }
}

// Autonomous Commands

void Forward() {
  TopRight.spin(forward);
  TopLeft.spin(forward);
  BottomRight.spin(forward);
  BottomLeft.spin(forward);
}

void Reverse() {
  TopRight.spin(reverse);
  TopLeft.spin(reverse);
  BottomRight.spin(reverse);
  BottomLeft.spin(reverse);
}

void Stop() {
  TopRight.stop();
  TopLeft.stop();
  BottomRight.stop();
  BottomLeft.stop();
}

void Right() {
  TopRight.spin(reverse);
  TopLeft.spin(forward);
  BottomRight.spin(reverse);
  BottomLeft.spin(forward);
}

void Left() {
  TopRight.spin(forward);
  TopLeft.spin(reverse);
  BottomRight.spin(forward);
  BottomLeft.spin(reverse);
}

// Other Commands

void LoadingScreenTips() {
  if (lsd == 500) {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);

    srand(Brain.Timer.systemHighResolution());

    meth = rand() % 48;

    Brain.Screen.print(sayings[meth-1]);

    lsd = 1;
  } else {
    lsd = lsd + 1;
  }
}

void pre_auton(void) {
  TopLeft.setBrake(brake);
  TopRight.setBrake(brake);
  BottomLeft.setBrake(brake);
  BottomRight.setBrake(brake);

  Arm.setVelocity(75, percent);
  TopLeft.setVelocity(100, percent);
  TopRight.setVelocity(100, percent);
  BottomLeft.setVelocity(100, percent);
  BottomRight.setVelocity(100, percent);
}

void autonomous(void) {
 Forward();
 wait(.8, sec);
 Stop();
 Reverse();
 wait(.8, sec);
 Stop();
}

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {

    // Call Driving Functions
    TopLeft.spin(forward, Controller1.Axis3.position(), percent);
    BottomLeft.spin(forward, Controller1.Axis3.position(), percent);
    TopRight.spin(forward, Controller1.Axis2.position(), percent);
    BottomRight.spin(forward, Controller1.Axis2.position(), percent);

    Controller1.ButtonR1.pressed(ArmUp);
    Controller1.ButtonR2.pressed(ArmDown);

    thread(LoadingScreenTips).detach();

    wait(20, msec);
  }
}

int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}

// MOTHERFUCKING BULLDOZER!
// YOU'RE UP AGAINST THE WALL, AND I AM THE FUCKING WALL!