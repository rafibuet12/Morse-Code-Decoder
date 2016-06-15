package triplemzimindustries.morsecode;

import android.content.DialogInterface;
import android.content.pm.PackageManager;
import android.hardware.Camera;
import android.os.Handler;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.BoringLayout;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    EditText txt;
    Button btn;

    private Camera camera;
    private boolean isFlashOn;
    private boolean hasFlash;
    private Camera.Parameters params;
    private String[] morseCodeMap;
    private int dit = 650;
    private int dah = 1200;
    private int dark = 2200;
    Boolean flag;
    int delay,cnt;
    Handler handler;
    String st;
    int idx,chridx;
    String sent;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        txt = (EditText) findViewById(R.id.txtMorse);
        btn = (Button) findViewById(R.id.btnMorse);
        camera = Camera.open();
        params = camera.getParameters();
        morseCodeMap = new String[40];
        morseCodeMap[0]="12";
        morseCodeMap[1]="2111";
        morseCodeMap[2]="2121";
        morseCodeMap[3]="211";
        morseCodeMap[4]="1";
        morseCodeMap[5]="1121";
        morseCodeMap[6]="221";
        morseCodeMap[7]="1111";
        morseCodeMap[8]="11";
        morseCodeMap[9]="1222";
        morseCodeMap[10]="212";
        morseCodeMap[11]="1211";
        morseCodeMap[12]="22";
        morseCodeMap[13]="21";
        morseCodeMap[14]="222";
        morseCodeMap[15]="1221";
        morseCodeMap[16]="2212";
        morseCodeMap[17]="121";
        morseCodeMap[18]="111";
        morseCodeMap[19]="2";
        morseCodeMap[20]="112";
        morseCodeMap[21]="1112";
        morseCodeMap[22]="122";
        morseCodeMap[23]="2112";
        morseCodeMap[24]="2122";
        morseCodeMap[25]="2211";
        morseCodeMap[26]="12222";
        morseCodeMap[27]="11222";
        morseCodeMap[28]="11122";
        morseCodeMap[29]="11112";
        morseCodeMap[30]="11111";
        morseCodeMap[31]="21111";
        morseCodeMap[32]="22111";
        morseCodeMap[33]="22211";
        morseCodeMap[34]="22221";
        morseCodeMap[35]="22222";
        morseCodeMap[36]="32"; //space


    }
    public void deploy(View view){


        hasFlash = getApplicationContext().getPackageManager()
                .hasSystemFeature(PackageManager.FEATURE_CAMERA_FLASH);
        if (!hasFlash) {
            // device doesn't support flash
            // Show alert message and close the application
            Toast.makeText(MainActivity.this, "No Flash Detected", Toast.LENGTH_SHORT).show();
          
            
            return;
        }



        delay = 1000;

        isFlashOn = false;
        st = txt.getText().toString();
        st = st.toUpperCase();
        idx = 0;
        chridx = 0;
        handler = new Handler();
        flag =true;
        txt.setText(st);
        do_the_work();










    }

    public void do_the_work(){
        if(flag == false){
            delay = 500;
            handler.postDelayed(runnable,delay);
            flag = true;
            return;
        }
        if(idx >= st.length()) return;
        char ch = st.charAt(idx);
        if(ch >'Z' || ch<'0'){
            idx++;
            do_the_work();
            return;
        }
        int j=35 ;
        if(ch>='A') j = (int)ch -(int)'A';
        if(ch>'0' && ch <='9') j = (int) ch -23 ;
        if(ch =='0') j = 35;
        sent = morseCodeMap[j];

        if(chridx >= sent.length()){
            idx++;
            chridx=0;
            delay = dark;
        }
        else{
            ch = sent.charAt(chridx);
            if(ch =='1') delay = dit;
            else if(ch == '2') delay = dah;
            chridx++;
            //txt.setText("Flash on");
            turnOnFlash();
            flag = false;
        }
//        turnOnFlash();


        handler.postDelayed(runnable,delay);



    }

    @Override
    protected void onStop() {
        super.onStop();
        if(camera!=null)
            camera.release();
    }

    /*
    * Turning On flash
    */
    private void turnOnFlash() {
        if (!isFlashOn) {
            if (camera == null || params == null) {
                return;
            }


            params = camera.getParameters();
            params.setFlashMode(Camera.Parameters.FLASH_MODE_TORCH);
            camera.setParameters(params);
            camera.startPreview();
            isFlashOn = true;



        }
    }
    private void turnOffFlash() {
        if (isFlashOn) {
            if (camera == null || params == null) {
                return;
            }


            params = camera.getParameters();
            params.setFlashMode(Camera.Parameters.FLASH_MODE_OFF);
            camera.setParameters(params);
            camera.stopPreview();
            isFlashOn = false;


        }
    }

    private Runnable runnable = new Runnable() {
        @Override
        public void run() {
//            isFlashOn = !isFlashOn;
//            if(!isFlashOn) {
//                txt.setText("Flash on");
////                turnOnFlash();
//                do_the_work();
//
//            }
//            else {

            //txt.setText("Flash off");
            turnOffFlash();
            do_the_work();

//            }



        }
    };
}
