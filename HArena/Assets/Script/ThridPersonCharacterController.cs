using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ThridPersonCharacterController : MonoBehaviour
{
    public float turnSpeed = 20f;
    public float Speed = 3;
    public float RunningSpeed = 5;
    private bool dead;
    private bool isAttacking = false;
    private bool isEffectDown = false;
    public Rigidbody rb;
    public static HealthSystem healthSystem;
    public GameObject menu;
    public AudioSource m_Source;
    public AudioClip run;
    public AudioClip attacked;
    public AudioClip attack;

    //private int attackingInt = 0;

    Animator m_Animator;
    Vector3 playerMovement;
    Quaternion m_Rotation = Quaternion.identity;



    // Update is called once per frame
    void Start()
    {
        healthSystem = new HealthSystem(100);
        m_Animator = GetComponent<Animator>();
        rb = GetComponent<Rigidbody>();
        m_Source.volume = 0.1f;

    }
    void Update()
    {
        
        if (dead) {
            ExitGame();
        }
        else
        {
            float hor = Input.GetAxis("Horizontal");
            float ver = Input.GetAxis("Vertical");
            bool hasHorizontalInput = !Mathf.Approximately(hor, 0f);
            bool hasVerticalInput = !Mathf.Approximately(ver, 0f);
            bool isWalking = hasHorizontalInput || hasVerticalInput;

            if (Input.GetButtonDown("effect"))
            {
                isEffectDown = true;
            }
            if (Input.GetButtonUp("effect"))
            {
                isEffectDown = false;
            }
            if (isEffectDown)
            {
                playerMovement = new Vector3(hor, 0f, ver) * RunningSpeed * Time.deltaTime;
                transform.Translate(playerMovement, Space.Self);
                m_Animator.SetBool("IsRunning", isWalking);
                m_Animator.SetBool("IsWalking", false);
                if (m_Source.isPlaying == false)
                {
                    m_Source.PlayOneShot(run);
                }
            }
            else
            {
                playerMovement = new Vector3(hor, 0f, ver) * Speed * Time.deltaTime;
                transform.Translate(playerMovement, Space.Self);
                m_Animator.SetBool("IsWalking", isWalking);
                m_Animator.SetBool("IsRunning", false);
            }


            Vector3 desiredForward = Vector3.RotateTowards(transform.forward, playerMovement, turnSpeed * Time.deltaTime, 0f);
            m_Rotation = Quaternion.LookRotation(desiredForward);
            if (Input.GetButtonDown("Fire1"))
            {
                isAttacking = true;
                m_Source.PlayOneShot(attack);
                m_Animator.SetTrigger("IsAttacking");
                StartCoroutine(stopAttack(1));
                activateTrails(true);
            }
            if (Input.GetButtonDown("Fire2"))
            {
                isAttacking = true;
                m_Animator.SetTrigger("IsHeaveAttacking");
                StartCoroutine(stopAttack(1));
                activateTrails(true);
            }
        }

    }
    public void ExitGame() {
        m_Animator.SetBool("IsDead", true);
        Time.timeScale = 0f;
        menu.gameObject.SetActive(true);
        Cursor.lockState = CursorLockMode.Confined;
        Cursor.visible = true;
    }
    public void takedamge(int a)
    {
        healthSystem.Dodamge(a);
        if (healthSystem.GetHealth() == 0) { dead = true; }
    }
    public void activateTrails(bool state)
    {
        var tails = GetComponentsInChildren<TrailRenderer>();
        foreach (TrailRenderer tt in tails)
        {
            tt.enabled = state;
        }
    }
    public IEnumerator stopAttack(float lenght)
    {
        yield return new WaitForSeconds(lenght); // attack lenght
        isAttacking = false;
        activateTrails(false);
    }

    void OnCollisionEnter(Collision target)
    {
        if (target.gameObject.name == "microMonster")
        {
            
            if (m_Source.isPlaying == true)
            {
                m_Source.Pause();
            }
            m_Source.PlayOneShot(attacked);
            takedamge(30 - InGameUI.bonusd);
            Debug.Log("character get hit!");
            rb.AddForce(transform.forward * -500f);
        }
        
    }

}
