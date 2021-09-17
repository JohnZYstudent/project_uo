using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Menu : MonoBehaviour
{
    // Start is called before the first frame update
    public GameObject menu;
    public static bool isPause = false;

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            if (isPause == false)
            {
                Pause();
            }
            else
            {
                Resum();
            }
        }
    }

    public void Pause()
    {
        menu.gameObject.SetActive(true);
        Time.timeScale = 0f;
        isPause = true;
        Cursor.visible = true;
        Cursor.lockState = CursorLockMode.Confined;
    }

    public void Resum()
    {
        menu.gameObject.SetActive(false);
        Time.timeScale = 1f;
        isPause = false;
        Cursor.visible = false;
        Cursor.lockState = CursorLockMode.Locked;
    }

    public void BackMainMenu(string name)
    {
        SceneManager.LoadScene(name);
    }

}
