/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Tyni2                                                     */
/*    Created:      9/26/2023, 5:40:18 PM                                     */
/*    Description:  Code for vroom vroom                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// Setup
competition Competition; // Competition
brain Brain; // Brain
controller Controller1 = controller(); // Controller
motor TopLeft = motor(PORT1, ratio18_1, true); // Top Left Drive Motor
motor BottomLeft = motor(PORT9, ratio6_1, true); // Bottom Left Drive Motor
motor TopRight = motor(PORT2, ratio18_1, false); // Top Right Drive Motor
motor BottomRight = motor(PORT10, ratio6_1, false); // Bottom Right Drive Motor
motor ExtraLeft = motor(PORT16, ratio18_1, true);
motor ExtraRight = motor(PORT17, ratio18_1, false);
motor SpinnySpin = motor(PORT5, ratio6_1, true); // Flywheel Motor
motor ArmRight = motor(PORT3, ratio18_1, false); // Right Side of Arm
motor ArmLeft = motor(PORT7, ratio18_1, false); // Left Side of Arm
digital_out wingPistonA(Brain.ThreeWirePort.A); // Wing
digital_out wingPistonB(Brain.ThreeWirePort.B); // Wing


// Variables
int meth = 1; // Determines which saying to print
int lsd = 500; // Timer using variable
bool spin = false;
bool deployed = false;

const char* sayings[] = {"Stop ordering Marinara, I beg of you...", "Commiting various warcrimes...", "That's right, it goes in the square hole!",
                        "Loading chicken noises mucka blucka...", "Ok, hear me out officer...", "Jesus Screw Part 2: Electric Boogaloo",
                        "Wuh-oh, looks like the [REDACTED] is kicking in! qowijdqoiwjdoiqwj", "Thank you for coming to our TED Talk", 
                        "Geneva Convention? I thought it was a checklist!", "popcat.mp3", "Evading taxes and law enforcement since 2020!",
                        "RIP Famine", "YOU, ME, GAS STATION!", "We eat PlayDoh. Cry about it.", "STRIKE ME DOWN ZEUS! YOU DON'T HAVE THE- *boom*",
                        "No Maidens?", "Crazy? I was crazy once!", "chicken_noises.mp3", "... --- ...", ":O", "Just ziptie it! It'll be fine! *crash*",
                        "I was bored, ok?", "Yo momma", "AROUND THE WORLD AROUND THE WORLD", "i ate plastic once. did not taste good.",
                        "Don't toucha mah spageht", "*pretending to work*", "Kilometers? I use calories per Big Mac", "Tyler has 20+ hats. Why?",
                        "Jack has magic hands. Be afraid.", "Navya keeps trying to draw on my tape", "Alexavier, I don't want the mower...",
                        "Hannah didn't let me play Payday 2 :(", "Seriously, who killed Heavy?", "vine_boom.mp3", "The ducks at the park are free. I have 432.",
                        "Triballs give you points when scored.", "Elevation is worth points.", "This is a robot :)", "i really need to get a job...",
                        "They locked me in here :(", "MAKE WAY FOR THE DOZER!", "FIGHT THE PAIN! FIGHT THE CLOWNS!", "It's juuuuuust a little blood!",
                        "I found the source of the ticking! A pipebomb!", "Alright ramblers, let's get rambling!", "I NEED A MEDIC BAG!",
                        "5 BULLETS LEFT!", "I don't like greek eggs and lamb.", "Current Mood:", "I think [Redacted by Twitter]"
                        };

// Driving Commands

void FUCKINGMOVEBITCH() {
  TopLeft.spin(forward, Controller1.Axis3.position(), percent);
  BottomLeft.spin(forward, Controller1.Axis3.position(), percent);
  TopRight.spin(forward, Controller1.Axis2.position(), percent);
  BottomRight.spin(forward, Controller1.Axis2.position(), percent);
  ExtraRight.spin(forward, Controller1.Axis2.position(), percent);
  ExtraLeft.spin(forward, Controller1.Axis3.position(), percent);
}

void SpinFlywheel() {
  if (spin == true) {
    SpinnySpin.spin(forward);
  } else {
    SpinnySpin.stop();
  }
}

void WingsETC() {
  if (Controller1.ButtonA.pressing()) {
    wingPistonA.set(0);
    wingPistonB.set(0);
  } else {
    wingPistonA.set(1);
    wingPistonB.set(1);
  }
}

// Autonomous Commands
void Stop() {
  TopRight.stop();
  TopLeft.stop();
  BottomRight.stop();
  BottomLeft.stop();
  ExtraRight.stop();
  ExtraLeft.stop();
}

void moveBiatch(double moveNumber) {
  TopRight.spinFor(moveNumber, rev, false);
  TopLeft.spinFor(moveNumber, rev, false);
  BottomRight.spinFor(moveNumber, rev, false);
  BottomLeft.spinFor(moveNumber, rev, false);
  ExtraRight.spinFor(moveNumber, rev, false);
  ExtraLeft.spinFor(moveNumber, rev, true);
}

void turnBiatch(double turnNumber) {
  TopRight.spinFor(-turnNumber, rev, false);
  TopLeft.spinFor(turnNumber, rev, false);
  BottomRight.spinFor(-turnNumber, rev, false);
  BottomLeft.spinFor(turnNumber, rev, false);
  ExtraLeft.spinFor(turnNumber, rev, false);
  ExtraRight.spinFor(-turnNumber, rev, true);
}

// Other Commands

void LoadingScreenTips() {
  if (lsd == 500) {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);

    srand(Brain.Timer.systemHighResolution());

    meth = rand() % 51;

    Brain.Screen.print(sayings[meth]);

    if (meth == 48) {
      Brain.Screen.setCursor(2,1);
      Brain.Screen.print("I don't like them at all, madame.");
      Brain.Screen.setCursor(3,1);
      Brain.Screen.print("Not with Hades. Not with the ladies.");
      Brain.Screen.setCursor(4,1);
      Brain.Screen.print("Not as a treat on the island of Crete.");
      Brain.Screen.setCursor(5,1);
      Brain.Screen.print("I will not eat them Persephone.");
      Brain.Screen.setCursor(6,1);
      Brain.Screen.print("I will not eat them. Let me be!");
    } else if (meth == 16) {
      Brain.Screen.setCursor(2,1);
      Brain.Screen.print("They locked me in a room.");
      Brain.Screen.setCursor(3,1);
      Brain.Screen.print("A rubber room! A rubber room with rats!");
      Brain.Screen.setCursor(4,1);
      Brain.Screen.print("And rats make me crazy! Crazy?");
    } else if (meth == 49) {
      Brain.Screen.setCursor(2, 1);
      Brain.Screen.print("The phrase touched in the head");
      Brain.Screen.setCursor(3, 1);
      Brain.Screen.print("originally implied tocuhed by God");
      Brain.Screen.setCursor(4, 1);
      Brain.Screen.print("or the divine. Currently I feel");
      Brain.Screen.setCursor(5, 1);
      Brain.Screen.print("as if a full choir of angels hath");
      Brain.Screen.setCursor(6, 1);
      Brain.Screen.print("come down to take turns");
      Brain.Screen.setCursor(7, 1);
      Brain.Screen.print("booping my brain.");
    } else if (meth == 50) {
      Brain.Screen.setCursor(2, 1);
      Brain.Screen.print("Reason: Expressing Opinion");
    }

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
  ExtraRight.setBrake(brake);
  ExtraLeft.setBrake(brake);
  ArmLeft.setBrake(hold);
  ArmRight.setBrake(hold);

  TopLeft.setVelocity(100, percent);
  TopRight.setVelocity(100, percent);
  BottomLeft.setVelocity(100, percent);
  BottomRight.setVelocity(100, percent);
  ExtraRight.setVelocity(100, percent);
  ExtraLeft.setVelocity(100, percent);
  SpinnySpin.setVelocity(100, percent);
  ArmLeft.setVelocity(50, percent);
  ArmRight.setVelocity(50, percent);

  wingPistonA.set(1);
  wingPistonB.set(1);
}

void autonomous(void) {
 moveBiatch(1);
 wait(.1, sec);
 moveBiatch(-1);
}

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {

    // Call Driving Functions
    thread(FUCKINGMOVEBITCH).detach();

    if(Controller1.ButtonL1.pressing()) {
      spin = true;
    }
    if(Controller1.ButtonL2.pressing()) {
      spin = false;
    }
    if(Controller1.ButtonR1.pressing()) {
      ArmLeft.spin(forward);
      ArmRight.spin(forward);
    }
    if(Controller1.ButtonR2.pressing()) {
      ArmLeft.spin(reverse);
      ArmRight.spin(reverse);
    }

    WingsETC();
    SpinFlywheel();

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
