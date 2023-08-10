using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AddBullet : MonoBehaviour {

    public GameObject bullet;
    float nowTime;

    public ShotBtn shot;

	// Use this for initialization
	void Start () {
        nowTime = Time.time;
	}
	
	// Update is called once per frame
	void Update () {
        if (shot.Pressed && Time.time - nowTime > 0.3f) //if(Input.GetMouseButtonDown(0))
        {
            GameObject b = Instantiate(bullet, transform.position, Quaternion.identity);
            b.GetComponent<Bullet>().AddBullet(transform.position.x, transform.position.y, transform.position.z);
            nowTime = Time.time;
            Sound.instance.ShootSound();
        }
	}

}
