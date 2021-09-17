using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.Threading;

public class InGameUI : MonoBehaviour
{
    // Start is called before the first frame update
    public static int score;
    private int enhance_num;
    public Text score_num;
    public Text attack_level;
    private int attackLevel;
    public Text defence_level;
    private int defenceLevel;
    public Text health_persent;
    public float health;
    public Text enhance_left;
    private int enhanc_used;
    private bool isexpress;
    public GameObject Levelup;
    public static int bonusa;
    public static int bonusd;
    private int difficulty;

    void Start()
    {
        score = 0;
        enhance_num = 0;
        enhanc_used = 0;
        isexpress = false;
        attackLevel = 0;
        defenceLevel = 0;
        bonusa = 20;
        bonusd = 0;
        difficulty = 0;
    }

    // Update is called once per frame
    void Update()
    {
        if (score/50 > difficulty)
        {
            bonusa -= 3;
            bonusd -= 3;
            difficulty = score / 100;
        }
        if (Input.GetKeyDown(KeyCode.B))
        {
            if (isexpress == false)
            {
                Time.timeScale = 0f;
                Levelup.gameObject.SetActive(true);
                Cursor.lockState = CursorLockMode.Confined;
                Cursor.visible = true;
                isexpress = true;
            }
            else
            {
                Time.timeScale = 1f;
                Levelup.gameObject.SetActive(false);
                Cursor.lockState = CursorLockMode.Locked;
                Cursor.visible = false;
                isexpress = false;
            }
        }
        health = ThridPersonCharacterController.healthSystem.GetPercentHealth();
        health_persent.text = (Mathf.Round(health * 100f)).ToString() + "%";
        score_num.text = score.ToString();
        enhance_num = score / 100;
        enhance_left.text = (enhance_num - enhanc_used).ToString();
    }

    public void AttackUp()
    {
        if (enhance_num - enhanc_used > 0) {
            attackLevel += 1;
            bonusa += 10;
            attack_level.text = "Lv."+ attackLevel.ToString();
            enhanc_used += 1;
        }
    }

    public void DefenceUp()
    {
        if (enhance_num - enhanc_used > 0)
        {
            defenceLevel += 1;
            bonusd += 10;
            defence_level.text = "Lv." + defenceLevel.ToString();
            enhanc_used += 1;
        }
    }

    public void Recovery()
    {
        if (enhance_num - enhanc_used > 0)
        {
            health_persent.text = (Mathf.Round(health * 100f)).ToString() + "%";
            ThridPersonCharacterController.healthSystem.Heal(25);
            enhanc_used += 1;
        }
    }
}
