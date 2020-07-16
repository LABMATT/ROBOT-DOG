using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/*
ABS (ANIMATED BALENCER SYSTEM)
LABMATT MARCH 15 2020
THIS SCRIPT IS IN CHARGE OF KEEPING CONSISTEN BALENCE OF THE ROBOT BY USE OF READING ASSELTMOTER, COMPARIING WEIGHT DISTOBUTIONS AND MODIFYING VECTORS BASED ON BALENCE PREMATERS.
*/

public class ABS : MonoBehaviour {

     public GameObject body; //LEG 1 LOWER. BOTTOM LEG LEFT LOWER
     public double ox, oy, oz;


    // Start is called before the first frame update
    void Start () {

    }

    // Update is called once per frame
    void Update () {

        double[] angler = angle();
        Debug.Log (angler[0] + ", " + angler[1] + ", " + angler[2]);

        ox = angler[0];
        oy = angler[1];
        oz = angler[2];

    }

    public bool balencer () {



        //If robot is in unrecovrable
        return false;
    }


    public double[] angle()
    {
        Rigidbody bodyangle = body.GetComponent<Rigidbody>();

double[] finalRot = new double[3];

        finalRot[0] = bodyangle.rotation.x;
        finalRot[1] = bodyangle.rotation.y;
        finalRot[2] = bodyangle.rotation.z;

        return finalRot;
    }

/*
//Defult robot postion.
private fetus(int speed)
{
 //LEG NUMBER, PART A B C, POSTION, FORCE, DAMPNING FORCE.
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

return null;
}
*/

}