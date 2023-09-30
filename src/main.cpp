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
motor Catapult = motor(PORT7, ratio36_1, true); // Catapult Motor

// Variables
int meth = 1; // Determines which saying to print
int lsd = 500; // Timer using variable

// Driving Commands
void YeetThatCorn() {
  Catapult.spin(forward);
}

void DontYeetCorn() {
  Catapult.stop();
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

    meth = rand() % 28 + 1;

    if (meth == 1) {
      Brain.Screen.print("Stop ordering Marinara, I beg of you...");
    }
    if (meth == 2) {
      Brain.Screen.print("Commiting various warcrimes...");
    }
    if (meth == 3) {
      Brain.Screen.print("That's right, it goes in the square hole!");
    }
    if (meth == 4) {
      Brain.Screen.print("Loading chicken noises mucka blucka...");
    }
    if (meth == 5) {
      Brain.Screen.print("Ok, hear me out officer...");
    }
    if (meth == 6) {
      Brain.Screen.print("Jesus Screw Part 2: Electric Boogaloo");
    }
    if (meth == 7) {
      Brain.Screen.print(
          "Wuh-oh, looks like the [REDACTED] is kicking in! qowijdqoiwjdoiqwj");
    }
    if (meth == 8) {
      Brain.Screen.print("Thank you for coming to our TED Talk");
    }
    if (meth == 9) {
      Brain.Screen.print("Geneva Convention? I thought it was a checklist!");
    }
    if (meth == 10) {
      Brain.Screen.print("popcat.mp3");
    }
    if (meth == 11) {
      Brain.Screen.print("Evading taxes and law enforcement since 2020!");
    }
    if (meth == 12) {
      Brain.Screen.print("RIP Famine");
    }
    if (meth == 13) {
      Brain.Screen.print("YOU, ME, GAS STATION!");
    }
    if (meth == 14) {
      Brain.Screen.print("We eat PlayDoh. Cry about it.");
    }
    if (meth == 15) {
      Brain.Screen.print("STRIKE ME DOWN ZEUS! YOU DON'T HAVE THE- *boom*");
    }
    if (meth == 16) {
      Brain.Screen.print("No Maidens?");
    }
    if (meth == 17) {
      Brain.Screen.print("Crazy? I was crazy once!");
    }
    if (meth == 18) {
      Brain.Screen.print("chicken_noises.mp3");
    }
    if (meth == 19) {
      Brain.Screen.print("... --- ...");
    }
    if (meth == 20) {
      Brain.Screen.print(":O");
    }
    if (meth == 21) {
      Brain.Screen.print("Just ziptie it! It'll be fine! *crash*");
    }
    if (meth == 22) {
      Brain.Screen.print("I was bored, ok?");
    }
    if (meth == 23) {
      Brain.Screen.print("Yo momma");
    }
    if (meth == 24) {
      Brain.Screen.print("AROUND THE WORLD AROUND THE WORLD");
    }
    if (meth == 25) {
      Brain.Screen.print("i ate plastic once. did not taste good.");
    }
    if (meth == 26) {
      Brain.Screen.print("Don't toucha mah spageht");
      wait(3, sec);
    }
    if (meth == 27) {
      Brain.Screen.print("*pretending to work*");
    }
    if (meth == 28) {
      Brain.Screen.print("Kilometers? I use calories per Big Mac");
    }

    lsd = 1;
  } else if (lsd < 1000) {
    lsd = lsd + 1;
  }
}

void pre_auton(void) {
  TopLeft.setBrake(brake);
  TopRight.setBrake(brake);
  BottomLeft.setBrake(brake);
  BottomRight.setBrake(brake);

  Catapult.setVelocity(75, percent);
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

    // Button Controls
    Controller1.ButtonR1.pressed(YeetThatCorn);
    Controller1.ButtonR2.pressed(DontYeetCorn);

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

// California Girls