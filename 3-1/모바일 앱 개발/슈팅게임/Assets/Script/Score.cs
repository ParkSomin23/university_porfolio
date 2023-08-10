using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class Score : MonoBehaviour
{
    public Text scoreText;
    public GameObject endPanel;
    public GameObject startPanel;
    public Text highScore;
    public Text highScoreStart;

    public static bool isStarted = false;

    private void Start()
    {
        startPanel.SetActive(true);
        isStarted = false;
        endPanel.SetActive(false);
    }

    // Start is called before the first frame update
    void Awake()
    {
        scoreText.text = "0";

        highScore.text = PlayerPrefs.GetInt("HighScore", 0).ToString();
        highScoreStart.text = PlayerPrefs.GetInt("HighScore", 0).ToString();
    }

    // Update is called once per frame
    void Update()
    {
        scoreText.text = Enemy.score.ToString();

        if (Enemy.end)
        {
            if (Enemy.score > PlayerPrefs.GetInt("HighScore", 0))
            {
                PlayerPrefs.SetInt("HighScore", Enemy.score);
                highScore.text = Enemy.score.ToString();
            }

            endPanel.SetActive(true);
            Time.timeScale = 0;
            isStarted = false;
        }
    }

    public void StartBtn()
    {
        startPanel.SetActive(false);
        isStarted = true;
    }

    public void Restart()
    {
        scoreText.text = "0";
        endPanel.SetActive(false);
        Enemy.score = 0;
        Time.timeScale = 1;
        Enemy.end = false;
        isStarted = true;

        SceneManager.LoadScene("shootingGame");

    }

    public void Exit()
    {
        Application.Quit();
    }
}
