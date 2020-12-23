using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using ArduinoBluetoothAPI;
using System.IO.Ports;

public class BTControlArduino : MonoBehaviour
{
    // Start is called before the first frame update
    [Header("ConnectiSetting")]
    private BluetoothHelper BTHelper;
    private string deviceName; //HC-05 Name


    private static int Speed = 0;
    public bool isFlower=false;

    // Start is called before the first frame update
    void Start()
    {
        deviceName = "BikeSpeed";

        try
        {
            BTHelper = BluetoothHelper.GetInstance(deviceName);
            BTHelper.OnConnected += OnConnected;
            BTHelper.OnConnectionFailed += OnConnFailed;

            BTHelper.setTerminatorBasedStream("\n");
            //BTHelper.setLengthBasedStream();

            //if we have already paired with the device
            if (BTHelper.isDevicePaired())
            {
                BTHelper.Connect(); //we manage to connect successfully
            }
        }
        catch (BluetoothHelper.BlueToothNotEnabledException ex)
        {

        }
        catch (BluetoothHelper.BlueToothNotReadyException ex)
        {

        }
        catch (BluetoothHelper.BlueToothNotSupportedException ex)
        {

        }

    }

    void OnConnected()
    {
        //Listening for incoming msg
        BTHelper.StartListening();
    }

    void OnConnFailed()
    {

    }

    // Update is called once per frame
    void Update()
    {
        if (BTHelper != null)
        {
            if (BTHelper.isConnected())
            {
                /* 看最後用哪個程式碼 */
                Speed = PlayerMovement.RPM;
                string msg = Speed.ToString();

                BTHelper.SendData(msg);
                //print("Speed: " + Speed);

                /* Determine whether to enter the flower area */
                if (isFlower)
                {
                    BTHelper.SendData("on");
                }
                else
                {
                    BTHelper.SendData("off");
                }
            }
        }
    }

    void OnTriggerStay(Collider other)
    {
        if (other.CompareTag("Floral"))
        {
            isFlower = true;
        }
    }

    void OnTriggerExit(Collider other)
    {
        if (other.CompareTag("Floral"))
        {
            isFlower = false;
        }
    }

    void OnDestroy()
    {
        BTHelper.SendData("disable");
        BTHelper.Disconnect();
    }

}
