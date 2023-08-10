using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayerController : MonoBehaviour
{
    public GameObject endPanel; // 게임 종료
    public GameObject startPanel;
    public GameObject plus;
    public GameObject minus;

    Rigidbody ballRigidbody;
    Renderer ballColor;

    public Camera cam; //카메라
    Vector3 camDis; //공-카메라 거리

    public int speed = 5;
    int count = 0;

    bool gameStart = false; //게임종료상태

    //시간 Text
    float time;
    float prevTime = 0;

    float itemTime = 3f;
    bool itemPlus = false;
    bool itemMinus = false;

    public Text timeText;
    public Text bestTimeText;

    void Start()
    {
        ballRigidbody = GetComponent<Rigidbody>();
        transform.position = new Vector3(0f, 1f, 0f);

        ballColor = GetComponent<Renderer>();
        camDis = cam.transform.position - transform.position;

        gameStart = false;
        itemPlus = false;
        itemMinus = false;

        endPanel.SetActive(false);
        startPanel.SetActive(true);

        plus.SetActive(false);
        minus.SetActive(false);
    }

    
    void Update()
    {
        if (gameStart)
        {
            startPanel.SetActive(false);
            time += Time.deltaTime;
        }

        TimeSetter();

        float h = Input.GetAxis("Horizontal");
        float v = Input.GetAxis("Vertical");

        //Debug.Log("Horizontal : " + h + "  Vertical : " + v);

        if(gameStart == true)
            ballRigidbody.AddForce(new Vector3(h, 0, v) * speed);

        // Color Change
        if (Input.GetMouseButtonDown(0))
        {
            count++;
            Debug.Log(count);

            if (count % 2 == 1)
                ballColor.material.color = new Color(1f, 0, 0);
            else if (count % 2 == 0)
                ballColor.material.color = new Color(0, .3f, 1f);
        }

        //Cam
        cam.transform.position = transform.position + camDis;

        //item


        if ((time - itemTime > 1.5f) && itemMinus)
        {
            minus.SetActive(false);
            itemMinus = false;
        }

        if ((time - itemTime > 1.5f) && itemPlus)
        {
            plus.SetActive(false);
            itemPlus = false;
        }

    }



    private void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Box")
        {
            Debug.Log("hit box");

            Renderer boxColor = other.GetComponent<Renderer>();
            boxColor.material.color = ballColor.material.color;

            plus.SetActive(false);
            minus.SetActive(false);

            endPanel.SetActive(true);

            if (prevTime == 0)
            {
                bestTimeText.text = timeText.text;
                prevTime = time;
            }
            else if (prevTime > time)
            {
                bestTimeText.text = timeText.text;
                prevTime = time;
            }

            gameStart = false; //game ended
        }

        if(other.tag == "SpeedUP")
        {
            

            itemMinus = true;
            minus.SetActive(true);

            Debug.Log(itemTime);

            time -= 3;
            itemTime = time;

            Destroy(other.gameObject);

        }

        if(other.tag == "SpeedDown")
        {
            

            plus.SetActive(true);
            itemPlus = true;

            Debug.Log(itemTime);

            time += 3;
            itemTime = time;

            Destroy(other.gameObject);

        }
    }


    public void Restart()
    {
        transform.position = new Vector3(0f, 1f, 0f);
        endPanel.SetActive(false);

        ballColor.material.color = Color.white;

        Renderer box = GameObject.FindGameObjectWithTag("Box").GetComponent<Renderer>();
        box.material.color = Color.white;

        time = 0;

        gameStart = true;
    }

    public void startTime()
    {
        time = 0;
        gameStart = true;
    }

    void TimeSetter()
    {
        
        int min = (int)time / 60;
        int s = (int)time % 60;
        float ms = time - min*60 - s;
        string ms_s = time.ToString(".00");

        timeText.text = min.ToString("00") + " : " + s.ToString("00") + ms.ToString(".00").Replace(".", " : ");
    }
}
