using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class JoyStick : MonoBehaviour
{
    protected Joystick joyStick;

    // Start is called before the first frame update
    void Start()
    {
        joyStick = FindObjectOfType<Joystick>();
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 pos = GetComponent<Transform>().position;
        GetComponent<Transform>().position = new Vector3(joyStick.Horizontal * 2f, -1.3f, 0);
    }
}
