using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;

public class NewBehaviourScript : MonoBehaviour {

    [DllImport("cppDll")]
    private static extern int add(int x, int y);


    [StructLayout(LayoutKind.Sequential)]
    public struct CppStruct
    {
        public int a;
        public int b;
        public int c;
    }

    [DllImport("cppDll")]
    private static extern bool getStructData(ref CppStruct info);

    [DllImport("cppDll")]
    private static extern bool getStructDataPtr(ref CppStruct info);

    [DllImport("cppDll")]
    private static extern bool setArrayData(int count, CppStruct[] info);


    CppStruct[] arrayInfo = new CppStruct[1000];
    // Use this for initialization
    void Start () {

        int x = 0;
        x = add(10, 20);
        Debug.Log(x);

        CppStruct info = new CppStruct();
        getStructData(ref info);
        Debug.Log(info.a);

        for (int i = 0; i < 0; i++)
        {
            arrayInfo[i] = new CppStruct();
        }
    }
	
	// Update is called once per frame
	void Update () {

        setArrayData(1000, arrayInfo);
        Debug.LogFormat("info[{0}] {1}", 400, arrayInfo[400].a);
    }
}
