using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour {

    float xPos;
    float yPos;
    float zPos;

    float speed = 0.1f;

    // Use this for initialization
    void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
        transform.position = new Vector3(xPos, yPos, zPos);
        yPos += speed;

        if (transform.position.y > 6.2)
            Destroy(gameObject);
	}

    public void AddBullet(float x, float y, float z)
    {
        xPos = x;
        yPos = y;
        zPos = z;
    }

}
