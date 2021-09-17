using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HealthBar : MonoBehaviour
{
    private HealthSystem healthSystem;

    public void Setup(HealthSystem healthSystem) {
        this.healthSystem = healthSystem;
    }
    private void Changed(object sender, System.EventArgs e) {
        transform.Find("Bar").localScale = new Vector3(healthSystem.GetPercentHealth()*10, 1);
    }

}
