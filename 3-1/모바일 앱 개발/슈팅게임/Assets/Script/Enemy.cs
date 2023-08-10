using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Enemy : MonoBehaviour {

    float xPos, yPos;
    float xSpeed, ySpeed;

    public static int score = 0;

    public static bool end = false;
    
	// Use this for initialization
	void Start () {
        xPos = transform.position.x;
        yPos = transform.position.y;
        xSpeed = Random.Range(-0.01f, 0.01f);
        ySpeed = Random.Range(0.05f, 0.08f);

    }
	
	// Update is called once per frame
	void Update () {
        xPos += xSpeed;
        yPos -= ySpeed;
        transform.position = new Vector3(xPos, yPos, 0);

        if (yPos < -5f)
            Destroy(gameObject);
        
	}

    private void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Bullet")
        {
            Destroy(gameObject);
            Destroy(other.gameObject);
            Sound.instance.DestroySound();

            score += 100;
        }

        if(other.tag == "Player")
        {
            Debug.Log("Game Over");
            Destroy(gameObject);
            Destroy(other.gameObject);
            Sound.instance.EndSound();

            end = true;
        }
    }

}
