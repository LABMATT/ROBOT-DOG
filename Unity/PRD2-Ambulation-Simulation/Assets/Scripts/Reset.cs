using System.Collections;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Reset : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {

        if (Input.GetKeyDown("r")) //If r is pressed then reset.
        {

            SceneManager.LoadScene(SceneManager.GetActiveScene().name); // loads current scene.
            Debug.Log("Reset");
        }
    }


}
