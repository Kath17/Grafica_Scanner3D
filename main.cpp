#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <cmath>
using namespace cv;
using namespace std;

//./main 1785.25 -s test con : (Prueba 3)
// 13cm objeto con cámara y
// 18cm cámara con láser
// 20cm objeto con láser
//Angulo: 60 , line:7

//Pasos a ejecutar: g++ -ggdb main.cpp -std=c++11 -o main `pkg-config --cflags --libs opencv`
//./main 2395.00 -s test
//pcl_viewer resPoints.pcd
//./greedy_projection

#define ANGLE 60 // 43 - 45
#define BASELINE 7 // 12 cm 264

//focal length = 50

#define PI 3.14159265

float focalLength;

typedef float Coord;
typedef tuple<Coord,Coord,Coord> Punto;

void savePoints(string file, vector<vector<Punto>> images){
	Coord x, y, z;
	ofstream filePoints(file.c_str());
	filePoints<<images.size()<<endl;
	for(auto vec : images){
		filePoints<<vec.size()<<endl;
		for(auto p : vec){
			x = get<0>(p);
			y = get<1>(p);
			z = get<2>(p);
			filePoints<<x<<" "<<y<<" "<<z<<endl;
		}
	}
	filePoints.close();
}

vector<vector<Punto>> loadPoints(string file){
	Coord coordenadas[3];
	vector<Punto> temp;
	vector<vector<Punto>> res;
	int numImages = 0;
	int numPoints = 0;
	ifstream filePoints(file.c_str());
	filePoints>>numImages;
	for(int i = 0; i < numImages; i++){
		temp.clear();
		filePoints>>numPoints;
		for(int j = 0; j < numPoints; j++){
			for(int k = 0; k < 3; k++){
				filePoints>>coordenadas[k];
			}
			temp.push_back(make_tuple(coordenadas[0],coordenadas[1],coordenadas[2]));
		}
		res.push_back(temp);
	}
	return res;
}

/*
vector<vector<tuple<float,float,float>>> getImages(vector<vector<tuple<float,float,float>>> images){
	vector<vector<tuple<float,float,float>>> res;
	int despl = images.size() / NUM_IMAGES;
	for(int i = 0; i < NUM_IMAGES; i++){
		res.push_back(images[i * despl]);
	}
	return res;
}
z -> 16.5 cm -> 623.622047
y -> 3.5 cm -> 132.283465
	*/

//NFC8B97A6D82B

Punto getRealPoint(float x, float y){
	Coord realX = 0;
	Coord realY = 0;
	Coord realZ = 0;
	realX = (BASELINE * x) / (focalLength * (1.0/tan(ANGLE * PI / 180.0)) - x);
	realY = (BASELINE * y) / (focalLength * (1.0/tan(ANGLE * PI / 180.0)) - x);
	realZ = (BASELINE * focalLength) / (focalLength * (1.0/tan(ANGLE * PI / 180.0)) - x);
	return make_tuple(realX, realY, realZ);
}

Punto rotate(Punto &point, float angle, Punto refPoint){
	Coord x = get<0>(point);
	Coord y = get<1>(point);
	Coord z = get<2>(point);
	Coord refX = get<0>(refPoint);
	Coord refY = get<1>(refPoint);
	Coord refZ = get<2>(refPoint);

	Coord newX = x - refX;
	Coord newY = y - refY;
	Coord newZ = z - refZ;
	Coord tempX = newX;
	newX = tempX * cos(angle * PI / 180.0) + newZ * sin(angle * PI / 180.0);
	newY = newY;
	newZ = tempX * (-1 * sin(angle * PI / 180.0)) + newZ * cos(angle * PI / 180.0);
	newX += refX;
	newY += refY;
	newZ += refZ;

	return make_tuple(newX, newY, newZ);
}

vector<Punto> rotatePoints(vector<Punto> points, float angle, Punto refPoint){
	vector<Punto> res;
	for(auto t : points){
		res.push_back(rotate(t, angle, refPoint));
	}
	return res;
}

vector<Punto> getPoints(Mat & img){
	vector<Punto> res;
	for(int i = 0; i < img.rows; i++){
		for(int j = 0; j < img.cols; j++){
			if(img.at<bool>(i,j) == 1){
				//res.push_back(make_tuple(i,j,0));
				res.push_back(getRealPoint(j,i));
			}
		}
	}
	return res;
}

void writePoints(string file, vector<Punto> &points){
	ofstream filePoints(file.c_str());
	filePoints<<"VERSION .7"<<endl;
	filePoints<<"FIELDS x y z"<<endl;
	filePoints<<"SIZE 4 4 4"<<endl;
	filePoints<<"TYPE F F F"<<endl;
	filePoints<<"COUNT 1 1 1"<<endl;
	filePoints<<"WIDTH "<<points.size()<<endl;
	filePoints<<"HEIGHT 1"<<endl;
	filePoints<<"VIEWPOINT 0 0 0 1 0 0 0"<<endl;
	filePoints<<"POINTS "<<points.size()<<endl;
	filePoints<<"DATA ascii"<<endl;
	Coord x = 0;
	Coord y = 0;
	Coord z = 0;
	for(Punto p : points){
		x = get<0>(p);
		y = get<1>(p);
		z = get<2>(p);
		filePoints<<x<<" "<<y<<" "<<z<<" "<<endl;
	}
	filePoints.close();
}


