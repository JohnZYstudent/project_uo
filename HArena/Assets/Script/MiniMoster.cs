using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Threading;

public class MiniMoster : MonoBehaviour
{
    public Transform player;
    UnityEngine.AI.NavMeshAgent nav;
    //float monster_heath = 100f;
    public HealthSystem healthSystem;
    public HealthBar healthBar;
    Animator m_Animator;
    public Rigidbody rb;
    public Transform bar;
    public static bool score;
    private int damage;


    private void Start()
    {
        score = false;
        damage = 0;
        healthSystem = new HealthSystem(100);
    }

    public void takedamge(int a)
    {
        healthSystem.Dodamge(a);
        bar.localScale = new Vector3(healthSystem.GetPercentHealth() * 10, 1);

    }



    // Start is called before the first frame update
    void Awake()
    {
        nav = GetComponent<UnityEngine.AI.NavMeshAgent>();
        m_Animator = GetComponent<Animator>();
        rb = GetComponent<Rigidbody>();
        //healthBar.Setup(healthSystem);
    }

    // Update is called once per frame
    void Update()
    {
        damage = InGameUI.bonusa;
        Navi();
    }
    void Navi()
    {
        if (healthSystem.GetHealth() > 0)
        {
            nav.SetDestination(player.position);
        }
        else
        {
            InGameUI.score += 20;
            nav.enabled = false;
            m_Animator.SetBool("IsDead", true);
            Destroy(this.gameObject);
        }
    }

    void OnCollisionEnter(Collision target)
    {
        if (target.gameObject.name == "BladeR")
        {
            takedamge(damage);
            m_Animator.SetTrigger("GetHit");
            Debug.Log("Dragon hit!");
            rb.AddForce(transform.forward * -5000f);

        }

    }
    void OnTriggerExit(Collider target)
    {
        if (target.gameObject.name == "BladeR")
        {
            

        }
    }
}
