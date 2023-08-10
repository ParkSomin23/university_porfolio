using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Sound : MonoBehaviour
{
    public AudioClip endSound;
    public AudioClip shootSound;
    public AudioClip destroySound;

    AudioSource myAudio;

    public static Sound instance;


    private void Awake()
    {
        if (Sound.instance == null)
            Sound.instance = this;
    }

    // Start is called before the first frame update
    void Start()
    {
        myAudio = GetComponent<AudioSource>();
    }

    // Update is called once per frame
    void Update()
    {

    }

    public void EndSound()
    {
        myAudio.PlayOneShot(endSound);
    }

    public void ShootSound()
    {
        myAudio.PlayOneShot(shootSound);
    }

    public void DestroySound()
    {
        myAudio.PlayOneShot(destroySound);
    }
}
