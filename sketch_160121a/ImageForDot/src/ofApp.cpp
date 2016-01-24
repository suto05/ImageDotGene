#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255,255,255);
    dotX = 50;
    dotY = 50;
    dotSize = 10;
    dotLine = 1;
    ofEnableSmoothing();
    openfile();
    ofSetWindowShape(dotX*dotSize+dotLine*2, dotY*dotSize+dotLine*2);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0,0,0);
    
    //入力画像の各ピクセルの色要素を保持
    float* imgR = new float[width*height];
    float* imgG = new float[width*height];
    float* imgB = new float[width*height];
    
    //１ドットごとの色要素を保持
    cv::Mat color = cv::Mat(dotX,dotY,CV_8UC3);
    
    //1ドットあたりのピクセル数を保持
    int Xdot_pixel = int(width/dotX);
    int Ydot_pixel = int(height/dotY);
    
    //一時的な各色要素のバッファ
    float tmp_R = 0.0;
    float tmp_G = 0.0;
    float tmp_B = 0.0;
    
    //inputImageからピクセルを取ってくる
    unsigned char* pixels = inputImage.getPixels();
    
    //inputImageのRGB要素を全て格納
    for(int i =0;i < width*height;i++)
    {
        imgR[i] = pixels[i*3];
        imgG[i] = pixels[i*3+1];
        imgB[i] = pixels[i*3+2];
    }
   
    //各ドット領域での平均色を求める
    int a = 0;
    for(int x = 0;x < dotX;x++)
    {
        for(int y = 0;y < dotY;y++)
        {
            tmp_R = 0.0;
            tmp_G = 0.0;
            tmp_B = 0.0;
            float Max = 0.0;
            for(int j = 0;j < Xdot_pixel;j++)
            {
                for(int k = 0;k < Ydot_pixel;k++)
                {
                    tmp_R += imgR[j+k*width + x*Xdot_pixel + y*width*Ydot_pixel];
                    tmp_G += imgG[j+k*width + x*Xdot_pixel + y*width*Ydot_pixel];
                    tmp_B += imgB[j+k*width + x*Xdot_pixel + y*width*Ydot_pixel];
                }
            }
            ofSetColor(tmp_R/(Xdot_pixel*Ydot_pixel),tmp_G/(Xdot_pixel*Ydot_pixel),tmp_B/(Xdot_pixel*Ydot_pixel), 100);
            ofRect(dotSize*x+dotLine, dotSize*y+dotLine,dotSize,dotSize);
            ofSetColor(0,0,0,100);
            ofLine(dotSize*x, 0, dotSize*(x)+dotLine, dotSize*dotY);
            ofLine(0, dotSize*y, dotSize*dotX, dotSize*y+dotLine);
        }
    }
    delete [] imgR;
    delete [] imgG;
    delete [] imgB;
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'o':
            openfile();
            break;
            
            case 'X':
            dotX += 1;
            ofSetWindowShape(dotX*dotSize+dotLine*2, dotY*dotSize+dotLine*2);
            break;
            
            case 'x':
            dotX -= 1;
            ofSetWindowShape(dotX*dotSize+dotLine*2, dotY*dotSize+dotLine*2);
            break;
            
            case 'Y':
            dotY += 1;
            ofSetWindowShape(dotX*dotSize+dotLine*2, dotY*dotSize+dotLine*2);
            break;
            
            case 'y':
            dotY -= 1;
            ofSetWindowShape(dotX*dotSize+dotLine*2, dotY*dotSize+dotLine*2);
            break;
            
            case 'l':
            dotSize += 2;
            ofSetWindowShape(dotX*dotSize+dotLine*2, dotY*dotSize+dotLine*2);
            break;
            
            case 's':
            dotSize -=2;
            ofSetWindowShape(dotX*dotSize+dotLine*2, dotY*dotSize+dotLine*2);
            break;
            
        case 'c':
            dotX = 50;
            dotY = 50;
            dotSize = 10;
            dotLine = 1;
            ofSetWindowShape(dotX*dotSize+dotLine*2, dotY*dotSize+dotLine*2);
            break;
            
            
            case 'p':
            
            saveImage.grabScreen(0, 0,dotX*dotSize+dotLine*2, dotY*dotSize+dotLine*2);
            saveImage.saveImage("./saveImage.png", OF_IMAGE_QUALITY_BEST);
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

void ofApp::openfile()
{
    ofFileDialogResult openFile = ofSystemLoadDialog("Select Image File");
    std::string filePath = openFile.getPath();
    if(!inputImage.loadImage(filePath))
    {
        return;
    }
    
    height = inputImage.height;
    width = inputImage.width;
}
