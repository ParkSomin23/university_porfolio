using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class AddEnemy : MonoBehaviour
{
    float nowTime;
    public GameObject enemy;

    // Start is called before the first frame update
    void Start()
    {
        nowTime = Time.time;
    }

    // Update is called once per frame
    void Update()
    {
        if (Score.isStarted)
        {
            if (Time.time - nowTime > 0.5f)
            {
                GameObject b = Instantiate(enemy, new Vector3(Random.Range(-3, 3), 7f, 0), Quaternion.identity);
                b.transform.Rotate(-270, -90, 90);
                b.transform.localScale = new Vector3(0.08f, 0.08f, 0.08f);
                nowTime = Time.time;
            }
        }
    }
}
