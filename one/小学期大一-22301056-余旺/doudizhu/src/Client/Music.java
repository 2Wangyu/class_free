package Client;

import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.FloatControl;
import javax.sound.sampled.SourceDataLine;


import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

//整体用于音乐的播放
public class Music {
    // wav文件的路径
    private File file;
    // 是否循环播放
    private volatile boolean isLoop = false;
    // 是否正在播放
    private volatile boolean isPlaying;
    // FloatControl.Type.MASTER_GAIN的值(可用于调节音量)
    private float newVolumn = 7;

    private PlayThread playThread;


    public Music(String srcPath) {
        file = new File(srcPath);
    }

    //播放音乐
    public void play() {
        isPlaying=true;
        if (playThread == null) {
            playThread = new PlayThread();
            playThread.start();
        }
    }

    //结束音乐
    public void over() {
        isPlaying = false;
        if (playThread != null) {
            playThread = null;
        }
    }

    //设置循环播放
    public Music setLoop(boolean isLoop) {
        this.isLoop = isLoop;
        return this;
    }

    //-80.0~6.0206测试,越小音量越小
    public Music setVolumn(float newVolumn) {
        this.newVolumn = newVolumn;
        return this;
    }

    // 暂停播放音频
    public void stopMusic() {
        synchronized (this) {
            isPlaying= false;
            notifyAll();
        }
    }

    // 继续播放音乐
    public void continueMusic() {
        synchronized (this) {
            isPlaying = true;
            notifyAll();
        }
    }


   // 异步播放线程
    private class PlayThread extends Thread {

        @Override
        public void run() {
            isPlaying = true;
            do {
//				isPlaying = true;

                SourceDataLine sourceDataLine = null;
                BufferedInputStream bufIn = null;
                AudioInputStream audioIn = null;
                try {
                    bufIn = new BufferedInputStream(new FileInputStream(file));
                    audioIn = AudioSystem.getAudioInputStream(bufIn); // 可直接传入file

                    AudioFormat format = audioIn.getFormat();

                    sourceDataLine = AudioSystem.getSourceDataLine(format);
                    sourceDataLine.open();
                    // 必须open之后
                    if (newVolumn != 7) {
                        FloatControl control = (FloatControl) sourceDataLine.getControl(FloatControl.Type.MASTER_GAIN);
//						System.out.println(control.getMaximum());
//						System.out.println(control.getMinimum());
                        //设置音量
                        control.setValue(newVolumn);
                    }

                    sourceDataLine.start();
                    byte[] buf = new byte[1024];
//					System.out.println(audioIn.available());
                    int len = -1;
                    //只要有数据就不断读取并且写入（把音乐传过来）
                    while (isPlaying && (len = audioIn.read(buf)) != -1) {
                        sourceDataLine.write(buf, 0, len);
                    }

                } catch (Exception e) {
                    e.printStackTrace();
                } finally {

                    if (sourceDataLine != null) {
                        sourceDataLine.drain();
                        sourceDataLine.close();
                    }
                    try {
                        if (bufIn != null) {
                            bufIn.close();
                        }
                        if (audioIn != null) {
                            audioIn.close();
                        }
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            } while (isPlaying && isLoop);
        }
    }



}
