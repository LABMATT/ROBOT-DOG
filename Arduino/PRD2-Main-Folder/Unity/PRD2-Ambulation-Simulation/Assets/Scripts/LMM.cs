using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/*
LEG MOTOR MANGER.
Contorll all sim leg springs.
Can be feed info to move VIRUTAL legs, weather form robot or sim.
This code is free to use and modfie for any ourpose. Origlay careated by Matthew Lewington LABMATT


ROBOT LEGS:

4 O###O 3
  #####
  #####
  #####
1 O###O 2

- With parts A B C


*/

public class LMM : MonoBehaviour {

        public int tForce, tpos, damp;

        public GameObject BLL_LOWER_PART; //LEG 1 LOWER. BOTTOM LEG LEFT LOWER
        public GameObject BLL_UPPER_PART; //LEG 1 UPPER. BOTTOM LEG LEFT UPPER

        public GameObject BLR_LOWER_PART; //BOTTOM LEG RIGHT LOWER
        public GameObject BLR_UPPER_PART; //BOTTOM LEG RIGHT UPPER

        public GameObject TLL_LOWER_PART; //TOP LEG LEFT LOWER
        public GameObject TLL_UPPER_PART; //TOP LEG LEFT UPPER

        public GameObject TLR_LOWER_PART; //TOP LEG RIGHT LOWER
        public GameObject TLR_UPPER_PART; //TOP LEG RIGHT UPPER

        public GameObject axis_bottom_leftV; //Bottom left axis.
        public GameObject axis_bottom_rightV; //Bottom right axis.

        public GameObject axis_top_leftV; //Top left axis.
        public GameObject axis_top_rightV; //Top right axis.

       /*
        void Start () {

                jointController (1, 'A', 90, 90, 0);
                jointController (2, 'A', 90, 90, 0);
                jointController (3, 'A', 90, 90, 0);
                jointController (4, 'A', 90, 90, 0);

                jointController (1, 'C', 0, 90, 0);
                jointController (2, 'C', 0, 90, 0);
                jointController (3, 'C', 0, 90, 0);
                jointController (4, 'C', 0, 90, 0);

                jointController (1, 'B', -45, 200, 0);
                jointController (2, 'B', -45, 200, 0);
                jointController (3, 'B', -45, 200, 0);
                jointController (4, 'B', -45, 200, 0);

                //Debug.Log("Seting force: " + tForce + ". and pos: " + tpos);

                tpos = 90;
        }
        */

        void Update () {
                //jointController(1, 'A', tpos, tForce, 0);
                //jointController(2, 'A', tpos, tForce, 0);
                //jointController(3, 'A', tpos, tForce, 0);
                //jointController(4, 'A', tpos, tForce, 0);
        }

        //MAIN LEG CONTROL FUNCTION JOINT. LEG NUMBER, PART A B C, POSTION, FORCE, DAMPNING FORCE.
        public void jointController (int leg, char part, double postion, int force, double damp) {

                HingeJoint hinge = getJoint (leg, part); //Reads hige from componete.

                JointSpring hingeSpring = hinge.spring; //Gets the motor vairable from hinge.
                hingeSpring.spring = force; //Sets the amout of force the motor is using.
                hingeSpring.damper = (float) damp;
                hingeSpring.targetPosition = (float) postion; //Sets motor to target postion.
                hinge.spring = hingeSpring; //Casts modfifed values to motor.
                hinge.useSpring = true; //Makes sure the motor mode is activec on hinge.
        }

        private HingeJoint getJoint (int leg, char part) {

                //Selects witch leg then gets the part. isent it intresting that comments arnt allowed on switch statments.
                switch (leg) {

                        case 1: //If LEG one is chosen.

                                switch (part) {

                                        case 'A':
                                                return BLL_LOWER_PART.GetComponent<HingeJoint> (); //If Lower part of leg return lower part.

                                        case 'B':
                                                return BLL_UPPER_PART.GetComponent<HingeJoint> (); //If upper part of leg return upper part.

                                        case 'C':
                                                return axis_bottom_leftV.GetComponent<HingeJoint> (); //If axis then get axis.
                                }
                                break;

                        case 2: //If LEG 2 is chosen.

                                switch (part) {

                                        case 'A':
                                                return BLR_LOWER_PART.GetComponent<HingeJoint> (); //If Lower part of leg return lower part.

                                        case 'B':
                                                return BLR_UPPER_PART.GetComponent<HingeJoint> (); //If upper part of leg return upper part.

                                        case 'C':
                                                return axis_bottom_rightV.GetComponent<HingeJoint> (); //If axis then get axis.
                                }
                                break;

                        case 3: //IF LEG 3 is chosen.

                                switch (part) {

                                        case 'A':
                                                return TLR_LOWER_PART.GetComponent<HingeJoint> (); //If Lower part of leg return lower part.

                                        case 'B':
                                                return TLR_UPPER_PART.GetComponent<HingeJoint> (); //If upper part of leg return upper part.

                                        case 'C':
                                                return axis_top_rightV.GetComponent<HingeJoint> (); //If axis then get axis.
                                }
                                break;

                        case 4: //IF LEG 4 is chosen.

                                switch (part) {

                                        case 'A':
                                                return TLL_LOWER_PART.GetComponent<HingeJoint> (); //If Lower part of leg return lower part.

                                        case 'B':
                                                return TLL_UPPER_PART.GetComponent<HingeJoint> (); //If upper part of leg return upper part.

                                        case 'C':
                                                return axis_top_leftV.GetComponent<HingeJoint> (); //If axis then get axis.
                                }
                                break;

                }
                return null;

        }
}