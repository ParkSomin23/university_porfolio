using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RotateBox : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
        /*
        transform.Rotate(new Vector3(180, 0, 0)*Time.deltaTime); // 1초동안 180번 돈다, 성능과 상관없이 일치하게 하는 기능
        Debug.Log(Time.deltaTime);
        */

        float r = Time.time; //게임이 시작하고 지난 시간 return
        //Debug.Log(r);
        transform.localRotation = Quaternion.Euler(new Vector3(0, r*80, 0)); //그냥 r만큼 회전해 있다 ex, r=30이면 30도가 돌아가서 멈춰있는다
	}
}
