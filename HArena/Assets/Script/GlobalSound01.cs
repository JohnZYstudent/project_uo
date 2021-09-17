using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GlobalSound01 : MonoBehaviour
{
    public Transform origin;
    public AudioSource m_Source;

    private void Update()
    {
        if (origin.position.y < 0.1)
        {
            m_Source.volume = 0;
        }
        else
        {
            m_Source.volume = 1;
        }
    }
}
