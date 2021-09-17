using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Backtomain : MonoBehaviour
{
    // Start is called before the first frame update
    public void LoadScene(string name)
    {
        Application.LoadLevel(name);
    }
}
