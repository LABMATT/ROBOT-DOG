using System;
using System.Collections;
using UnityEngine;

/*
POINT LEG VECTORING SYSTEM.
This file is in charge of resiving a point then working out what angles and math needs to happen to get the leg to that point.
*/

public class PLVS : MonoBehaviour {

    public GameObject objectWithScript;

    public double x;
    public double y;
    public double z;

    // Start is called before the first frame update
    void Start () {

    }

    // Update is called once per frame
    void Update () {

        LMM scripto = objectWithScript.GetComponent<LMM> ();

       //returnedVal = new double[3];
        try{
                 double[] returnedVal = vectorLeg(0.9, 0.9, x, y, z);

   Debug.Log ("Angle A = " + returnedVal[0] + ". Angle B = " + returnedVal[1] + ". Angle C = " + returnedVal[2]);

int strenth = 900;

                scripto.jointController (1, 'A', returnedVal[0], strenth, 0);
                scripto.jointController (2, 'A', returnedVal[0], strenth, 0);
                scripto.jointController (3, 'A', returnedVal[0], strenth, 0);
                scripto.jointController (4, 'A', returnedVal[0], strenth, 0);

                scripto.jointController (1, 'B', returnedVal[1], strenth, 0);
                scripto.jointController (2, 'B', returnedVal[1], strenth, 0);
                scripto.jointController (3, 'B', returnedVal[1], strenth, 0);
                scripto.jointController (4, 'B', returnedVal[1], strenth, 0);
                
                scripto.jointController (1, 'C', returnedVal[2], strenth, 0);
                scripto.jointController (2, 'C', returnedVal[2], strenth, 0);
                scripto.jointController (3, 'C', returnedVal[2], strenth, 0);
                scripto.jointController (4, 'C', returnedVal[2], strenth, 0);


        }
        catch(InvalidOperationException e)
        {
            Debug.Log("Error vectoring leg: " + e);
        }

     
    }

    public double[] mapRang () {

        return null;
    }




    //Returns [A,B,C]
    public double[] vectorLeg (double leg_A_lenth, double leg_B_lenth, double x, double y, double z) {

        //Returned angles for the leg
        double[] finalDouble = new double[3];
        bool wasneg = false;
        bool zwasneg = false;

        Debug.Log("input is x:" + x + " y:" + y);

        if(x + y + z == 0)  
        {
            return new double[] {0, 0, 0};
        }

//check if x was a negative number
        if(x < 0)
        {
            x = x * -1;
            wasneg = true;
            Debug.Log ("was neg");
        }


        //check if z was a negative number
        if(z < 0)
        {
            z = z * -1;
            zwasneg = true;
            Debug.Log ("z was neg");
        }


        double vd = Math.Sqrt (Math.Pow (x, 2) + Math.Pow (y, 2)); //Work out the distance between axis and point in space. 
        Debug.Log ("vd = " + vd);


//Work out the distance between z axis and point in space. 
        double vdz = Math.Sqrt (Math.Pow (z, 2) + Math.Pow (y, 2)); 


        //Check if the legs lenth is loger than the leg can reach.
        if (!(vd > (leg_A_lenth + leg_B_lenth)) && (vd != (leg_A_lenth + leg_B_lenth)) && (vd != 0)) //Check if the point if futher than the legs reach.
        {


   

        //Get distance between leg point and z
        if(!(vdz > (leg_A_lenth + leg_B_lenth)) && (vdz != (leg_A_lenth + leg_B_lenth)) && (vdz != 0))
        {
            //Use the 
            finalDouble[2] = (Math.Acos (vd / vdz) * 180 / Math.PI);

            if(zwasneg)
            {
                finalDouble[2] = finalDouble[2] * -1;
            }
        }
        else
        {
            throw new System.InvalidOperationException("Point was futher than leg can move on z axis.");
        }


            //Work out the final triangles angle reltive to the 0 angle downwards. Use VD as adjecent and y postion as hy
            double relitiveAngle = (Math.Acos (y / vd) * 180 / Math.PI);
            Debug.Log ("RA = " + relitiveAngle);

            //Find the angle at joint A
            finalDouble[0] = (Math.Acos ((Math.Pow (leg_A_lenth, 2) + Math.Pow (leg_B_lenth, 2) - Math.Pow (vd, 2)) / (2 * leg_A_lenth * leg_B_lenth)) * 180 / Math.PI);
            Debug.Log ("Raw angle A = " + finalDouble[0]);

            //Find the angle at hoint B
            finalDouble[1] = (Math.Acos ((Math.Pow (leg_B_lenth, 2) + Math.Pow (vd, 2) - Math.Pow (leg_A_lenth, 2)) / (2 * leg_B_lenth * vd)) * 180 / Math.PI);
            Debug.Log ("Raw angle B = " + finalDouble[1]);

            if (finalDouble[0] + finalDouble[1] > 180) {
                Debug.Log ("angle is way to big");
                return new double[] { 0, 0, 0 };
            }

            //If x is less than 0 then the leg is backworkds. This formats varaibales acordingly. [A,B,C]
            if (wasneg) {
                Debug.Log ("Reversing dir");

                finalDouble[0] = 180.0 - finalDouble[0];
                Debug.Log ("after " + finalDouble[0]);

                //Change part B to face -x value. Then add reltive angle. This is to say -angle for the postion of leg.
                finalDouble[1] = finalDouble[1] + relitiveAngle;
                finalDouble[1] = finalDouble[1] * -1;

                return finalDouble;

            } else {

                Debug.Log ("Before " + finalDouble[0]);

                //Because unity draws the angle from 0 witch is considerd striagjt down. we subtract 180 to get the equivlent if 0 was at the triangle.
                finalDouble[0] = 180.0 - finalDouble[0];

                Debug.Log ("after " + finalDouble[0]);

                //Add relative angle to triangle.
                finalDouble[1] = finalDouble[1] + relitiveAngle;

                //Make sure Angle A is inwards towards y = 0.
                finalDouble[0] = finalDouble[0] - finalDouble[0] * 2;

                return finalDouble;
            }
        } else {

            // return null;
            Debug.Log("Point was futher than leg can move.");

        
        throw new System.InvalidOperationException("Point was futher than leg can move.");
        }

    }
}