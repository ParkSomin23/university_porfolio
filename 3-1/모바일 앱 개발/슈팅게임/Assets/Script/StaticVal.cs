using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StaticVal : MonoBehaviour
{
    public static int gameScore = 0;

    // Start is called before the first frame update
    void Awake()
    {
        gameScore = 0;
    }
    
}
