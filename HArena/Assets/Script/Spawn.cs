using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spawn : MonoBehaviour
{
    public Transform[] spawnPoint;
    public GameObject[] monsters;
    int randomSpawnPoint, randomMonster;
    public static bool spawnAllowed;

    // Start is called before the first frame update
    void Start()
    {
        spawnAllowed = true;
        InvokeRepeating("spawnAMonster", 5f, 5f);
    }


    void spawnAMonster() {
        if (spawnAllowed ) {
            randomSpawnPoint = Random.Range(0, spawnPoint.Length);
            randomMonster = Random.Range(0, monsters.Length);
            Instantiate(monsters[randomMonster], spawnPoint[randomSpawnPoint].position, Quaternion.identity);
        }
    }
}
