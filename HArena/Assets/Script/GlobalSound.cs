using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GlobalSound : MonoBehaviour
{
    public Transform origin;
    public AudioSource m_Source;
    public float curlevel;
    public float maxvol;

    private void Update()
    {
        if (origin.position.y < curlevel || origin.position.y > curlevel+5.9)
        {
            m_Source.volume = 0;
        }
        else
        {
            m_Source.volume = maxvol;
        }
    }
}
