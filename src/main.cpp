
#include <iostream>
#include <fstream>
#include "FrameGrabber.h"

using std::cout;
using std::endl;
using std::string;

void writeY420pData(std::ofstream& os, unsigned char* data, int linesize, int width, int height) {
  char* p = reinterpret_cast<char*>(data);
  for (int i = 0; i < height; i++) {
    os.write(p + (__int64)i * linesize, width);
  }
}

void testReadFileInfo() {
  string inputFile = "D:/data/video/VID_20181123_214724.mp4";
  string outputFile = "tempout001.yuv";
  FrameGrabber grabber{inputFile};

  try {
    grabber.start();

    cout << "getWidth:" << grabber.getWidth() << endl;
    cout << "getHeight:" << grabber.getHeight() << endl;
    cout << "getFrameRate:" << grabber.getFrameRate() << endl;
    cout << "getPixelFormat:" << grabber.getPixelFormat() << endl;
    cout << "getVideoCodecId:" << grabber.getVideoCodecId() << endl;
    cout << "getVideoCodecName:" << grabber.getVideoCodecName() << endl;

    cout << "------------------------------------------------" << endl;
    AVFrame* frame = av_frame_alloc();

    int count = 0;
    // TODO go on test write YUV file.

    std::ofstream os{outputFile, std::ios::binary};

    int height = grabber.getHeight();
    int width = grabber.getWidth();
    cout << "height: " << height << endl;

    while (grabber.grabImageFrame(frame) == 0) {
      writeY420pData(os, frame->data[0], frame->linesize[0], width, height);
      writeY420pData(os, frame->data[1], frame->linesize[1], width/2, height/2);
      writeY420pData(os, frame->data[2], frame->linesize[2], width/2, height/2);


      count += 1;
      if (count % 10 == 0) {
        cout << "image frame count:" << count << endl;
      }
    }
    os.close();
    cout << "------------------" << endl;
    cout << "image frame count:" << count << endl;
  } catch (std::exception ex) {
    cout << "got exception:" << ex.what() << endl;
  }

  cout << "DONE." << endl;
}

int main(int argc, char* argv[]) {
  cout << "hello, little player." << endl;

  testReadFileInfo();
  return 0;
}