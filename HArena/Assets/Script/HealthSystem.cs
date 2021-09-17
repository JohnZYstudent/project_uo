using System;

public class HealthSystem {
    private int health;
    private int MaxHealth;
    public static bool score;

    public event EventHandler Changed;

    public HealthSystem(int h) {
        this.MaxHealth = h;
        health = h;
    }

    public int GetHealth()
    {
        if (health <= 0)
        {
            score = true;
        }
        else {
            score = false;
        }
        return health;
    }

    public void Dodamge(int damge) {
        health -= damge;
        if (health < 0) { health = 0; }
        if (Changed != null) { Changed(this, EventArgs.Empty); }
    }

    public float GetPercentHealth() {
        return (float)health / MaxHealth;
    }

    public void Heal(int heal) {
        health += heal;
        if (health > MaxHealth) { health = MaxHealth; }
        if (Changed != null) { Changed(this, EventArgs.Empty); }
    }
}    