int main(int argc, char ** argv) {
	if(argc != 4){
		cout<<"Faltan argumentos <focal length> <option:-s/-l> <file>"<<endl;
		return 0;
	}

	focalLength = atof(argv[1]);
	string option = argv[2];
	string file = argv[3];

	vector<vector<Punto>> images;
	vector<Punto> points;

	// int iLowH  = 0;
	// int iHighH = 0;
	// int iLowS = 0;
	// int iHighS = 0;
	// int iLowV = 0;  //vaso 200 plato 118 cono 218
	// int iHighV = 225;
	//
	// namedWindow("Control", CV_WINDOW_AUTOSIZE);
	// cvCreateTrackbar("LowH","Control", &iLowH, 225);
	// cvCreateTrackbar("HighH","Control", &iHighH,225);
	//
	// cvCreateTrackbar("LowS","Control", &iLowS, 225);
	// cvCreateTrackbar("HighS","Control", &iHighS,225);
	//
	// cvCreateTrackbar("LowV","Control", &iLowV, 225);
	// cvCreateTrackbar("HighV","Control", &iHighV,225);

	if(option == "-s"){
		VideoCapture stream1;
		// stream1.open("http://192.168.0.28:8080/video");
		stream1.open("http://192.168.8.105:8080/video");

		if (!stream1.isOpened()){
			cout<<"cannot open camera";
		}

		Mat cameraFrame;
		Mat hsvImage;
		Mat res;

		while(true){
			stream1.read(cameraFrame);
			cvtColor(cameraFrame, hsvImage, COLOR_BGR2HSV);
			//Funcion
			// inRange(hsvImage, Scalar(0, 0, 42), Scalar(255, 25, 255), res); //bueno
			inRange(hsvImage, Scalar(0, 0, 42), Scalar(255, 55, 255), res); //mejor
			// inRange(hsvImage, Scalar(0, 0, 0), Scalar(0, 0, 255), res);
			// inRange(hsvImage, Scalar(0, 0, 40), Scalar(255, 25, 255), res);
			// inRange(hsvImage, Scalar(0, 0, 50), Scalar(20, 150, 180), res);
			// inRange(hsvImage, Scalar(0, 0, 230), Scalar(0, 20, 255), res);
			imshow("cam1", cameraFrame);
			imshow("cam", res);
			if (waitKey(32) >= 0) break;
		}

		int count = 0;

		while(true){

			stream1.read(cameraFrame);
			cvtColor(cameraFrame, hsvImage, COLOR_BGR2HSV);
			//Funciona
			// inRange(hsvImage, Scalar(0, 0, 42), Scalar(255, 25, 255), res); //bueno
			inRange(hsvImage, Scalar(0, 0, 42), Scalar(255, 55, 255), res); //mejor
			// inRange(hsvImage, Scalar(0, 0, 0), Scalar(0, 0, 255), res);
			// inRange(hsvImage, Scalar(0, 0, 40), Scalar(255, 25, 255), res);
			// inRange(hsvImage, Scalar(0, 0, 230), Scalar(0, 20, 255), res);
			//inRange(hsvImage, Scalar(iLowH, iLowS, iLowV),Scalar(iHighH,iHighS,iHighV), res);
			//inRange(hsvImage, Scalar(0, 0, 0), Scalar(0, 0, 255), res);
			imshow("cam1", cameraFrame);
			imshow("cam", res);
			auto vec = getPoints(res);
			images.push_back(vec);
			count++;
			cout<<"Frame: "<<count<<endl;
			// if (waitKey(32) >= 0 or count == 250) break;
			if (waitKey(32) >= 0 or count == 150) break;
		}

		savePoints(file, images);

	}
	else if(option == "-l"){
		images = loadPoints(file);
	}



	cout<<"Numero de Frames->"<<images.size()<<endl;
	float d_angle = 360.0 / images.size();
	cout<<"Ángulo->"<<d_angle<<endl;
	float actualAngle = 0;
	auto refPoint = make_tuple(get<0>(images.front().front()) + 0.5,get<1>(images.front().front()) + 0.5,get<2>(images.front().front()) + 0.5);


	for(auto vec : images){
		auto temp = rotatePoints(vec, actualAngle, refPoint);
		actualAngle += d_angle;
		points.insert(points.end(), temp.begin(), temp.end());
	}


	writePoints("resPoints.pcd", points);

	return 0;
}
