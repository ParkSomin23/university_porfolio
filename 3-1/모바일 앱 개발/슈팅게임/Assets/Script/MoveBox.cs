using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveBox : MonoBehaviour
{
    float yPos;
    float xPos;
    float zPos;

    float speed = 0.1f;

    // Start is called before the first frame update
    void Start()
    {
        xPos = GetComponent<Transform>().position.x;
        yPos = GetComponent<Transform>().position.y;
        zPos = GetComponent<Transform>().position.z;
    }

    // Update is called once per frame
    void Update()
    {
        yPos -= speed;
        transform.position = new Vector3(xPos, yPos, zPos);

        if (yPos < -5f)
        {
            StaticVal.gameScore += 1;
            Debug.Log(StaticVal.gameScore);
            Destroy(gameObject);
        }

    }
}
